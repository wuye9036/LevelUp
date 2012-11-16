using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using DevExpress.XtraBars;
using SwarmExperimentalAnalyser.Model.Experiment;
using SwarmExperimentalAnalyser.UI.Exporter;
using SwarmExperimentalAnalyser.UI.ExperimentInformation;
using SwarmExperimentalAnalyser.UI.Sandbox;
using SwarmExperimentalAnalyser.Model.ChunkIO;
using SwarmExperimentalAnalyser.UI.Plotters;

namespace SwarmExperimentalAnalyser
{
	public partial class MainForm : DevExpress.XtraBars.Ribbon.RibbonForm
	{
		public MainForm()
		{
			InitializeComponent();
		}

		private void bbiOpen_ItemClick(object sender, ItemClickEventArgs e) {
			OpenFileDialog ofd = new OpenFileDialog();
			ofd.Filter = "SWARM Expriment Record File(*.serf)|*.serf";
			if (ofd.ShowDialog() == DialogResult.Cancel) {
				return;
			}
			ChunkReader reader = new ChunkReader( ofd.FileName );
			BatchExperiment batch = new BatchExperiment(reader.RootChunk);

			InitializeExperiment(batch);

			if (expListForm == null) {
				expListForm = new UI.ExperimentInformation.ExperimentListForm();
			}

			expListForm.BindExperiment(ctxt);
			expListForm.MdiParent = this;
			expListForm.Show();

			MessageBox.Show(batch.ExperimentCount.ToString());
		}

		private void InitializeExperiment(BatchExperiment batch) {
			ctxt = new Context();
			ctxt.BatchExperiment = batch;
			ctxt.FocusedItemChanged += this.OnSelectedItemChanged;
		}

		private void OnSelectedItemChanged(Context ctxt) {
			DataFormat dataFmt = ctxt.BatchExperiment.GetDataFormats(ctxt.FocusedItem.IsTimeSeries)[ctxt.FocusedItem.Index];

			bbiDrawTSScalar.Enabled = false;
			bbiExportTSVAsCSV.Enabled = false;
			bbiExportMatrix.Enabled = false;
			bbiExportTSMatrix.Enabled = false;
			bbiShowMatrix.Enabled = false;
			bbiShowNTSMatrix.Enabled = false;

			if (dataFmt.IsTimeSeries == true && dataFmt.Dimension == DataFormat.DataDimension.Scalar) {
				bbiDrawTSScalar.Enabled = true;
				bbiExportTSVAsCSV.Enabled = true;
			}
			if (dataFmt.IsTimeSeries == true && dataFmt.Dimension == DataFormat.DataDimension.Array2D) {
				bbiExportTSMatrix.Enabled = true;
				bbiShowMatrix.Enabled = true;
			}
			if (dataFmt.IsTimeSeries == false && dataFmt.Dimension == DataFormat.DataDimension.Array2D) {
				bbiExportMatrix.Enabled = true;
				bbiShowNTSMatrix.Enabled = true;
			}
		}

		private Context ctxt;
		private UI.ExperimentInformation.ExperimentListForm expListForm;

		private void bbiExportTSVAsCSV_ItemClick(object sender, ItemClickEventArgs e) {
			TSScalarExporterForm tssExporterDlg = new TSScalarExporterForm(ctxt);
			tssExporterDlg.ShowDialog();
		}

		private void bbiExportMatrix_ItemClick(object sender, ItemClickEventArgs e) {
			NTSMatrixExporterForm ntsmExporterDlg = new NTSMatrixExporterForm(ctxt);
			ntsmExporterDlg.ShowDialog();
		}

		private void barButtonItem1_ItemClick(object sender, ItemClickEventArgs e) {
			StochasticTest testForm = new StochasticTest();
			testForm.ShowDialog();
		}

		private void bbiExportTSMatrix_ItemClick(object sender, ItemClickEventArgs e) {
			TSMatrixExporterForm tsmExporterDlg = new TSMatrixExporterForm(ctxt);
			tsmExporterDlg.ShowDialog();
		}

		private void bbiShowMatrix_ItemClick(object sender, ItemClickEventArgs e) {
			PlotTSMatrixForm frm = new PlotTSMatrixForm(ctxt);
			frm.ShowDialog();
		}

		private void bbiShowNTSMatrix_ItemClick(object sender, ItemClickEventArgs e) {
			PlotNTSMatrixForm frm = new PlotNTSMatrixForm(ctxt);
			frm.ShowDialog();
		}
	}
}