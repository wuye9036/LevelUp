using System;
using System.Collections.Generic;
using System.Text;
using System.Runtime.InteropServices;

namespace SwarmExperimentalAnalyser.Model.Experiment {
	public class DataFormat {
		#region "Format Enumerations"
		public enum IOType {
			input,
			output
		}
		public enum DataDimension {
			Scalar,
			Array1D,
			Array2D
		}
		#endregion

		public DataFormat(
			IOType ioType,
			DataDimension dimension,
			Type elemType,
			string name,
			bool isTimeSeries,
			long[] itemSize
			) {
			this.ioType = ioType;
			this.dimension = dimension;
			this.dataType = elemType;
			this.name = name;
			this.isTimeSeries = isTimeSeries;
			this.lengthArray = itemSize;
			this.formatIndex = -1;
		}

		#region "Properties"
		public DataDimension Dimension {
			get { return dimension; }
		}
		public int DimensionCount {
			get {
				switch (Dimension) {
					case DataDimension.Scalar:
						return 0;
					case DataDimension.Array1D:
						return 1;
					case DataDimension.Array2D:
						return 2;
				}
				return -1;
			}
		}
		public Type DataType {
			get { return dataType; }
		}
		public string Name {
			get { return name; }
		}
		public string IO {
			get {
				if (ioType == IOType.input) return "input";
				return "output";
			}
		}
		public bool IsTimeSeries {
			get { return isTimeSeries; }
		}
		public long[] LengthArray {
			get { return lengthArray; }
		}
		public int FormatIndex {
			get { return this.formatIndex; }
			set { this.formatIndex = value; }
		}
		#endregion

		#region "Marshall Size"
		public const int IOTypeCodeSize = 1;
		public const int DimensionCodeSize = 4;
		public const int ElementTypeCodeSize = 8;
		public const int LengthSize = 8;

		public bool IsStaticSizedData {
			get {
				switch(dimension){
					case DataDimension.Scalar:
						return true;
					case DataDimension.Array1D:
						return lengthArray[0] > 0;
					case DataDimension.Array2D:
						return lengthArray[0] > 0 && lengthArray[1] > 0;
				}
				return false;
			}
		}

		public int ElementDataSize {
			get { return Marshal.SizeOf(DataType); }
		}

		#endregion

		#region "Attributes"
		private IOType ioType;
		private DataDimension dimension;
		private Type dataType;
		private string name;
		private bool isTimeSeries;
		private long[] lengthArray;
		private int formatIndex;
		#endregion
	}
}
