namespace Backuper
{
	partial class FileOperationProgress
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
			this.pbTotal = new System.Windows.Forms.ProgressBar();
			this.pbFile = new System.Windows.Forms.ProgressBar();
			this.lblOperationName = new System.Windows.Forms.Label();
			this.lblFileName = new System.Windows.Forms.Label();
			this.btnCancel = new System.Windows.Forms.Button();
			this.label3 = new System.Windows.Forms.Label();
			this.label4 = new System.Windows.Forms.Label();
			this.lblElapsedTime = new System.Windows.Forms.Label();
			this.lblResidualTime = new System.Windows.Forms.Label();
			this.lblFilePercentage = new System.Windows.Forms.Label();
			this.timerUpdateTimeLbl = new System.Windows.Forms.Timer(this.components);
			this.lblTotalPercentage = new System.Windows.Forms.Label();
			this.SuspendLayout();
			// 
			// pbTotal
			// 
			this.pbTotal.Location = new System.Drawing.Point(12, 181);
			this.pbTotal.MarqueeAnimationSpeed = 1000;
			this.pbTotal.Maximum = 1000;
			this.pbTotal.Name = "pbTotal";
			this.pbTotal.Size = new System.Drawing.Size(422, 11);
			this.pbTotal.TabIndex = 0;
			// 
			// pbFile
			// 
			this.pbFile.Location = new System.Drawing.Point(12, 108);
			this.pbFile.Maximum = 1000;
			this.pbFile.Name = "pbFile";
			this.pbFile.Size = new System.Drawing.Size(422, 11);
			this.pbFile.TabIndex = 1;
			// 
			// lblOperationName
			// 
			this.lblOperationName.AutoSize = true;
			this.lblOperationName.Location = new System.Drawing.Point(14, 36);
			this.lblOperationName.Name = "lblOperationName";
			this.lblOperationName.Size = new System.Drawing.Size(0, 13);
			this.lblOperationName.TabIndex = 2;
			// 
			// lblFileName
			// 
			this.lblFileName.AutoSize = true;
			this.lblFileName.Location = new System.Drawing.Point(14, 75);
			this.lblFileName.Name = "lblFileName";
			this.lblFileName.Size = new System.Drawing.Size(0, 13);
			this.lblFileName.TabIndex = 3;
			// 
			// btnCancel
			// 
			this.btnCancel.Location = new System.Drawing.Point(361, 31);
			this.btnCancel.Name = "btnCancel";
			this.btnCancel.Size = new System.Drawing.Size(75, 23);
			this.btnCancel.TabIndex = 4;
			this.btnCancel.Text = "Cancel";
			this.btnCancel.UseVisualStyleBackColor = true;
			this.btnCancel.Click += new System.EventHandler(this.btnCancel_Click);
			// 
			// label3
			// 
			this.label3.AutoSize = true;
			this.label3.Location = new System.Drawing.Point(12, 132);
			this.label3.Name = "label3";
			this.label3.Size = new System.Drawing.Size(88, 13);
			this.label3.TabIndex = 5;
			this.label3.Text = "Time Elapsed:";
			// 
			// label4
			// 
			this.label4.AutoSize = true;
			this.label4.Location = new System.Drawing.Point(12, 156);
			this.label4.Name = "label4";
			this.label4.Size = new System.Drawing.Size(104, 13);
			this.label4.TabIndex = 6;
			this.label4.Text = "Time Remaining:";
			// 
			// lblElapsedTime
			// 
			this.lblElapsedTime.AutoSize = true;
			this.lblElapsedTime.Location = new System.Drawing.Point(129, 132);
			this.lblElapsedTime.Name = "lblElapsedTime";
			this.lblElapsedTime.Size = new System.Drawing.Size(59, 13);
			this.lblElapsedTime.TabIndex = 7;
			this.lblElapsedTime.Text = "00:00:00";
			// 
			// lblResidualTime
			// 
			this.lblResidualTime.AutoSize = true;
			this.lblResidualTime.Location = new System.Drawing.Point(129, 156);
			this.lblResidualTime.Name = "lblResidualTime";
			this.lblResidualTime.Size = new System.Drawing.Size(59, 13);
			this.lblResidualTime.TabIndex = 8;
			this.lblResidualTime.Text = "00:00:00";
			// 
			// lblFilePercentage
			// 
			this.lblFilePercentage.Location = new System.Drawing.Point(361, 75);
			this.lblFilePercentage.Name = "lblFilePercentage";
			this.lblFilePercentage.Size = new System.Drawing.Size(75, 12);
			this.lblFilePercentage.TabIndex = 9;
			this.lblFilePercentage.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
			// 
			// timerUpdateTimeLbl
			// 
			this.timerUpdateTimeLbl.Tick += new System.EventHandler(this.timerUpdateTimeLbl_Tick);
			// 
			// lblTotalPercentage
			// 
			this.lblTotalPercentage.Location = new System.Drawing.Point(364, 156);
			this.lblTotalPercentage.Name = "lblTotalPercentage";
			this.lblTotalPercentage.Size = new System.Drawing.Size(70, 12);
			this.lblTotalPercentage.TabIndex = 10;
			this.lblTotalPercentage.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
			// 
			// FileOperationProgress
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 13F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(455, 204);
			this.Controls.Add(this.lblTotalPercentage);
			this.Controls.Add(this.lblFilePercentage);
			this.Controls.Add(this.lblResidualTime);
			this.Controls.Add(this.lblElapsedTime);
			this.Controls.Add(this.label4);
			this.Controls.Add(this.label3);
			this.Controls.Add(this.btnCancel);
			this.Controls.Add(this.lblFileName);
			this.Controls.Add(this.lblOperationName);
			this.Controls.Add(this.pbFile);
			this.Controls.Add(this.pbTotal);
			this.Font = new System.Drawing.Font("Verdana", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.Name = "FileOperationProgress";
			this.Text = "FileOperationProgress";
			this.Shown += new System.EventHandler(this.FileOperationProgress_Shown);
			this.ResumeLayout(false);
			this.PerformLayout();

		}

		#endregion

		private System.Windows.Forms.ProgressBar pbTotal;
		private System.Windows.Forms.ProgressBar pbFile;
		private System.Windows.Forms.Label lblOperationName;
		private System.Windows.Forms.Label lblFileName;
		private System.Windows.Forms.Button btnCancel;
		private System.Windows.Forms.Label label3;
		private System.Windows.Forms.Label label4;
		private System.Windows.Forms.Label lblElapsedTime;
		private System.Windows.Forms.Label lblResidualTime;
		private System.Windows.Forms.Label lblFilePercentage;
		private System.Windows.Forms.Timer timerUpdateTimeLbl;
		private System.Windows.Forms.Label lblTotalPercentage;
	}
}