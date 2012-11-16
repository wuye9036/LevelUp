namespace SwarmExperimentalAnalyser.UI.Plotters {
	partial class PlotNTSMatrixForm {
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
			this.lueExprs = new DevExpress.XtraEditors.LookUpEdit();
			this.mdTSMatrix = new SwarmExperimentalAnalyser.UI.Plotters.MatrixDrawers();
			this.layoutControlGroup1 = new DevExpress.XtraLayout.LayoutControlGroup();
			this.lciInformation = new DevExpress.XtraLayout.LayoutControlItem();
			this.layoutControlItem1 = new DevExpress.XtraLayout.LayoutControlItem();
			((System.ComponentModel.ISupportInitialize)(this.layoutControl1)).BeginInit();
			this.layoutControl1.SuspendLayout();
			((System.ComponentModel.ISupportInitialize)(this.lueExprs.Properties)).BeginInit();
			((System.ComponentModel.ISupportInitialize)(this.layoutControlGroup1)).BeginInit();
			((System.ComponentModel.ISupportInitialize)(this.lciInformation)).BeginInit();
			((System.ComponentModel.ISupportInitialize)(this.layoutControlItem1)).BeginInit();
			this.SuspendLayout();
			// 
			// layoutControl1
			// 
			this.layoutControl1.Appearance.DisabledLayoutGroupCaption.ForeColor = System.Drawing.SystemColors.GrayText;
			this.layoutControl1.Appearance.DisabledLayoutGroupCaption.Options.UseForeColor = true;
			this.layoutControl1.Appearance.DisabledLayoutItem.ForeColor = System.Drawing.SystemColors.GrayText;
			this.layoutControl1.Appearance.DisabledLayoutItem.Options.UseForeColor = true;
			this.layoutControl1.Controls.Add(this.lueExprs);
			this.layoutControl1.Controls.Add(this.mdTSMatrix);
			this.layoutControl1.Dock = System.Windows.Forms.DockStyle.Fill;
			this.layoutControl1.Location = new System.Drawing.Point(0, 0);
			this.layoutControl1.Name = "layoutControl1";
			this.layoutControl1.Root = this.layoutControlGroup1;
			this.layoutControl1.Size = new System.Drawing.Size(396, 443);
			this.layoutControl1.TabIndex = 0;
			this.layoutControl1.Text = "layoutControl1";
			// 
			// lueExprs
			// 
			this.lueExprs.Location = new System.Drawing.Point(7, 417);
			this.lueExprs.Name = "lueExprs";
			this.lueExprs.Properties.Buttons.AddRange(new DevExpress.XtraEditors.Controls.EditorButton[] {
            new DevExpress.XtraEditors.Controls.EditorButton(DevExpress.XtraEditors.Controls.ButtonPredefines.Combo)});
			this.lueExprs.Properties.Columns.AddRange(new DevExpress.XtraEditors.Controls.LookUpColumnInfo[] {
            new DevExpress.XtraEditors.Controls.LookUpColumnInfo("NAME", "实验名称")});
			this.lueExprs.Properties.DisplayMember = "NAME";
			this.lueExprs.Properties.NullText = "<请选择一个实验>";
			this.lueExprs.Properties.ValueMember = "EXPIDX";
			this.lueExprs.Size = new System.Drawing.Size(383, 20);
			this.lueExprs.StyleController = this.layoutControl1;
			this.lueExprs.TabIndex = 6;
			this.lueExprs.EditValueChanged += new System.EventHandler(this.lueExprs_EditValueChanged);
			// 
			// mdTSMatrix
			// 
			this.mdTSMatrix.Location = new System.Drawing.Point(7, 25);
			this.mdTSMatrix.Name = "mdTSMatrix";
			this.mdTSMatrix.Size = new System.Drawing.Size(383, 381);
			this.mdTSMatrix.TabIndex = 4;
			// 
			// layoutControlGroup1
			// 
			this.layoutControlGroup1.CustomizationFormText = "layoutControlGroup1";
			this.layoutControlGroup1.Items.AddRange(new DevExpress.XtraLayout.BaseLayoutItem[] {
            this.lciInformation,
            this.layoutControlItem1});
			this.layoutControlGroup1.Location = new System.Drawing.Point(0, 0);
			this.layoutControlGroup1.Name = "layoutControlGroup1";
			this.layoutControlGroup1.Size = new System.Drawing.Size(396, 443);
			this.layoutControlGroup1.Spacing = new DevExpress.XtraLayout.Utils.Padding(0, 0, 0, 0);
			this.layoutControlGroup1.Text = "layoutControlGroup1";
			this.layoutControlGroup1.TextVisible = false;
			// 
			// lciInformation
			// 
			this.lciInformation.Control = this.mdTSMatrix;
			this.lciInformation.CustomizationFormText = "显示：";
			this.lciInformation.Location = new System.Drawing.Point(0, 0);
			this.lciInformation.Name = "lciInformation";
			this.lciInformation.Size = new System.Drawing.Size(394, 410);
			this.lciInformation.Text = "显示：";
			this.lciInformation.TextLocation = DevExpress.Utils.Locations.Top;
			this.lciInformation.TextSize = new System.Drawing.Size(36, 13);
			// 
			// layoutControlItem1
			// 
			this.layoutControlItem1.Control = this.lueExprs;
			this.layoutControlItem1.CustomizationFormText = "实验列表：";
			this.layoutControlItem1.Location = new System.Drawing.Point(0, 410);
			this.layoutControlItem1.Name = "layoutControlItem1";
			this.layoutControlItem1.Size = new System.Drawing.Size(394, 31);
			this.layoutControlItem1.Text = "实验列表：";
			this.layoutControlItem1.TextLocation = DevExpress.Utils.Locations.Left;
			this.layoutControlItem1.TextSize = new System.Drawing.Size(0, 0);
			this.layoutControlItem1.TextToControlDistance = 0;
			this.layoutControlItem1.TextVisible = false;
			// 
			// PlotNTSMatrixForm
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(396, 443);
			this.Controls.Add(this.layoutControl1);
			this.Name = "PlotNTSMatrixForm";
			this.Text = "环境视图";
			((System.ComponentModel.ISupportInitialize)(this.layoutControl1)).EndInit();
			this.layoutControl1.ResumeLayout(false);
			((System.ComponentModel.ISupportInitialize)(this.lueExprs.Properties)).EndInit();
			((System.ComponentModel.ISupportInitialize)(this.layoutControlGroup1)).EndInit();
			((System.ComponentModel.ISupportInitialize)(this.lciInformation)).EndInit();
			((System.ComponentModel.ISupportInitialize)(this.layoutControlItem1)).EndInit();
			this.ResumeLayout(false);

		}

		#endregion

		private DevExpress.XtraLayout.LayoutControl layoutControl1;
		private MatrixDrawers mdTSMatrix;
		private DevExpress.XtraLayout.LayoutControlGroup layoutControlGroup1;
		private DevExpress.XtraLayout.LayoutControlItem lciInformation;
		private DevExpress.XtraEditors.LookUpEdit lueExprs;
		private DevExpress.XtraLayout.LayoutControlItem layoutControlItem1;
	}
}