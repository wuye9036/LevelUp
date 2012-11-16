namespace Mesh2D
{
	partial class Animation2DDemo
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
			this.panelDraw = new System.Windows.Forms.Panel();
			this.sbBone10 = new System.Windows.Forms.HScrollBar();
			this.sbBone20 = new System.Windows.Forms.HScrollBar();
			this.b10 = new System.Windows.Forms.Label();
			this.b20 = new System.Windows.Forms.Label();
			this.sbBone00 = new System.Windows.Forms.HScrollBar();
			this.b00 = new System.Windows.Forms.Label();
			this.SuspendLayout();
			// 
			// panelDraw
			// 
			this.panelDraw.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
			this.panelDraw.Location = new System.Drawing.Point(12, 12);
			this.panelDraw.Name = "panelDraw";
			this.panelDraw.Size = new System.Drawing.Size(400, 400);
			this.panelDraw.TabIndex = 0;
			this.panelDraw.Paint += new System.Windows.Forms.PaintEventHandler(this.panelDraw_Paint);
			// 
			// sbBone10
			// 
			this.sbBone10.Location = new System.Drawing.Point(71, 475);
			this.sbBone10.Maximum = 628;
			this.sbBone10.Name = "sbBone10";
			this.sbBone10.Size = new System.Drawing.Size(341, 15);
			this.sbBone10.TabIndex = 3;
			this.sbBone10.ValueChanged += new System.EventHandler(this.sbBone10_ValueChanged);
			// 
			// sbBone20
			// 
			this.sbBone20.Location = new System.Drawing.Point(71, 508);
			this.sbBone20.Maximum = 628;
			this.sbBone20.Name = "sbBone20";
			this.sbBone20.Size = new System.Drawing.Size(341, 15);
			this.sbBone20.TabIndex = 4;
			this.sbBone20.ValueChanged += new System.EventHandler(this.sbBone20_ValueChanged);
			// 
			// b10
			// 
			this.b10.AutoSize = true;
			this.b10.Location = new System.Drawing.Point(10, 475);
			this.b10.Name = "b10";
			this.b10.Size = new System.Drawing.Size(41, 12);
			this.b10.TabIndex = 6;
			this.b10.Text = "骨骼10";
			// 
			// b20
			// 
			this.b20.AutoSize = true;
			this.b20.Location = new System.Drawing.Point(10, 508);
			this.b20.Name = "b20";
			this.b20.Size = new System.Drawing.Size(41, 12);
			this.b20.TabIndex = 7;
			this.b20.Text = "骨骼20";
			// 
			// sbBone00
			// 
			this.sbBone00.Location = new System.Drawing.Point(71, 442);
			this.sbBone00.Maximum = 628;
			this.sbBone00.Name = "sbBone00";
			this.sbBone00.Size = new System.Drawing.Size(341, 15);
			this.sbBone00.TabIndex = 2;
			this.sbBone00.ValueChanged += new System.EventHandler(this.sbBone00_ValueChanged);
			// 
			// b00
			// 
			this.b00.AutoSize = true;
			this.b00.Location = new System.Drawing.Point(10, 442);
			this.b00.Name = "b00";
			this.b00.Size = new System.Drawing.Size(41, 12);
			this.b00.TabIndex = 5;
			this.b00.Text = "骨骼00";
			// 
			// Animation2DDemo
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(426, 553);
			this.Controls.Add(this.b20);
			this.Controls.Add(this.b10);
			this.Controls.Add(this.b00);
			this.Controls.Add(this.sbBone20);
			this.Controls.Add(this.sbBone10);
			this.Controls.Add(this.sbBone00);
			this.Controls.Add(this.panelDraw);
			this.MaximumSize = new System.Drawing.Size(434, 580);
			this.MinimumSize = new System.Drawing.Size(434, 580);
			this.Name = "Animation2DDemo";
			this.Text = "2D骨骼演示";
			this.ResumeLayout(false);
			this.PerformLayout();

		}

		#endregion

		private System.Windows.Forms.Panel panelDraw;
		private System.Windows.Forms.HScrollBar sbBone10;
		private System.Windows.Forms.HScrollBar sbBone20;
		private System.Windows.Forms.Label b10;
		private System.Windows.Forms.Label b20;
		private System.Windows.Forms.HScrollBar sbBone00;
		private System.Windows.Forms.Label b00;
	}
}

