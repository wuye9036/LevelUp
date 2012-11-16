namespace Backuper
{
	partial class ChecksumComputeProgress
	{
		/// <summary>
		/// 必需的设计器变量。
		/// </summary>
		private System.ComponentModel.IContainer components = null;

		/// <summary>
		/// 清理所有正在使用的资源。
		/// </summary>
		/// <param name="disposing">如果应释放托管资源，为 true；否则为 false。</param>
		protected override void Dispose( bool disposing ) {
			if( disposing && ( components != null ) ) {
				components.Dispose();
			}
			base.Dispose( disposing );
		}

		#region Windows 窗体设计器生成的代码

		/// <summary>
		/// 设计器支持所需的方法 - 不要
		/// 使用代码编辑器修改此方法的内容。
		/// </summary>
		private void InitializeComponent() {
			this.components = new System.ComponentModel.Container();
			this.progressBar1 = new System.Windows.Forms.ProgressBar();
			this.lblProgressInfo = new System.Windows.Forms.Label();
			this.lblPassedTime = new System.Windows.Forms.Label();
			this.lblResidualTime = new System.Windows.Forms.Label();
			this.btnCancel = new System.Windows.Forms.Button();
			this.timerUpdateLabel = new System.Windows.Forms.Timer( this.components );
			this.SuspendLayout();
			// 
			// progressBar1
			// 
			this.progressBar1.Anchor = ( (System.Windows.Forms.AnchorStyles)( ( System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left ) ) );
			this.progressBar1.Location = new System.Drawing.Point( 15, 93 );
			this.progressBar1.Maximum = 1000;
			this.progressBar1.Name = "progressBar1";
			this.progressBar1.Size = new System.Drawing.Size( 413, 23 );
			this.progressBar1.Step = 30;
			this.progressBar1.Style = System.Windows.Forms.ProgressBarStyle.Continuous;
			this.progressBar1.TabIndex = 0;
			// 
			// lblProgressInfo
			// 
			this.lblProgressInfo.Font = new System.Drawing.Font( "Verdana", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ( (byte)( 0 ) ) );
			this.lblProgressInfo.Location = new System.Drawing.Point( 12, 25 );
			this.lblProgressInfo.Name = "lblProgressInfo";
			this.lblProgressInfo.Size = new System.Drawing.Size( 335, 23 );
			this.lblProgressInfo.TabIndex = 1;
			this.lblProgressInfo.Text = "Preparing...";
			this.lblProgressInfo.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
			// 
			// lblPassedTime
			// 
			this.lblPassedTime.Anchor = ( (System.Windows.Forms.AnchorStyles)( ( System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left ) ) );
			this.lblPassedTime.Location = new System.Drawing.Point( 12, 63 );
			this.lblPassedTime.Name = "lblPassedTime";
			this.lblPassedTime.Size = new System.Drawing.Size( 185, 13 );
			this.lblPassedTime.TabIndex = 3;
			this.lblPassedTime.Text = "0 s";
			this.lblPassedTime.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
			// 
			// lblResidualTime
			// 
			this.lblResidualTime.Anchor = ( (System.Windows.Forms.AnchorStyles)( ( System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right ) ) );
			this.lblResidualTime.Location = new System.Drawing.Point( 234, 63 );
			this.lblResidualTime.Name = "lblResidualTime";
			this.lblResidualTime.Size = new System.Drawing.Size( 194, 13 );
			this.lblResidualTime.TabIndex = 4;
			this.lblResidualTime.Text = "0 s";
			this.lblResidualTime.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
			// 
			// btnCancel
			// 
			this.btnCancel.Location = new System.Drawing.Point( 353, 25 );
			this.btnCancel.Name = "btnCancel";
			this.btnCancel.Size = new System.Drawing.Size( 75, 23 );
			this.btnCancel.TabIndex = 5;
			this.btnCancel.Text = "Cancel";
			this.btnCancel.UseVisualStyleBackColor = true;
			this.btnCancel.Click += new System.EventHandler( this.btnCancel_Click );
			// 
			// timerUpdateLabel
			// 
			this.timerUpdateLabel.Enabled = true;
			this.timerUpdateLabel.Interval = 1000;
			this.timerUpdateLabel.Tick += new System.EventHandler( this.timerUpdateLabel_Tick );
			// 
			// ChecksumComputeProgress
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF( 7F, 13F );
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size( 440, 128 );
			this.Controls.Add( this.btnCancel );
			this.Controls.Add( this.lblResidualTime );
			this.Controls.Add( this.lblPassedTime );
			this.Controls.Add( this.lblProgressInfo );
			this.Controls.Add( this.progressBar1 );
			this.Font = new System.Drawing.Font( "Verdana", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ( (byte)( 0 ) ) );
			this.Name = "ChecksumComputeProgress";
			this.Text = "Compute Checksum Running...";
			this.Shown += new System.EventHandler( this.ChecksumComputeProgress_Shown );
			this.ResumeLayout( false );

		}

		#endregion

		private System.Windows.Forms.Label lblProgressInfo;
		private System.Windows.Forms.Button btnCancel;
		public System.Windows.Forms.ProgressBar progressBar1;
		public System.Windows.Forms.Label lblPassedTime;
		public System.Windows.Forms.Label lblResidualTime;
		private System.Windows.Forms.Timer timerUpdateLabel;
	}
}