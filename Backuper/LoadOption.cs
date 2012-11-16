using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

using System.Xml;

namespace Backuper
{
	public partial class LoadOption : Form
	{
		public XmlDocument Document = null;
		public TreeSide LeftSource = TreeSide.None;
		public TreeSide RightSource = TreeSide.None;
		public bool IsLoadCorr = false;

		public LoadOption() {
			InitializeComponent();
			SetControlsEnabled();
		}

		private void btnOpenFile_Click( object sender, EventArgs e ) {
			OpenFileDialog ofd = new OpenFileDialog();
			ofd.Filter = "BackupGuy Path Tree Files (*.bpt)|*.bpt|All Files(*.*)|*.*";
			if( ofd.ShowDialog() == DialogResult.OK ) {
				tbOpenFilePath.Text = ofd.FileName;
				Document = new XmlDocument();
				try {
					Document.Load( ofd.FileName );
					if( Document.GetElementsByTagName( "PathTree" ).Count > 0 ) {
						comboLeftSource.Items.Add( "Left" );
						comboRightSource.Items.Add( "Left" );

					} else if( Document.GetElementsByTagName( "PathTreePair" ).Count > 0 ) {
						comboLeftSource.Items.Add( "Left" );
						comboLeftSource.Items.Add( "Right" );
						comboRightSource.Items.Add( "Left" );
						comboRightSource.Items.Add( "Right" );
					} else {
						throw new Exception();
					}
				} catch {
					MessageBox.Show( "文档格式不正确！" );
					Document = null;
				}
				SetControlsEnabled();
			}
		}

		private void SetControlsEnabled() {
			if( Document == null ) {
				cbIsLoadCorrInfo.Enabled = false;
				cbIsLoadCorrInfo.Checked = false;
				cbIsLoadLeft.Enabled = false;
				cbIsLoadLeft.Checked = false;
				cbIsLoadRight.Enabled = false;
				cbIsLoadRight.Checked = false;
				btnOpen.Enabled = false;

			} else {
				cbIsLoadLeft.Enabled = true;
				cbIsLoadRight.Enabled = true;
				btnOpen.Enabled = true;
			}
		}

		private void SetCBIsCorrEnabled() {
			cbIsLoadCorrInfo.Enabled = false;
		}
		private void btnOpen_Click( object sender, EventArgs e ) {
			if( cbIsLoadLeft.Checked ) {
				LeftSource = (TreeSide)( Enum.Parse( typeof( TreeSide ), comboLeftSource.Text ) );
				
			}
			if( cbIsLoadRight.Checked ) {
				RightSource = (TreeSide)( Enum.Parse( typeof( TreeSide ), comboRightSource.Text ) );
			}
			IsLoadCorr = cbIsLoadCorrInfo.Checked;
			Close();
		}

		private void btnCancel_Click( object sender, EventArgs e ) {
			Document = null;
			LeftSource = RightSource = TreeSide.None;
			IsLoadCorr = false;
			Close();
		}

		private void cbIsLoad_CheckedChanged( object sender, EventArgs e ) {
			SetCBIsCorrEnabled();
		}
	}
}