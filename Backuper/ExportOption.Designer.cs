namespace Backuper
{
	partial class ExportOption
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
			this.groupBox1 = new System.Windows.Forms.GroupBox();
			this.rbExportNew = new System.Windows.Forms.RadioButton();
			this.rbExportCommon = new System.Windows.Forms.RadioButton();
			this.groupBox3 = new System.Windows.Forms.GroupBox();
			this.tbXMLPath = new System.Windows.Forms.TextBox();
			this.tbTextPath = new System.Windows.Forms.TextBox();
			this.btnOpenXMLFile = new System.Windows.Forms.Button();
			this.btnOpenTextFile = new System.Windows.Forms.Button();
			this.btnOpenMoveDestDir = new System.Windows.Forms.Button();
			this.btnOpenCopyDestDir = new System.Windows.Forms.Button();
			this.tbCopyFilePath = new System.Windows.Forms.TextBox();
			this.tbMoveFilePath = new System.Windows.Forms.TextBox();
			this.rbMoveFiles = new System.Windows.Forms.RadioButton();
			this.rbCopyFiles = new System.Windows.Forms.RadioButton();
			this.rbText = new System.Windows.Forms.RadioButton();
			this.rbXML = new System.Windows.Forms.RadioButton();
			this.btnOK = new System.Windows.Forms.Button();
			this.btnCancel = new System.Windows.Forms.Button();
			this.groupBox1.SuspendLayout();
			this.groupBox3.SuspendLayout();
			this.SuspendLayout();
			// 
			// groupBox1
			// 
			this.groupBox1.Controls.Add( this.rbExportNew );
			this.groupBox1.Controls.Add( this.rbExportCommon );
			this.groupBox1.Location = new System.Drawing.Point( 382, 12 );
			this.groupBox1.Name = "groupBox1";
			this.groupBox1.Size = new System.Drawing.Size( 204, 175 );
			this.groupBox1.TabIndex = 0;
			this.groupBox1.TabStop = false;
			this.groupBox1.Text = "Export Item";
			// 
			// rbExportNew
			// 
			this.rbExportNew.AutoSize = true;
			this.rbExportNew.Location = new System.Drawing.Point( 26, 73 );
			this.rbExportNew.Name = "rbExportNew";
			this.rbExportNew.Size = new System.Drawing.Size( 90, 17 );
			this.rbExportNew.TabIndex = 1;
			this.rbExportNew.TabStop = true;
			this.rbExportNew.Text = "Export New";
			this.rbExportNew.UseVisualStyleBackColor = true;
			// 
			// rbExportCommon
			// 
			this.rbExportCommon.AutoSize = true;
			this.rbExportCommon.Location = new System.Drawing.Point( 26, 36 );
			this.rbExportCommon.Name = "rbExportCommon";
			this.rbExportCommon.Size = new System.Drawing.Size( 118, 17 );
			this.rbExportCommon.TabIndex = 0;
			this.rbExportCommon.TabStop = true;
			this.rbExportCommon.Text = "Export Common";
			this.rbExportCommon.UseVisualStyleBackColor = true;
			// 
			// groupBox3
			// 
			this.groupBox3.Controls.Add( this.tbXMLPath );
			this.groupBox3.Controls.Add( this.tbTextPath );
			this.groupBox3.Controls.Add( this.btnOpenXMLFile );
			this.groupBox3.Controls.Add( this.btnOpenTextFile );
			this.groupBox3.Controls.Add( this.btnOpenMoveDestDir );
			this.groupBox3.Controls.Add( this.btnOpenCopyDestDir );
			this.groupBox3.Controls.Add( this.tbCopyFilePath );
			this.groupBox3.Controls.Add( this.tbMoveFilePath );
			this.groupBox3.Controls.Add( this.rbMoveFiles );
			this.groupBox3.Controls.Add( this.rbCopyFiles );
			this.groupBox3.Controls.Add( this.rbText );
			this.groupBox3.Controls.Add( this.rbXML );
			this.groupBox3.Location = new System.Drawing.Point( 12, 12 );
			this.groupBox3.Name = "groupBox3";
			this.groupBox3.Size = new System.Drawing.Size( 348, 175 );
			this.groupBox3.TabIndex = 2;
			this.groupBox3.TabStop = false;
			this.groupBox3.Text = "Export Form";
			// 
			// tbXMLPath
			// 
			this.tbXMLPath.Location = new System.Drawing.Point( 96, 18 );
			this.tbXMLPath.Name = "tbXMLPath";
			this.tbXMLPath.ReadOnly = true;
			this.tbXMLPath.Size = new System.Drawing.Size( 202, 21 );
			this.tbXMLPath.TabIndex = 11;
			// 
			// tbTextPath
			// 
			this.tbTextPath.Location = new System.Drawing.Point( 96, 51 );
			this.tbTextPath.Name = "tbTextPath";
			this.tbTextPath.ReadOnly = true;
			this.tbTextPath.Size = new System.Drawing.Size( 202, 21 );
			this.tbTextPath.TabIndex = 10;
			// 
			// btnOpenXMLFile
			// 
			this.btnOpenXMLFile.Location = new System.Drawing.Point( 304, 17 );
			this.btnOpenXMLFile.Name = "btnOpenXMLFile";
			this.btnOpenXMLFile.Size = new System.Drawing.Size( 38, 23 );
			this.btnOpenXMLFile.TabIndex = 9;
			this.btnOpenXMLFile.Text = "...";
			this.btnOpenXMLFile.UseVisualStyleBackColor = true;
			this.btnOpenXMLFile.Click += new System.EventHandler( this.btnOpenXMLFile_Click );
			// 
			// btnOpenTextFile
			// 
			this.btnOpenTextFile.Location = new System.Drawing.Point( 304, 50 );
			this.btnOpenTextFile.Name = "btnOpenTextFile";
			this.btnOpenTextFile.Size = new System.Drawing.Size( 38, 23 );
			this.btnOpenTextFile.TabIndex = 8;
			this.btnOpenTextFile.Text = "...";
			this.btnOpenTextFile.UseVisualStyleBackColor = true;
			this.btnOpenTextFile.Click += new System.EventHandler( this.btnOpenTextFile_Click );
			// 
			// btnOpenMoveDestDir
			// 
			this.btnOpenMoveDestDir.Location = new System.Drawing.Point( 304, 116 );
			this.btnOpenMoveDestDir.Name = "btnOpenMoveDestDir";
			this.btnOpenMoveDestDir.Size = new System.Drawing.Size( 38, 23 );
			this.btnOpenMoveDestDir.TabIndex = 7;
			this.btnOpenMoveDestDir.Text = "...";
			this.btnOpenMoveDestDir.UseVisualStyleBackColor = true;
			this.btnOpenMoveDestDir.Click += new System.EventHandler( this.btnOpenMoveDestDir_Click );
			// 
			// btnOpenCopyDestDir
			// 
			this.btnOpenCopyDestDir.Location = new System.Drawing.Point( 304, 83 );
			this.btnOpenCopyDestDir.Name = "btnOpenCopyDestDir";
			this.btnOpenCopyDestDir.Size = new System.Drawing.Size( 38, 23 );
			this.btnOpenCopyDestDir.TabIndex = 6;
			this.btnOpenCopyDestDir.Text = "...";
			this.btnOpenCopyDestDir.UseVisualStyleBackColor = true;
			this.btnOpenCopyDestDir.Click += new System.EventHandler( this.btnOpenCopyDestDir_Click );
			// 
			// tbCopyFilePath
			// 
			this.tbCopyFilePath.Location = new System.Drawing.Point( 96, 84 );
			this.tbCopyFilePath.Name = "tbCopyFilePath";
			this.tbCopyFilePath.ReadOnly = true;
			this.tbCopyFilePath.Size = new System.Drawing.Size( 202, 21 );
			this.tbCopyFilePath.TabIndex = 5;
			// 
			// tbMoveFilePath
			// 
			this.tbMoveFilePath.Location = new System.Drawing.Point( 96, 117 );
			this.tbMoveFilePath.Name = "tbMoveFilePath";
			this.tbMoveFilePath.ReadOnly = true;
			this.tbMoveFilePath.Size = new System.Drawing.Size( 202, 21 );
			this.tbMoveFilePath.TabIndex = 4;
			// 
			// rbMoveFiles
			// 
			this.rbMoveFiles.AutoSize = true;
			this.rbMoveFiles.Location = new System.Drawing.Point( 6, 119 );
			this.rbMoveFiles.Name = "rbMoveFiles";
			this.rbMoveFiles.Size = new System.Drawing.Size( 84, 17 );
			this.rbMoveFiles.TabIndex = 3;
			this.rbMoveFiles.TabStop = true;
			this.rbMoveFiles.Text = "Move Files";
			this.rbMoveFiles.UseVisualStyleBackColor = true;
			// 
			// rbCopyFiles
			// 
			this.rbCopyFiles.AutoSize = true;
			this.rbCopyFiles.Location = new System.Drawing.Point( 6, 86 );
			this.rbCopyFiles.Name = "rbCopyFiles";
			this.rbCopyFiles.Size = new System.Drawing.Size( 84, 17 );
			this.rbCopyFiles.TabIndex = 2;
			this.rbCopyFiles.TabStop = true;
			this.rbCopyFiles.Text = "Copy Files";
			this.rbCopyFiles.UseVisualStyleBackColor = true;
			// 
			// rbText
			// 
			this.rbText.AutoSize = true;
			this.rbText.Location = new System.Drawing.Point( 6, 53 );
			this.rbText.Name = "rbText";
			this.rbText.Size = new System.Drawing.Size( 50, 17 );
			this.rbText.TabIndex = 1;
			this.rbText.TabStop = true;
			this.rbText.Text = "Text";
			this.rbText.UseVisualStyleBackColor = true;
			// 
			// rbXML
			// 
			this.rbXML.AutoSize = true;
			this.rbXML.Location = new System.Drawing.Point( 6, 20 );
			this.rbXML.Name = "rbXML";
			this.rbXML.Size = new System.Drawing.Size( 48, 17 );
			this.rbXML.TabIndex = 0;
			this.rbXML.TabStop = true;
			this.rbXML.Text = "XML";
			this.rbXML.UseVisualStyleBackColor = true;
			// 
			// btnOK
			// 
			this.btnOK.Location = new System.Drawing.Point( 408, 209 );
			this.btnOK.Name = "btnOK";
			this.btnOK.Size = new System.Drawing.Size( 75, 23 );
			this.btnOK.TabIndex = 3;
			this.btnOK.Text = "OK";
			this.btnOK.UseVisualStyleBackColor = true;
			this.btnOK.Click += new System.EventHandler( this.btnOK_Click );
			// 
			// btnCancel
			// 
			this.btnCancel.Location = new System.Drawing.Point( 511, 209 );
			this.btnCancel.Name = "btnCancel";
			this.btnCancel.Size = new System.Drawing.Size( 75, 23 );
			this.btnCancel.TabIndex = 4;
			this.btnCancel.Text = "Cancel";
			this.btnCancel.UseVisualStyleBackColor = true;
			this.btnCancel.Click += new System.EventHandler( this.btnCancel_Click );
			// 
			// ExportOption
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF( 7F, 13F );
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size( 598, 249 );
			this.Controls.Add( this.btnCancel );
			this.Controls.Add( this.btnOK );
			this.Controls.Add( this.groupBox3 );
			this.Controls.Add( this.groupBox1 );
			this.Font = new System.Drawing.Font( "Verdana", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ( (byte)( 0 ) ) );
			this.Name = "ExportOption";
			this.Text = "Export";
			this.groupBox1.ResumeLayout( false );
			this.groupBox1.PerformLayout();
			this.groupBox3.ResumeLayout( false );
			this.groupBox3.PerformLayout();
			this.ResumeLayout( false );

		}

		#endregion

		private System.Windows.Forms.GroupBox groupBox1;
		private System.Windows.Forms.RadioButton rbExportCommon;
		private System.Windows.Forms.RadioButton rbExportNew;
		private System.Windows.Forms.GroupBox groupBox3;
		private System.Windows.Forms.Button btnOpenXMLFile;
		private System.Windows.Forms.Button btnOpenTextFile;
		private System.Windows.Forms.Button btnOpenMoveDestDir;
		private System.Windows.Forms.Button btnOpenCopyDestDir;
		private System.Windows.Forms.TextBox tbCopyFilePath;
		private System.Windows.Forms.TextBox tbMoveFilePath;
		private System.Windows.Forms.RadioButton rbMoveFiles;
		private System.Windows.Forms.RadioButton rbCopyFiles;
		private System.Windows.Forms.RadioButton rbText;
		private System.Windows.Forms.RadioButton rbXML;
		private System.Windows.Forms.TextBox tbXMLPath;
		private System.Windows.Forms.TextBox tbTextPath;
		private System.Windows.Forms.Button btnOK;
		private System.Windows.Forms.Button btnCancel;
	}
}