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
	public partial class TSScalarExporterForm : DevExpress.XtraEditors.XtraForm {
		public TSScalarExporterForm(Context ctxt) {
			InitializeComponent();
			this.ctxt = ctxt;
			InitializeTable(ctxt.ExperimentTable.DataTable);
		}

		public void InitializeTable(DataTable expTbl) {
			foreach (DataRow dr in expTbl.Rows) {
				clbcExperiments.Items.Add(dr["EXPIDX"], (string)dr["NAME"], CheckState.Unchecked, true);
			}
		}

		private void sbSelectAll_Click(object sender, EventArgs e) {
			clbcExperiments.BeginUpdate();
			foreach (CheckedListBoxItem item in clbcExperiments.Items) {
				item.CheckState = CheckState.Checked;
			}
			clbcExperiments.EndUpdate();
		}

		private void sbSelectNone_Click(object sender, EventArgs e) {
			clbcExperiments.BeginUpdate();
			foreach (CheckedListBoxItem item in clbcExperiments.Items) {
				item.CheckState = CheckState.Unchecked;
			}
			clbcExperiments.EndUpdate();
		}

		private void sbSelectInverse_Click(object sender, EventArgs e) {
			clbcExperiments.BeginUpdate();
			foreach (CheckedListBoxItem item in clbcExperiments.Items) {
				if (item.CheckState == CheckState.Checked) {
					item.CheckState = CheckState.Unchecked;
				} else {
					item.CheckState = CheckState.Checked;
				}
			}
			clbcExperiments.EndUpdate();
		}

		private void clbcExperiments_ItemCheck(object sender, DevExpress.XtraEditors.Controls.ItemCheckEventArgs e) {
			if (e.State == CheckState.Indeterminate) {
				clbcExperiments.SetItemCheckState(e.Index, CheckState.Checked);
			}
		}

		private void beOutputFile_ButtonClick(object sender, ButtonPressedEventArgs e) {
			SaveFileDialog sfd = new SaveFileDialog();
			sfd.Filter = "Excel CSV File(*.csv)|*.csv";
			sfd.OverwritePrompt = true;
			sfd.Title = "导出时间序列标量值为CSV格式";
			if (sfd.ShowDialog() == DialogResult.OK) {
				beOutputFile.Text = sfd.FileName;
			}
		}

		private void sbConfirm_Click(object sender, EventArgs e) {
			if (clbcExperiments.CheckedItems.Count == 0) {
				MessageBox.Show("请选择至少一个实验作为导出数据。");
				return;
			}
			if (string.IsNullOrEmpty(beOutputFile.Text)) {
				MessageBox.Show("请指定输出文件的保存路径。");
				return;
			}

			int[] checkedExps = new int[clbcExperiments.CheckedItems.Count];
			for (int iCheckedExp = 0; iCheckedExp < clbcExperiments.CheckedItems.Count; ++iCheckedExp) {
				checkedExps[iCheckedExp] = (int)(clbcExperiments.CheckedItems[iCheckedExp]);
			}

			ValueExporter exporter = new ValueExporter(ctxt.BatchExperiment);
			exporter.ExportScalar(beOutputFile.Text, checkedExps, ctxt.FocusedItem.Index);

			Close();
		}

		private Context ctxt;

		private void sbCancel_Click(object sender, EventArgs e) {
			Close();
		}
	}
}
