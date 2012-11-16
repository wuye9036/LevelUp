namespace Backuper
{
	partial class LoadOption
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
			this.cbIsLoadCorrInfo = new System.Windows.Forms.CheckBox();
			this.comboRightSource = new System.Windows.Forms.ComboBox();
			this.cbIsLoadRight = new System.Windows.Forms.CheckBox();
			this.comboLeftSource = new System.Windows.Forms.ComboBox();
			this.cbIsLoadLeft = new System.Windows.Forms.CheckBox();
			this.groupBox2 = new System.Windows.Forms.GroupBox();
			this.btnOpenFile = new System.Windows.Forms.Button();
			this.tbOpenFilePath = new System.Windows.Forms.TextBox();
			this.label1 = new System.Windows.Forms.Label();
			this.btnOpen = new System.Windows.Forms.Button();
			this.btnCancel = new System.Windows.Forms.Button();
			this.groupBox1.SuspendLayout();
			this.groupBox2.SuspendLayout();
			this.SuspendLayout();
			// 
			// groupBox1
			// 
			this.groupBox1.Controls.Add( this.cbIsLoadCorrInfo );
			this.groupBox1.Controls.Add( this.comboRightSource );
			this.groupBox1.Controls.Add( this.cbIsLoadRight );
			this.groupBox1.Controls.Add( this.comboLeftSource );
			this.groupBox1.Controls.Add( this.cbIsLoadLeft );
			this.groupBox1.Location = new System.Drawing.Point( 378, 13 );
			this.groupBox1.Name = "groupBox1";
			this.groupBox1.Size = new System.Drawing.Size( 225, 153 );
			this.groupBox1.TabIndex = 1;
			this.groupBox1.TabStop = false;
			this.groupBox1.Text = "Open To";
			// 
			// cbIsLoadCorrInfo
			// 
			this.cbIsLoadCorrInfo.AutoSize = true;
			this.cbIsLoadCorrInfo.Location = new System.Drawing.Point( 6, 115 );
			this.cbIsLoadCorrInfo.Name = "cbIsLoadCorrInfo";
			this.cbIsLoadCorrInfo.Size = new System.Drawing.Size( 212, 17 );
			this.cbIsLoadCorrInfo.TabIndex = 4;
			this.cbIsLoadCorrInfo.Text = "Load Corresponding Information";
			this.cbIsLoadCorrInfo.UseVisualStyleBackColor = true;
			// 
			// comboRightSource
			// 
			this.comboRightSource.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
			this.comboRightSource.FormattingEnabled = true;
			this.comboRightSource.Location = new System.Drawing.Point( 80, 64 );
			this.comboRightSource.Name = "comboRightSource";
			this.comboRightSource.Size = new System.Drawing.Size( 121, 21 );
			this.comboRightSource.TabIndex = 3;
			// 
			// cbIsLoadRight
			// 
			this.cbIsLoadRight.AutoSize = true;
			this.cbIsLoadRight.Location = new System.Drawing.Point( 6, 66 );
			this.cbIsLoadRight.Name = "cbIsLoadRight";
			this.cbIsLoadRight.Size = new System.Drawing.Size( 55, 17 );
			this.cbIsLoadRight.TabIndex = 2;
			this.cbIsLoadRight.Text = "Right";
			this.cbIsLoadRight.UseVisualStyleBackColor = true;
			// 
			// comboLeftSource
			// 
			this.comboLeftSource.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
			this.comboLeftSource.FormattingEnabled = true;
			this.comboLeftSource.Location = new System.Drawing.Point( 80, 29 );
			this.comboLeftSource.Name = "comboLeftSource";
			this.comboLeftSource.Size = new System.Drawing.Size( 121, 21 );
			this.comboLeftSource.TabIndex = 1;
			// 
			// cbIsLoadLeft
			// 
			this.cbIsLoadLeft.AutoSize = true;
			this.cbIsLoadLeft.Location = new System.Drawing.Point( 6, 31 );
			this.cbIsLoadLeft.Name = "cbIsLoadLeft";
			this.cbIsLoadLeft.Size = new System.Drawing.Size( 47, 17 );
			this.cbIsLoadLeft.TabIndex = 0;
			this.cbIsLoadLeft.Text = "Left";
			this.cbIsLoadLeft.UseVisualStyleBackColor = true;
			this.cbIsLoadLeft.CheckedChanged += new System.EventHandler( this.cbIsLoad_CheckedChanged );
			// 
			// groupBox2
			// 
			this.groupBox2.Controls.Add( this.btnOpenFile );
			this.groupBox2.Controls.Add( this.tbOpenFilePath );
			this.groupBox2.Controls.Add( this.label1 );
			this.groupBox2.Location = new System.Drawing.Point( 13, 13 );
			this.groupBox2.Name = "groupBox2";
			this.groupBox2.Size = new System.Drawing.Size( 312, 153 );
			this.groupBox2.TabIndex = 2;
			this.groupBox2.TabStop = false;
			this.groupBox2.Text = "Open From";
			// 
			// btnOpenFile
			// 
			this.btnOpenFile.Location = new System.Drawing.Point( 273, 46 );
			this.btnOpenFile.Name = "btnOpenFile";
			this.btnOpenFile.Size = new System.Drawing.Size( 33, 22 );
			this.btnOpenFile.TabIndex = 2;
			this.btnOpenFile.Text = "...";
			this.btnOpenFile.UseVisualStyleBackColor = true;
			this.btnOpenFile.Click += new System.EventHandler( this.btnOpenFile_Click );
			// 
			// tbOpenFilePath
			// 
			this.tbOpenFilePath.Location = new System.Drawing.Point( 22, 47 );
			this.tbOpenFilePath.Name = "tbOpenFilePath";
			this.tbOpenFilePath.ReadOnly = true;
			this.tbOpenFilePath.Size = new System.Drawing.Size( 245, 21 );
			this.tbOpenFilePath.TabIndex = 1;
			// 
			// label1
			// 
			this.label1.AutoSize = true;
			this.label1.Location = new System.Drawing.Point( 7, 21 );
			this.label1.Name = "label1";
			this.label1.Size = new System.Drawing.Size( 31, 13 );
			this.label1.TabIndex = 0;
			this.label1.Text = "File:";
			// 
			// btnOpen
			// 
			this.btnOpen.Location = new System.Drawing.Point( 416, 205 );
			this.btnOpen.Name = "btnOpen";
			this.btnOpen.Size = new System.Drawing.Size( 75, 23 );
			this.btnOpen.TabIndex = 3;
			this.btnOpen.Text = "Open";
			this.btnOpen.UseVisualStyleBackColor = true;
			this.btnOpen.Click += new System.EventHandler( this.btnOpen_Click );
			// 
			// btnCancel
			// 
			this.btnCancel.Location = new System.Drawing.Point( 528, 205 );
			this.btnCancel.Name = "btnCancel";
			this.btnCancel.Size = new System.Drawing.Size( 75, 23 );
			this.btnCancel.TabIndex = 4;
			this.btnCancel.Text = "Cancel";
			this.btnCancel.UseVisualStyleBackColor = true;
			this.btnCancel.Click += new System.EventHandler( this.btnCancel_Click );
			// 
			// LoadOption
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF( 7F, 13F );
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size( 615, 248 );
			this.Controls.Add( this.btnCancel );
			this.Controls.Add( this.btnOpen );
			this.Controls.Add( this.groupBox2 );
			this.Controls.Add( this.groupBox1 );
			this.Font = new System.Drawing.Font( "Verdana", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ( (byte)( 0 ) ) );
			this.Margin = new System.Windows.Forms.Padding( 4, 3, 4, 3 );
			this.Name = "LoadOption";
			this.Text = "Open";
			this.groupBox1.ResumeLayout( false );
			this.groupBox1.PerformLayout();
			this.groupBox2.ResumeLayout( false );
			this.groupBox2.PerformLayout();
			this.ResumeLayout( false );

		}

		#endregion

		private System.Windows.Forms.GroupBox groupBox1;
		private System.Windows.Forms.CheckBox cbIsLoadCorrInfo;
		private System.Windows.Forms.ComboBox comboRightSource;
		private System.Windows.Forms.CheckBox cbIsLoadRight;
		private System.Windows.Forms.ComboBox comboLeftSource;
		private System.Windows.Forms.CheckBox cbIsLoadLeft;
		private System.Windows.Forms.GroupBox groupBox2;
		private System.Windows.Forms.Button btnOpenFile;
		private System.Windows.Forms.TextBox tbOpenFilePath;
		private System.Windows.Forms.Label label1;
		private System.Windows.Forms.Button btnOpen;
		private System.Windows.Forms.Button btnCancel;

	}
}