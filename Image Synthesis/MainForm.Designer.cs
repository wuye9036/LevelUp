namespace WindowsApplication1
{
	partial class MainForm
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
			this.src1PicBox = new System.Windows.Forms.PictureBox();
			this.destPicBox = new System.Windows.Forms.PictureBox();
			this.btnLoad0 = new System.Windows.Forms.Button();
			this.btnLoad1 = new System.Windows.Forms.Button();
			this.btnSyn = new System.Windows.Forms.Button();
			this.btnSave = new System.Windows.Forms.Button();
			this.src0PicBox = new System.Windows.Forms.PictureBox();
			this.groupBox1 = new System.Windows.Forms.GroupBox();
			this.groupBox2 = new System.Windows.Forms.GroupBox();
			this.gb3 = new System.Windows.Forms.GroupBox();
			((System.ComponentModel.ISupportInitialize)(this.src1PicBox)).BeginInit();
			((System.ComponentModel.ISupportInitialize)(this.destPicBox)).BeginInit();
			((System.ComponentModel.ISupportInitialize)(this.src0PicBox)).BeginInit();
			this.groupBox1.SuspendLayout();
			this.groupBox2.SuspendLayout();
			this.gb3.SuspendLayout();
			this.SuspendLayout();
			// 
			// src1PicBox
			// 
			this.src1PicBox.Location = new System.Drawing.Point(6, 20);
			this.src1PicBox.Name = "src1PicBox";
			this.src1PicBox.Size = new System.Drawing.Size(260, 260);
			this.src1PicBox.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom;
			this.src1PicBox.TabIndex = 1;
			this.src1PicBox.TabStop = false;
			// 
			// destPicBox
			// 
			this.destPicBox.Location = new System.Drawing.Point(12, 20);
			this.destPicBox.Name = "destPicBox";
			this.destPicBox.Size = new System.Drawing.Size(260, 260);
			this.destPicBox.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom;
			this.destPicBox.TabIndex = 2;
			this.destPicBox.TabStop = false;
			// 
			// btnLoad0
			// 
			this.btnLoad0.Location = new System.Drawing.Point(360, 376);
			this.btnLoad0.Name = "btnLoad0";
			this.btnLoad0.Size = new System.Drawing.Size(157, 45);
			this.btnLoad0.TabIndex = 3;
			this.btnLoad0.Text = "装载源图一";
			this.btnLoad0.UseVisualStyleBackColor = true;
			this.btnLoad0.Click += new System.EventHandler(this.btnLoad0_Click);
			// 
			// btnLoad1
			// 
			this.btnLoad1.Location = new System.Drawing.Point(360, 442);
			this.btnLoad1.Name = "btnLoad1";
			this.btnLoad1.Size = new System.Drawing.Size(157, 45);
			this.btnLoad1.TabIndex = 4;
			this.btnLoad1.Text = "装载源图二";
			this.btnLoad1.UseVisualStyleBackColor = true;
			this.btnLoad1.Click += new System.EventHandler(this.btnLoad1_Click);
			// 
			// btnSyn
			// 
			this.btnSyn.Location = new System.Drawing.Point(360, 508);
			this.btnSyn.Name = "btnSyn";
			this.btnSyn.Size = new System.Drawing.Size(157, 45);
			this.btnSyn.TabIndex = 5;
			this.btnSyn.Text = "执行融合";
			this.btnSyn.UseVisualStyleBackColor = true;
			this.btnSyn.Click += new System.EventHandler(this.btnSyn_Click);
			// 
			// btnSave
			// 
			this.btnSave.Location = new System.Drawing.Point(360, 574);
			this.btnSave.Name = "btnSave";
			this.btnSave.Size = new System.Drawing.Size(157, 45);
			this.btnSave.TabIndex = 6;
			this.btnSave.Text = "保存融合后图像";
			this.btnSave.UseVisualStyleBackColor = true;
			this.btnSave.Click += new System.EventHandler(this.btnSave_Click);
			// 
			// src0PicBox
			// 
			this.src0PicBox.Location = new System.Drawing.Point(12, 20);
			this.src0PicBox.Name = "src0PicBox";
			this.src0PicBox.Size = new System.Drawing.Size(260, 260);
			this.src0PicBox.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom;
			this.src0PicBox.TabIndex = 0;
			this.src0PicBox.TabStop = false;
			// 
			// groupBox1
			// 
			this.groupBox1.AutoSize = true;
			this.groupBox1.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
			this.groupBox1.Controls.Add(this.src0PicBox);
			this.groupBox1.Location = new System.Drawing.Point(12, 12);
			this.groupBox1.Name = "groupBox1";
			this.groupBox1.Size = new System.Drawing.Size(278, 300);
			this.groupBox1.TabIndex = 7;
			this.groupBox1.TabStop = false;
			this.groupBox1.Text = "源位图0";
			// 
			// groupBox2
			// 
			this.groupBox2.AutoSize = true;
			this.groupBox2.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
			this.groupBox2.Controls.Add(this.src1PicBox);
			this.groupBox2.Location = new System.Drawing.Point(310, 12);
			this.groupBox2.Name = "groupBox2";
			this.groupBox2.Size = new System.Drawing.Size(272, 300);
			this.groupBox2.TabIndex = 8;
			this.groupBox2.TabStop = false;
			this.groupBox2.Text = "源位图1";
			// 
			// gb3
			// 
			this.gb3.AutoSize = true;
			this.gb3.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
			this.gb3.Controls.Add(this.destPicBox);
			this.gb3.Location = new System.Drawing.Point(12, 344);
			this.gb3.Name = "gb3";
			this.gb3.Size = new System.Drawing.Size(278, 300);
			this.gb3.TabIndex = 9;
			this.gb3.TabStop = false;
			this.gb3.Text = "融合后图像";
			// 
			// MainForm
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.AutoScroll = true;
			this.ClientSize = new System.Drawing.Size(631, 650);
			this.Controls.Add(this.gb3);
			this.Controls.Add(this.groupBox2);
			this.Controls.Add(this.groupBox1);
			this.Controls.Add(this.btnSave);
			this.Controls.Add(this.btnSyn);
			this.Controls.Add(this.btnLoad1);
			this.Controls.Add(this.btnLoad0);
			this.Name = "MainForm";
			this.Text = "图像融合";
			((System.ComponentModel.ISupportInitialize)(this.src1PicBox)).EndInit();
			((System.ComponentModel.ISupportInitialize)(this.destPicBox)).EndInit();
			((System.ComponentModel.ISupportInitialize)(this.src0PicBox)).EndInit();
			this.groupBox1.ResumeLayout(false);
			this.groupBox2.ResumeLayout(false);
			this.gb3.ResumeLayout(false);
			this.ResumeLayout(false);
			this.PerformLayout();

		}

		#endregion

		private System.Windows.Forms.PictureBox src1PicBox;
		private System.Windows.Forms.PictureBox destPicBox;
		private System.Windows.Forms.Button btnLoad0;
		private System.Windows.Forms.Button btnLoad1;
		private System.Windows.Forms.Button btnSyn;
		private System.Windows.Forms.Button btnSave;
		private System.Windows.Forms.PictureBox src0PicBox;
		private System.Windows.Forms.GroupBox groupBox1;
		private System.Windows.Forms.GroupBox groupBox2;
		private System.Windows.Forms.GroupBox gb3;
	}
}

