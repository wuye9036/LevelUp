namespace SwarmExperimentalAnalyser.UI.ExperimentInformation
{
	partial class ExperimentListForm
	{
		/// <summary>
		/// Required designer variable.
		/// </summary>
		private System.ComponentModel.IContainer components = null;

		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		/// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
		protected override void Dispose(bool disposing)
		{
			if (disposing && (components != null))
			{
				components.Dispose();
			}
			base.Dispose(disposing);
		}

		#region Windows Form Designer generated code

		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		private void InitializeComponent()
		{
			this.layoutControl1 = new DevExpress.XtraLayout.LayoutControl();
			this.gcExpInfo = new DevExpress.XtraGrid.GridControl();
			this.gvExpInfo = new DevExpress.XtraGrid.Views.Grid.GridView();
			this.gcName = new DevExpress.XtraGrid.Columns.GridColumn();
			this.gcType = new DevExpress.XtraGrid.Columns.GridColumn();
			this.gcTimeSeries = new DevExpress.XtraGrid.Columns.GridColumn();
			this.gcValue = new DevExpress.XtraGrid.Columns.GridColumn();
			this.gcExpList = new DevExpress.XtraGrid.GridControl();
			this.gvExpList = new DevExpress.XtraGrid.Views.Grid.GridView();
			this.gcExpName = new DevExpress.XtraGrid.Columns.GridColumn();
			this.meExpDesc = new DevExpress.XtraEditors.MemoEdit();
			this.layoutControlGroup1 = new DevExpress.XtraLayout.LayoutControlGroup();
			this.layoutControlItem1 = new DevExpress.XtraLayout.LayoutControlItem();
			this.layoutControlItem2 = new DevExpress.XtraLayout.LayoutControlItem();
			this.layoutControlItem3 = new DevExpress.XtraLayout.LayoutControlItem();
			((System.ComponentModel.ISupportInitialize)(this.layoutControl1)).BeginInit();
			this.layoutControl1.SuspendLayout();
			((System.ComponentModel.ISupportInitialize)(this.gcExpInfo)).BeginInit();
			((System.ComponentModel.ISupportInitialize)(this.gvExpInfo)).BeginInit();
			((System.ComponentModel.ISupportInitialize)(this.gcExpList)).BeginInit();
			((System.ComponentModel.ISupportInitialize)(this.gvExpList)).BeginInit();
			((System.ComponentModel.ISupportInitialize)(this.meExpDesc.Properties)).BeginInit();
			((System.ComponentModel.ISupportInitialize)(this.layoutControlGroup1)).BeginInit();
			((System.ComponentModel.ISupportInitialize)(this.layoutControlItem1)).BeginInit();
			((System.ComponentModel.ISupportInitialize)(this.layoutControlItem2)).BeginInit();
			((System.ComponentModel.ISupportInitialize)(this.layoutControlItem3)).BeginInit();
			this.SuspendLayout();
			// 
			// layoutControl1
			// 
			this.layoutControl1.Appearance.DisabledLayoutGroupCaption.ForeColor = System.Drawing.SystemColors.GrayText;
			this.layoutControl1.Appearance.DisabledLayoutGroupCaption.Options.UseForeColor = true;
			this.layoutControl1.Appearance.DisabledLayoutItem.ForeColor = System.Drawing.SystemColors.GrayText;
			this.layoutControl1.Appearance.DisabledLayoutItem.Options.UseForeColor = true;
			this.layoutControl1.Controls.Add(this.gcExpInfo);
			this.layoutControl1.Controls.Add(this.gcExpList);
			this.layoutControl1.Controls.Add(this.meExpDesc);
			this.layoutControl1.Dock = System.Windows.Forms.DockStyle.Fill;
			this.layoutControl1.Location = new System.Drawing.Point(0, 0);
			this.layoutControl1.Name = "layoutControl1";
			this.layoutControl1.Root = this.layoutControlGroup1;
			this.layoutControl1.Size = new System.Drawing.Size(656, 355);
			this.layoutControl1.TabIndex = 0;
			this.layoutControl1.Text = "layoutControl1";
			// 
			// gcExpInfo
			// 
			this.gcExpInfo.Location = new System.Drawing.Point(219, 26);
			this.gcExpInfo.MainView = this.gvExpInfo;
			this.gcExpInfo.Name = "gcExpInfo";
			this.gcExpInfo.Size = new System.Drawing.Size(431, 323);
			this.gcExpInfo.TabIndex = 6;
			this.gcExpInfo.ViewCollection.AddRange(new DevExpress.XtraGrid.Views.Base.BaseView[] {
            this.gvExpInfo});
			// 
			// gvExpInfo
			// 
			this.gvExpInfo.Columns.AddRange(new DevExpress.XtraGrid.Columns.GridColumn[] {
            this.gcName,
            this.gcType,
            this.gcTimeSeries,
            this.gcValue});
			this.gvExpInfo.GridControl = this.gcExpInfo;
			this.gvExpInfo.Name = "gvExpInfo";
			this.gvExpInfo.OptionsBehavior.Editable = false;
			this.gvExpInfo.OptionsView.ShowGroupPanel = false;
			this.gvExpInfo.FocusedRowChanged += new DevExpress.XtraGrid.Views.Base.FocusedRowChangedEventHandler(this.gvExpInfo_FocusedRowChanged);
			// 
			// gcName
			// 
			this.gcName.Caption = "名称";
			this.gcName.FieldName = "NAME";
			this.gcName.Name = "gcName";
			this.gcName.Visible = true;
			this.gcName.VisibleIndex = 0;
			// 
			// gcType
			// 
			this.gcType.Caption = "类型";
			this.gcType.FieldName = "TYPE";
			this.gcType.Name = "gcType";
			this.gcType.Visible = true;
			this.gcType.VisibleIndex = 1;
			// 
			// gcTimeSeries
			// 
			this.gcTimeSeries.Caption = "时间序列";
			this.gcTimeSeries.FieldName = "ISTIMESERIES";
			this.gcTimeSeries.Name = "gcTimeSeries";
			this.gcTimeSeries.Visible = true;
			this.gcTimeSeries.VisibleIndex = 2;
			// 
			// gcValue
			// 
			this.gcValue.Caption = "参数值";
			this.gcValue.FieldName = "VALUE";
			this.gcValue.Name = "gcValue";
			this.gcValue.Visible = true;
			this.gcValue.VisibleIndex = 3;
			// 
			// gcExpList
			// 
			this.gcExpList.Location = new System.Drawing.Point(7, 145);
			this.gcExpList.MainView = this.gvExpList;
			this.gcExpList.Name = "gcExpList";
			this.gcExpList.Size = new System.Drawing.Size(201, 204);
			this.gcExpList.TabIndex = 5;
			this.gcExpList.ViewCollection.AddRange(new DevExpress.XtraGrid.Views.Base.BaseView[] {
            this.gvExpList});
			// 
			// gvExpList
			// 
			this.gvExpList.Columns.AddRange(new DevExpress.XtraGrid.Columns.GridColumn[] {
            this.gcExpName});
			this.gvExpList.GridControl = this.gcExpList;
			this.gvExpList.Name = "gvExpList";
			this.gvExpList.OptionsBehavior.Editable = false;
			this.gvExpList.OptionsView.ShowGroupPanel = false;
			this.gvExpList.FocusedRowChanged += new DevExpress.XtraGrid.Views.Base.FocusedRowChangedEventHandler(this.gvExpList_FocusedRowChanged);
			// 
			// gcExpName
			// 
			this.gcExpName.Caption = "名称";
			this.gcExpName.FieldName = "NAME";
			this.gcExpName.Name = "gcExpName";
			this.gcExpName.Visible = true;
			this.gcExpName.VisibleIndex = 0;
			// 
			// meExpDesc
			// 
			this.meExpDesc.Location = new System.Drawing.Point(7, 26);
			this.meExpDesc.Name = "meExpDesc";
			this.meExpDesc.Properties.ReadOnly = true;
			this.meExpDesc.Size = new System.Drawing.Size(201, 89);
			this.meExpDesc.StyleController = this.layoutControl1;
			this.meExpDesc.TabIndex = 4;
			// 
			// layoutControlGroup1
			// 
			this.layoutControlGroup1.CustomizationFormText = "Root";
			this.layoutControlGroup1.Items.AddRange(new DevExpress.XtraLayout.BaseLayoutItem[] {
            this.layoutControlItem1,
            this.layoutControlItem2,
            this.layoutControlItem3});
			this.layoutControlGroup1.Location = new System.Drawing.Point(0, 0);
			this.layoutControlGroup1.Name = "Root";
			this.layoutControlGroup1.Size = new System.Drawing.Size(656, 355);
			this.layoutControlGroup1.Spacing = new DevExpress.XtraLayout.Utils.Padding(0, 0, 0, 0);
			this.layoutControlGroup1.Text = "Root";
			this.layoutControlGroup1.TextVisible = false;
			// 
			// layoutControlItem1
			// 
			this.layoutControlItem1.AppearanceItemCaption.Font = new System.Drawing.Font("Tahoma", 9F);
			this.layoutControlItem1.AppearanceItemCaption.Options.UseFont = true;
			this.layoutControlItem1.Control = this.meExpDesc;
			this.layoutControlItem1.CustomizationFormText = "实验描述：";
			this.layoutControlItem1.Location = new System.Drawing.Point(0, 0);
			this.layoutControlItem1.Name = "layoutControlItem1";
			this.layoutControlItem1.Size = new System.Drawing.Size(212, 119);
			this.layoutControlItem1.Text = "实验描述：";
			this.layoutControlItem1.TextLocation = DevExpress.Utils.Locations.Top;
			this.layoutControlItem1.TextSize = new System.Drawing.Size(60, 14);
			// 
			// layoutControlItem2
			// 
			this.layoutControlItem2.AppearanceItemCaption.Font = new System.Drawing.Font("Tahoma", 9F);
			this.layoutControlItem2.AppearanceItemCaption.Options.UseFont = true;
			this.layoutControlItem2.Control = this.gcExpList;
			this.layoutControlItem2.CustomizationFormText = "实验列表：";
			this.layoutControlItem2.Location = new System.Drawing.Point(0, 119);
			this.layoutControlItem2.Name = "layoutControlItem2";
			this.layoutControlItem2.Size = new System.Drawing.Size(212, 234);
			this.layoutControlItem2.Text = "实验列表：";
			this.layoutControlItem2.TextLocation = DevExpress.Utils.Locations.Top;
			this.layoutControlItem2.TextSize = new System.Drawing.Size(60, 14);
			// 
			// layoutControlItem3
			// 
			this.layoutControlItem3.AppearanceItemCaption.Font = new System.Drawing.Font("Tahoma", 9F);
			this.layoutControlItem3.AppearanceItemCaption.Options.UseFont = true;
			this.layoutControlItem3.Control = this.gcExpInfo;
			this.layoutControlItem3.CustomizationFormText = "实验信息：";
			this.layoutControlItem3.Location = new System.Drawing.Point(212, 0);
			this.layoutControlItem3.Name = "layoutControlItem3";
			this.layoutControlItem3.Size = new System.Drawing.Size(442, 353);
			this.layoutControlItem3.Text = "实验信息：";
			this.layoutControlItem3.TextLocation = DevExpress.Utils.Locations.Top;
			this.layoutControlItem3.TextSize = new System.Drawing.Size(60, 14);
			// 
			// ExperimentListForm
			// 
			this.ClientSize = new System.Drawing.Size(656, 355);
			this.Controls.Add(this.layoutControl1);
			this.Name = "ExperimentListForm";
			this.Text = "实验列表";
			((System.ComponentModel.ISupportInitialize)(this.layoutControl1)).EndInit();
			this.layoutControl1.ResumeLayout(false);
			((System.ComponentModel.ISupportInitialize)(this.gcExpInfo)).EndInit();
			((System.ComponentModel.ISupportInitialize)(this.gvExpInfo)).EndInit();
			((System.ComponentModel.ISupportInitialize)(this.gcExpList)).EndInit();
			((System.ComponentModel.ISupportInitialize)(this.gvExpList)).EndInit();
			((System.ComponentModel.ISupportInitialize)(this.meExpDesc.Properties)).EndInit();
			((System.ComponentModel.ISupportInitialize)(this.layoutControlGroup1)).EndInit();
			((System.ComponentModel.ISupportInitialize)(this.layoutControlItem1)).EndInit();
			((System.ComponentModel.ISupportInitialize)(this.layoutControlItem2)).EndInit();
			((System.ComponentModel.ISupportInitialize)(this.layoutControlItem3)).EndInit();
			this.ResumeLayout(false);

		}

		#endregion

		private DevExpress.XtraLayout.LayoutControl layoutControl1;
		private DevExpress.XtraLayout.LayoutControlGroup layoutControlGroup1;
		private DevExpress.XtraEditors.MemoEdit meExpDesc;
		private DevExpress.XtraLayout.LayoutControlItem layoutControlItem1;
		private DevExpress.XtraGrid.GridControl gcExpList;
		private DevExpress.XtraGrid.Views.Grid.GridView gvExpList;
		private DevExpress.XtraLayout.LayoutControlItem layoutControlItem2;
		private DevExpress.XtraGrid.GridControl gcExpInfo;
		private DevExpress.XtraGrid.Views.Grid.GridView gvExpInfo;
		private DevExpress.XtraLayout.LayoutControlItem layoutControlItem3;
		private DevExpress.XtraGrid.Columns.GridColumn gcName;
		private DevExpress.XtraGrid.Columns.GridColumn gcType;
		private DevExpress.XtraGrid.Columns.GridColumn gcTimeSeries;
		private DevExpress.XtraGrid.Columns.GridColumn gcValue;
		private DevExpress.XtraGrid.Columns.GridColumn gcExpName;
	}
}