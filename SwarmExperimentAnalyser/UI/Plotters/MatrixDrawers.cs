using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Text;
using System.Windows.Forms;
using DevExpress.XtraEditors;

namespace SwarmExperimentalAnalyser.UI.Plotters {
	public partial class MatrixDrawers : DevExpress.XtraEditors.XtraUserControl {
		public MatrixDrawers() {
			InitializeComponent();
		}

		public void Draw( Array2DPlotter plotter){
			this.plotter = plotter;
			pePlot.Image = null;
			pePlot.Image = plotter.GetPlottedImage(Width, Height);
		}

		private void pePlot_Resize(object sender, EventArgs e) {
			if (plotter != null) {
				pePlot.Image = null;
				pePlot.Image = plotter.GetPlottedImage(Width, Height);
			}
		}

		Array2DPlotter plotter;
	}
}
