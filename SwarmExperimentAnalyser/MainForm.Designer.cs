namespace SwarmExperimentalAnalyser
{
	partial class MainForm
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
			this.components = new System.ComponentModel.Container();
			System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(MainForm));
			this.ribbon = new DevExpress.XtraBars.Ribbon.RibbonControl();
			this.amMain = new DevExpress.XtraBars.Ribbon.ApplicationMenu(this.components);
			this.bbiOpen = new DevExpress.XtraBars.BarButtonItem();
			this.bbiExportTSVAsCSV = new DevExpress.XtraBars.BarButtonItem();
			this.bbiExportMatrix = new DevExpress.XtraBars.BarButtonItem();
			this.bbiDrawTSScalar = new DevExpress.XtraBars.BarButtonItem();
			this.bbiExportTSMatrix = new DevExpress.XtraBars.BarButtonItem();
			this.bbiGenSAData = new DevExpress.XtraBars.BarButtonItem();
			this.bbiShowMatrix = new DevExpress.XtraBars.BarButtonItem();
			this.bbiShowNTSMatrix = new DevExpress.XtraBars.BarButtonItem();
			this.icLarge = new DevExpress.Utils.ImageCollection(this.components);
			this.rpStart = new DevExpress.XtraBars.Ribbon.RibbonPage();
			this.rpgFile = new DevExpress.XtraBars.Ribbon.RibbonPageGroup();
			this.rpgExportTimeSeries = new DevExpress.XtraBars.Ribbon.RibbonPageGroup();
			this.rpgExportSlice = new DevExpress.XtraBars.Ribbon.RibbonPageGroup();
			this.rpgView = new DevExpress.XtraBars.Ribbon.RibbonPageGroup();
			this.ribbonStatusBar = new DevExpress.XtraBars.Ribbon.RibbonStatusBar();
			this.xtmmMain = new DevExpress.XtraTabbedMdi.XtraTabbedMdiManager(this.components);
			((System.ComponentModel.ISupportInitialize)(this.amMain)).BeginInit();
			((System.ComponentModel.ISupportInitialize)(this.icLarge)).BeginInit();
			((System.ComponentModel.ISupportInitialize)(this.xtmmMain)).BeginInit();
			this.SuspendLayout();
			// 
			// ribbon
			// 
			this.ribbon.ApplicationButtonDropDownControl = this.amMain;
			this.ribbon.ApplicationIcon = null;
			this.ribbon.Font = new System.Drawing.Font("微软雅黑", 10F);
			this.ribbon.Items.AddRange(new DevExpress.XtraBars.BarItem[] {
            this.bbiOpen,
            this.bbiExportTSVAsCSV,
            this.bbiExportMatrix,
            this.bbiDrawTSScalar,
            this.bbiExportTSMatrix,
            this.bbiGenSAData,
            this.bbiShowMatrix,
            this.bbiShowNTSMatrix});
			this.ribbon.LargeImages = this.icLarge;
			this.ribbon.Location = new System.Drawing.Point(0, 0);
			this.ribbon.Margin = new System.Windows.Forms.Padding(4);
			this.ribbon.MaxItemId = 11;
			this.ribbon.Name = "ribbon";
			this.ribbon.Pages.AddRange(new DevExpress.XtraBars.Ribbon.RibbonPage[] {
            this.rpStart});
			this.ribbon.SelectedPage = this.rpStart;
			this.ribbon.Size = new System.Drawing.Size(947, 143);
			this.ribbon.StatusBar = this.ribbonStatusBar;
			// 
			// amMain
			// 
			this.amMain.BottomPaneControlContainer = null;
			this.amMain.ItemLinks.Add(this.bbiOpen);
			this.amMain.MenuAppearance.Menu.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
			this.amMain.MenuAppearance.Menu.Options.UseFont = true;
			this.amMain.MenuAppearance.MenuBar.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
			this.amMain.MenuAppearance.MenuBar.Options.UseFont = true;
			this.amMain.MenuDrawMode = DevExpress.XtraBars.MenuDrawMode.LargeImagesText;
			this.amMain.Name = "amMain";
			this.amMain.Ribbon = this.ribbon;
			this.amMain.RightPaneControlContainer = null;
			// 
			// bbiOpen
			// 
			this.bbiOpen.Caption = "打开(&O)";
			this.bbiOpen.Id = 3;
			this.bbiOpen.LargeImageIndex = 0;
			this.bbiOpen.Name = "bbiOpen";
			this.bbiOpen.ItemClick += new DevExpress.XtraBars.ItemClickEventHandler(this.bbiOpen_ItemClick);
			// 
			// bbiExportTSVAsCSV
			// 
			this.bbiExportTSVAsCSV.Caption = "导出标量快照...";
			this.bbiExportTSVAsCSV.Enabled = false;
			this.bbiExportTSVAsCSV.Id = 4;
			this.bbiExportTSVAsCSV.Name = "bbiExportTSVAsCSV";
			this.bbiExportTSVAsCSV.ItemClick += new DevExpress.XtraBars.ItemClickEventHandler(this.bbiExportTSVAsCSV_ItemClick);
			// 
			// bbiExportMatrix
			// 
			this.bbiExportMatrix.Caption = "导出环境...";
			this.bbiExportMatrix.Enabled = false;
			this.bbiExportMatrix.Id = 5;
			this.bbiExportMatrix.Name = "bbiExportMatrix";
			this.bbiExportMatrix.ItemClick += new DevExpress.XtraBars.ItemClickEventHandler(this.bbiExportMatrix_ItemClick);
			// 
			// bbiDrawTSScalar
			// 
			this.bbiDrawTSScalar.Caption = "绘制时间序列值...";
			this.bbiDrawTSScalar.Id = 6;
			this.bbiDrawTSScalar.Name = "bbiDrawTSScalar";
			// 
			// bbiExportTSMatrix
			// 
			this.bbiExportTSMatrix.Caption = "导出环境快照...";
			this.bbiExportTSMatrix.Enabled = false;
			this.bbiExportTSMatrix.Id = 7;
			this.bbiExportTSMatrix.Name = "bbiExportTSMatrix";
			this.bbiExportTSMatrix.ItemClick += new DevExpress.XtraBars.ItemClickEventHandler(this.bbiExportTSMatrix_ItemClick);
			// 
			// bbiGenSAData
			// 
			this.bbiGenSAData.Caption = "自相关数据生成示例";
			this.bbiGenSAData.Id = 8;
			this.bbiGenSAData.Name = "bbiGenSAData";
			this.bbiGenSAData.ItemClick += new DevExpress.XtraBars.ItemClickEventHandler(this.barButtonItem1_ItemClick);
			// 
			// bbiShowMatrix
			// 
			this.bbiShowMatrix.Caption = "环境快照视图";
			this.bbiShowMatrix.Enabled = false;
			this.bbiShowMatrix.Id = 9;
			this.bbiShowMatrix.Name = "bbiShowMatrix";
			this.bbiShowMatrix.ItemClick += new DevExpress.XtraBars.ItemClickEventHandler(this.bbiShowMatrix_ItemClick);
			// 
			// bbiShowNTSMatrix
			// 
			this.bbiShowNTSMatrix.Caption = "环境视图";
			this.bbiShowNTSMatrix.Enabled = false;
			this.bbiShowNTSMatrix.Id = 10;
			this.bbiShowNTSMatrix.Name = "bbiShowNTSMatrix";
			this.bbiShowNTSMatrix.ItemClick += new DevExpress.XtraBars.ItemClickEventHandler(this.bbiShowNTSMatrix_ItemClick);
			// 
			// icLarge
			// 
			this.icLarge.ImageSize = new System.Drawing.Size(32, 32);
			this.icLarge.ImageStream = ((DevExpress.Utils.ImageCollectionStreamer)(resources.GetObject("icLarge.ImageStream")));
			this.icLarge.Images.SetKeyName(0, "fileopen.png");
			// 
			// rpStart
			// 
			this.rpStart.Groups.AddRange(new DevExpress.XtraBars.Ribbon.RibbonPageGroup[] {
            this.rpgFile,
            this.rpgExportTimeSeries,
            this.rpgExportSlice,
            this.rpgView});
			this.rpStart.Name = "rpStart";
			this.rpStart.Text = "开始";
			// 
			// rpgFile
			// 
			this.rpgFile.ItemLinks.Add(this.bbiOpen);
			this.rpgFile.Name = "rpgFile";
			this.rpgFile.Text = "文件";
			// 
			// rpgExportTimeSeries
			// 
			this.rpgExportTimeSeries.ItemLinks.Add(this.bbiExportTSVAsCSV);
			this.rpgExportTimeSeries.Name = "rpgExportTimeSeries";
			this.rpgExportTimeSeries.Text = "导出时间序列值";
			// 
			// rpgExportSlice
			// 
			this.rpgExportSlice.ItemLinks.Add(this.bbiExportMatrix);
			this.rpgExportSlice.ItemLinks.Add(this.bbiExportTSMatrix);
			this.rpgExportSlice.ItemLinks.Add(this.bbiGenSAData);
			this.rpgExportSlice.Name = "rpgExportSlice";
			this.rpgExportSlice.Text = "导出环境数据";
			// 
			// rpgView
			// 
			this.rpgView.ItemLinks.Add(this.bbiShowMatrix);
			this.rpgView.ItemLinks.Add(this.bbiShowNTSMatrix);
			this.rpgView.Name = "rpgView";
			this.rpgView.Text = "视图";
			// 
			// ribbonStatusBar
			// 
			this.ribbonStatusBar.Location = new System.Drawing.Point(0, 614);
			this.ribbonStatusBar.Margin = new System.Windows.Forms.Padding(4);
			this.ribbonStatusBar.Name = "ribbonStatusBar";
			this.ribbonStatusBar.Ribbon = this.ribbon;
			this.ribbonStatusBar.Size = new System.Drawing.Size(947, 25);
			// 
			// xtmmMain
			// 
			this.xtmmMain.AppearancePage.Header.Font = new System.Drawing.Font("Tahoma", 9F);
			this.xtmmMain.AppearancePage.Header.Options.UseFont = true;
			this.xtmmMain.AppearancePage.HeaderActive.Font = new System.Drawing.Font("Tahoma", 9F, System.Drawing.FontStyle.Bold);
			this.xtmmMain.AppearancePage.HeaderActive.Options.UseFont = true;
			this.xtmmMain.AppearancePage.HeaderDisabled.Font = new System.Drawing.Font("Tahoma", 9F);
			this.xtmmMain.AppearancePage.HeaderDisabled.Options.UseFont = true;
			this.xtmmMain.AppearancePage.HeaderHotTracked.Font = new System.Drawing.Font("Tahoma", 9F);
			this.xtmmMain.AppearancePage.HeaderHotTracked.Options.UseFont = true;
			this.xtmmMain.AppearancePage.PageClient.Font = new System.Drawing.Font("Tahoma", 9F);
			this.xtmmMain.AppearancePage.PageClient.Options.UseFont = true;
			this.xtmmMain.MdiParent = this;
			// 
			// MainForm
			// 
			this.Appearance.Font = new System.Drawing.Font("Tahoma", 12F);
			this.Appearance.Options.UseFont = true;
			this.AutoScaleDimensions = new System.Drawing.SizeF(9F, 19F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(947, 639);
			this.Controls.Add(this.ribbonStatusBar);
			this.Controls.Add(this.ribbon);
			this.IsMdiContainer = true;
			this.Margin = new System.Windows.Forms.Padding(4);
			this.Name = "MainForm";
			this.Ribbon = this.ribbon;
			this.StatusBar = this.ribbonStatusBar;
			this.Text = "SWARM实验分析工具";
			((System.ComponentModel.ISupportInitialize)(this.amMain)).EndInit();
			((System.ComponentModel.ISupportInitialize)(this.icLarge)).EndInit();
			((System.ComponentModel.ISupportInitialize)(this.xtmmMain)).EndInit();
			this.ResumeLayout(false);

		}

		#endregion

		private DevExpress.XtraBars.Ribbon.RibbonControl ribbon;
		private DevExpress.XtraBars.Ribbon.RibbonStatusBar ribbonStatusBar;
		private DevExpress.XtraBars.Ribbon.ApplicationMenu amMain;
		private DevExpress.XtraBars.BarButtonItem bbiOpen;
		private DevExpress.Utils.ImageCollection icLarge;
		private DevExpress.XtraBars.Ribbon.RibbonPage rpStart;
		private DevExpress.XtraTabbedMdi.XtraTabbedMdiManager xtmmMain;
		private DevExpress.XtraBars.Ribbon.RibbonPageGroup rpgExportTimeSeries;
		private DevExpress.XtraBars.Ribbon.RibbonPageGroup rpgExportSlice;
		private DevExpress.XtraBars.BarButtonItem bbiExportTSVAsCSV;
		private DevExpress.XtraBars.BarButtonItem bbiExportMatrix;
		private DevExpress.XtraBars.BarButtonItem bbiDrawTSScalar;
		private DevExpress.XtraBars.BarButtonItem bbiExportTSMatrix;
		private DevExpress.XtraBars.Ribbon.RibbonPageGroup rpgFile;
		private DevExpress.XtraBars.BarButtonItem bbiGenSAData;
		private DevExpress.XtraBars.BarButtonItem bbiShowMatrix;
		private DevExpress.XtraBars.Ribbon.RibbonPageGroup rpgView;
		private DevExpress.XtraBars.BarButtonItem bbiShowNTSMatrix;
	}
}