namespace Backuper
{
	partial class OverwritePrompt
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
			this.lblPrompt = new System.Windows.Forms.Label();
			this.btnYes = new System.Windows.Forms.Button();
			this.btnNoToAll = new System.Windows.Forms.Button();
			this.btnYesToAll = new System.Windows.Forms.Button();
			this.btnNo = new System.Windows.Forms.Button();
			this.SuspendLayout();
			// 
			// lblPrompt
			// 
			this.lblPrompt.Location = new System.Drawing.Point(12, 9);
			this.lblPrompt.Name = "lblPrompt";
			this.lblPrompt.Size = new System.Drawing.Size(354, 50);
			this.lblPrompt.TabIndex = 0;
			// 
			// btnYes
			// 
			this.btnYes.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
			this.btnYes.Location = new System.Drawing.Point(15, 80);
			this.btnYes.Name = "btnYes";
			this.btnYes.Size = new System.Drawing.Size(75, 23);
			this.btnYes.TabIndex = 1;
			this.btnYes.Text = "&Yes";
			this.btnYes.UseVisualStyleBackColor = true;
			this.btnYes.Click += new System.EventHandler(this.btnYes_Click);
			// 
			// btnNoToAll
			// 
			this.btnNoToAll.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
			this.btnNoToAll.Location = new System.Drawing.Point(291, 80);
			this.btnNoToAll.Name = "btnNoToAll";
			this.btnNoToAll.Size = new System.Drawing.Size(75, 23);
			this.btnNoToAll.TabIndex = 4;
			this.btnNoToAll.Text = "No To All";
			this.btnNoToAll.UseVisualStyleBackColor = true;
			this.btnNoToAll.Click += new System.EventHandler(this.btnNoToAll_Click);
			// 
			// btnYesToAll
			// 
			this.btnYesToAll.Anchor = System.Windows.Forms.AnchorStyles.Bottom;
			this.btnYesToAll.Location = new System.Drawing.Point(107, 80);
			this.btnYesToAll.Name = "btnYesToAll";
			this.btnYesToAll.Size = new System.Drawing.Size(75, 23);
			this.btnYesToAll.TabIndex = 2;
			this.btnYesToAll.Text = "Yes To &All";
			this.btnYesToAll.UseVisualStyleBackColor = true;
			this.btnYesToAll.Click += new System.EventHandler(this.btnYesToAll_Click);
			// 
			// btnNo
			// 
			this.btnNo.Anchor = System.Windows.Forms.AnchorStyles.Bottom;
			this.btnNo.Location = new System.Drawing.Point(199, 80);
			this.btnNo.Name = "btnNo";
			this.btnNo.Size = new System.Drawing.Size(75, 23);
			this.btnNo.TabIndex = 3;
			this.btnNo.Text = "&No";
			this.btnNo.UseVisualStyleBackColor = true;
			this.btnNo.Click += new System.EventHandler(this.btnNo_Click);
			// 
			// OverwritePrompt
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 13F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(380, 115);
			this.ControlBox = false;
			this.Controls.Add(this.btnNo);
			this.Controls.Add(this.btnYesToAll);
			this.Controls.Add(this.btnNoToAll);
			this.Controls.Add(this.btnYes);
			this.Controls.Add(this.lblPrompt);
			this.Font = new System.Drawing.Font("Verdana", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.Name = "OverwritePrompt";
			this.Text = "Overwrite Prompt";
			this.ResumeLayout(false);

		}

		#endregion

		private System.Windows.Forms.Label lblPrompt;
		private System.Windows.Forms.Button btnYes;
		private System.Windows.Forms.Button btnNoToAll;
		private System.Windows.Forms.Button btnYesToAll;
		private System.Windows.Forms.Button btnNo;
	}
}