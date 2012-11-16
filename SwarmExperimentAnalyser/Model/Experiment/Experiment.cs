using System;
using System.Collections.Generic;
using System.Text;
using SwarmExperimentalAnalyser.Model.ChunkIO;
using System.Runtime.InteropServices;
using Core;

namespace SwarmExperimentalAnalyser.Model.Experiment {
	public abstract class ChunkSerializable {
		protected ChunkSerializable(Chunk chunk) {
			this.dataChunk = chunk;
		}
		public void Release(){
			this.dataChunk.Release();
			ReleaseDerived();
			GC.Collect();
		}

		protected abstract void ReleaseDerived();

		protected Chunk dataChunk;
	}

	public class BatchExperiment : ChunkSerializable {
		public BatchExperiment( Chunk chunk ): base(chunk) {
		}

		protected override void  ReleaseDerived(){
 			desc = null;
			formats = null;
			experiments = null;
		}

		public string BatchDescription {
			get { 
				if(string.IsNullOrEmpty(desc)){
					Chunk descChunk = dataChunk["DESC"][0];
					ChunkParser.Parse(descChunk, out desc);
				}
				return desc;
			}
		}

		public DataFormatCollection DataFormats {
			get {
				if (formats == null) {
					Chunk formatChunk = dataChunk["RIFD"][0];
					formats = new DataFormatCollection(formatChunk);
				}
				return formats; 
			}
		}

		public List<DataFormat> GetDataFormats(bool isTimeSereis) {
			if (isTimeSereis) {
				return DataFormats.TSFormats;
			} else {
				return DataFormats.NTSFormats;
			}
		}

		public int ExperimentCount {
			get { return dataChunk["EXPR"].Count; }
		}

		public List<Experiment> Experiments {
			get {
				if (experiments == null) {
					experiments = new List<Experiment>();
					foreach (Chunk exprChunk in dataChunk["EXPR"]) {
						experiments.Add(new Experiment(exprChunk, this.DataFormats));
					}
				}
				return experiments;
			}
		}

		private string desc;
		private DataFormatCollection formats;
		private List<Experiment> experiments;
	}

	public class DataFormatCollection : ChunkSerializable {
		public DataFormatCollection(Chunk chunk)
			: base(chunk) {
		}

		protected override void ReleaseDerived() {
			ntsFormats = null;
			tsFormats = null;
		}

		public List<DataFormat> NTSFormats {
			get {
				if (ntsFormats == null) {
					Initialize();
				}
				return ntsFormats;
			}
		}

		public List<DataFormat> TSFormats {
			get {
				if (tsFormats == null) {
					Initialize();
				}
				return tsFormats;
			}
		}

		private void Initialize() {
			ntsFormats = new List<DataFormat>();
			tsFormats = new List<DataFormat>();

			int readCursor = 0;
			byte[] bytes = dataChunk.ChunkBytes;
			while (readCursor < bytes.Length) {
				string ioType = ChunkReader.BytesToString(bytes, readCursor, DataFormat.IOTypeCodeSize);
				readCursor += DataFormat.IOTypeCodeSize;
				string dimension = ChunkReader.BytesToString(bytes, readCursor, DataFormat.DimensionCodeSize);
				readCursor += DataFormat.DimensionCodeSize;
				string name = ChunkReader.NullTerminatedBytesToString(bytes, readCursor, ref readCursor);
				string elemType = ChunkReader.BytesToString(bytes, readCursor, DataFormat.ElementTypeCodeSize);
				readCursor += DataFormat.ElementTypeCodeSize;

				long[] length = new long[4];
				for (int iLength = 0; iLength < 4; ++iLength) {
					length[iLength] = ChunkReader.BigEndianBytesToInt64(bytes, readCursor);
					readCursor += DataFormat.LengthSize;
				}

				DataFormat fmt = CreateDataFormat(ioType, dimension, name, elemType, length);
				if (fmt.IsTimeSeries) {
					fmt.FormatIndex = tsFormats.Count;
					tsFormats.Add(fmt);
				} else {
					fmt.FormatIndex = ntsFormats.Count;
					ntsFormats.Add(fmt);
				}
			}
		}

		private DataFormat CreateDataFormat(
			string ioType,
			string dimension,
			string name,
			string elemType,
			long[] itemSize
			) {

			DataFormat.IOType io = (ioType == "I") ? DataFormat.IOType.input : DataFormat.IOType.output;

			DataFormat.DataDimension type = DataFormat.DataDimension.Scalar;
			if (dimension.Contains("SV")) {
				type = DataFormat.DataDimension.Scalar;
			} else if (dimension.Contains("1D")) {
				type = DataFormat.DataDimension.Array1D;
			} else if (dimension.Contains("2D")) {
				type = DataFormat.DataDimension.Array2D;
			}

			bool isTimeSeries = dimension.Contains("T");
			Type dataType = null;
			switch (elemType) {
				case "int":
					dataType = typeof(int);
					break;
				case "float":
					dataType = typeof(float);
					break;
				case "double":
					dataType = typeof(double);
					break;
				case "string":
					dataType = typeof(string);
					break;
			}

			return new DataFormat(io, type, dataType, name, isTimeSeries, itemSize);
		}
		private List<DataFormat> ntsFormats;
		private List<DataFormat> tsFormats;
	}

	public class Experiment: ChunkSerializable {
		public Experiment( Chunk chunk, DataFormatCollection dataFmts ): base(chunk){
			this.dataFormats = dataFmts;
		}

