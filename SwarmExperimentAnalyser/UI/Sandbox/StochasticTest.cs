using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using DevExpress.XtraEditors;
using SwarmExperimentalAnalyser.UI.Plotters;

namespace SwarmExperimentalAnalyser.UI.Sandbox {
	public partial class StochasticTest : DevExpress.XtraEditors.XtraForm {
		public StochasticTest() {
			InitializeComponent();
		}

		private void simpleButton2_Click(object sender, EventArgs e) {
			isCancel = false;
			
			ColorMap cm = ColorMapGenerator.Instance.GenerateLinearColorMap(Color.Black, Color.Blue, 2700.0, 3300.0);
			orgPlot = new Array2DPlotter(cm);
			destPlot = new Array2DPlotter(cm);

			GaussSurfaceGenerator gsg = new GaussSurfaceGenerator();
			int size = 41;
			data_ = gsg.Generate(size, 3000.0, 500.0, 15, 3.0);
			object[,] objdata = new object[size, size];
			for (int i = 0; i < size; ++i) {
				for (int j = 0; j < size; ++j) {
					objdata[i, j] = data_[i, j];
				}
			}
			orgPlot.ResetData(objdata);
			mdOrg.Draw(orgPlot);

		}

		private bool isCancel = false;
		private double[,] data_;
		private Array2DPlotter orgPlot;
		private Array2DPlotter destPlot;

		private void simpleButton1_Click(object sender, EventArgs e) {
			isCancel = true;
		}
	}
}