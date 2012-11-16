namespace Backuper
{
	partial class CopyFiles
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
			this.lvFiles = new System.Windows.Forms.ListView();
			this.PathName = new System.Windows.Forms.ColumnHeader();
			this.FullPath = new System.Windows.Forms.ColumnHeader();
			this.FileSize = new System.Windows.Forms.ColumnHeader();
			this.LastWriteTime = new System.Windows.Forms.ColumnHeader();
			this.Checksum = new System.Windows.Forms.ColumnHeader();
			this.cbSelectAll = new System.Windows.Forms.CheckBox();
			this.btnOK = new System.Windows.Forms.Button();
			this.btnCancel = new System.Windows.Forms.Button();
			this.Target = new System.Windows.Forms.Label();
			this.tbTarget = new System.Windows.Forms.TextBox();
			this.groupBox1.SuspendLayout();
			this.SuspendLayout();
			// 
			// groupBox1
			// 
			this.groupBox1.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
						| System.Windows.Forms.AnchorStyles.Left)
						| System.Windows.Forms.AnchorStyles.Right)));
			this.groupBox1.Controls.Add(this.lvFiles);
			this.groupBox1.Controls.Add(this.cbSelectAll);
			this.groupBox1.Location = new System.Drawing.Point(12, 12);
			this.groupBox1.Name = "groupBox1";
			this.groupBox1.Size = new System.Drawing.Size(556, 276);
			this.groupBox1.TabIndex = 0;
			this.groupBox1.TabStop = false;
			this.groupBox1.Text = "Copying Files";
			// 
			// lvFiles
			// 
			this.lvFiles.AllowColumnReorder = true;
			this.lvFiles.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
						| System.Windows.Forms.AnchorStyles.Left)
						| System.Windows.Forms.AnchorStyles.Right)));
			this.lvFiles.CheckBoxes = true;
			this.lvFiles.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.PathName,
            this.FullPath,
            this.FileSize,
            this.LastWriteTime,
            this.Checksum});
			this.lvFiles.GridLines = true;
			this.lvFiles.Location = new System.Drawing.Point(6, 20);
			this.lvFiles.Name = "lvFiles";
			this.lvFiles.ShowGroups = false;
			this.lvFiles.ShowItemToolTips = true;
			this.lvFiles.Size = new System.Drawing.Size(544, 208);
			this.lvFiles.TabIndex = 2;
			this.lvFiles.UseCompatibleStateImageBehavior = false;
			this.lvFiles.View = System.Windows.Forms.View.Details;
			// 
			// PathName
			// 
			this.PathName.Text = "Name";
			// 
			// FullPath
			// 
			this.FullPath.Text = "Full Path";
			this.FullPath.Width = 200;
			// 
			// FileSize
			// 
			this.FileSize.Text = "File Size";
			this.FileSize.Width = 80;
			// 
			// LastWriteTime
			// 
			this.LastWriteTime.DisplayIndex = 4;
			this.LastWriteTime.Text = "Last Write Time";
			this.LastWriteTime.Width = 110;
			// 
			// Checksum
			// 
			this.Checksum.DisplayIndex = 3;
			this.Checksum.Text = "Checksum";
			this.Checksum.Width = 80;
			// 
			// cbSelectAll
			// 
			this.cbSelectAll.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
			this.cbSelectAll.AutoSize = true;
			this.cbSelectAll.Location = new System.Drawing.Point(462, 245);
			this.cbSelectAll.Name = "cbSelectAll";
			this.cbSelectAll.Size = new System.Drawing.Size(79, 17);
			this.cbSelectAll.TabIndex = 1;
			this.cbSelectAll.Text = "Select All";
			this.cbSelectAll.UseVisualStyleBackColor = true;
			this.cbSelectAll.CheckedChanged += new System.EventHandler(this.cbSelectAll_CheckedChanged);
			// 
			// btnOK
			// 
			this.btnOK.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
			this.btnOK.Location = new System.Drawing.Point(385, 356);
			this.btnOK.Name = "btnOK";
			this.btnOK.Size = new System.Drawing.Size(75, 23);
			this.btnOK.TabIndex = 1;
			this.btnOK.Text = "OK";
			this.btnOK.UseVisualStyleBackColor = true;
			this.btnOK.Click += new System.EventHandler(this.btnOK_Click);
			// 
			// btnCancel
			// 
			this.btnCancel.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
			this.btnCancel.Location = new System.Drawing.Point(488, 356);
			this.btnCancel.Name = "btnCancel";
			this.btnCancel.Size = new System.Drawing.Size(75, 23);
			this.btnCancel.TabIndex = 2;
			this.btnCancel.Text = "Cancel";
			this.btnCancel.UseVisualStyleBackColor = true;
			this.btnCancel.Click += new System.EventHandler(this.btnCancel_Click);
			// 
			// Target
			// 
			this.Target.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
			this.Target.AutoSize = true;
			this.Target.Location = new System.Drawing.Point(15, 310);
			this.Target.Name = "Target";
			this.Target.Size = new System.Drawing.Size(49, 13);
			this.Target.TabIndex = 3;
			this.Target.Text = "Target:";
			// 
			// tbTarget
			// 
			this.tbTarget.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
			this.tbTarget.Location = new System.Drawing.Point(70, 307);
			this.tbTarget.Name = "tbTarget";
			this.tbTarget.ReadOnly = true;
			this.tbTarget.Size = new System.Drawing.Size(285, 21);
			this.tbTarget.TabIndex = 4;
			// 
			// CopyFiles
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 13F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(580, 394);
			this.Controls.Add(this.tbTarget);
			this.Controls.Add(this.Target);
			this.Controls.Add(this.btnCancel);
			this.Controls.Add(this.btnOK);
			this.Controls.Add(this.groupBox1);
			this.Font = new System.Drawing.Font("Verdana", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.Margin = new System.Windows.Forms.Padding(4, 3, 4, 3);
			this.Name = "CopyFiles";
			this.Text = "Copy Files";
			this.Load += new System.EventHandler(this.CopyFiles_Load);
			this.groupBox1.ResumeLayout(false);
			this.groupBox1.PerformLayout();
			this.ResumeLayout(false);
			this.PerformLayout();

		}

		#endregion

		private System.Windows.Forms.GroupBox groupBox1;
		private System.Windows.Forms.CheckBox cbSelectAll;
		private System.Windows.Forms.Button btnOK;
		private System.Windows.Forms.Button btnCancel;
		private System.Windows.Forms.Label Target;
		private System.Windows.Forms.TextBox tbTarget;
		private System.Windows.Forms.ListView lvFiles;
		private System.Windows.Forms.ColumnHeader PathName;
		private System.Windows.Forms.ColumnHeader FullPath;
		private System.Windows.Forms.ColumnHeader FileSize;
		private System.Windows.Forms.ColumnHeader Checksum;
		private System.Windows.Forms.ColumnHeader LastWriteTime;

	}
}