		protected override void ReleaseDerived() {
			name = null;
			ntsData = null;
			tsData = null;
			dataFormats = null;
		}

		public string Name {
			get {
				if (name == null) {
					ChunkParser.Parse(dataChunk["DESC"][0], out name);
				}
				return name; 
			}
		}

		public NTSData NonTimeSeriesData {
			get {
				if (ntsData == null) {
					ntsData = new NTSData(dataFormats, dataChunk["NTSD"][0]);
				}
				return ntsData;
			}
		}

		public TSData TimeSeriesData {
			get {
				if (tsData == null) {
					tsData = new TSData(dataFormats, dataChunk);
				}
				return tsData;
			}
		}
		private NTSData ntsData;
		private TSData tsData;
		private DataFormatCollection dataFormats;
		private string name;
	}

	public class NTSData: ChunkSerializable {
		public NTSData(DataFormatCollection dataFormats, Chunk chunk): base(chunk) {
			// chunk: expr
			formats = dataFormats;
		}

		protected override void  ReleaseDerived(){
			formats = null;
			dataList = null;
			dataNameToIndex = null;
		}
		public object this[long index] {
			get {
				if (dataList == null) {
					Initialize();
				}
				return dataList[(int)index];
			}
		}

		public object this[string dataName] {
			get {
				if (dataList == null) {
					Initialize();
				}
				return this[dataNameToIndex[dataName]];
			}
		}

		private void Initialize() {
			dataList = new List<object>(formats.NTSFormats.Count);
			dataNameToIndex = new Dictionary<string, int>();

			int iFormat = 0;
			int readCursor = 0;
			foreach (DataFormat fmt in formats.NTSFormats) {
				int readDataSize = 0;
				dataList.Add( ChunkParser.Parse( dataChunk, fmt, readCursor, out readDataSize ) );
				readCursor += readDataSize;
				dataNameToIndex.Add( fmt.Name, iFormat++ );
			}
		}

		private DataFormatCollection formats;
		private Dictionary<string, int> dataNameToIndex;
		private List<object> dataList;
	}

	// Time Series的数据整体较大，因此不做预读处理。
	public class TSData : ChunkSerializable {
		public TSData(DataFormatCollection tsFormats, Chunk chunk ): base(chunk){
			this.tsFormats = tsFormats;
		}

		protected override void ReleaseDerived() {
			tsFormats = null;
			tsIdxDataItems = null;
			idxTsDataItems = null;
		}

		public object this[int timeStamp, int formatIdx] {
			get {
				Initialize();
				if (!tsIdxDataItems.ContainsKey(timeStamp)) {
					return null;
				}
				if (!tsIdxDataItems[timeStamp].ContainsKey(formatIdx)) {
					return null;
				}
				byte[] content = dataChunk["TIME"][tsIdxDataItems[timeStamp][formatIdx]].ReadChunkBytes(sizeof(int) * 2, -1);
				int readDataSize = 0;
				return ChunkParser.Parse(content, tsFormats.TSFormats[formatIdx], 0, out readDataSize);
			}
		}

		public List<int> TimeSeries {
			get {
				Initialize();
				return new List<int>( tsIdxDataItems.Keys );
			}
		}

		public List<int> DataIndexes {
			get {
				Initialize();
				return new List<int>(idxTsDataItems.Keys);
			}
		}

		public List<int> GetTimeSeries(int dataIndex) {
			Initialize();
			if ( idxTsDataItems.ContainsKey(dataIndex) ) {
				return new List<int>(idxTsDataItems[dataIndex].Keys);
			}
			return null;
		}

		public List<int> GetDataIndexes(int timeSeries) {
			Initialize();
			if (tsIdxDataItems.ContainsKey(timeSeries)) {
				return new List<int>(tsIdxDataItems[timeSeries].Keys);
			}
			return null;
		}

		private void Initialize() {
			if (tsIdxDataItems == null || idxTsDataItems == null ) {
				tsIdxDataItems = new Dictionary<int, Dictionary<int, int>>();
				idxTsDataItems = new Dictionary<int, Dictionary<int, int>>();

				for (int iTSData = 0; iTSData < dataChunk["TIME"].Count; ++iTSData) {
					int timeStamp = 0;
					int formatIdx = 0;
					ReadTimeStampAndFormatIndex(dataChunk["TIME"][iTSData], out timeStamp, out formatIdx);

					// add first
					if (!tsIdxDataItems.ContainsKey(timeStamp)) {
						tsIdxDataItems[timeStamp] = new Dictionary<int, int>();
					}
					if (!idxTsDataItems.ContainsKey(formatIdx)) {
						idxTsDataItems[formatIdx] = new Dictionary<int, int>();
					}
					tsIdxDataItems[timeStamp][formatIdx] = iTSData;
					idxTsDataItems[formatIdx][timeStamp] = iTSData;
				}
			}
		}

		private void ReadTimeStampAndFormatIndex(Chunk tsChunk, out int timeStamp, out int formatIdx) {
			byte[] tsIdxBytes = tsChunk.ReadChunkBytes(0, sizeof(int) * 2);
			timeStamp = ChunkReader.BigEndianBytesToInt32(tsIdxBytes, 0);
			formatIdx = ChunkReader.BigEndianBytesToInt32(tsIdxBytes, sizeof(int));
		}

		Dictionary<int, Dictionary<int, int>> tsIdxDataItems;
		Dictionary< int, Dictionary<int, int> > idxTsDataItems;

		DataFormatCollection tsFormats;
	}
}
