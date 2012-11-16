using System;
using System.Collections.Generic;
using System.Text;
using System.Data;
using SwarmExperimentalAnalyser.Model.Experiment;

namespace SwarmExperimentalAnalyser.UI.ExperimentInformation {
	public class DataFormatTable {
		public DataFormatTable(BatchExperiment batch) {
			this.batch = batch;
		}

		public DataTable this[Experiment exp] {
			get {
				if (dt == null) {
					InitializeDataTable();
				}
				if (exp != null) {
					foreach (DataRow dr in dt.Rows) {
						if ((bool)dr["ISTIMESERIES"]) break;
						dr["VALUE"] = exp.NonTimeSeriesData[dr["NAME"].ToString()];
					}
				}
				return dt;
			}
		}

		public DataTable this[int expIndex]{
			get{
				return expIndex == -1 ? this[null] : this[batch.Experiments[expIndex]];
			}
		}

		public void InitializeDataTable() {
			dt = new DataTable("DataFormat");
			dt.Columns.Add("NAME", typeof(string));
			dt.Columns.Add("TYPE", typeof(string));
			dt.Columns.Add("ISTIMESERIES", typeof(bool));
			dt.Columns.Add("VALUE", typeof(string));
			dt.Columns.Add("FORMAT_INDEX", typeof(int));

			foreach (DataFormat fmt in batch.DataFormats.NTSFormats) {
				string itemTypeModifier = "";

				if (fmt.Dimension == DataFormat.DataDimension.Scalar) {
					// do nothing
				} else if (fmt.Dimension == DataFormat.DataDimension.Array1D) {
					itemTypeModifier = "array";
				} else if (fmt.Dimension == DataFormat.DataDimension.Array2D) {
					itemTypeModifier = "matrix";
				}

				dt.Rows.Add(
					fmt.Name,
					string.Format("{0} {1}", fmt.DataType.Name, itemTypeModifier),
					fmt.IsTimeSeries,
					"N/A",
					fmt.FormatIndex
				);
			}

			foreach (DataFormat fmt in batch.DataFormats.TSFormats) {
				string itemTypeModifier = "";

				if (fmt.Dimension == DataFormat.DataDimension.Scalar) {
					// do nothing
				} else if (fmt.Dimension == DataFormat.DataDimension.Array1D) {
					itemTypeModifier = "array";
				} else if (fmt.Dimension == DataFormat.DataDimension.Array2D) {
					itemTypeModifier = "matrix";
				}

				dt.Rows.Add(
					fmt.Name,
					string.Format("{0} {1}", fmt.DataType.Name, itemTypeModifier),
					fmt.IsTimeSeries,
					"N/A",
					fmt.FormatIndex
				);
			}
		}

		private DataTable dt;
		private BatchExperiment batch;
	}

	public class ExperimentTable {
		public ExperimentTable(BatchExperiment batch) {
			this.batch = batch;
		}

		public DataTable DataTable {
			get {
				if (dt == null) {
					dt = new DataTable("Experiment Names");
					dt.Columns.Add("NAME", typeof(string));
					dt.Columns.Add("EXPIDX", typeof(int));
					for (int i = 0; i < batch.ExperimentCount; ++i) {
						dt.Rows.Add( batch.Experiments[i].Name, i);
					}
				}
				return dt;
			}
		}

		DataTable dt;
		BatchExperiment batch;
	}
}
