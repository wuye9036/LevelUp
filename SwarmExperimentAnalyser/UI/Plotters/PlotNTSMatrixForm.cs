using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using DevExpress.XtraEditors;

namespace SwarmExperimentalAnalyser.UI.Plotters {
	public partial class PlotNTSMatrixForm : DevExpress.XtraEditors.XtraForm {
		public PlotNTSMatrixForm( Context ctxt ) {
			this.ctxt = ctxt;
			InitializeComponent();

			InitializeExprComboBox();
		}

		private ColorMap CreateColorMap(int expIdx) {
			minValue = double.PositiveInfinity;
			maxValue = double.NegativeInfinity;
			
			double total = 0.0;
			int count = 0;
			object[,] data = ctxt.BatchExperiment.Experiments[expIdx].NonTimeSeriesData[ctxt.FocusedItem.Index] as object[,];
			foreach (object ov in data) {
				double v = Convert.ToDouble(ov);
				minValue = Math.Min(v, minValue);
				maxValue = Math.Max(v, maxValue);
				total += v;
				++count;
			}

			mean = total / count;
			stdDev = 0.0;
			foreach (object ov in data) {
				double v = Convert.ToDouble(ov);
				stdDev += (v - mean) * (v - mean);
			}

			stdDev = Math.Sqrt(stdDev / count);

			return ColorMapGenerator.Instance.GenerateLinearColorMap(Color.Black, Color.Aqua, minValue, maxValue);
		}

		private void Display(int expIdx) {
			object[,] data = ctxt.BatchExperiment.Experiments[expIdx].NonTimeSeriesData[ctxt.FocusedItem.Index] as object[,];

			ColorMap cm = CreateColorMap(expIdx);
			plotter = new Array2DPlotter(cm);

			plotter.ResetData(data);
			mdTSMatrix.Draw(plotter);

			lciInformation.Text = string.Format("实验\"{0}\"( 最低值:{1:F3} 最高值:{2:F3} 均值:{3:F3} 标准差:{4:F3} )", lueExprs.Text, minValue, maxValue, mean, stdDev);
		}

		private void InitializeExprComboBox() {
			lueExprs.Properties.DataSource = ctxt.ExperimentTable.DataTable;
		}

		private Context ctxt;
		private double minValue;
		private double maxValue;
		private double stdDev;
		private double mean;
		private Array2DPlotter plotter;

		private void lueExprs_EditValueChanged(object sender, EventArgs e) {
			Display((int)lueExprs.EditValue);
		}
	}
}