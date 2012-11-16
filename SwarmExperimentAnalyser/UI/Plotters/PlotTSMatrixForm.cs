using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using DevExpress.XtraEditors;

namespace SwarmExperimentalAnalyser.UI.Plotters {
	public partial class PlotTSMatrixForm : DevExpress.XtraEditors.XtraForm {
		public PlotTSMatrixForm( Context ctxt ) {
			this.ctxt = ctxt;
			InitializeComponent();

			timeStampList = ctxt.FocusedExperiment.TimeSeriesData.GetTimeSeries(ctxt.FocusedItem.Index);
			timeStampList.Sort();

			tbcTime.Properties.Minimum = rtbcPlayback.Properties.Minimum = 0;
			tbcTime.Properties.Maximum = rtbcPlayback.Properties.Maximum = timeStampList.Count - 1;

			ColorMap cm = CreateColorMap();
			plotter = new Array2DPlotter(cm);
		}

		private ColorMap CreateColorMap() {
			double min = double.PositiveInfinity;
			double max = double.NegativeInfinity;

			foreach (int ts in timeStampList) {
				object[,] data = ctxt.FocusedExperiment.TimeSeriesData[ts, ctxt.FocusedItem.Index] as object[,];
				foreach (object ov in data) {
					double v = Convert.ToDouble(ov);
					min = Math.Min(v, min);
					max = Math.Max(v, max);
				}
			}

			return ColorMapGenerator.Instance.GenerateLinearColorMap(Color.DarkBlue, Color.White, min, max);
		}

		private void timerPlay_Tick(object sender, EventArgs e) {
			++currentTimeStampId;

			if (currentTimeStampId > playbackEnd) {
				currentTimeStampId = playbackBegin;
				isPlaying = false;
				UpdatePlaybackTracker();
				return;
			}

			Display(currentTimeStampId);
		}

		private void UpdatePlaybackTracker() {
			sbPlay.Enabled = !isPlaying;
			sbStop.Enabled = isPlaying;
			rtbcPlayback.Enabled = !isPlaying;
			tbcTime.Enabled = !isPlaying;

			if (isPlaying != timerPlay.Enabled) {
				if (sePlaybackSpeed.Value <= 0) {
					sePlaybackSpeed.Value = 1;
				} else if (sePlaybackSpeed.Value >= 10) {
					sePlaybackSpeed.Value = 10;
				}
				timerPlay.Interval = (int)(1.0f / (double)sePlaybackSpeed.Value * 1000);

				timerPlay.Enabled = isPlaying;
			}
		}

		private void Display(int tsIdx) {
			int ts = timeStampList[tsIdx];
			object[,] data = ctxt.FocusedExperiment.TimeSeriesData[ts, ctxt.FocusedItem.Index] as object[,];
			plotter.ResetData(data);
			mdTSMatrix.Draw(plotter);
			tbcTime.Value = tsIdx;

			this.Text = string.Format("环境快照视图 - {0}", ts);
		}

		private void rtbcPlayback_EditValueChanged(object sender, EventArgs e) {
			playbackBegin = rtbcPlayback.Value.Minimum;
			playbackEnd = rtbcPlayback.Value.Maximum;
		}

		private List<int> timeStampList;

		private int currentTimeStampId;
		private int playbackBegin;
		private int playbackEnd;

		private bool isPlaying;
		private Context ctxt;
		private Array2DPlotter plotter;

		private void tbcTime_EditValueChanged(object sender, EventArgs e) {
			Display(tbcTime.Value);
		}

		private void sbPlay_Click(object sender, EventArgs e) {
			isPlaying = true;
			UpdatePlaybackTracker();
		}

		private void sbStop_Click(object sender, EventArgs e) {
			isPlaying = false;
			UpdatePlaybackTracker();
		}

		private void PlotTSMatrixForm_FormClosing(object sender, FormClosingEventArgs e) {
			isPlaying = false;
			UpdatePlaybackTracker();
		}
		
	}
}