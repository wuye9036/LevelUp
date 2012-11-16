using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace Backuper
{
	public partial class ChecksumComputeProgress : Form
	{
		private List<PathNode> pathNodes_;
		public bool IsOK = true;
		public bool IsNeedCancel = false;
		public string passedTimeStr = "";
		public string residualTimeStr = "";

		public ChecksumComputeProgress(List<PathNode> pathNodes) {
			InitializeComponent();
			pathNodes_ = pathNodes;
		}

		private void ChecksumComputeProgress_Shown( object sender, EventArgs e ) {
			lblProgressInfo.Text = "Computation Preparing...";

			//统计字节数
			long totalBytes = 0;
			foreach (PathNode node in pathNodes_)
			{
				totalBytes += node.Size;
			}
			long computedSize = 0;
			int startTick = Environment.TickCount;

			foreach (PathNode node in pathNodes_) {
				lblProgressInfo.Text = string.Format(
					"{0}", node.Name
				);
				ChecksumCallback callback = new ChecksumCallback( 
					computedSize, 
					totalBytes, 
					this, 
					startTick 
					);

				string error = node.ComputeChecksumAsync(callback);
				if( error != null ) {
					if( MessageBox.Show( "Checksum computation was interrupted.\n" + error+ "\nContinue Computation?", "Error", MessageBoxButtons.YesNo ) == DialogResult.No ) {
						IsOK = false;
						Close();
						return;
					}
				}
				computedSize += node.Size;
			}
			
			Close();
		}

		private void btnCancel_Click( object sender, EventArgs e ) {
			IsNeedCancel = true;
		}

		private void timerUpdateLabel_Tick( object sender, EventArgs e ) {
			lblPassedTime.Text = passedTimeStr;
			lblResidualTime.Text = residualTimeStr;
		}
	}

	public class ChecksumCallback : IComputeChecksumCallback
	{
		private long computedSize_ = 0;
		private long totalSize_ = 0;
		private long startMicroseconds_ = 0;
		private ChecksumComputeProgress owner_ = null;

		public ChecksumCallback(
			long computedSize,
			long totalSize,
			ChecksumComputeProgress owner,
			long startMicroseconds
			){
			computedSize_ = computedSize;
			totalSize_ = totalSize;
			startMicroseconds_ = startMicroseconds;
			owner_ = owner;
		}

		public override bool RaiseCallback(long curPos, long total)
		{
			int thisTick = System.Environment.TickCount;
			int elapsedTick = (int)(thisTick - startMicroseconds_);

			long totalTick = (long)( (double)elapsedTick / (double)(computedSize_ + curPos) * (double)totalSize_  );
			long residualTick = totalTick - elapsedTick;

			owner_.passedTimeStr = MicroSecondToString( elapsedTick );
			owner_.residualTimeStr = MicroSecondToString( residualTick );
			owner_.progressBar1.Minimum = 0 ;
			owner_.progressBar1.Maximum= (int)totalTick;
			owner_.progressBar1.Value = elapsedTick;

			Application.DoEvents();
			if( owner_.IsNeedCancel ) {
				return false;
			}

			return true;
		}

		private string MicroSecondToString(long tick) {
			long S = 1000;
			long M = 60 * S;
			long H = 60 * M;

			long residualTick = tick;
			if( residualTick >= H ) {
				return 
					string.Format( "{0:D2}:", Math.DivRem( residualTick, H, out residualTick ) )+
					string.Format( "{0:D2}:", Math.DivRem( residualTick, M, out residualTick ) ) +
					string.Format( "{0:D2}", Math.DivRem( residualTick, S, out residualTick ) );
			} 
			return
					string.Format( "{0:D2}:", Math.DivRem( residualTick, M, out residualTick ) ) +
					string.Format( "{0:D2}", Math.DivRem( residualTick, S, out residualTick ) );
		}
	}
}