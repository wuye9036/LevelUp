using System;
using System.Collections.Generic;
using System.Text;
using SwarmExperimentalAnalyser.Model.Experiment;
using System.Runtime.InteropServices;
using SwarmExperimentalAnalyser.Model.ChunkIO;
using System.Diagnostics;

namespace SwarmExperimentalAnalyser.Model.Experiment {

	public class ChunkParser {
		static public void Parse(Chunk chunk, out string v) {
			v = ChunkReader.BytesToString(chunk.ChunkBytes);
		}
		static public object Parse(Chunk chunk, DataFormat fmt, int startOffset, out int readDataSize) {
			return Parse(chunk.ChunkBytes, fmt, startOffset, out readDataSize);
		}
		static public object Parse(byte[] data, DataFormat fmt, int startOffset, out int readDataSize) {
			readDataSize = 0;

			// calculate data size
			int elemDataSize = fmt.ElementDataSize;
			long[] lengthArray = null;
			if (fmt.IsStaticSizedData) {
				lengthArray = fmt.LengthArray;
			} else {
				int lengthArraySize = 0;
				lengthArray = ReadLengthArray(data, startOffset, fmt.DimensionCount, out lengthArraySize);
				readDataSize += lengthArraySize;
			}

			// read data and generate object
			switch (fmt.Dimension) {
				case DataFormat.DataDimension.Scalar: {
						object v = ChunkReader.BigEndianBytesToObject(data, readDataSize + startOffset, fmt.DataType);
						readDataSize += elemDataSize;
						return v;
					}
				case DataFormat.DataDimension.Array1D: {
						object[] v = new object[lengthArray[0]];
						for (int iElem = 0; iElem < lengthArray[0]; ++iElem) {
							v[iElem] = ChunkReader.BigEndianBytesToObject(data, readDataSize + startOffset, fmt.DataType);
							readDataSize += elemDataSize;
						}
						return v;
					}
				case DataFormat.DataDimension.Array2D: {
						object[,] v = new object[lengthArray[0], lengthArray[1]];
						for (int yElem = 0; yElem < lengthArray[1]; ++yElem) {
							for (int xElem = 0; xElem < lengthArray[0]; ++xElem) {
								v[xElem, yElem] = ChunkReader.BigEndianBytesToObject(data, readDataSize + startOffset, fmt.DataType);
								readDataSize += elemDataSize;
							}
						}
						return v;
					}
			}
			return null;
		}
		static private long[] ReadLengthArray(byte[] bytes, int startOffset, int dataDimension, out int readDataSize) {
			long[] lengthArray = new long[dataDimension];
			readDataSize = dataDimension * Marshal.SizeOf(typeof(long));
			for (int iDim = 0; iDim < dataDimension; ++iDim) {
				lengthArray[iDim] = ChunkReader.BigEndianBytesToInt64(bytes, startOffset + iDim *  Marshal.SizeOf(typeof(long)));
			}
			return lengthArray;
		}
	}

	//public class ChunkParser_
	//{
	//    public ChunkParser_(FileParser parser) {
	//        this.parser = parser;
	//    }
	//    public string HeaderTag {
	//        get { return FileParser.BytesToString(parser.HeaderBytes); }
	//    }
	//    public string Description {
	//        get { return FileParser.BytesToString(parser.DescriptionBytes); }
	//    }
	//    public int DataFormatCount {
	//        get { return parser.RecordItemCount; }
	//    }

