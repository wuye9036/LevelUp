using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.Data.OleDb;
using System.Collections.Specialized;

namespace DatabaseReschema_AddField
{
	public partial class mainForm : Form
	{
		public mainForm()
		{
			InitializeComponent();
		}

		private void openFile_Click(object sender, EventArgs e)
		{
			openFileDlg.CheckPathExists = true;
			openFileDlg.CheckFileExists = true;
			openFileDlg.Multiselect = false;
			openFileDlg.FileName = "";
			openFileDlg.Filter = "数据库文件(*.mdb)|*.mdb|所有文件(*.*)|*.*";
			openFileDlg.Title = "打开数据库文件";
			
			if (openFileDlg.ShowDialog() == DialogResult.OK)
			{
				fileNameTB.Text = openFileDlg.FileName;
			}
		}

		private void addField_Click(object sender, EventArgs e)
		{
			StringBuilder sb = new StringBuilder();

			if (String.IsNullOrEmpty(textBox2.Text) || String.IsNullOrEmpty(fileNameTB.Text))
			{
				//sb.Append("Provider=Microsoft.Jet.OLEDB.4.0;Data Source=\"C:\\Documents and Settings\\LightSky\\桌面\\DBTest.mdb\"");
				sb.AppendFormat("Provider=Microsoft.Jet.OLEDB.4.0;Data Source=\"{0}\";"
				, fileNameTB.Text);
			}
			else
			{
				sb.AppendFormat("Provider=Microsoft.Jet.OLEDB.4.0;Data Source=\"{0}\";User ID={1};Password={2};"
		,fileNameTB.Text, textBox1.Text, textBox2.Text );
			}

			OleDbConnection dbconn = new OleDbConnection();
			dbconn.ConnectionString = sb.ToString();
			dbconn.Open();
			if (dbconn.State != ConnectionState.Open)
			{
				MessageBox.Show("数据库打开出错！");
			}

			DataTable dt = dbconn.GetSchema("Tables");
			StringCollection sc = new StringCollection();
			foreach(DataRow row in dt.Rows)
			{
				if((string)(row["TABLE_TYPE"]) == "TABLE")
				{
					sc.Add((string)row["TABLE_NAME"]);
				}
			}
			fieldListBox.DataSource = sc;

			OleDbCommand addCmd = new OleDbCommand();
			StringBuilder errStr = new StringBuilder();

			foreach (string tableName in sc)
			{
				if (char.ToLower(tableName[0]) != 'a')
					continue;
				addCmd.Connection = dbconn;
				addCmd.CommandText = "ALTER TABLE " + sc[0] + " ADD COLUMN JLSJ TEXT(8)";
				try
				{
					addCmd.ExecuteNonQuery();
				}
				catch (Exception exc)
				{
					errStr.AppendFormat("{0}\n", exc.Message);
				}

				addCmd.CommandText = "ALTER TABLE " + sc[0] + " ADD COLUMN SCSJ TEXT(8)";
				try
				{
					addCmd.ExecuteNonQuery();
				}
				catch (Exception exc)
				{
					errStr.AppendFormat("{0}\n", exc.Message);
				}
			}

			if (!string.IsNullOrEmpty(errStr.ToString()))
			{
				MessageBox.Show(errStr.ToString(), "Error");
			}
		}
	}
}