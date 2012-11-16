using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace Backuper
{
	public enum ExportContent{
		None,
		New,
		Common
	}

	public enum ExportFormat{
		None,
		XML,
		Text,
		CopyFile,
		MoveFile
	}

	public partial class ExportOption : Form
	{
		public TreeSide ExportTreeSide = TreeSide.None;
		public ExportContent ExportContent = ExportContent.None;
		public ExportFormat ExportFormat = ExportFormat.None;
		public string ExportPath = "";

		public bool IsOK = false;

		public ExportOption() {
			InitializeComponent();
		}

		private void btnOK_Click(object sender, EventArgs e)
		{
			if (rbExportNew.Checked)
			{
				ExportContent = ExportContent.New;
			}
			if (rbExportCommon.Checked)
			{
				ExportContent = ExportContent.Common;
			}

			if (rbXML.Checked)
			{
				ExportFormat = ExportFormat.XML;
				ExportPath = tbXMLPath.Text;
			}
			if (rbText.Checked)
			{
				ExportFormat = ExportFormat.Text;
				ExportPath = tbTextPath.Text;
			}
			if (rbCopyFiles.Checked)
			{
				ExportFormat = ExportFormat.CopyFile;
				ExportPath = tbCopyFilePath.Text;
			}
			if (rbMoveFiles.Checked)
			{
				ExportFormat = ExportFormat.MoveFile;
				ExportPath = tbMoveFilePath.Text;
			}

			if (
				ExportContent != ExportContent.None
				&& ExportFormat != ExportFormat.None
				&& !string.IsNullOrEmpty(ExportPath)
				)
			{
				IsOK = true;
				Close();
			}
			else
			{
				MessageBox.Show("Export options has some matters. Please check and repair options.");
			}
		}

		private void btnCancel_Click(object sender, EventArgs e)
		{
			IsOK = false;
			ExportContent = ExportContent.None;
			ExportFormat = ExportFormat.None;
			ExportPath = "";
			Close();
		}

		private void btnOpenXMLFile_Click(object sender, EventArgs e)
		{
			SaveFileDialog ofd = new SaveFileDialog();
			ofd.Filter = "Backup Guy Export XML File(*.bex)|*.bex";
			ofd.OverwritePrompt = true;
			if (ofd.ShowDialog() == DialogResult.OK)
			{
				tbXMLPath.Text = ofd.FileName;
				rbXML.Checked = true;
			}
		}

		private void btnOpenTextFile_Click(object sender, EventArgs e)
		{
			SaveFileDialog ofd = new SaveFileDialog();
			ofd.Filter = "Backup Guy Export Text File(*.bet)|*.bet";
			ofd.OverwritePrompt = true;
			if (ofd.ShowDialog() == DialogResult.OK)
			{
				tbTextPath.Text = ofd.FileName;
				rbText.Checked = true;
			}
		}

		private void btnOpenCopyDestDir_Click(object sender, EventArgs e)
		{
			FolderBrowserDialog fbd = new FolderBrowserDialog();
			fbd.ShowNewFolderButton = true;
			if (fbd.ShowDialog() == DialogResult.OK)
			{
				tbCopyFilePath.Text = fbd.SelectedPath;
				rbCopyFiles.Checked = true;
			}
		}

		private void btnOpenMoveDestDir_Click(object sender, EventArgs e)
		{
			FolderBrowserDialog fbd = new FolderBrowserDialog();
			fbd.ShowNewFolderButton = true;
			if (fbd.ShowDialog() == DialogResult.OK)
			{
				tbMoveFilePath.Text = fbd.SelectedPath;
				rbMoveFiles.Checked = true;
			}
		}




	}
}