	//    public int ExperimentCount {
	//        get { return parser.ExperimentCount; }
	//    }
	//    public string GetExperimentName(int i) {
	//        return parser.ExperimentName(i);
	//    }
	//    public object GetExperimentNonTimeSeriesData(int expId, int itemIdx) {
	//        FillNonTimeSeriesDataOffsetAndTimeSeriesDataSize();
	//        DataFormat recFmt = DataFormat(itemIdx);
	//        byte[] bytes = parser.ExperimentNonTimeSeriesDataBytes(expId, noTimeSeriesValueOffset[itemIdx], noTimeSeriesValueSize[itemIdx]);
	//        if (recFmt.ItemType == DataDimension._scalar) {
	//            return FileParser.BigEndianBytesToObject(bytes, 0, recFmt.DataType);
	//        } else if (recFmt.ItemType == DataDimension._2D) {
	//            object[,] arr2d = new object[recFmt.LengthArray[0], recFmt.LengthArray[1]];
	//            for (int ix = 0; ix < recFmt.LengthArray[0]; ++ix) {
	//                for (int iy = 0; iy < recFmt.LengthArray[1]; ++iy) {
	//                    arr2d[ix, iy] = FileParser.BigEndianBytesToObject(bytes, (int)(Marshal.SizeOf(recFmt.DataType) * (iy + ix * recFmt.LengthArray[1])), recFmt.DataType);
	//                }
	//            }
	//            return arr2d;
	//        } else {
	//            throw new Exception("不支持...");
	//        }
	//    }
	//    public int TimeStampCount(int expId) {
	//        return TimeStamps(expId) == null ? 0 : TimeStamps(expId).Count;
	//    }
	//    public List<int> TimeStamps(int expIdx) {
	//        if (!expTimeStamps.ContainsKey(expIdx)) {
	//            List<int> timeStamps = parser.ExperimentTimeStamps(expIdx);
	//            timeStamps.Sort();
	//            expTimeStamps[expIdx] = timeStamps;
	//        }
	//        return expTimeStamps[expIdx];
	//    }
	//    public object GetExperimentTimeSeriesData(int expId, int timeStamp, int itemIdx) {
	//        FillNonTimeSeriesDataOffsetAndTimeSeriesDataSize();

	//        int fmtItemIdx = itemIdx < noTimeSeriesValueOffset.Count ? itemIdx + noTimeSeriesValueOffset.Count : itemIdx;
	//        int dataItemIdx = fmtItemIdx - noTimeSeriesValueOffset.Count;

	//        DataFormat recFmt = DataFormat(fmtItemIdx);
	//        byte[] bytes =
	//            bytes = parser.ExperimentTimeSeriesDataBytes(expId, timeStamp, dataItemIdx, (int)timeSeriesDataSize[dataItemIdx]); 
	//        if (recFmt.ItemType == DataDimension._scalar) {
	//            return FileParser.BigEndianBytesToObject(bytes, 0, recFmt.DataType);
	//        } else if (recFmt.ItemType == DataDimension._2D) {
	//            object[,] arr2d = new object[recFmt.LengthArray[0], recFmt.LengthArray[1]];
	//            for (int ix = 0; ix < recFmt.LengthArray[0]; ++ix) {
	//                for (int iy = 0; iy < recFmt.LengthArray[1]; ++iy) {
	//                    arr2d[ix,iy] = FileParser.BigEndianBytesToObject(bytes, (int)(Marshal.SizeOf(recFmt.DataType) * (iy + ix * recFmt.LengthArray[1])), recFmt.DataType);
	//                }
	//            }
	//            return arr2d;
	//        } else {
	//            throw new Exception("不支持...");
	//        }
	//    }

	//    private void FillNonTimeSeriesDataOffsetAndTimeSeriesDataSize() {
	//        if (noTimeSeriesValueOffset != null) {
	//            return;	
	//        }

	//        noTimeSeriesValueOffset = new List<long>();
	//        noTimeSeriesValueSize = new List<int>();
	//        timeSeriesDataSize = new List<long>();

	//        long totalSize = 0;
	//        for (int i = 0; i < DataFormatCount; ++i) {
	//            if (!DataFormat(i).IsTimeSeries) {
	//                noTimeSeriesValueOffset.Add(totalSize);
	//            }

	//            long lengthArray = 0;
	//            int cellSize = Marshal.SizeOf(DataFormat(i).DataType);

	//            switch (DataFormat(i).ItemType ){
	//                case DataDimension._scalar:
	//                    lengthArray = cellSize;
	//                    break;
	//                case DataDimension._1D:
	//                    lengthArray = cellSize * DataFormat(i).LengthArray[0];
	//                    break;
	//                case DataDimension._2D:
	//                    lengthArray = cellSize * DataFormat(i).LengthArray[0] * DataFormat(i).LengthArray[1];
	//                    break;
	//            }

	//            totalSize += lengthArray;
	//            if (DataFormat(i).IsTimeSeries) {
	//                timeSeriesDataSize.Add(lengthArray);
	//            } else {
	//                noTimeSeriesValueSize.Add((int)lengthArray); 
	//            }
	//        }
	//    }

	//    private FileParser parser;
	//    private List<long> noTimeSeriesValueOffset;
	//    private List<int> noTimeSeriesValueSize;
	//    private List<long> timeSeriesDataSize;
	//    private Dictionary<int, List<int>> expTimeStamps = new Dictionary<int,List<int>>();
	//}
}
