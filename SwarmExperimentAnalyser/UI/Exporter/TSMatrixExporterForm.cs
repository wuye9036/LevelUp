using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using DevExpress.XtraEditors;
using DevExpress.XtraEditors.Controls;

namespace SwarmExperimentalAnalyser.UI.Exporter {
	public partial class TSMatrixExporterForm : DevExpress.XtraEditors.XtraForm {
		public TSMatrixExporterForm(Context ctxt) {
			InitializeComponent();
			this.ctxt = ctxt;
			InitializeExperimentList();
		}

		private void InitializeExperimentList() {
			clbcExprs.BeginUpdate();
			foreach (DataRow dr in ctxt.ExperimentTable.DataTable.Rows) {
				clbcExprs.Items.Add(dr["EXPIDX"], (string)dr["NAME"]);
			}
			clbcExprs.EndUpdate();
		}

		public Context ctxt;

		private void sbConfirm_Click(object sender, EventArgs e) {
			if (timeStamps == null || timeStamps.Count == 0) {
				MessageBox.Show("请选择至少一个数据。");
				return;
			}

			if (string.IsNullOrEmpty(beOutputPath.Text)) {
				MessageBox.Show("请选择输出文件。");
				return;
			}

			Exporter.ValueExporter exporter = new ValueExporter(ctxt.BatchExperiment);
			exporter.Export2DSlice(beOutputPath.Text, ctxt.FocusedItem.Index, ExprIdTsDict());
			Close();
		}

		private void sbCancel_Click(object sender, EventArgs e) {
			Close();
		}

		private void UpdateTimeStampList() {
			clbcTimeStamps.BeginUpdate();
			clbcTimeStamps.Items.Clear();
			foreach (int key in timeStamps.Keys) {
				clbcTimeStamps.Items.Add(key);
			}
			clbcTimeStamps.EndUpdate();
		}

		private void sbSelect_Click(object sender, EventArgs e) {
			ParseStringToRangeList();
			foreach( CheckedListBoxItem item in clbcTimeStamps.Items ){
				int ts = (int)item.Value;
				if (IsInRange(ts)) {
					item.CheckState = CheckState.Checked;
				}
			}
		}

		private bool IsInRange(int v) {
			if (ranges == null || ranges.Count == 0) {
				return true;
			}
			for (int i = 0; i < ranges.Count / 2; ++i) {
				if (ranges[i * 2] <= v && v <= ranges[i * 2 + 1]) {
					return true;
				}
			}
			return false;
		}

		private void ParseStringToRangeList() {
			ranges = new List<int>();
			try {
				string[] range_strs = beTimeRange.Text.Split(',');
				foreach (string range_str in range_strs) {
					string[] begin_end = range_str.Split('-');
					int begin = Int32.Parse(begin_end[0]);
					int end = begin_end.Length == 1 ? begin : Int32.Parse(begin_end[1]);
					ranges.Add(begin);
					ranges.Add(end);
				}
			} catch (Exception) {
				MessageBox.Show("请输入正确的格式！");
				return;
			}
		}

		private List<int> ranges;
		private SortedDictionary<int, List<int> > timeStamps;

		private void sbSelNone_Click(object sender, EventArgs e) {
			ParseStringToRangeList();
			foreach (CheckedListBoxItem item in clbcTimeStamps.Items) {
				int ts = (int)item.Value;
				if (IsInRange(ts)) {
					item.CheckState = CheckState.Unchecked;
				}
			}
		}

		private void sbInverse_Click(object sender, EventArgs e) {
			ParseStringToRangeList();
			foreach (CheckedListBoxItem item in clbcTimeStamps.Items) {
				int ts = (int)item.Value;
				if (IsInRange(ts)) {
					if (item.CheckState == CheckState.Unchecked) {
						item.CheckState = CheckState.Checked;
					} else {
						item.CheckState = CheckState.Unchecked;
					}
				}
			}
		}

		private void clbcExprs_ItemCheck(object sender, DevExpress.XtraEditors.Controls.ItemCheckEventArgs e) {
			timeStamps = new SortedDictionary<int, List<int>>();
			foreach (CheckedListBoxItem item in clbcExprs.CheckedItems) {
				int iExpr = (int)item.Value;

				foreach (int t in ctxt.BatchExperiment.Experiments[iExpr].TimeSeriesData.GetTimeSeries(ctxt.FocusedItem.Index)) {
					if (!timeStamps.ContainsKey(t)) {
						timeStamps[t] = new List<int>();
					}
					timeStamps[t].Add(iExpr);
				}
			}

			UpdateTimeStampList();
		}

		private void beTimeRange_Properties_ButtonClick(object sender, ButtonPressedEventArgs e) {
			ParseStringToRangeList();
		}

		private void sbSelectAllExpr_Click(object sender, EventArgs e) {
			clbcExprs.BeginUpdate();
			foreach (CheckedListBoxItem item in clbcExprs.Items) {
				item.CheckState = CheckState.Checked;
			}
			clbcExprs.EndUpdate();
		}

		private void sbSelectNoneExpr_Click(object sender, EventArgs e) {
			clbcExprs.BeginUpdate();
			foreach (CheckedListBoxItem item in clbcExprs.Items) {
				item.CheckState = CheckState.Unchecked;
			}
			clbcExprs.EndUpdate();
		}

		private void sbInverseSelectExpr_Click(object sender, EventArgs e) {
			clbcExprs.BeginUpdate();
			foreach (CheckedListBoxItem item in clbcExprs.Items) {
				if (item.CheckState == CheckState.Unchecked) {
					item.CheckState = CheckState.Checked;
				} else {
					item.CheckState = CheckState.Unchecked;
				}
			}
			clbcExprs.EndUpdate();
		}

		private SortedDictionary<int, List<int>> ExprIdTsDict() {
			if (timeStamps == null) {
				return null;
			}

			SortedDictionary<int, List<int>> ret = new SortedDictionary<int, List<int>>();
			foreach (CheckedListBoxItem item in clbcTimeStamps.CheckedItems) {
				int time = (int)item.Value;
				foreach (int expr in timeStamps[time]) {
					if (!ret.ContainsKey(expr)) {
						ret[expr] = new List<int>();
					}
					ret[expr].Add(time);
				}
			}

			return ret;
		}

		private void beOutputPath_Properties_Click(object sender, EventArgs e) {
			SaveFileDialog sfd = new SaveFileDialog();
			sfd.Filter = "Excel CSV File(*.csv)|*.csv";
			sfd.OverwritePrompt = true;
			sfd.Title = "导出时间序列矩阵值为CSV格式";
			if (sfd.ShowDialog() == DialogResult.OK) {
				beOutputPath.Text = sfd.FileName;
			}
		}
	}
}