using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

using System.IO;

namespace Backuper
{
	public partial class FileOperationProgress : Form
	{
		private List<PathNode> pathNodes_ = null;
		private string rootTreePath_ = null;
		private string outPath_ = null;
		private long totalSize_ = 0;
		private bool isOverwriteAll_ = false;
		private bool isNoOverwriteAll_ = false;
		private int startTick_ = 0;
		
		private string elapsedTimeStr_ = "00:00:00";
		private string residualTimeStr_ = "00:00:00";

		private bool isNeedExit_ = false;

		public FileOperationProgress(
			List<PathNode> pathNodes,
			string rootTreePath,
			string outPath
			) {
			InitializeComponent();
			pathNodes_ = pathNodes;
			rootTreePath_ = rootTreePath;
			outPath_ = outPath;
			lblOperationName.Text = "Copying...";
		}

		private void FileOperationProgress_Shown( object sender, EventArgs e ) {
			//统计总的字节数
			foreach( PathNode pathNode in pathNodes_ ) {
				totalSize_ += pathNode.Size;
			}

			long transferedSize = 0;
			try {
				startTick_ = Environment.TickCount;
				foreach( PathNode pathNode in pathNodes_ ) {
					string destPath = GetDestPath(
						pathNode.TreeNode.FullPath,
						rootTreePath_,
						outPath_
					);
					lblFileName.Text = pathNode.Name;
					Copy( pathNode.FullName, destPath, transferedSize );
					transferedSize += pathNode.Size;
				}
				MessageBox.Show("File copy finished successfully!");
			} catch( Exception exc ) {
				MessageBox.Show( "File Copy Aborted:\n" + exc.Message );
			} finally {
				Close();
			}
		}

		private string GetDestPath( string nodeTreePath, string rootTreePath, string outDirPath ) {
			return Path.Combine(
				outDirPath,
				nodeTreePath.Substring( rootTreePath.Length+1 )
				);
		}

		private void Copy( string fromFile, string toFile, long transferedSize ) {
			if( !File.Exists( fromFile ) ) {
				throw new Exception( "Input File " + fromFile + "Can't Opened." );
			}

			if( File.Exists( toFile ) ) {
				if( isNoOverwriteAll_ ) {
					return;
				}
				if( !isOverwriteAll_ ) {
					OverwritePrompt opWnd = new OverwritePrompt();
					OverwriteOption owOp = opWnd.ExecuteDialog( "File " + toFile + " was exists. Overwrite it?" );
					if( owOp == OverwriteOption.NoToAll ) {
						isNoOverwriteAll_ = true;
						return;
					}
					if( owOp == OverwriteOption.No ) {
						return;
					}
					if( owOp == OverwriteOption.YesToAll ) {
						isOverwriteAll_ = true;
					}
				}
			}
			FileStream fin = null;
			FileStream fout = null;
			try
			{
				string outDirectory = Path.GetDirectoryName(toFile);
				if(!Directory.Exists(outDirectory)){
					Directory.CreateDirectory(outDirectory);
				}
				fin = new FileStream(fromFile, FileMode.Open, FileAccess.Read, FileShare.ReadWrite);
				fout = new FileStream(toFile, FileMode.Create, FileAccess.Write, FileShare.ReadWrite);

				int bufsize = 64 * 1024; // 64K Buffer
				byte[] buf = new byte[bufsize];

				long curPos = 0;
				while (true)
				{
					if (isNeedExit_)
					{
						throw new Exception(
							"File copy was aborted by user."
							);
					}

					int readCount = fin.Read(buf, 0, bufsize);
					fout.Write(buf, 0, readCount);
					curPos += readCount;

					//设置进度条和时间
					pbTotal.Value = (int)((double)(curPos + transferedSize) / (double)totalSize_ * 1000.0);
					pbFile.Value = (int)((double)curPos / (double)fin.Length * 1000.0);
					int thisTick = Environment.TickCount;
					int elapsedTick = thisTick - startTick_;
					int totalTick = (int)((double)elapsedTick / (double)(curPos + transferedSize) * (double)totalSize_);

					TimeSpan ts = new TimeSpan(elapsedTick / 1000);
					elapsedTimeStr_ = ts.ToString();
					ts = new TimeSpan(totalTick - elapsedTick);
					residualTimeStr_ = ts.ToString();

					lblFilePercentage.Text = (pbFile.Value / 10).ToString() + "%";
					lblTotalPercentage.Text = (pbTotal.Value / 10).ToString() + "%";

					Application.DoEvents();

					if (readCount < bufsize)
					{
						break;
					}
				}
			}
			catch (Exception exc)
			{
				if (fin != null)
				{
					fin.Close();
				}
				if (fout != null)
				{
					fout.Close();
				}
				try
				{
					File.Delete(toFile);
				}
				catch
				{
					; //null
				}
				throw exc;
			}
			finally
			{
				fin.Close();
				fout.Close();

				FileInfo srcFileInfo = new FileInfo(fromFile);
				FileInfo toFileInfo = new FileInfo(toFile);

				toFileInfo.LastWriteTime = srcFileInfo.LastWriteTime;
			}
		}

		private void btnCancel_Click( object sender, EventArgs e ) {
			isNeedExit_ = true;
		}

		private void timerUpdateTimeLbl_Tick( object sender, EventArgs e ) {
			lblElapsedTime.Text = elapsedTimeStr_;
			lblResidualTime.Text = residualTimeStr_;
		}
	}
}