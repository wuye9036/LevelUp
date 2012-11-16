using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using DevExpress.XtraEditors;

namespace SwarmExperimentalAnalyser.UI.ExperimentInformation
{
	public partial class ExperimentListForm : DevExpress.XtraEditors.XtraForm
	{
		public ExperimentListForm()
		{
			InitializeComponent();
		}

		public void BindExperiment(Context ctxt) {
			this.ctxt = ctxt;
			ctxt.ExperimentTable = new ExperimentTable(ctxt.BatchExperiment);
			rifDt = new DataFormatTable(ctxt.BatchExperiment);

			meExpDesc.EditValue = ctxt.BatchExperiment.BatchDescription;
			gcExpList.DataSource = ctxt.ExperimentTable.DataTable;
			gcExpInfo.DataSource = rifDt[-1];
		}

		private void gvExpList_FocusedRowChanged(object sender, DevExpress.XtraGrid.Views.Base.FocusedRowChangedEventArgs e) {
			ctxt.FocusedExperiment = ctxt.BatchExperiment.Experiments[(int)gvExpList.GetDataRow(e.FocusedRowHandle)["EXPIDX"]];
			gcExpInfo.DataSource = rifDt[ctxt.FocusedExperiment];
		}

		private void gvExpInfo_FocusedRowChanged(object sender, DevExpress.XtraGrid.Views.Base.FocusedRowChangedEventArgs e) {
			ctxt.FocusedItem = new DataItem(
				gvExpInfo.GetDataRow(e.FocusedRowHandle)["ISTIMESERIES"],
				gvExpInfo.GetDataRow(e.FocusedRowHandle)["FORMAT_INDEX"]
				);
		}

		private Context ctxt;
		private DataFormatTable rifDt;
	}
}