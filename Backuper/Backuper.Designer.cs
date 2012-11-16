namespace Backuper
{
	partial class Backuper
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
			System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Backuper));
			this.menuStrip1 = new System.Windows.Forms.MenuStrip();
			this.tmsiFile = new System.Windows.Forms.ToolStripMenuItem();
			this.openToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.openLeftToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.openRightToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.saveToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.saveLeftToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.saveRightToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.toolStripSeparator4 = new System.Windows.Forms.ToolStripSeparator();
			this.exitToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.editToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.undoToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.redoToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.viewToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.toolsToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.pereferenceToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.toolStrip1 = new System.Windows.Forms.ToolStrip();
			this.tsbOpen = new System.Windows.Forms.ToolStripButton();
			this.tsbAddRecursive = new System.Windows.Forms.ToolStripButton();
			this.tsbAddFile = new System.Windows.Forms.ToolStripButton();
			this.tsbAddFolderShallow = new System.Windows.Forms.ToolStripButton();
			this.tsbSave = new System.Windows.Forms.ToolStripButton();
			this.toolStripSeparator5 = new System.Windows.Forms.ToolStripSeparator();
			this.tsbDelete = new System.Windows.Forms.ToolStripButton();
			this.tsbDeleteAllSub = new System.Windows.Forms.ToolStripButton();
			this.toolStripSeparator8 = new System.Windows.Forms.ToolStripSeparator();
			this.tsbRefresh = new System.Windows.Forms.ToolStripButton();
			this.tsbComputeChecksum = new System.Windows.Forms.ToolStripButton();
			this.toolStripSeparator6 = new System.Windows.Forms.ToolStripSeparator();
			this.tsbCorresponding = new System.Windows.Forms.ToolStripButton();
			this.tsbShowInfo = new System.Windows.Forms.ToolStripButton();
			this.toolStripSeparator7 = new System.Windows.Forms.ToolStripSeparator();
			this.tsbExport = new System.Windows.Forms.ToolStripButton();
			this.imgLst = new System.Windows.Forms.ImageList(this.components);
			this.cmsTreeItem = new System.Windows.Forms.ContextMenuStrip(this.components);
			this.tsmiAddFolderShallow = new System.Windows.Forms.ToolStripMenuItem();
			this.tsmiAddFolderRecursive = new System.Windows.Forms.ToolStripMenuItem();
			this.tsmiAddFiles = new System.Windows.Forms.ToolStripMenuItem();
			this.toolStripSeparator1 = new System.Windows.Forms.ToolStripSeparator();
			this.tsmiAddFolderAsSub = new System.Windows.Forms.ToolStripMenuItem();
			this.tsmiAddFolderRecursiveAsSubNode = new System.Windows.Forms.ToolStripMenuItem();
			this.toolStripMenuItem3 = new System.Windows.Forms.ToolStripSeparator();
			this.tsmiDelete = new System.Windows.Forms.ToolStripMenuItem();
			this.tsmiDeleteAllSub = new System.Windows.Forms.ToolStripMenuItem();
			this.toolStripSeparator2 = new System.Windows.Forms.ToolStripSeparator();
			this.tsmiRemoveCorrNode = new System.Windows.Forms.ToolStripMenuItem();
			this.toolStripSeparator3 = new System.Windows.Forms.ToolStripSeparator();
			this.tsmiShowInfo = new System.Windows.Forms.ToolStripMenuItem();
			this.BottomToolStripPanel = new System.Windows.Forms.ToolStripPanel();
			this.TopToolStripPanel = new System.Windows.Forms.ToolStripPanel();
			this.RightToolStripPanel = new System.Windows.Forms.ToolStripPanel();
			this.LeftToolStripPanel = new System.Windows.Forms.ToolStripPanel();
			this.ContentPanel = new System.Windows.Forms.ToolStripContentPanel();
			this.statusStrip1 = new System.Windows.Forms.StatusStrip();
			this.splitContainer1 = new System.Windows.Forms.SplitContainer();
			this.ltv = new System.Windows.Forms.TreeView();
			this.rtv = new System.Windows.Forms.TreeView();
			this.menuStrip1.SuspendLayout();
			this.toolStrip1.SuspendLayout();
			this.cmsTreeItem.SuspendLayout();
			this.splitContainer1.Panel1.SuspendLayout();
			this.splitContainer1.Panel2.SuspendLayout();
			this.splitContainer1.SuspendLayout();
			this.SuspendLayout();
			// 
			// menuStrip1
			// 
			this.menuStrip1.Font = new System.Drawing.Font("Verdana", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.tmsiFile,
            this.editToolStripMenuItem,
            this.viewToolStripMenuItem,
            this.toolsToolStripMenuItem});
			this.menuStrip1.Location = new System.Drawing.Point(0, 0);
			this.menuStrip1.Name = "menuStrip1";
			this.menuStrip1.Padding = new System.Windows.Forms.Padding(8, 2, 0, 2);
			this.menuStrip1.Size = new System.Drawing.Size(669, 24);
			this.menuStrip1.TabIndex = 0;
			this.menuStrip1.Text = "menuStrip1";
			// 
			// tmsiFile
			// 
			this.tmsiFile.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.openToolStripMenuItem,
            this.saveToolStripMenuItem,
            this.toolStripSeparator4,
            this.exitToolStripMenuItem});
			this.tmsiFile.Name = "tmsiFile";
			this.tmsiFile.Size = new System.Drawing.Size(40, 20);
			this.tmsiFile.Text = "&File";
			// 
			// openToolStripMenuItem
			// 
			this.openToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.openLeftToolStripMenuItem,
            this.openRightToolStripMenuItem});
			this.openToolStripMenuItem.Image = global::Backuper.Properties.Resources.open;
			this.openToolStripMenuItem.Name = "openToolStripMenuItem";
			this.openToolStripMenuItem.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.O)));
			this.openToolStripMenuItem.Size = new System.Drawing.Size(156, 22);
			this.openToolStripMenuItem.Text = "&Open";
			// 
			// openLeftToolStripMenuItem
			// 
			this.openLeftToolStripMenuItem.Name = "openLeftToolStripMenuItem";
			this.openLeftToolStripMenuItem.ShortcutKeys = ((System.Windows.Forms.Keys)(((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.Shift)
						| System.Windows.Forms.Keys.O)));
			this.openLeftToolStripMenuItem.Size = new System.Drawing.Size(233, 22);
			this.openLeftToolStripMenuItem.Text = "Open &Left...";
			this.openLeftToolStripMenuItem.Click += new System.EventHandler(this.openLeftToolStripMenuItem_Click);
			// 
			// openRightToolStripMenuItem
			// 
			this.openRightToolStripMenuItem.Name = "openRightToolStripMenuItem";
			this.openRightToolStripMenuItem.ShortcutKeys = ((System.Windows.Forms.Keys)(((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.Alt)
						| System.Windows.Forms.Keys.O)));
			this.openRightToolStripMenuItem.Size = new System.Drawing.Size(233, 22);
			this.openRightToolStripMenuItem.Text = "Open &Right...";
			// 
			// saveToolStripMenuItem
			// 
			this.saveToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.saveLeftToolStripMenuItem,
            this.saveRightToolStripMenuItem});
			this.saveToolStripMenuItem.Image = global::Backuper.Properties.Resources.save;
			this.saveToolStripMenuItem.Name = "saveToolStripMenuItem";
			this.saveToolStripMenuItem.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.S)));
			this.saveToolStripMenuItem.Size = new System.Drawing.Size(156, 22);
			this.saveToolStripMenuItem.Text = "&Save";
			// 
			// saveLeftToolStripMenuItem
			// 
			this.saveLeftToolStripMenuItem.Name = "saveLeftToolStripMenuItem";
			this.saveLeftToolStripMenuItem.ShortcutKeys = ((System.Windows.Forms.Keys)(((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.Shift)
						| System.Windows.Forms.Keys.S)));
			this.saveLeftToolStripMenuItem.Size = new System.Drawing.Size(261, 22);
			this.saveLeftToolStripMenuItem.Text = "Save &Left...";
			// 
			// saveRightToolStripMenuItem
			// 
			this.saveRightToolStripMenuItem.Name = "saveRightToolStripMenuItem";
			this.saveRightToolStripMenuItem.ShortcutKeys = ((System.Windows.Forms.Keys)((((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.Alt)
						| System.Windows.Forms.Keys.Shift)
						| System.Windows.Forms.Keys.S)));
			this.saveRightToolStripMenuItem.Size = new System.Drawing.Size(261, 22);
			this.saveRightToolStripMenuItem.Text = "Save &Right...";
			// 
			// toolStripSeparator4
			// 
			this.toolStripSeparator4.Name = "toolStripSeparator4";
			this.toolStripSeparator4.Size = new System.Drawing.Size(153, 6);
			// 
			// exitToolStripMenuItem
			// 
			this.exitToolStripMenuItem.Name = "exitToolStripMenuItem";
			this.exitToolStripMenuItem.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.X)));
			this.exitToolStripMenuItem.Size = new System.Drawing.Size(156, 22);
			this.exitToolStripMenuItem.Text = "E&xit";
			this.exitToolStripMenuItem.Click += new System.EventHandler(this.exitToolStripMenuItem_Click);
			// 
			// editToolStripMenuItem
			// 
			this.editToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.undoToolStripMenuItem,
            this.redoToolStripMenuItem});
			this.editToolStripMenuItem.Name = "editToolStripMenuItem";
			this.editToolStripMenuItem.Size = new System.Drawing.Size(43, 20);
			this.editToolStripMenuItem.Text = "&Edit";
			// 
			// undoToolStripMenuItem
			// 
			this.undoToolStripMenuItem.AutoSize = false;
			this.undoToolStripMenuItem.Image = global::Backuper.Properties.Resources.undo;
			this.undoToolStripMenuItem.Name = "undoToolStripMenuItem";
			this.undoToolStripMenuItem.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.Z)));
			this.undoToolStripMenuItem.Size = new System.Drawing.Size(152, 22);
			this.undoToolStripMenuItem.Text = "&Undo";
			// 
			// redoToolStripMenuItem
			// 
			this.redoToolStripMenuItem.Image = global::Backuper.Properties.Resources.redo;
			this.redoToolStripMenuItem.Name = "redoToolStripMenuItem";
			this.redoToolStripMenuItem.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.Y)));
			this.redoToolStripMenuItem.Size = new System.Drawing.Size(153, 22);
			this.redoToolStripMenuItem.Text = "&Redo";
			// 
			// viewToolStripMenuItem
			// 
			this.viewToolStripMenuItem.Name = "viewToolStripMenuItem";
			this.viewToolStripMenuItem.Size = new System.Drawing.Size(49, 20);
			this.viewToolStripMenuItem.Text = "&View";
			// 
			// toolsToolStripMenuItem
			// 
			this.toolsToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.pereferenceToolStripMenuItem});
			this.toolsToolStripMenuItem.Name = "toolsToolStripMenuItem";
			this.toolsToolStripMenuItem.Size = new System.Drawing.Size(52, 20);
			this.toolsToolStripMenuItem.Text = "&Tools";
			// 
			// pereferenceToolStripMenuItem
			// 
			this.pereferenceToolStripMenuItem.Name = "pereferenceToolStripMenuItem";
			this.pereferenceToolStripMenuItem.Size = new System.Drawing.Size(162, 22);
			this.pereferenceToolStripMenuItem.Text = "&Pereference...";
			// 
			// toolStrip1
			// 
			this.toolStrip1.Font = new System.Drawing.Font("Verdana", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.toolStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.tsbOpen,
            this.tsbAddRecursive,
            this.tsbAddFile,
            this.tsbAddFolderShallow,
            this.tsbSave,
            this.toolStripSeparator5,
            this.tsbDelete,
            this.tsbDeleteAllSub,
            this.toolStripSeparator8,
            this.tsbRefresh,
            this.tsbComputeChecksum,
            this.toolStripSeparator6,
            this.tsbCorresponding,
            this.tsbShowInfo,
            this.toolStripSeparator7,
            this.tsbExport});
			this.toolStrip1.Location = new System.Drawing.Point(0, 24);
			this.toolStrip1.Name = "toolStrip1";
			this.toolStrip1.Size = new System.Drawing.Size(669, 25);
			this.toolStrip1.TabIndex = 1;
			this.toolStrip1.Text = "toolStrip1";
			// 
			// tsbOpen
			// 
			this.tsbOpen.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
			this.tsbOpen.Image = global::Backuper.Properties.Resources.open;
			this.tsbOpen.ImageTransparentColor = System.Drawing.Color.Magenta;
			this.tsbOpen.Name = "tsbOpen";
			this.tsbOpen.Size = new System.Drawing.Size(23, 22);
			this.tsbOpen.Text = "Open";
			this.tsbOpen.Click += new System.EventHandler(this.tsbOpen_Click);
			// 
			// tsbAddRecursive
			// 
			this.tsbAddRecursive.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
			this.tsbAddRecursive.Image = global::Backuper.Properties.Resources.add;
			this.tsbAddRecursive.ImageTransparentColor = System.Drawing.Color.Magenta;
			this.tsbAddRecursive.Name = "tsbAddRecursive";
			this.tsbAddRecursive.Size = new System.Drawing.Size(23, 22);
			this.tsbAddRecursive.Text = "Add Folder Recursive";
			this.tsbAddRecursive.Click += new System.EventHandler(this.tsbAddFolder_Click);
			// 
			// tsbAddFile
			// 
			this.tsbAddFile.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
			this.tsbAddFile.Image = global::Backuper.Properties.Resources.add_file;
			this.tsbAddFile.ImageTransparentColor = System.Drawing.Color.Magenta;
			this.tsbAddFile.Name = "tsbAddFile";
			this.tsbAddFile.Size = new System.Drawing.Size(23, 22);
			this.tsbAddFile.Text = "Add File";
			this.tsbAddFile.Click += new System.EventHandler(this.tsbAddFile_Click);
			// 
			// tsbAddFolderShallow
			// 
			this.tsbAddFolderShallow.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
			this.tsbAddFolderShallow.Image = global::Backuper.Properties.Resources.add_folder;
			this.tsbAddFolderShallow.ImageTransparentColor = System.Drawing.Color.Magenta;
			this.tsbAddFolderShallow.Name = "tsbAddFolderShallow";
			this.tsbAddFolderShallow.Size = new System.Drawing.Size(23, 22);
			this.tsbAddFolderShallow.Text = "Add Folder Shallow";
			this.tsbAddFolderShallow.Click += new System.EventHandler(this.tsbAddFolder_Click);
			// 
			// tsbSave
			// 
			this.tsbSave.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
			this.tsbSave.Image = global::Backuper.Properties.Resources.save;
			this.tsbSave.ImageTransparentColor = System.Drawing.Color.Magenta;
			this.tsbSave.Name = "tsbSave";
			this.tsbSave.Size = new System.Drawing.Size(23, 22);
			this.tsbSave.Text = "Save";
			this.tsbSave.Click += new System.EventHandler(this.tsbSave_Click);
			// 
			// toolStripSeparator5
			// 
			this.toolStripSeparator5.Name = "toolStripSeparator5";
			this.toolStripSeparator5.Size = new System.Drawing.Size(6, 25);
			// 
			// tsbDelete
			// 
			this.tsbDelete.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
			this.tsbDelete.Image = global::Backuper.Properties.Resources.delete;
			this.tsbDelete.ImageTransparentColor = System.Drawing.Color.Magenta;
			this.tsbDelete.Name = "tsbDelete";
			this.tsbDelete.Size = new System.Drawing.Size(23, 22);
			this.tsbDelete.Text = "toolStripButton1";
			this.tsbDelete.Click += new System.EventHandler(this.tsbDelete_Click);
			// 
			// tsbDeleteAllSub
			// 
			this.tsbDeleteAllSub.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
			this.tsbDeleteAllSub.Image = global::Backuper.Properties.Resources.trash;
			this.tsbDeleteAllSub.ImageTransparentColor = System.Drawing.Color.Magenta;
			this.tsbDeleteAllSub.Name = "tsbDeleteAllSub";
			this.tsbDeleteAllSub.Size = new System.Drawing.Size(23, 22);
			this.tsbDeleteAllSub.Text = "toolStripButton2";
			this.tsbDeleteAllSub.Click += new System.EventHandler(this.tsbDeleteAllSub_Click);
			// 
			// toolStripSeparator8
			// 
			this.toolStripSeparator8.Name = "toolStripSeparator8";
			this.toolStripSeparator8.Size = new System.Drawing.Size(6, 25);
			// 
			// tsbRefresh
			// 
			this.tsbRefresh.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
			this.tsbRefresh.Image = global::Backuper.Properties.Resources.refresh;
			this.tsbRefresh.ImageTransparentColor = System.Drawing.Color.Magenta;
			this.tsbRefresh.Name = "tsbRefresh";
			this.tsbRefresh.Size = new System.Drawing.Size(23, 22);
			this.tsbRefresh.Text = "Refresh";
			this.tsbRefresh.Click += new System.EventHandler(this.tsbRefresh_Click);
			// 
			// tsbComputeChecksum
			// 
			this.tsbComputeChecksum.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
			this.tsbComputeChecksum.Image = global::Backuper.Properties.Resources.applications;
			this.tsbComputeChecksum.ImageTransparentColor = System.Drawing.Color.Magenta;
			this.tsbComputeChecksum.Name = "tsbComputeChecksum";
			this.tsbComputeChecksum.Size = new System.Drawing.Size(23, 22);
			this.tsbComputeChecksum.Text = "Compute Checksum";
			this.tsbComputeChecksum.Click += new System.EventHandler(this.tsbComputeChecksum_Click);
			// 
			// toolStripSeparator6
			// 
			this.toolStripSeparator6.Name = "toolStripSeparator6";
			this.toolStripSeparator6.Size = new System.Drawing.Size(6, 25);
			// 
			// tsbCorresponding
			// 
			this.tsbCorresponding.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
			this.tsbCorresponding.Image = global::Backuper.Properties.Resources.web_link;
			this.tsbCorresponding.ImageTransparentColor = System.Drawing.Color.Magenta;
			this.tsbCorresponding.Name = "tsbCorresponding";
			this.tsbCorresponding.Size = new System.Drawing.Size(23, 22);
			this.tsbCorresponding.Text = "Set Corresponding";
			// 
			// tsbShowInfo
			// 
			this.tsbShowInfo.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
			this.tsbShowInfo.Image = global::Backuper.Properties.Resources.info2;
			this.tsbShowInfo.ImageTransparentColor = System.Drawing.Color.Magenta;
			this.tsbShowInfo.Name = "tsbShowInfo";
			this.tsbShowInfo.Size = new System.Drawing.Size(23, 22);
			this.tsbShowInfo.Text = "Show Info";
			this.tsbShowInfo.Click += new System.EventHandler(this.tsbShowInfo_Click);
			// 
			// toolStripSeparator7
			// 
			this.toolStripSeparator7.Name = "toolStripSeparator7";
			this.toolStripSeparator7.Size = new System.Drawing.Size(6, 25);
			// 
			// tsbExport
			// 
			this.tsbExport.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
			this.tsbExport.Image = global::Backuper.Properties.Resources.export;
			this.tsbExport.ImageTransparentColor = System.Drawing.Color.Magenta;
			this.tsbExport.Name = "tsbExport";
			this.tsbExport.Size = new System.Drawing.Size(23, 22);
			this.tsbExport.Text = "Export";
			this.tsbExport.Click += new System.EventHandler(this.tsbExport_Click);
			// 
			// imgLst
			// 
			this.imgLst.ImageStream = ((System.Windows.Forms.ImageListStreamer)(resources.GetObject("imgLst.ImageStream")));
			this.imgLst.TransparentColor = System.Drawing.Color.Transparent;
			this.imgLst.Images.SetKeyName(0, "File.ico");
			this.imgLst.Images.SetKeyName(1, "FolderClosed.ico");
			this.imgLst.Images.SetKeyName(2, "FolderOpen.ico");
			// 
			// cmsTreeItem
			// 
			this.cmsTreeItem.Font = new System.Drawing.Font("Verdana", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.cmsTreeItem.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.tsmiAddFolderShallow,
            this.tsmiAddFolderRecursive,
            this.tsmiAddFiles,
            this.toolStripSeparator1,
            this.tsmiAddFolderAsSub,
            this.tsmiAddFolderRecursiveAsSubNode,
            this.toolStripMenuItem3,
            this.tsmiDelete,
            this.tsmiDeleteAllSub,
            this.toolStripSeparator2,
            this.tsmiRemoveCorrNode,
            this.toolStripSeparator3,
            this.tsmiShowInfo});
			this.cmsTreeItem.Name = "cmsTreeItem";
			this.cmsTreeItem.Size = new System.Drawing.Size(282, 226);
			// 
			// tsmiAddFolderShallow
			// 
			this.tsmiAddFolderShallow.Image = global::Backuper.Properties.Resources.add;
			this.tsmiAddFolderShallow.Name = "tsmiAddFolderShallow";
			this.tsmiAddFolderShallow.Size = new System.Drawing.Size(281, 22);
			this.tsmiAddFolderShallow.Text = "Add One-Level Folder...";
			this.tsmiAddFolderShallow.Click += new System.EventHandler(this.tsmiAddFolder_Click);
			// 
			// tsmiAddFolderRecursive
			// 
			this.tsmiAddFolderRecursive.Image = global::Backuper.Properties.Resources.add_folder;
			this.tsmiAddFolderRecursive.Name = "tsmiAddFolderRecursive";
			this.tsmiAddFolderRecursive.Size = new System.Drawing.Size(281, 22);
			this.tsmiAddFolderRecursive.Text = "Add Folder Recursive...";
			this.tsmiAddFolderRecursive.Click += new System.EventHandler(this.tsmiAddFolder_Click);
			// 
			// tsmiAddFiles
			// 
			this.tsmiAddFiles.Image = global::Backuper.Properties.Resources.add_file;
			this.tsmiAddFiles.Name = "tsmiAddFiles";
			this.tsmiAddFiles.Size = new System.Drawing.Size(281, 22);
			this.tsmiAddFiles.Text = "Add Files...";
			this.tsmiAddFiles.Click += new System.EventHandler(this.tsmiAddFiles_Click);
			// 
			// toolStripSeparator1
			// 
			this.toolStripSeparator1.Name = "toolStripSeparator1";
			this.toolStripSeparator1.Size = new System.Drawing.Size(278, 6);
			// 
			// tsmiAddFolderAsSub
			// 
			this.tsmiAddFolderAsSub.Name = "tsmiAddFolderAsSub";
			this.tsmiAddFolderAsSub.Size = new System.Drawing.Size(281, 22);
			this.tsmiAddFolderAsSub.Text = "Add One-Level Folder As Subnode...";
			this.tsmiAddFolderAsSub.Click += new System.EventHandler(this.tsmiAddFolderAsSub_Click);
			// 
			// tsmiAddFolderRecursiveAsSubNode
			// 
			this.tsmiAddFolderRecursiveAsSubNode.Name = "tsmiAddFolderRecursiveAsSubNode";
			this.tsmiAddFolderRecursiveAsSubNode.Size = new System.Drawing.Size(281, 22);
			this.tsmiAddFolderRecursiveAsSubNode.Text = "Add Folder Recursive As Subnode...";
			this.tsmiAddFolderRecursiveAsSubNode.Click += new System.EventHandler(this.tsmiAddFolderAsSub_Click);
			// 
			// toolStripMenuItem3
			// 
			this.toolStripMenuItem3.Name = "toolStripMenuItem3";
			this.toolStripMenuItem3.Size = new System.Drawing.Size(278, 6);
			// 
			// tsmiDelete
			// 
			this.tsmiDelete.Image = global::Backuper.Properties.Resources.delete;
			this.tsmiDelete.Name = "tsmiDelete";
			this.tsmiDelete.Size = new System.Drawing.Size(281, 22);
			this.tsmiDelete.Text = "Delete";
			this.tsmiDelete.Click += new System.EventHandler(this.tmsiDelete_Click);
			// 
			// tsmiDeleteAllSub
			// 
			this.tsmiDeleteAllSub.Image = global::Backuper.Properties.Resources.trash;
			this.tsmiDeleteAllSub.Name = "tsmiDeleteAllSub";
			this.tsmiDeleteAllSub.Size = new System.Drawing.Size(281, 22);
			this.tsmiDeleteAllSub.Text = "Delete All Subnodes";
			this.tsmiDeleteAllSub.Click += new System.EventHandler(this.tsmiDeleteAllSub_Click);
			// 
			// toolStripSeparator2
			// 
			this.toolStripSeparator2.Name = "toolStripSeparator2";
			this.toolStripSeparator2.Size = new System.Drawing.Size(278, 6);
			// 
			// tsmiRemoveCorrNode
			// 
			this.tsmiRemoveCorrNode.Enabled = false;
			this.tsmiRemoveCorrNode.Image = global::Backuper.Properties.Resources.cancel1;
			this.tsmiRemoveCorrNode.Name = "tsmiRemoveCorrNode";
			this.tsmiRemoveCorrNode.Size = new System.Drawing.Size(281, 22);
			this.tsmiRemoveCorrNode.Text = "Remove Corresponding Node...";
			// 
			// toolStripSeparator3
			// 
			this.toolStripSeparator3.Name = "toolStripSeparator3";
			this.toolStripSeparator3.Size = new System.Drawing.Size(278, 6);
			// 
			// tsmiShowInfo
			// 
			this.tsmiShowInfo.Image = global::Backuper.Properties.Resources.info2;
			this.tsmiShowInfo.Name = "tsmiShowInfo";
			this.tsmiShowInfo.Size = new System.Drawing.Size(281, 22);
			this.tsmiShowInfo.Text = "Show Information...";
			this.tsmiShowInfo.Click += new System.EventHandler(this.tsmiShowInfo_Click);
			// 
			// BottomToolStripPanel
			// 
			this.BottomToolStripPanel.Location = new System.Drawing.Point(0, 0);
			this.BottomToolStripPanel.Name = "BottomToolStripPanel";
			this.BottomToolStripPanel.Orientation = System.Windows.Forms.Orientation.Horizontal;
			this.BottomToolStripPanel.RowMargin = new System.Windows.Forms.Padding(3, 0, 0, 0);
			this.BottomToolStripPanel.Size = new System.Drawing.Size(0, 0);
			// 
			// TopToolStripPanel
			// 
			this.TopToolStripPanel.Location = new System.Drawing.Point(0, 0);
			this.TopToolStripPanel.Name = "TopToolStripPanel";
			this.TopToolStripPanel.Orientation = System.Windows.Forms.Orientation.Horizontal;
			this.TopToolStripPanel.RowMargin = new System.Windows.Forms.Padding(3, 0, 0, 0);
			this.TopToolStripPanel.Size = new System.Drawing.Size(0, 0);
			// 
			// RightToolStripPanel
			// 
			this.RightToolStripPanel.Location = new System.Drawing.Point(0, 0);
			this.RightToolStripPanel.Name = "RightToolStripPanel";
			this.RightToolStripPanel.Orientation = System.Windows.Forms.Orientation.Horizontal;
			this.RightToolStripPanel.RowMargin = new System.Windows.Forms.Padding(3, 0, 0, 0);
			this.RightToolStripPanel.Size = new System.Drawing.Size(0, 0);
			// 
			// LeftToolStripPanel
			// 
			this.LeftToolStripPanel.Location = new System.Drawing.Point(0, 0);
			this.LeftToolStripPanel.Name = "LeftToolStripPanel";
			this.LeftToolStripPanel.Orientation = System.Windows.Forms.Orientation.Horizontal;
			this.LeftToolStripPanel.RowMargin = new System.Windows.Forms.Padding(3, 0, 0, 0);
			this.LeftToolStripPanel.Size = new System.Drawing.Size(0, 0);
			// 
			// ContentPanel
			// 
			this.ContentPanel.Size = new System.Drawing.Size(150, 175);
			// 
			// statusStrip1
			// 
			this.statusStrip1.Location = new System.Drawing.Point(0, 360);
			this.statusStrip1.Name = "statusStrip1";
			this.statusStrip1.Size = new System.Drawing.Size(669, 22);
			this.statusStrip1.TabIndex = 2;
			this.statusStrip1.Text = "statusStrip1";
			// 
			// splitContainer1
			// 
			this.splitContainer1.Dock = System.Windows.Forms.DockStyle.Fill;
			this.splitContainer1.Location = new System.Drawing.Point(0, 49);
			this.splitContainer1.Name = "splitContainer1";
			// 
			// splitContainer1.Panel1
			// 
			this.splitContainer1.Panel1.Controls.Add(this.ltv);
			// 
			// splitContainer1.Panel2
			// 
			this.splitContainer1.Panel2.Controls.Add(this.rtv);
			this.splitContainer1.Size = new System.Drawing.Size(669, 311);
			this.splitContainer1.SplitterDistance = 331;
			this.splitContainer1.TabIndex = 3;
			// 
			// ltv
			// 
			this.ltv.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(224)))), ((int)(((byte)(224)))), ((int)(((byte)(224)))));
			this.ltv.Dock = System.Windows.Forms.DockStyle.Fill;
			this.ltv.ImageIndex = 0;
			this.ltv.ImageList = this.imgLst;
			this.ltv.Location = new System.Drawing.Point(0, 0);
			this.ltv.Name = "ltv";
			this.ltv.PathSeparator = "/";
			this.ltv.SelectedImageIndex = 0;
			this.ltv.Size = new System.Drawing.Size(331, 311);
			this.ltv.TabIndex = 0;
			this.ltv.NodeMouseDoubleClick += new System.Windows.Forms.TreeNodeMouseClickEventHandler(this.tv_NodeMouseDoubleClick);
			this.ltv.NodeMouseClick += new System.Windows.Forms.TreeNodeMouseClickEventHandler(this.tv_NodeMouseClick);
			// 
			// rtv
			// 
			this.rtv.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(224)))), ((int)(((byte)(224)))), ((int)(((byte)(224)))));
			this.rtv.Dock = System.Windows.Forms.DockStyle.Fill;
			this.rtv.ImageIndex = 0;
			this.rtv.ImageList = this.imgLst;
			this.rtv.Location = new System.Drawing.Point(0, 0);
			this.rtv.Name = "rtv";
			this.rtv.PathSeparator = "/";
			this.rtv.SelectedImageIndex = 0;
			this.rtv.Size = new System.Drawing.Size(334, 311);
			this.rtv.TabIndex = 0;
			this.rtv.NodeMouseDoubleClick += new System.Windows.Forms.TreeNodeMouseClickEventHandler(this.tv_NodeMouseDoubleClick);
			this.rtv.NodeMouseClick += new System.Windows.Forms.TreeNodeMouseClickEventHandler(this.tv_NodeMouseClick);
			// 
			// Backuper
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 14F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(669, 382);
			this.Controls.Add(this.splitContainer1);
			this.Controls.Add(this.toolStrip1);
			this.Controls.Add(this.menuStrip1);
			this.Controls.Add(this.statusStrip1);
			this.Font = new System.Drawing.Font("Verdana", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.MainMenuStrip = this.menuStrip1;
			this.Margin = new System.Windows.Forms.Padding(4, 3, 4, 3);
			this.Name = "Backuper";
			this.Text = "Backup Guy";
			this.Load += new System.EventHandler(this.Backuper_Load);
			this.menuStrip1.ResumeLayout(false);
			this.menuStrip1.PerformLayout();
			this.toolStrip1.ResumeLayout(false);
			this.toolStrip1.PerformLayout();
			this.cmsTreeItem.ResumeLayout(false);
			this.splitContainer1.Panel1.ResumeLayout(false);
			this.splitContainer1.Panel2.ResumeLayout(false);
			this.splitContainer1.ResumeLayout(false);
			this.ResumeLayout(false);
			this.PerformLayout();

		}

		#endregion

		private System.Windows.Forms.MenuStrip menuStrip1;
		private System.Windows.Forms.ToolStrip toolStrip1;
		private System.Windows.Forms.ToolStripMenuItem tmsiFile;
		private System.Windows.Forms.ToolStripMenuItem openToolStripMenuItem;
		private System.Windows.Forms.ToolStripMenuItem viewToolStripMenuItem;
		private System.Windows.Forms.ToolStripMenuItem toolsToolStripMenuItem;
		private System.Windows.Forms.ToolStripMenuItem pereferenceToolStripMenuItem;
		private System.Windows.Forms.ToolStripMenuItem openLeftToolStripMenuItem;
		private System.Windows.Forms.ToolStripMenuItem openRightToolStripMenuItem;
		private System.Windows.Forms.ContextMenuStrip cmsTreeItem;
		private System.Windows.Forms.ToolStripMenuItem tsmiAddFolderShallow;
		private System.Windows.Forms.ToolStripMenuItem tsmiAddFiles;
		private System.Windows.Forms.ToolStripMenuItem tsmiAddFolderRecursive;
		private System.Windows.Forms.ToolStripSeparator toolStripSeparator1;
		private System.Windows.Forms.ToolStripMenuItem tsmiDelete;
		private System.Windows.Forms.ToolStripSeparator toolStripSeparator2;
		private System.Windows.Forms.ToolStripMenuItem saveToolStripMenuItem;
		private System.Windows.Forms.ToolStripMenuItem saveLeftToolStripMenuItem;
		private System.Windows.Forms.ToolStripMenuItem saveRightToolStripMenuItem;
		private System.Windows.Forms.ToolStripSeparator toolStripSeparator4;
		private System.Windows.Forms.ToolStripMenuItem exitToolStripMenuItem;
		private System.Windows.Forms.ToolStripMenuItem editToolStripMenuItem;
		private System.Windows.Forms.ToolStripMenuItem undoToolStripMenuItem;
		private System.Windows.Forms.ToolStripMenuItem redoToolStripMenuItem;
		private System.Windows.Forms.ToolStripMenuItem tsmiShowInfo;
		private System.Windows.Forms.ImageList imgLst;
		private System.Windows.Forms.ToolStripMenuItem tsmiAddFolderAsSub;
		private System.Windows.Forms.ToolStripMenuItem tsmiAddFolderRecursiveAsSubNode;
		private System.Windows.Forms.ToolStripSeparator toolStripMenuItem3;
		private System.Windows.Forms.ToolStripMenuItem tsmiDeleteAllSub;
		private System.Windows.Forms.ToolStripButton tsbRefresh;
		private System.Windows.Forms.ToolStripButton tsbSave;
		private System.Windows.Forms.ToolStripButton tsbCorresponding;
		private System.Windows.Forms.ToolStripButton tsbShowInfo;
		private System.Windows.Forms.ToolStripMenuItem tsmiRemoveCorrNode;
		private System.Windows.Forms.ToolStripSeparator toolStripSeparator3;
		private System.Windows.Forms.ToolStripPanel BottomToolStripPanel;
		private System.Windows.Forms.ToolStripPanel TopToolStripPanel;
		private System.Windows.Forms.ToolStripPanel RightToolStripPanel;
		private System.Windows.Forms.ToolStripPanel LeftToolStripPanel;
		private System.Windows.Forms.ToolStripContentPanel ContentPanel;
		private System.Windows.Forms.StatusStrip statusStrip1;
		private System.Windows.Forms.SplitContainer splitContainer1;
		private System.Windows.Forms.TreeView ltv;
		private System.Windows.Forms.TreeView rtv;
		private System.Windows.Forms.ToolStripButton tsbOpen;
		private System.Windows.Forms.ToolStripSeparator toolStripSeparator5;
		private System.Windows.Forms.ToolStripButton tsbComputeChecksum;
		private System.Windows.Forms.ToolStripSeparator toolStripSeparator6;
		private System.Windows.Forms.ToolStripButton tsbAddRecursive;
		private System.Windows.Forms.ToolStripButton tsbAddFile;
		private System.Windows.Forms.ToolStripButton tsbAddFolderShallow;
		private System.Windows.Forms.ToolStripSeparator toolStripSeparator7;
		private System.Windows.Forms.ToolStripButton tsbExport;
		private System.Windows.Forms.ToolStripButton tsbDelete;
		private System.Windows.Forms.ToolStripButton tsbDeleteAllSub;
		private System.Windows.Forms.ToolStripSeparator toolStripSeparator8;
	}
}

