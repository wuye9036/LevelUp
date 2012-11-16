using System;
using System.Collections.Generic;
using System.Text;
using SwarmExperimentalAnalyser.Model.Experiment;
using System.IO;

namespace SwarmExperimentalAnalyser.UI.Exporter {
	class ValueExporter {
		public ValueExporter( BatchExperiment batch ) {
			this.batch = batch;
		}

		public void ExportScalar(string fileName, int[] expIds, int recordItemId) {
		    TextWriter wt = new StreamWriter(fileName, false, Encoding.Default);

		    //收集全部有效的TimeStamp
		    Dictionary<int, object> validTimeStampsSet = new Dictionary<int, object>();
		    foreach (int expIdx in expIds) {
				List<int> exprTimes = batch.Experiments[expIdx].TimeSeriesData.GetTimeSeries(recordItemId);
		        foreach (int timeStamp in exprTimes) {
		            validTimeStampsSet[timeStamp] = null;
		        }
		    }

		    //整理成timestamps列表
		    List<int> timeStamps = new List<int>(validTimeStampsSet.Keys);

		    wt.Write("{0},", batch.BatchDescription);
		    foreach (int expIdx in expIds) {
		        wt.Write("{0}, ", batch.Experiments[expIdx].Name);	
		    }
		    wt.WriteLine();

		    foreach(int timeStamp in timeStamps){
		        wt.Write("{0}, ", timeStamp);
		        foreach (int expIdx in expIds) {
		            object v = batch.Experiments[expIdx].TimeSeriesData[timeStamp,recordItemId];
		            if (v == null) {
		                wt.Write(",");
		            } else {
		                wt.Write("{0},", v);
		            }
		        }
		        wt.WriteLine();
		    }

		    wt.Close();
		}

		public void Export2DSlice(string fileName, int dataIndex, SortedDictionary<int, List<int> > exprTs ) {
			TextWriter wt = new StreamWriter(fileName, false, Encoding.Default);

			foreach (int expIndex in exprTs.Keys) {
				Experiment expr = batch.Experiments[expIndex];

				foreach (int time in exprTs[expIndex]) {
					wt.WriteLine(string.Format("{0}, Time: {1}", expr.Name, time));
					object[,] arr2d = expr.TimeSeriesData[time, dataIndex] as object[,];
					for (int i = 0; i < arr2d.GetLength(0); ++i) {
						for (int j = 0; j < arr2d.GetLength(1); ++j) {
							wt.Write("{0}, ", arr2d[i, j]);
						}
						wt.WriteLine();
					}
					wt.WriteLine();
				}
			}

			wt.Close();
		}

		public void ExportNTSData2D(string fileName, int[] experimentIndexes, int dataIndex) {
			TextWriter wt = new StreamWriter(fileName, false, Encoding.Default);

			foreach (int expIndex in experimentIndexes) {
				Experiment expr = batch.Experiments[expIndex];

				wt.WriteLine(expr.Name);
				object[,] arr2d = expr.NonTimeSeriesData[dataIndex] as object[,];
				for (int i = 0; i < arr2d.GetLength(0); ++i ) {
					for( int j = 0; j < arr2d.GetLength(1); ++j) {
						wt.Write("{0}, ", arr2d[i,j] );
					}
					wt.WriteLine();
				}
				wt.WriteLine();	
			}
			
			wt.Close();
		}

		private BatchExperiment batch;
	}
}
