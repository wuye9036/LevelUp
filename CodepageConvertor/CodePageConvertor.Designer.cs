namespace CodepageConvertor {
	partial class CodePageConvertor {
		/// <summary>
		/// 必需的设计器变量。
		/// </summary>
		private System.ComponentModel.IContainer components = null;

		/// <summary>
		/// 清理所有正在使用的资源。
		/// </summary>
		/// <param name="disposing">如果应释放托管资源，为 true；否则为 false。</param>
		protected override void Dispose( bool disposing ) {
			if ( disposing && ( components != null ) ) {
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
			this.tableLayoutPanel1 = new System.Windows.Forms.TableLayoutPanel();
			this.label1 = new System.Windows.Forms.Label();
			this.comboSrcCodePage = new System.Windows.Forms.ComboBox();
			this.btnAutoSelectedCodePage = new System.Windows.Forms.Button();
			this.label2 = new System.Windows.Forms.Label();
			this.comboTargetCodePage = new System.Windows.Forms.ComboBox();
			this.tbContent = new System.Windows.Forms.TextBox();
			this.tableLayoutPanel2 = new System.Windows.Forms.TableLayoutPanel();
			this.btnOpen = new System.Windows.Forms.Button();
			this.btnSaveAs = new System.Windows.Forms.Button();
			this.btnFromClipboard = new System.Windows.Forms.Button();
			this.btnToClipboard = new System.Windows.Forms.Button();
			this.btnConvert = new System.Windows.Forms.Button();
			this.btnSave = new System.Windows.Forms.Button();
			this.tableLayoutPanel1.SuspendLayout();
			this.tableLayoutPanel2.SuspendLayout();
			this.SuspendLayout();
			// 
			// tableLayoutPanel1
			// 
			this.tableLayoutPanel1.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
						| System.Windows.Forms.AnchorStyles.Left)
						| System.Windows.Forms.AnchorStyles.Right)));
			this.tableLayoutPanel1.ColumnCount = 6;
			this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle());
			this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle());
			this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle());
			this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 100F));
			this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle());
			this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle());
			this.tableLayoutPanel1.Controls.Add(this.label1, 0, 0);
			this.tableLayoutPanel1.Controls.Add(this.comboSrcCodePage, 1, 0);
			this.tableLayoutPanel1.Controls.Add(this.btnAutoSelectedCodePage, 2, 0);
			this.tableLayoutPanel1.Controls.Add(this.label2, 4, 0);
			this.tableLayoutPanel1.Controls.Add(this.comboTargetCodePage, 5, 0);
			this.tableLayoutPanel1.Controls.Add(this.tbContent, 0, 1);
			this.tableLayoutPanel1.Controls.Add(this.tableLayoutPanel2, 0, 2);
			this.tableLayoutPanel1.Location = new System.Drawing.Point(11, 15);
			this.tableLayoutPanel1.Margin = new System.Windows.Forms.Padding(20, 22, 20, 22);
			this.tableLayoutPanel1.Name = "tableLayoutPanel1";
			this.tableLayoutPanel1.RowCount = 3;
			this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle());
			this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 100F));
			this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle());
			this.tableLayoutPanel1.Size = new System.Drawing.Size(769, 486);
			this.tableLayoutPanel1.TabIndex = 0;
			// 
			// label1
			// 
			this.label1.AutoSize = true;
			this.label1.Dock = System.Windows.Forms.DockStyle.Fill;
			this.label1.Location = new System.Drawing.Point(3, 0);
			this.label1.Name = "label1";
			this.label1.Size = new System.Drawing.Size(55, 39);
			this.label1.TabIndex = 0;
			this.label1.Text = "源代码页";
			this.label1.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
			// 
			// comboSrcCodePage
			// 
			this.comboSrcCodePage.AutoCompleteMode = System.Windows.Forms.AutoCompleteMode.Suggest;
			this.comboSrcCodePage.AutoCompleteSource = System.Windows.Forms.AutoCompleteSource.ListItems;
			this.comboSrcCodePage.Dock = System.Windows.Forms.DockStyle.Fill;
			this.comboSrcCodePage.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
			this.comboSrcCodePage.FormattingEnabled = true;
			this.comboSrcCodePage.Location = new System.Drawing.Point(69, 9);
			this.comboSrcCodePage.Margin = new System.Windows.Forms.Padding(8, 9, 8, 9);
			this.comboSrcCodePage.Name = "comboSrcCodePage";
			this.comboSrcCodePage.Size = new System.Drawing.Size(240, 21);
			this.comboSrcCodePage.TabIndex = 1;
			// 
			// btnAutoSelectedCodePage
			// 
			this.btnAutoSelectedCodePage.AutoSize = true;
			this.btnAutoSelectedCodePage.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
			this.btnAutoSelectedCodePage.Dock = System.Windows.Forms.DockStyle.Fill;
			this.btnAutoSelectedCodePage.Location = new System.Drawing.Point(322, 5);
			this.btnAutoSelectedCodePage.Margin = new System.Windows.Forms.Padding(5);
			this.btnAutoSelectedCodePage.Name = "btnAutoSelectedCodePage";
			this.btnAutoSelectedCodePage.Size = new System.Drawing.Size(65, 29);
			this.btnAutoSelectedCodePage.TabIndex = 2;
			this.btnAutoSelectedCodePage.Text = "自动选择";
			this.btnAutoSelectedCodePage.UseVisualStyleBackColor = true;
			// 
			// label2
			// 
			this.label2.AutoSize = true;
			this.label2.Dock = System.Windows.Forms.DockStyle.Fill;
			this.label2.Location = new System.Drawing.Point(443, 0);
			this.label2.Name = "label2";
			this.label2.Size = new System.Drawing.Size(67, 39);
			this.label2.TabIndex = 3;
			this.label2.Text = "目标代码页";
			this.label2.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
			// 
			// comboTargetCodePage
			// 
			this.comboTargetCodePage.Dock = System.Windows.Forms.DockStyle.Fill;
			this.comboTargetCodePage.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
			this.comboTargetCodePage.FormattingEnabled = true;
			this.comboTargetCodePage.Location = new System.Drawing.Point(521, 9);
			this.comboTargetCodePage.Margin = new System.Windows.Forms.Padding(8, 9, 8, 9);
			this.comboTargetCodePage.Name = "comboTargetCodePage";
			this.comboTargetCodePage.Size = new System.Drawing.Size(240, 21);
			this.comboTargetCodePage.TabIndex = 4;
			// 
			// tbContent
			// 
			this.tbContent.AllowDrop = true;
			this.tableLayoutPanel1.SetColumnSpan(this.tbContent, 6);
			this.tbContent.Dock = System.Windows.Forms.DockStyle.Fill;
			this.tbContent.Location = new System.Drawing.Point(3, 42);
			this.tbContent.MaxLength = 1024000;
			this.tbContent.Multiline = true;
			this.tbContent.Name = "tbContent";
			this.tbContent.ScrollBars = System.Windows.Forms.ScrollBars.Both;
			this.tbContent.Size = new System.Drawing.Size(763, 406);
			this.tbContent.TabIndex = 5;
			this.tbContent.DragDrop += new System.Windows.Forms.DragEventHandler(this.tbContent_DragDrop);
			this.tbContent.DragEnter += new System.Windows.Forms.DragEventHandler(this.tbContent_DragEnter);
			// 
			// tableLayoutPanel2
			// 
			this.tableLayoutPanel2.AutoSize = true;
			this.tableLayoutPanel2.ColumnCount = 7;
			this.tableLayoutPanel1.SetColumnSpan(this.tableLayoutPanel2, 6);
			this.tableLayoutPanel2.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle());
			this.tableLayoutPanel2.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 100F));
			this.tableLayoutPanel2.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle());
			this.tableLayoutPanel2.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle());
			this.tableLayoutPanel2.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle());
			this.tableLayoutPanel2.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle());
			this.tableLayoutPanel2.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle());
			this.tableLayoutPanel2.Controls.Add(this.btnOpen, 2, 0);
			this.tableLayoutPanel2.Controls.Add(this.btnSaveAs, 4, 0);
			this.tableLayoutPanel2.Controls.Add(this.btnFromClipboard, 6, 0);
			this.tableLayoutPanel2.Controls.Add(this.btnToClipboard, 5, 0);
			this.tableLayoutPanel2.Controls.Add(this.btnConvert, 0, 0);
			this.tableLayoutPanel2.Controls.Add(this.btnSave, 3, 0);
			this.tableLayoutPanel2.Dock = System.Windows.Forms.DockStyle.Fill;
			this.tableLayoutPanel2.Location = new System.Drawing.Point(3, 454);
			this.tableLayoutPanel2.Name = "tableLayoutPanel2";
			this.tableLayoutPanel2.RowCount = 1;
			this.tableLayoutPanel2.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 100F));
			this.tableLayoutPanel2.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 20F));
			this.tableLayoutPanel2.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 20F));
			this.tableLayoutPanel2.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 20F));
			this.tableLayoutPanel2.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 20F));
			this.tableLayoutPanel2.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 20F));
			this.tableLayoutPanel2.Size = new System.Drawing.Size(763, 29);
			this.tableLayoutPanel2.TabIndex = 6;
			// 
			// btnOpen
			// 
			this.btnOpen.AutoSize = true;
			this.btnOpen.Location = new System.Drawing.Point(333, 3);
			this.btnOpen.Name = "btnOpen";
			this.btnOpen.Size = new System.Drawing.Size(75, 23);
			this.btnOpen.TabIndex = 0;
			this.btnOpen.Text = "打开";
			this.btnOpen.UseVisualStyleBackColor = true;
			this.btnOpen.Click += new System.EventHandler(this.btnOpen_Click);
			// 
			// btnSaveAs
			// 
			this.btnSaveAs.AutoSize = true;
			this.btnSaveAs.Location = new System.Drawing.Point(495, 3);
			this.btnSaveAs.Name = "btnSaveAs";
			this.btnSaveAs.Size = new System.Drawing.Size(75, 23);
			this.btnSaveAs.TabIndex = 1;
			this.btnSaveAs.Text = "另存为";
			this.btnSaveAs.UseVisualStyleBackColor = true;
			this.btnSaveAs.Click += new System.EventHandler(this.btnSaveAs_Click);
			// 
			// btnFromClipboard
			// 
			this.btnFromClipboard.AutoSize = true;
			this.btnFromClipboard.Location = new System.Drawing.Point(671, 3);
			this.btnFromClipboard.Name = "btnFromClipboard";
			this.btnFromClipboard.Size = new System.Drawing.Size(89, 23);
			this.btnFromClipboard.TabIndex = 2;
			this.btnFromClipboard.Text = "从剪贴板读入";
			this.btnFromClipboard.UseVisualStyleBackColor = true;
			this.btnFromClipboard.Click += new System.EventHandler(this.btnFromClipboard_Click);
			// 
			// btnToClipboard
			// 
			this.btnToClipboard.AutoSize = true;
			this.btnToClipboard.Location = new System.Drawing.Point(576, 3);
			this.btnToClipboard.Name = "btnToClipboard";
			this.btnToClipboard.Size = new System.Drawing.Size(89, 23);
			this.btnToClipboard.TabIndex = 3;
			this.btnToClipboard.Text = "保存至剪贴板";
			this.btnToClipboard.UseVisualStyleBackColor = true;
			this.btnToClipboard.Click += new System.EventHandler(this.btnToClipboard_Click);
			// 
			// btnConvert
			// 
			this.btnConvert.AutoSize = true;
			this.btnConvert.Location = new System.Drawing.Point(3, 3);
			this.btnConvert.Name = "btnConvert";
			this.btnConvert.Size = new System.Drawing.Size(75, 23);
			this.btnConvert.TabIndex = 4;
			this.btnConvert.Text = "转换";
			this.btnConvert.UseVisualStyleBackColor = true;
			this.btnConvert.Click += new System.EventHandler(this.btnConvert_Click);
			// 
			// btnSave
			// 
			this.btnSave.Location = new System.Drawing.Point(414, 3);
			this.btnSave.Name = "btnSave";
			this.btnSave.Size = new System.Drawing.Size(75, 23);
			this.btnSave.TabIndex = 5;
			this.btnSave.Text = "保存";
			this.btnSave.UseVisualStyleBackColor = true;
			this.btnSave.Click += new System.EventHandler(this.btnSave_Click);
			// 
			// CodePageConvertor
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(784, 501);
			this.Controls.Add(this.tableLayoutPanel1);
			this.MaximizeBox = false;
			this.MaximumSize = new System.Drawing.Size(800, 539);
			this.MinimumSize = new System.Drawing.Size(800, 539);
			this.Name = "CodePageConvertor";
			this.Text = "代码页转换工具";
			this.tableLayoutPanel1.ResumeLayout(false);
			this.tableLayoutPanel1.PerformLayout();
			this.tableLayoutPanel2.ResumeLayout(false);
			this.tableLayoutPanel2.PerformLayout();
			this.ResumeLayout(false);

		}

		#endregion

		private System.Windows.Forms.TableLayoutPanel tableLayoutPanel1;
		private System.Windows.Forms.Label label1;
		private System.Windows.Forms.ComboBox comboSrcCodePage;
		private System.Windows.Forms.Button btnAutoSelectedCodePage;
		private System.Windows.Forms.Label label2;
		private System.Windows.Forms.ComboBox comboTargetCodePage;
		private System.Windows.Forms.TextBox tbContent;
		private System.Windows.Forms.TableLayoutPanel tableLayoutPanel2;
		private System.Windows.Forms.Button btnOpen;
		private System.Windows.Forms.Button btnSaveAs;
		private System.Windows.Forms.Button btnFromClipboard;
		private System.Windows.Forms.Button btnToClipboard;
		private System.Windows.Forms.Button btnConvert;
		private System.Windows.Forms.Button btnSave;
	}
}

