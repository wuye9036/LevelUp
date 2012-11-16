namespace Backuper
{
	partial class ChecksumOption
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
			this.cbIsUseSizeThreshold = new System.Windows.Forms.CheckBox();
			this.btnOK = new System.Windows.Forms.Button();
			this.btnCancel = new System.Windows.Forms.Button();
			this.comboThresholdType = new System.Windows.Forms.ComboBox();
			this.nudThreshold = new System.Windows.Forms.NumericUpDown();
			this.cbIsRecomputeAll = new System.Windows.Forms.CheckBox();
			this.groupBox1.SuspendLayout();
			( (System.ComponentModel.ISupportInitialize)( this.nudThreshold ) ).BeginInit();
			this.SuspendLayout();
			// 
			// groupBox1
			// 
			this.groupBox1.Controls.Add( this.cbIsRecomputeAll );
			this.groupBox1.Controls.Add( this.nudThreshold );
			this.groupBox1.Controls.Add( this.comboThresholdType );
			this.groupBox1.Controls.Add( this.cbIsUseSizeThreshold );
			this.groupBox1.Location = new System.Drawing.Point( 12, 12 );
			this.groupBox1.Name = "groupBox1";
			this.groupBox1.Size = new System.Drawing.Size( 437, 111 );
			this.groupBox1.TabIndex = 1;
			this.groupBox1.TabStop = false;
			this.groupBox1.Text = "Option";
			// 
			// cbIsUseSizeThreshold
			// 
			this.cbIsUseSizeThreshold.AutoSize = true;
			this.cbIsUseSizeThreshold.Location = new System.Drawing.Point( 21, 36 );
			this.cbIsUseSizeThreshold.Name = "cbIsUseSizeThreshold";
			this.cbIsUseSizeThreshold.Size = new System.Drawing.Size( 202, 17 );
			this.cbIsUseSizeThreshold.TabIndex = 0;
			this.cbIsUseSizeThreshold.Text = "Use File Size Threshold(As KB)";
			this.cbIsUseSizeThreshold.UseVisualStyleBackColor = true;
			// 
			// btnOK
			// 
			this.btnOK.Location = new System.Drawing.Point( 275, 151 );
			this.btnOK.Name = "btnOK";
			this.btnOK.Size = new System.Drawing.Size( 75, 23 );
			this.btnOK.TabIndex = 2;
			this.btnOK.Text = "OK";
			this.btnOK.UseVisualStyleBackColor = true;
			this.btnOK.Click += new System.EventHandler( this.btnOK_Click );
			// 
			// btnCancel
			// 
			this.btnCancel.Location = new System.Drawing.Point( 374, 151 );
			this.btnCancel.Name = "btnCancel";
			this.btnCancel.Size = new System.Drawing.Size( 75, 23 );
			this.btnCancel.TabIndex = 3;
			this.btnCancel.Text = "Cancel";
			this.btnCancel.UseVisualStyleBackColor = true;
			this.btnCancel.Click += new System.EventHandler( this.btnCancel_Click );
			// 
			// comboThresholdType
			// 
			this.comboThresholdType.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
			this.comboThresholdType.FormattingEnabled = true;
			this.comboThresholdType.Items.AddRange( new object[] {
            "Least",
            "Most"} );
			this.comboThresholdType.Location = new System.Drawing.Point( 251, 36 );
			this.comboThresholdType.Name = "comboThresholdType";
			this.comboThresholdType.Size = new System.Drawing.Size( 74, 21 );
			this.comboThresholdType.TabIndex = 1;
			// 
			// nudThreshold
			// 
			this.nudThreshold.Location = new System.Drawing.Point( 334, 36 );
			this.nudThreshold.Maximum = new decimal( new int[] {
            1000000000,
            0,
            0,
            0} );
			this.nudThreshold.Name = "nudThreshold";
			this.nudThreshold.Size = new System.Drawing.Size( 82, 21 );
			this.nudThreshold.TabIndex = 2;
			// 
			// cbIsRecomputeAll
			// 
			this.cbIsRecomputeAll.AutoSize = true;
			this.cbIsRecomputeAll.Location = new System.Drawing.Point( 21, 70 );
			this.cbIsRecomputeAll.Name = "cbIsRecomputeAll";
			this.cbIsRecomputeAll.Size = new System.Drawing.Size( 167, 17 );
			this.cbIsRecomputeAll.TabIndex = 3;
			this.cbIsRecomputeAll.Text = "Update Exist Checksums";
			this.cbIsRecomputeAll.UseVisualStyleBackColor = true;
			// 
			// ChecksumOption
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF( 7F, 13F );
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size( 462, 191 );
			this.Controls.Add( this.btnCancel );
			this.Controls.Add( this.btnOK );
			this.Controls.Add( this.groupBox1 );
			this.Font = new System.Drawing.Font( "Verdana", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ( (byte)( 0 ) ) );
			this.Name = "ChecksumOption";
			this.Text = "Compute Checksum";
			this.groupBox1.ResumeLayout( false );
			this.groupBox1.PerformLayout();
			( (System.ComponentModel.ISupportInitialize)( this.nudThreshold ) ).EndInit();
			this.ResumeLayout( false );

		}

		#endregion

		private System.Windows.Forms.GroupBox groupBox1;
		private System.Windows.Forms.CheckBox cbIsUseSizeThreshold;
		private System.Windows.Forms.Button btnOK;
		private System.Windows.Forms.Button btnCancel;
		private System.Windows.Forms.NumericUpDown nudThreshold;
		private System.Windows.Forms.ComboBox comboThresholdType;
		private System.Windows.Forms.CheckBox cbIsRecomputeAll;
	}
}