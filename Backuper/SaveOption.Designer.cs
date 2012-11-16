namespace Backuper
{
	partial class SaveOption
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
			this.btnConfirm = new System.Windows.Forms.Button();
			this.btnCancel = new System.Windows.Forms.Button();
			this.cbIsSaveLeft = new System.Windows.Forms.CheckBox();
			this.cbIsSaveRight = new System.Windows.Forms.CheckBox();
			this.cbIsSaveCorrInfo = new System.Windows.Forms.CheckBox();
			this.btnChooseFile = new System.Windows.Forms.Button();
			this.groupBox1 = new System.Windows.Forms.GroupBox();
			this.label1 = new System.Windows.Forms.Label();
			this.tbSavePath = new System.Windows.Forms.TextBox();
			this.groupBox1.SuspendLayout();
			this.SuspendLayout();
			// 
			// btnConfirm
			// 
			this.btnConfirm.Enabled = false;
			this.btnConfirm.Location = new System.Drawing.Point( 244, 242 );
			this.btnConfirm.Name = "btnConfirm";
			this.btnConfirm.Size = new System.Drawing.Size( 72, 26 );
			this.btnConfirm.TabIndex = 0;
			this.btnConfirm.Text = "OK";
			this.btnConfirm.UseVisualStyleBackColor = true;
			this.btnConfirm.Click += new System.EventHandler( this.btnConfirm_Click );
			// 
			// btnCancel
			// 
			this.btnCancel.Location = new System.Drawing.Point( 345, 242 );
			this.btnCancel.Name = "btnCancel";
			this.btnCancel.Size = new System.Drawing.Size( 72, 26 );
			this.btnCancel.TabIndex = 1;
			this.btnCancel.Text = "Cancel";
			this.btnCancel.UseVisualStyleBackColor = true;
			this.btnCancel.Click += new System.EventHandler( this.btnCancel_Click );
			// 
			// cbIsSaveLeft
			// 
			this.cbIsSaveLeft.AutoSize = true;
			this.cbIsSaveLeft.Location = new System.Drawing.Point( 16, 27 );
			this.cbIsSaveLeft.Name = "cbIsSaveLeft";
			this.cbIsSaveLeft.Size = new System.Drawing.Size( 47, 17 );
			this.cbIsSaveLeft.TabIndex = 2;
			this.cbIsSaveLeft.Text = "Left";
			this.cbIsSaveLeft.UseVisualStyleBackColor = true;
			this.cbIsSaveLeft.CheckedChanged += new System.EventHandler( this.cbIsSaveTree_CheckedChanged );
			// 
			// cbIsSaveRight
			// 
			this.cbIsSaveRight.AutoSize = true;
			this.cbIsSaveRight.Location = new System.Drawing.Point( 16, 64 );
			this.cbIsSaveRight.Name = "cbIsSaveRight";
			this.cbIsSaveRight.Size = new System.Drawing.Size( 55, 17 );
			this.cbIsSaveRight.TabIndex = 3;
			this.cbIsSaveRight.Text = "Right";
			this.cbIsSaveRight.UseVisualStyleBackColor = true;
			this.cbIsSaveRight.CheckedChanged += new System.EventHandler( this.cbIsSaveTree_CheckedChanged );
			// 
			// cbIsSaveCorrInfo
			// 
			this.cbIsSaveCorrInfo.AutoSize = true;
			this.cbIsSaveCorrInfo.Enabled = false;
			this.cbIsSaveCorrInfo.Location = new System.Drawing.Point( 30, 140 );
			this.cbIsSaveCorrInfo.Name = "cbIsSaveCorrInfo";
			this.cbIsSaveCorrInfo.Size = new System.Drawing.Size( 207, 17 );
			this.cbIsSaveCorrInfo.TabIndex = 4;
			this.cbIsSaveCorrInfo.Text = "Save Corrsponding Information";
			this.cbIsSaveCorrInfo.UseVisualStyleBackColor = true;
			// 
			// btnChooseFile
			// 
			this.btnChooseFile.Location = new System.Drawing.Point( 378, 182 );
			this.btnChooseFile.Name = "btnChooseFile";
			this.btnChooseFile.Size = new System.Drawing.Size( 39, 23 );
			this.btnChooseFile.TabIndex = 5;
			this.btnChooseFile.Text = "...";
			this.btnChooseFile.UseVisualStyleBackColor = true;
			this.btnChooseFile.Click += new System.EventHandler( this.btnChooseFile_Click );
			// 
			// groupBox1
			// 
			this.groupBox1.Controls.Add( this.cbIsSaveRight );
			this.groupBox1.Controls.Add( this.cbIsSaveLeft );
			this.groupBox1.Location = new System.Drawing.Point( 14, 13 );
			this.groupBox1.Name = "groupBox1";
			this.groupBox1.Size = new System.Drawing.Size( 233, 108 );
			this.groupBox1.TabIndex = 6;
			this.groupBox1.TabStop = false;
			this.groupBox1.Text = "Save Branch";
			// 
			// label1
			// 
			this.label1.AutoSize = true;
			this.label1.Location = new System.Drawing.Point( 28, 186 );
			this.label1.Name = "label1";
			this.label1.Size = new System.Drawing.Size( 77, 13 );
			this.label1.TabIndex = 7;
			this.label1.Text = "Save Path：";
			// 
			// tbSavePath
			// 
			this.tbSavePath.Location = new System.Drawing.Point( 118, 182 );
			this.tbSavePath.Name = "tbSavePath";
			this.tbSavePath.ReadOnly = true;
			this.tbSavePath.Size = new System.Drawing.Size( 251, 20 );
			this.tbSavePath.TabIndex = 8;
			// 
			// SaveOption
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF( 7F, 13F );
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size( 436, 281 );
			this.Controls.Add( this.tbSavePath );
			this.Controls.Add( this.label1 );
			this.Controls.Add( this.groupBox1 );
			this.Controls.Add( this.btnChooseFile );
			this.Controls.Add( this.cbIsSaveCorrInfo );
			this.Controls.Add( this.btnCancel );
			this.Controls.Add( this.btnConfirm );
			this.Font = new System.Drawing.Font( "Verdana", 8F );
			this.Name = "SaveOption";
			this.Text = "Save Option Setting";
			this.groupBox1.ResumeLayout( false );
			this.groupBox1.PerformLayout();
			this.ResumeLayout( false );
			this.PerformLayout();

		}

		#endregion

		private System.Windows.Forms.Button btnConfirm;
		private System.Windows.Forms.Button btnCancel;
		private System.Windows.Forms.Button btnChooseFile;
		private System.Windows.Forms.GroupBox groupBox1;
		private System.Windows.Forms.Label label1;
		public System.Windows.Forms.CheckBox cbIsSaveLeft;
		public System.Windows.Forms.CheckBox cbIsSaveRight;
		public System.Windows.Forms.CheckBox cbIsSaveCorrInfo;
		public System.Windows.Forms.TextBox tbSavePath;
	}
}