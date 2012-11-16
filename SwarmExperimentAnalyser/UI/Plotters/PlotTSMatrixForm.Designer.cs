namespace SwarmExperimentalAnalyser.UI.Plotters {
	partial class PlotTSMatrixForm {
		/// <summary>
		/// Required designer variable.
		/// </summary>
		private System.ComponentModel.IContainer components = null;

		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		/// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
		protected override void Dispose(bool disposing) {
			if (disposing && (components != null)) {
				components.Dispose();
			}
			base.Dispose(disposing);
		}

		#region Windows Form Designer generated code

		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		private void InitializeComponent() {
			this.components = new System.ComponentModel.Container();
			this.layoutControl1 = new DevExpress.XtraLayout.LayoutControl();
			this.sePlaybackSpeed = new DevExpress.XtraEditors.SpinEdit();
			this.sbStop = new DevExpress.XtraEditors.SimpleButton();
			this.sbPlay = new DevExpress.XtraEditors.SimpleButton();
			this.tbcTime = new DevExpress.XtraEditors.TrackBarControl();
			this.rtbcPlayback = new DevExpress.XtraEditors.RangeTrackBarControl();
			this.mdTSMatrix = new SwarmExperimentalAnalyser.UI.Plotters.MatrixDrawers();
			this.layoutControlGroup1 = new DevExpress.XtraLayout.LayoutControlGroup();
			this.layoutControlItem1 = new DevExpress.XtraLayout.LayoutControlItem();
			this.layoutControlItem2 = new DevExpress.XtraLayout.LayoutControlItem();
			this.layoutControlItem3 = new DevExpress.XtraLayout.LayoutControlItem();
			this.layoutControlItem4 = new DevExpress.XtraLayout.LayoutControlItem();
			this.layoutControlItem5 = new DevExpress.XtraLayout.LayoutControlItem();
			this.layoutControlItem6 = new DevExpress.XtraLayout.LayoutControlItem();
			this.timerPlay = new System.Windows.Forms.Timer(this.components);
			((System.ComponentModel.ISupportInitialize)(this.layoutControl1)).BeginInit();
			this.layoutControl1.SuspendLayout();
			((System.ComponentModel.ISupportInitialize)(this.sePlaybackSpeed.Properties)).BeginInit();
			((System.ComponentModel.ISupportInitialize)(this.tbcTime)).BeginInit();
			((System.ComponentModel.ISupportInitialize)(this.tbcTime.Properties)).BeginInit();
			((System.ComponentModel.ISupportInitialize)(this.rtbcPlayback)).BeginInit();
			((System.ComponentModel.ISupportInitialize)(this.rtbcPlayback.Properties)).BeginInit();
			((System.ComponentModel.ISupportInitialize)(this.layoutControlGroup1)).BeginInit();
			((System.ComponentModel.ISupportInitialize)(this.layoutControlItem1)).BeginInit();
			((System.ComponentModel.ISupportInitialize)(this.layoutControlItem2)).BeginInit();
			((System.ComponentModel.ISupportInitialize)(this.layoutControlItem3)).BeginInit();
			((System.ComponentModel.ISupportInitialize)(this.layoutControlItem4)).BeginInit();
			((System.ComponentModel.ISupportInitialize)(this.layoutControlItem5)).BeginInit();
			((System.ComponentModel.ISupportInitialize)(this.layoutControlItem6)).BeginInit();
			this.SuspendLayout();
			// 
			// layoutControl1
			// 
			this.layoutControl1.Appearance.DisabledLayoutGroupCaption.ForeColor = System.Drawing.SystemColors.GrayText;
			this.layoutControl1.Appearance.DisabledLayoutGroupCaption.Options.UseForeColor = true;
			this.layoutControl1.Appearance.DisabledLayoutItem.ForeColor = System.Drawing.SystemColors.GrayText;
			this.layoutControl1.Appearance.DisabledLayoutItem.Options.UseForeColor = true;
			this.layoutControl1.Controls.Add(this.sePlaybackSpeed);
			this.layoutControl1.Controls.Add(this.sbStop);
			this.layoutControl1.Controls.Add(this.sbPlay);
			this.layoutControl1.Controls.Add(this.tbcTime);
			this.layoutControl1.Controls.Add(this.rtbcPlayback);
			this.layoutControl1.Controls.Add(this.mdTSMatrix);
			this.layoutControl1.Dock = System.Windows.Forms.DockStyle.Fill;
			this.layoutControl1.Location = new System.Drawing.Point(0, 0);
			this.layoutControl1.Name = "layoutControl1";
			this.layoutControl1.Root = this.layoutControlGroup1;
			this.layoutControl1.Size = new System.Drawing.Size(396, 443);
			this.layoutControl1.TabIndex = 0;
			this.layoutControl1.Text = "layoutControl1";
			// 
			// sePlaybackSpeed
			// 
			this.sePlaybackSpeed.EditValue = new decimal(new int[] {
            0,
            0,
            0,
            0});
			this.sePlaybackSpeed.Location = new System.Drawing.Point(156, 415);
			this.sePlaybackSpeed.Name = "sePlaybackSpeed";
			this.sePlaybackSpeed.Properties.Buttons.AddRange(new DevExpress.XtraEditors.Controls.EditorButton[] {
            new DevExpress.XtraEditors.Controls.EditorButton()});
			this.sePlaybackSpeed.Size = new System.Drawing.Size(234, 20);
			this.sePlaybackSpeed.StyleController = this.layoutControl1;
			this.sePlaybackSpeed.TabIndex = 9;
			// 
			// sbStop
			// 
			this.sbStop.Location = new System.Drawing.Point(55, 415);
			this.sbStop.Name = "sbStop";
			this.sbStop.Size = new System.Drawing.Size(37, 22);
			this.sbStop.StyleController = this.layoutControl1;
			this.sbStop.TabIndex = 8;
			this.sbStop.Text = "停止";
			this.sbStop.Click += new System.EventHandler(this.sbStop_Click);
			// 
			// sbPlay
			// 
			this.sbPlay.Location = new System.Drawing.Point(7, 415);
			this.sbPlay.Name = "sbPlay";
			this.sbPlay.Size = new System.Drawing.Size(37, 22);
			this.sbPlay.StyleController = this.layoutControl1;
			this.sbPlay.TabIndex = 7;
			this.sbPlay.Text = "播放";
			this.sbPlay.Click += new System.EventHandler(this.sbPlay_Click);
			// 
			// tbcTime
			// 
			this.tbcTime.EditValue = null;
			this.tbcTime.Location = new System.Drawing.Point(60, 359);
			this.tbcTime.Name = "tbcTime";
			this.tbcTime.Size = new System.Drawing.Size(330, 45);
			this.tbcTime.StyleController = this.layoutControl1;
			this.tbcTime.TabIndex = 6;
			this.tbcTime.EditValueChanged += new System.EventHandler(this.tbcTime_EditValueChanged);
			// 
			// rtbcPlayback
			// 
			this.rtbcPlayback.EditValue = new DevExpress.XtraEditors.Repository.TrackBarRange(0, 0);
			this.rtbcPlayback.Location = new System.Drawing.Point(60, 303);
			this.rtbcPlayback.Name = "rtbcPlayback";
			this.rtbcPlayback.Size = new System.Drawing.Size(330, 45);
			this.rtbcPlayback.StyleController = this.layoutControl1;
			this.rtbcPlayback.TabIndex = 5;
			this.rtbcPlayback.EditValueChanged += new System.EventHandler(this.rtbcPlayback_EditValueChanged);
			// 
			// mdTSMatrix
			// 
			this.mdTSMatrix.Location = new System.Drawing.Point(7, 7);
			this.mdTSMatrix.Name = "mdTSMatrix";
			this.mdTSMatrix.Size = new System.Drawing.Size(383, 285);
			this.mdTSMatrix.TabIndex = 4;
			// 
			// layoutControlGroup1
			// 
			this.layoutControlGroup1.CustomizationFormText = "layoutControlGroup1";
			this.layoutControlGroup1.Items.AddRange(new DevExpress.XtraLayout.BaseLayoutItem[] {
            this.layoutControlItem1,
            this.layoutControlItem2,
            this.layoutControlItem3,
            this.layoutControlItem4,
            this.layoutControlItem5,
            this.layoutControlItem6});
			this.layoutControlGroup1.Location = new System.Drawing.Point(0, 0);
			this.layoutControlGroup1.Name = "layoutControlGroup1";
			this.layoutControlGroup1.Size = new System.Drawing.Size(396, 443);
			this.layoutControlGroup1.Spacing = new DevExpress.XtraLayout.Utils.Padding(0, 0, 0, 0);
			this.layoutControlGroup1.Text = "layoutControlGroup1";
			this.layoutControlGroup1.TextVisible = false;
			// 
			// layoutControlItem1
			// 
			this.layoutControlItem1.Control = this.mdTSMatrix;
			this.layoutControlItem1.CustomizationFormText = "显示：";
			this.layoutControlItem1.Location = new System.Drawing.Point(0, 0);
			this.layoutControlItem1.Name = "layoutControlItem1";
			this.layoutControlItem1.Size = new System.Drawing.Size(394, 296);
			this.layoutControlItem1.Text = "显示：";
			this.layoutControlItem1.TextLocation = DevExpress.Utils.Locations.Top;
			this.layoutControlItem1.TextSize = new System.Drawing.Size(0, 0);
			this.layoutControlItem1.TextToControlDistance = 0;
			this.layoutControlItem1.TextVisible = false;
			// 
			// layoutControlItem2
			// 
			this.layoutControlItem2.Control = this.rtbcPlayback;
			this.layoutControlItem2.CustomizationFormText = "播放段落";
			this.layoutControlItem2.Location = new System.Drawing.Point(0, 296);
			this.layoutControlItem2.Name = "layoutControlItem2";
			this.layoutControlItem2.Size = new System.Drawing.Size(394, 56);
			this.layoutControlItem2.Text = "播放段落";
			this.layoutControlItem2.TextLocation = DevExpress.Utils.Locations.Left;
			this.layoutControlItem2.TextSize = new System.Drawing.Size(48, 13);
			// 
			// layoutControlItem3
			// 
			this.layoutControlItem3.Control = this.tbcTime;
			this.layoutControlItem3.CustomizationFormText = "时间轴";
			this.layoutControlItem3.Location = new System.Drawing.Point(0, 352);
			this.layoutControlItem3.Name = "layoutControlItem3";
			this.layoutControlItem3.Size = new System.Drawing.Size(394, 56);
			this.layoutControlItem3.Text = "时间轴";
			this.layoutControlItem3.TextLocation = DevExpress.Utils.Locations.Left;
			this.layoutControlItem3.TextSize = new System.Drawing.Size(48, 13);
			// 
			// layoutControlItem4
			// 
			this.layoutControlItem4.Control = this.sbPlay;
			this.layoutControlItem4.CustomizationFormText = "layoutControlItem4";
			this.layoutControlItem4.Location = new System.Drawing.Point(0, 408);
			this.layoutControlItem4.Name = "layoutControlItem4";
			this.layoutControlItem4.Size = new System.Drawing.Size(48, 33);
			this.layoutControlItem4.Text = "layoutControlItem4";
			this.layoutControlItem4.TextLocation = DevExpress.Utils.Locations.Left;
			this.layoutControlItem4.TextSize = new System.Drawing.Size(0, 0);
			this.layoutControlItem4.TextToControlDistance = 0;
			this.layoutControlItem4.TextVisible = false;
			// 
			// layoutControlItem5
			// 
			this.layoutControlItem5.Control = this.sbStop;
			this.layoutControlItem5.CustomizationFormText = "layoutControlItem5";
			this.layoutControlItem5.Location = new System.Drawing.Point(48, 408);
			this.layoutControlItem5.Name = "layoutControlItem5";
			this.layoutControlItem5.Size = new System.Drawing.Size(48, 33);
			this.layoutControlItem5.Text = "layoutControlItem5";
			this.layoutControlItem5.TextLocation = DevExpress.Utils.Locations.Left;
			this.layoutControlItem5.TextSize = new System.Drawing.Size(0, 0);
			this.layoutControlItem5.TextToControlDistance = 0;
			this.layoutControlItem5.TextVisible = false;
			// 
			// layoutControlItem6
			// 
			this.layoutControlItem6.Control = this.sePlaybackSpeed;
			this.layoutControlItem6.CustomizationFormText = "播放速率";
			this.layoutControlItem6.Location = new System.Drawing.Point(96, 408);
			this.layoutControlItem6.Name = "layoutControlItem6";
			this.layoutControlItem6.Size = new System.Drawing.Size(298, 33);
			this.layoutControlItem6.Text = "播放速率";
			this.layoutControlItem6.TextLocation = DevExpress.Utils.Locations.Left;
			this.layoutControlItem6.TextSize = new System.Drawing.Size(48, 13);
			// 
			// timerPlay
			// 
			this.timerPlay.Tick += new System.EventHandler(this.timerPlay_Tick);
			// 
			// PlotTSMatrixForm
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(396, 443);
			this.Controls.Add(this.layoutControl1);
			this.Name = "PlotTSMatrixForm";
			this.Text = "环境快照视图";
			this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.PlotTSMatrixForm_FormClosing);
			((System.ComponentModel.ISupportInitialize)(this.layoutControl1)).EndInit();
			this.layoutControl1.ResumeLayout(false);
			((System.ComponentModel.ISupportInitialize)(this.sePlaybackSpeed.Properties)).EndInit();
			((System.ComponentModel.ISupportInitialize)(this.tbcTime.Properties)).EndInit();
			((System.ComponentModel.ISupportInitialize)(this.tbcTime)).EndInit();
			((System.ComponentModel.ISupportInitialize)(this.rtbcPlayback.Properties)).EndInit();
			((System.ComponentModel.ISupportInitialize)(this.rtbcPlayback)).EndInit();
			((System.ComponentModel.ISupportInitialize)(this.layoutControlGroup1)).EndInit();
			((System.ComponentModel.ISupportInitialize)(this.layoutControlItem1)).EndInit();
			((System.ComponentModel.ISupportInitialize)(this.layoutControlItem2)).EndInit();
			((System.ComponentModel.ISupportInitialize)(this.layoutControlItem3)).EndInit();
			((System.ComponentModel.ISupportInitialize)(this.layoutControlItem4)).EndInit();
			((System.ComponentModel.ISupportInitialize)(this.layoutControlItem5)).EndInit();
			((System.ComponentModel.ISupportInitialize)(this.layoutControlItem6)).EndInit();
			this.ResumeLayout(false);

		}

		#endregion

		private DevExpress.XtraLayout.LayoutControl layoutControl1;
		private MatrixDrawers mdTSMatrix;
		private DevExpress.XtraLayout.LayoutControlGroup layoutControlGroup1;
		private DevExpress.XtraLayout.LayoutControlItem layoutControlItem1;
		private DevExpress.XtraEditors.TrackBarControl tbcTime;
		private DevExpress.XtraEditors.RangeTrackBarControl rtbcPlayback;
		private DevExpress.XtraLayout.LayoutControlItem layoutControlItem2;
		private DevExpress.XtraLayout.LayoutControlItem layoutControlItem3;
		private DevExpress.XtraEditors.SimpleButton sbStop;
		private DevExpress.XtraEditors.SimpleButton sbPlay;
		private DevExpress.XtraLayout.LayoutControlItem layoutControlItem4;
		private DevExpress.XtraLayout.LayoutControlItem layoutControlItem5;
		private DevExpress.XtraEditors.SpinEdit sePlaybackSpeed;
		private DevExpress.XtraLayout.LayoutControlItem layoutControlItem6;
		private System.Windows.Forms.Timer timerPlay;
	}
}