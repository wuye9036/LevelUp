using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace Backuper
{
	public partial class CopyFiles : Form
	{
		private List<PathNode> paths_;
		private string rootTreePath_;

		public CopyFiles( List<PathNode> paths, string targetPath, string rootTreePath ) {
			InitializeComponent();
			paths_ = paths;
			rootTreePath_ = rootTreePath;
			tbTarget.Text = targetPath;
		}

		private void InitializeFileLists() {
			foreach( PathNode pathNode in paths_ ) {
				ListViewItem lvi = new ListViewItem();
				lvFiles.Items.Add( lvi );
				lvi.Tag = pathNode;
				lvi.SubItems[0].Text = pathNode.Name;
				lvi.SubItems.Add( pathNode.FullName );
				lvi.SubItems.Add( pathNode.Size.ToString( "N0" ) );
				lvi.SubItems.Add( pathNode.LastWriteTime.ToString() );
				lvi.SubItems.Add( pathNode.Checksum );
			}
		}

		private void CopyFiles_Load( object sender, EventArgs e ) {
			InitializeFileLists();
		}

		private void cbSelectAll_CheckedChanged( object sender, EventArgs e ) {
			foreach( ListViewItem lvi in lvFiles.Items ) {
				lvi.Checked = cbSelectAll.Checked;
			}
		}

		private void btnOK_Click( object sender, EventArgs e ) {
			List<PathNode> copiedPathNodes = new List<PathNode>();
			foreach( ListViewItem lvi in lvFiles.CheckedItems ) {
				copiedPathNodes.Add( lvi.Tag as PathNode );
			}

			FileOperationProgress fop = new FileOperationProgress(
				copiedPathNodes, rootTreePath_, tbTarget.Text 
				);

			fop.ShowDialog();
			Close();
		}

		private void btnCancel_Click(object sender, EventArgs e)
		{
			Close();
		}
	}
}