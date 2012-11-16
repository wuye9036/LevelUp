using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace Backuper
{
	public enum OverwriteOption
	{
		Yes,
		YesToAll,
		No,
		NoToAll
	}

	public partial class OverwritePrompt : Form
	{
		private OverwriteOption overwriteOption_ = OverwriteOption.No;

		public OverwritePrompt(){
			InitializeComponent();
		}

		public OverwriteOption ExecuteDialog(string prompt) {
			lblPrompt.Text = prompt;
			ShowDialog();
			return overwriteOption_;
		}

		private void btnYes_Click( object sender, EventArgs e ) {
			overwriteOption_ = OverwriteOption.Yes;
			Close();
		}

		private void btnYesToAll_Click( object sender, EventArgs e ) {
			overwriteOption_ = OverwriteOption.YesToAll;
			Close();
		}

		private void btnNo_Click( object sender, EventArgs e ) {
			overwriteOption_ = OverwriteOption.No;
			Close();
		}

		private void btnNoToAll_Click( object sender, EventArgs e ) {
			overwriteOption_ = OverwriteOption.NoToAll;
			Close();
		}
	}
}