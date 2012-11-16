namespace SwarmExperimentalAnalyser.UI.Exporter {
	partial class NTSMatrixExporterForm {
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
			this.layoutControl1 = new DevExpress.XtraLayout.LayoutControl();
			this.sbCancel = new DevExpress.XtraEditors.SimpleButton();
			this.sbConfirm = new DevExpress.XtraEditors.SimpleButton();
			this.beOutputFile = new DevExpress.XtraEditors.ButtonEdit();
			this.sbSelectInverse = new DevExpress.XtraEditors.SimpleButton();
			this.sbSelectNone = new DevExpress.XtraEditors.SimpleButton();
			this.sbSelectAll = new DevExpress.XtraEditors.SimpleButton();
			this.clbcExperiments = new DevExpress.XtraEditors.CheckedListBoxControl();
			this.layoutControlGroup1 = new DevExpress.XtraLayout.LayoutControlGroup();
			this.layoutControlItem1 = new DevExpress.XtraLayout.LayoutControlItem();
			this.layoutControlItem3 = new DevExpress.XtraLayout.LayoutControlItem();
			this.layoutControlItem4 = new DevExpress.XtraLayout.LayoutControlItem();
			this.layoutControlItem5 = new DevExpress.XtraLayout.LayoutControlItem();
			this.layoutControlItem2 = new DevExpress.XtraLayout.LayoutControlItem();
			this.layoutControlItem6 = new DevExpress.XtraLayout.LayoutControlItem();
			this.layoutControlItem7 = new DevExpress.XtraLayout.LayoutControlItem();
			this.emptySpaceItem1 = new DevExpress.XtraLayout.EmptySpaceItem();
			((System.ComponentModel.ISupportInitialize)(this.layoutControl1)).BeginInit();
			this.layoutControl1.SuspendLayout();
			((System.ComponentModel.ISupportInitialize)(this.beOutputFile.Properties)).BeginInit();
			((System.ComponentModel.ISupportInitialize)(this.clbcExperiments)).BeginInit();
			((System.ComponentModel.ISupportInitialize)(this.layoutControlGroup1)).BeginInit();
			((System.ComponentModel.ISupportInitialize)(this.layoutControlItem1)).BeginInit();
			((System.ComponentModel.ISupportInitialize)(this.layoutControlItem3)).BeginInit();
			((System.ComponentModel.ISupportInitialize)(this.layoutControlItem4)).BeginInit();
			((System.ComponentModel.ISupportInitialize)(this.layoutControlItem5)).BeginInit();
			((System.ComponentModel.ISupportInitialize)(this.layoutControlItem2)).BeginInit();
			((System.ComponentModel.ISupportInitialize)(this.layoutControlItem6)).BeginInit();
			((System.ComponentModel.ISupportInitialize)(this.layoutControlItem7)).BeginInit();
			((System.ComponentModel.ISupportInitialize)(this.emptySpaceItem1)).BeginInit();
			this.SuspendLayout();
			// 
			// layoutControl1
			// 
			this.layoutControl1.Appearance.DisabledLayoutGroupCaption.ForeColor = System.Drawing.SystemColors.GrayText;
			this.layoutControl1.Appearance.DisabledLayoutGroupCaption.Options.UseForeColor = true;
			this.layoutControl1.Appearance.DisabledLayoutItem.ForeColor = System.Drawing.SystemColors.GrayText;
			this.layoutControl1.Appearance.DisabledLayoutItem.Options.UseForeColor = true;
			this.layoutControl1.Controls.Add(this.sbCancel);
			this.layoutControl1.Controls.Add(this.sbConfirm);
			this.layoutControl1.Controls.Add(this.beOutputFile);
			this.layoutControl1.Controls.Add(this.sbSelectInverse);
			this.layoutControl1.Controls.Add(this.sbSelectNone);
			this.layoutControl1.Controls.Add(this.sbSelectAll);
			this.layoutControl1.Controls.Add(this.clbcExperiments);
			this.layoutControl1.Dock = System.Windows.Forms.DockStyle.Fill;
			this.layoutControl1.Location = new System.Drawing.Point(0, 0);
			this.layoutControl1.Name = "layoutControl1";
			this.layoutControl1.Root = this.layoutControlGroup1;
			this.layoutControl1.Size = new System.Drawing.Size(651, 322);
			this.layoutControl1.TabIndex = 0;
			this.layoutControl1.Text = "layoutControl1";
			// 
			// sbCancel
			// 
			this.sbCancel.AutoSizeInLayoutControl = false;
			this.sbCancel.Location = new System.Drawing.Point(546, 294);
			this.sbCancel.Name = "sbCancel";
			this.sbCancel.Size = new System.Drawing.Size(99, 22);
			this.sbCancel.StyleController = this.layoutControl1;
			this.sbCancel.TabIndex = 10;
			this.sbCancel.Text = "取消";
			this.sbCancel.Click += new System.EventHandler(this.sbCancel_Click);
			// 
			// sbConfirm
			// 
			this.sbConfirm.AutoSizeInLayoutControl = false;
			this.sbConfirm.Location = new System.Drawing.Point(441, 294);
			this.sbConfirm.Name = "sbConfirm";
			this.sbConfirm.Size = new System.Drawing.Size(94, 22);
			this.sbConfirm.StyleController = this.layoutControl1;
			this.sbConfirm.TabIndex = 9;
			this.sbConfirm.Text = "确定";
			this.sbConfirm.Click += new System.EventHandler(this.sbConfirm_Click);
			// 
			// beOutputFile
			// 
			this.beOutputFile.Location = new System.Drawing.Point(72, 294);
			this.beOutputFile.Name = "beOutputFile";
			this.beOutputFile.Properties.Buttons.AddRange(new DevExpress.XtraEditors.Controls.EditorButton[] {
            new DevExpress.XtraEditors.Controls.EditorButton()});
			this.beOutputFile.Properties.TextEditStyle = DevExpress.XtraEditors.Controls.TextEditStyles.DisableTextEditor;
			this.beOutputFile.Size = new System.Drawing.Size(358, 20);
			this.beOutputFile.StyleController = this.layoutControl1;
			this.beOutputFile.TabIndex = 8;
			this.beOutputFile.ButtonClick += new DevExpress.XtraEditors.Controls.ButtonPressedEventHandler(this.beOutputFile_ButtonClick);
			// 
			// sbSelectInverse
			// 
			this.sbSelectInverse.AutoSizeInLayoutControl = false;
			this.sbSelectInverse.Location = new System.Drawing.Point(193, 261);
			this.sbSelectInverse.Name = "sbSelectInverse";
			this.sbSelectInverse.Size = new System.Drawing.Size(98, 22);
			this.sbSelectInverse.StyleController = this.layoutControl1;
			this.sbSelectInverse.TabIndex = 7;
			this.sbSelectInverse.Text = "反选";
			this.sbSelectInverse.Click += new System.EventHandler(this.sbSelectInverse_Click);
			// 
			// sbSelectNone
			// 
			this.sbSelectNone.AutoSizeInLayoutControl = false;
			this.sbSelectNone.Location = new System.Drawing.Point(100, 261);
			this.sbSelectNone.Name = "sbSelectNone";
			this.sbSelectNone.Size = new System.Drawing.Size(82, 22);
			this.sbSelectNone.StyleController = this.layoutControl1;
			this.sbSelectNone.TabIndex = 6;
			this.sbSelectNone.Text = "全不选";
			this.sbSelectNone.Click += new System.EventHandler(this.sbSelectNone_Click);
			// 
			// sbSelectAll
			// 
			this.sbSelectAll.AutoSizeInLayoutControl = false;
			this.sbSelectAll.Location = new System.Drawing.Point(7, 261);
			this.sbSelectAll.Name = "sbSelectAll";
			this.sbSelectAll.Size = new System.Drawing.Size(82, 22);
			this.sbSelectAll.StyleController = this.layoutControl1;
			this.sbSelectAll.TabIndex = 5;
			this.sbSelectAll.Text = "全选";
			this.sbSelectAll.Click += new System.EventHandler(this.sbSelectAll_Click);
			// 
			// clbcExperiments
			// 
			this.clbcExperiments.CheckOnClick = true;
			this.clbcExperiments.Location = new System.Drawing.Point(7, 25);
			this.clbcExperiments.Name = "clbcExperiments";
			this.clbcExperiments.Size = new System.Drawing.Size(638, 225);
			this.clbcExperiments.StyleController = this.layoutControl1;
			this.clbcExperiments.TabIndex = 4;
			this.clbcExperiments.ItemCheck += new DevExpress.XtraEditors.Controls.ItemCheckEventHandler(this.clbcExperiments_ItemCheck);
			// 
			// layoutControlGroup1
			// 
			this.layoutControlGroup1.CustomizationFormText = "layoutControlGroup1";
			this.layoutControlGroup1.Items.AddRange(new DevExpress.XtraLayout.BaseLayoutItem[] {
            this.layoutControlItem1,
            this.layoutControlItem3,
            this.layoutControlItem4,
            this.layoutControlItem5,
            this.layoutControlItem2,
            this.layoutControlItem6,
            this.layoutControlItem7,
            this.emptySpaceItem1});
			this.layoutControlGroup1.Location = new System.Drawing.Point(0, 0);
			this.layoutControlGroup1.Name = "layoutControlGroup1";
			this.layoutControlGroup1.Size = new System.Drawing.Size(651, 322);
			this.layoutControlGroup1.Spacing = new DevExpress.XtraLayout.Utils.Padding(0, 0, 0, 0);
			this.layoutControlGroup1.Text = "layoutControlGroup1";
			this.layoutControlGroup1.TextVisible = false;
			// 
			// layoutControlItem1
			// 
			this.layoutControlItem1.Control = this.clbcExperiments;
			this.layoutControlItem1.CustomizationFormText = "layoutControlItem1";
			this.layoutControlItem1.Location = new System.Drawing.Point(0, 0);
			this.layoutControlItem1.Name = "layoutControlItem1";
			this.layoutControlItem1.Size = new System.Drawing.Size(649, 254);
			this.layoutControlItem1.Text = "实验列表：";
			this.layoutControlItem1.TextLocation = DevExpress.Utils.Locations.Top;
			this.layoutControlItem1.TextSize = new System.Drawing.Size(60, 13);
			// 
			// layoutControlItem3
			// 
			this.layoutControlItem3.Control = this.sbSelectNone;
			this.layoutControlItem3.CustomizationFormText = "layoutControlItem3";
			this.layoutControlItem3.Location = new System.Drawing.Point(93, 254);
			this.layoutControlItem3.Name = "layoutControlItem3";
			this.layoutControlItem3.Size = new System.Drawing.Size(93, 33);
			this.layoutControlItem3.Text = "layoutControlItem3";
			this.layoutControlItem3.TextLocation = DevExpress.Utils.Locations.Left;
			this.layoutControlItem3.TextSize = new System.Drawing.Size(0, 0);
			this.layoutControlItem3.TextToControlDistance = 0;
			this.layoutControlItem3.TextVisible = false;
			// 
			// layoutControlItem4
			// 
			this.layoutControlItem4.Control = this.sbSelectInverse;
			this.layoutControlItem4.CustomizationFormText = "layoutControlItem4";
			this.layoutControlItem4.Location = new System.Drawing.Point(186, 254);
			this.layoutControlItem4.Name = "layoutControlItem4";
			this.layoutControlItem4.Size = new System.Drawing.Size(109, 33);
			this.layoutControlItem4.Text = "layoutControlItem4";
			this.layoutControlItem4.TextLocation = DevExpress.Utils.Locations.Left;
			this.layoutControlItem4.TextSize = new System.Drawing.Size(0, 0);
			this.layoutControlItem4.TextToControlDistance = 0;
			this.layoutControlItem4.TextVisible = false;
			// 
			// layoutControlItem5
			// 
			this.layoutControlItem5.Control = this.beOutputFile;
			this.layoutControlItem5.CustomizationFormText = "目标文件：";
			this.layoutControlItem5.Location = new System.Drawing.Point(0, 287);
			this.layoutControlItem5.Name = "layoutControlItem5";
			this.layoutControlItem5.Size = new System.Drawing.Size(434, 33);
			this.layoutControlItem5.Text = "目标文件：";
			this.layoutControlItem5.TextLocation = DevExpress.Utils.Locations.Left;
			this.layoutControlItem5.TextSize = new System.Drawing.Size(60, 13);
			// 
			// layoutControlItem2
			// 
			this.layoutControlItem2.Control = this.sbSelectAll;
			this.layoutControlItem2.CustomizationFormText = "layoutControlItem2";
			this.layoutControlItem2.Location = new System.Drawing.Point(0, 254);
			this.layoutControlItem2.Name = "layoutControlItem2";
			this.layoutControlItem2.Size = new System.Drawing.Size(93, 33);
			this.layoutControlItem2.Text = "layoutControlItem2";
			this.layoutControlItem2.TextLocation = DevExpress.Utils.Locations.Left;
			this.layoutControlItem2.TextSize = new System.Drawing.Size(0, 0);
			this.layoutControlItem2.TextToControlDistance = 0;
			this.layoutControlItem2.TextVisible = false;
			// 
			// layoutControlItem6
			// 
			this.layoutControlItem6.Control = this.sbConfirm;
			this.layoutControlItem6.CustomizationFormText = "layoutControlItem6";
			this.layoutControlItem6.Location = new System.Drawing.Point(434, 287);
			this.layoutControlItem6.Name = "layoutControlItem6";
			this.layoutControlItem6.Size = new System.Drawing.Size(105, 33);
			this.layoutControlItem6.Text = "layoutControlItem6";
			this.layoutControlItem6.TextLocation = DevExpress.Utils.Locations.Left;
			this.layoutControlItem6.TextSize = new System.Drawing.Size(0, 0);
			this.layoutControlItem6.TextToControlDistance = 0;
			this.layoutControlItem6.TextVisible = false;
			// 
			// layoutControlItem7
			// 
			this.layoutControlItem7.Control = this.sbCancel;
			this.layoutControlItem7.CustomizationFormText = "layoutControlItem7";
			this.layoutControlItem7.Location = new System.Drawing.Point(539, 287);
			this.layoutControlItem7.Name = "layoutControlItem7";
			this.layoutControlItem7.Size = new System.Drawing.Size(110, 33);
			this.layoutControlItem7.Text = "layoutControlItem7";
			this.layoutControlItem7.TextLocation = DevExpress.Utils.Locations.Left;
			this.layoutControlItem7.TextSize = new System.Drawing.Size(0, 0);
			this.layoutControlItem7.TextToControlDistance = 0;
			this.layoutControlItem7.TextVisible = false;
			// 
			// emptySpaceItem1
			// 
			this.emptySpaceItem1.CustomizationFormText = "emptySpaceItem1";
			this.emptySpaceItem1.Location = new System.Drawing.Point(295, 254);
			this.emptySpaceItem1.Name = "emptySpaceItem1";
			this.emptySpaceItem1.Size = new System.Drawing.Size(354, 33);
			this.emptySpaceItem1.Text = "emptySpaceItem1";
			this.emptySpaceItem1.TextSize = new System.Drawing.Size(0, 0);
			// 
			// NTSMatrixExporterForm
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(651, 322);
			this.Controls.Add(this.layoutControl1);
			this.Name = "NTSMatrixExporterForm";
			this.Text = "导出环境";
			((System.ComponentModel.ISupportInitialize)(this.layoutControl1)).EndInit();
			this.layoutControl1.ResumeLayout(false);
			((System.ComponentModel.ISupportInitialize)(this.beOutputFile.Properties)).EndInit();
			((System.ComponentModel.ISupportInitialize)(this.clbcExperiments)).EndInit();
			((System.ComponentModel.ISupportInitialize)(this.layoutControlGroup1)).EndInit();
			((System.ComponentModel.ISupportInitialize)(this.layoutControlItem1)).EndInit();
			((System.ComponentModel.ISupportInitialize)(this.layoutControlItem3)).EndInit();
			((System.ComponentModel.ISupportInitialize)(this.layoutControlItem4)).EndInit();
			((System.ComponentModel.ISupportInitialize)(this.layoutControlItem5)).EndInit();
			((System.ComponentModel.ISupportInitialize)(this.layoutControlItem2)).EndInit();
			((System.ComponentModel.ISupportInitialize)(this.layoutControlItem6)).EndInit();
			((System.ComponentModel.ISupportInitialize)(this.layoutControlItem7)).EndInit();
			((System.ComponentModel.ISupportInitialize)(this.emptySpaceItem1)).EndInit();
			this.ResumeLayout(false);

		}

		#endregion

		private DevExpress.XtraLayout.LayoutControl layoutControl1;
		private DevExpress.XtraEditors.SimpleButton sbSelectInverse;
		private DevExpress.XtraEditors.SimpleButton sbSelectNone;
		private DevExpress.XtraEditors.SimpleButton sbSelectAll;
		private DevExpress.XtraEditors.CheckedListBoxControl clbcExperiments;
		private DevExpress.XtraLayout.LayoutControlGroup layoutControlGroup1;
		private DevExpress.XtraLayout.LayoutControlItem layoutControlItem1;
		private DevExpress.XtraLayout.LayoutControlItem layoutControlItem2;
		private DevExpress.XtraLayout.LayoutControlItem layoutControlItem3;
		private DevExpress.XtraLayout.LayoutControlItem layoutControlItem4;
		private DevExpress.XtraEditors.SimpleButton sbCancel;
		private DevExpress.XtraEditors.SimpleButton sbConfirm;
		private DevExpress.XtraEditors.ButtonEdit beOutputFile;
		private DevExpress.XtraLayout.LayoutControlItem layoutControlItem5;
		private DevExpress.XtraLayout.LayoutControlItem layoutControlItem6;
		private DevExpress.XtraLayout.LayoutControlItem layoutControlItem7;
		private DevExpress.XtraLayout.EmptySpaceItem emptySpaceItem1;

	}
}