namespace DatabaseReschema_AddField
{
	partial class mainForm
	{
		/// <summary>
		/// 必需的设计器变量。
		/// </summary>
		private System.ComponentModel.IContainer components = null;

		/// <summary>
		/// 清理所有正在使用的资源。
		/// </summary>
		/// <param name="disposing">如果应释放托管资源，为 true；否则为 false。</param>
		protected override void Dispose(bool disposing)
		{
			if (disposing && (components != null))
			{
				components.Dispose();
			}
			base.Dispose(disposing);
		}

		#region Windows 窗体设计器生成的代码

		/// <summary>
		/// 设计器支持所需的方法 - 不要
		/// 使用代码编辑器修改此方法的内容。
		/// </summary>
		private void InitializeComponent()
		{
			this.openFileDlg = new System.Windows.Forms.OpenFileDialog();
			this.openFile = new System.Windows.Forms.Button();
			this.fileNameTB = new System.Windows.Forms.TextBox();
			this.fieldListBox = new System.Windows.Forms.ListBox();
			this.addField = new System.Windows.Forms.Button();
			this.label1 = new System.Windows.Forms.Label();
			this.textBox1 = new System.Windows.Forms.TextBox();
			this.label2 = new System.Windows.Forms.Label();
			this.textBox2 = new System.Windows.Forms.TextBox();
			this.SuspendLayout();
			// 
			// openFileDlg
			// 
			this.openFileDlg.FileName = "openFileDialog1";
			// 
			// openFile
			// 
			this.openFile.Location = new System.Drawing.Point(23, 43);
			this.openFile.Name = "openFile";
			this.openFile.Size = new System.Drawing.Size(85, 25);
			this.openFile.TabIndex = 0;
			this.openFile.Text = "打开文件";
			this.openFile.UseVisualStyleBackColor = true;
			this.openFile.Click += new System.EventHandler(this.openFile_Click);
			// 
			// fileNameTB
			// 
			this.fileNameTB.Location = new System.Drawing.Point(114, 47);
			this.fileNameTB.Name = "fileNameTB";
			this.fileNameTB.Size = new System.Drawing.Size(274, 21);
			this.fileNameTB.TabIndex = 1;
			// 
			// fieldListBox
			// 
			this.fieldListBox.FormattingEnabled = true;
			this.fieldListBox.ItemHeight = 12;
			this.fieldListBox.Location = new System.Drawing.Point(23, 167);
			this.fieldListBox.Name = "fieldListBox";
			this.fieldListBox.Size = new System.Drawing.Size(122, 136);
			this.fieldListBox.TabIndex = 2;
			// 
			// addField
			// 
			this.addField.Location = new System.Drawing.Point(259, 242);
			this.addField.Name = "addField";
			this.addField.Size = new System.Drawing.Size(102, 25);
			this.addField.TabIndex = 3;
			this.addField.Text = "添加字段";
			this.addField.UseVisualStyleBackColor = true;
			this.addField.Click += new System.EventHandler(this.addField_Click);
			// 
			// label1
			// 
			this.label1.AutoSize = true;
			this.label1.Location = new System.Drawing.Point(21, 95);
			this.label1.Name = "label1";
			this.label1.Size = new System.Drawing.Size(41, 12);
			this.label1.TabIndex = 4;
			this.label1.Text = "用户名";
			// 
			// textBox1
			// 
			this.textBox1.Location = new System.Drawing.Point(86, 90);
			this.textBox1.Name = "textBox1";
			this.textBox1.Size = new System.Drawing.Size(143, 21);
			this.textBox1.TabIndex = 5;
			// 
			// label2
			// 
			this.label2.AutoSize = true;
			this.label2.Location = new System.Drawing.Point(22, 130);
			this.label2.Name = "label2";
			this.label2.Size = new System.Drawing.Size(29, 12);
			this.label2.TabIndex = 6;
			this.label2.Text = "密码";
			// 
			// textBox2
			// 
			this.textBox2.Location = new System.Drawing.Point(86, 125);
			this.textBox2.Name = "textBox2";
			this.textBox2.PasswordChar = '*';
			this.textBox2.Size = new System.Drawing.Size(142, 21);
			this.textBox2.TabIndex = 7;
			// 
			// mainForm
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(577, 318);
			this.Controls.Add(this.textBox2);
			this.Controls.Add(this.label2);
			this.Controls.Add(this.textBox1);
			this.Controls.Add(this.label1);
			this.Controls.Add(this.addField);
			this.Controls.Add(this.fieldListBox);
			this.Controls.Add(this.fileNameTB);
			this.Controls.Add(this.openFile);
			this.Name = "mainForm";
			this.Text = "数据库架构修改器";
			this.ResumeLayout(false);
			this.PerformLayout();

		}

		#endregion

		private System.Windows.Forms.OpenFileDialog openFileDlg;
		private System.Windows.Forms.Button openFile;
		private System.Windows.Forms.TextBox fileNameTB;
		private System.Windows.Forms.ListBox fieldListBox;
		private System.Windows.Forms.Button addField;
		private System.Windows.Forms.Label label1;
		private System.Windows.Forms.TextBox textBox1;
		private System.Windows.Forms.Label label2;
		private System.Windows.Forms.TextBox textBox2;
	}
}

