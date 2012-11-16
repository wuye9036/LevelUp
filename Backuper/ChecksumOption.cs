using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace Backuper
{
	public enum ThresholdType{
		None,
		Least,
		Most
	}

	public partial class ChecksumOption : Form
	{
		public bool IsOK = false;
		public bool IsUpdateExistChecksum = false;
		public ThresholdType ThresholdType = ThresholdType.None;
		public long Bound = 0;

		public ChecksumOption() {
			InitializeComponent();
		}

		private void btnOK_Click( object sender, EventArgs e ) {
			if( !cbIsUseSizeThreshold.Checked ) {
				ThresholdType = ThresholdType.None;
			} else {
				ThresholdType =
					comboThresholdType.Text == "Least" ?
						ThresholdType.Least :
						comboThresholdType.Text == "Most" ?
							ThresholdType.Most : 
							ThresholdType.None;
				Bound = (long)nudThreshold.Value * 1024;
			}
			IsUpdateExistChecksum = cbIsRecomputeAll.Checked;
			IsOK = true;
			Close();
		}

		private void btnCancel_Click( object sender, EventArgs e ) {
			ThresholdType = ThresholdType.None;
			IsOK = false;
			Close();
		}
	}
}