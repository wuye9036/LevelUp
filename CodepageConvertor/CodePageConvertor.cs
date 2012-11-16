using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace CodepageConvertor {
	public partial class CodePageConvertor : Form {
		private Encoding srcEncoding;
		private Encoding targetEncoding;
		private List<int> validCPs = new List<int>();
		private string currentFileName = null;

		public CodePageConvertor() {
			InitializeComponent();
			InitializeCodePageComboBox();
		}

		private void InitializeCodePageComboBox(){
			int[] validCPArray = {
				932, 
				936, 
                950,
				1200, 1201, 
				1252, 10003, 10008, 20127, 20936, 20949, 28591, 
				50220, 50221, 50222,
				50225, 50227, 51932, 51936,
				51949, 52936, 54936,
				65000, 65001, 65005, 65006
			};
			validCPs.AddRange( validCPArray );
			foreach ( EncodingInfo encodeInfo in Encoding.GetEncodings() ) {
				if ( !validCPs.Contains( encodeInfo.CodePage ) ) {
					continue;
				}
				string encodeStr = string.Format( "{0} - {1}", encodeInfo.CodePage, encodeInfo.DisplayName );
				comboSrcCodePage.Items.Add( encodeStr );
				comboTargetCodePage.Items.Add( encodeStr );

				if ( encodeInfo.CodePage == 936 ) {
					comboSrcCodePage.SelectedItem = comboSrcCodePage.Items[comboSrcCodePage.Items.Count - 1];
				}

				if (encodeInfo.CodePage == 65001){
					comboTargetCodePage.SelectedItem = comboTargetCodePage.Items[comboTargetCodePage.Items.Count - 1];
				}
			}
		}

		private void UpdateEncoding() {
			string srcCPStr = (string)comboSrcCodePage.SelectedItem;
			string tarCPStr = (string)comboTargetCodePage.SelectedItem;

			if ( srcCPStr == null ) {
				MessageBox.Show( "请选择一个源代码页" );
			}

			if ( tarCPStr == null ) {
				MessageBox.Show( "请选择一个目标代码页" );
			}

			string srcCPCodeStr = srcCPStr.Split( "-".ToCharArray() )[0];
			string targetCPCodeStr = tarCPStr.Split( "-".ToCharArray() )[0];

			srcEncoding = Encoding.GetEncoding( int.Parse( srcCPCodeStr ) );
			targetEncoding = Encoding.GetEncoding( int.Parse( targetCPCodeStr ) );
		}

		private void Convert() {
			UpdateEncoding();
			tbContent.Text = targetEncoding.GetString( srcEncoding.GetBytes(tbContent.Text) );
		}

		private void btnConvert_Click( object sender, EventArgs e ) {
			Convert();
		}

		private void btnOpen_Click( object sender, EventArgs e ) {
			OpenFileDialog ofd = new OpenFileDialog();
			ofd.Filter = "Text Files(*.txt; *.cue)|*.txt;*.cue|All Files(*.*)|*.*";
			if( ofd.ShowDialog() != DialogResult.OK ){
				return;
			}

			OpenFile(ofd.FileName);
		}

		private void OpenFile(string fileName) {
			UpdateEncoding();
			tbContent.Text = System.IO.File.ReadAllText(fileName, srcEncoding);
			currentFileName = fileName;
		}

		private void SaveFile(string fileName) {
			UpdateEncoding();
			System.IO.File.WriteAllText(fileName, tbContent.Text, targetEncoding);
			currentFileName = fileName;
		}

		private void SaveFile() {
			SaveFile(currentFileName);
		}

		private void btnSaveAs_Click( object sender, EventArgs e ) {
			SaveFileDialog sfd = new SaveFileDialog();
			sfd.Filter = "Text Files(*.txt; *.cue)|*.txt;*.cue|All Files(*.*)|*.*";
			if ( sfd.ShowDialog() != DialogResult.OK ) {
				return;
			}

			SaveFile(sfd.FileName);
		}

		private void btnFromClipboard_Click( object sender, EventArgs e ) {
			if ( Clipboard.ContainsText() ) {
				tbContent.Text = Clipboard.GetText();
			}
		}

		private void btnToClipboard_Click( object sender, EventArgs e ) {
			Clipboard.SetText( tbContent.Text );
		}

		private void tbContent_DragEnter(object sender, DragEventArgs e) {
			if (e.Data.GetDataPresent(DataFormats.FileDrop)) {
				e.Effect = DragDropEffects.All;
			} else {
				e.Effect = DragDropEffects.None;
			}
		}

		private void tbContent_DragDrop(object sender, DragEventArgs e) {
			string fileName = ((string[])e.Data.GetData(DataFormats.FileDrop, false))[0];
			OpenFile(fileName);
		}

		private void btnSave_Click(object sender, EventArgs e) {
			if (currentFileName != null) {
				SaveFile();
			}
		}

	}
}