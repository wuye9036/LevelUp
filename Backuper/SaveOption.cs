using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace Backuper
{
	public partial class SaveOption : Form
	{
		public bool IsOK = false;

		public SaveOption() {
			InitializeComponent();
		}

		private void cbIsSaveTree_CheckedChanged( object sender, EventArgs e ) {
			if( cbIsSaveLeft.Checked && cbIsSaveRight.Checked ) {
				cbIsSaveCorrInfo.Enabled = true;
			} else {
				cbIsSaveCorrInfo.Enabled = false;
				cbIsSaveCorrInfo.Checked = false;
			}

			SetConfirmButtonEnabled();
		}

		private void btnChooseFile_Click( object sender, EventArgs e ) {
			SaveFileDialog sfd = new SaveFileDialog();
			sfd.OverwritePrompt = true;
			sfd.Filter = "BackupGuy Path Tree Files (*.bpt)|*.bpt";
			if( sfd.ShowDialog() == DialogResult.OK ) {
				tbSavePath.Text = sfd.FileName;
			}
			SetConfirmButtonEnabled();
		}

		private void SetConfirmButtonEnabled() {
			if( string.IsNullOrEmpty( tbSavePath.Text ) ) {
				btnConfirm.Enabled = false;
			} else {
				if( cbIsSaveLeft.Checked || cbIsSaveRight.Checked ) {
					btnConfirm.Enabled = true;
				} else {
					btnConfirm.Enabled = false;
				}
			}
		}

		private void btnConfirm_Click( object sender, EventArgs e ) {
			IsOK = true;
			this.Close();
		}

		private void btnCancel_Click( object sender, EventArgs e ) {
			IsOK = false;
			this.Close();
		}


	}
}