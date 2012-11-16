using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

using System.Drawing.Imaging;

namespace WindowsApplication1
{
	public partial class MainForm : Form
	{
		public MainForm()
		{
			InitializeComponent();
		}

		private void btnLoad0_Click(object sender, EventArgs e)
		{
			OpenFileDialog ofDlg = new OpenFileDialog();
			ofDlg.Filter = "位图文件(*.BMP) | *.BMP";
			ofDlg.Multiselect = false;

			ofDlg.ShowDialog();
			if (!string.IsNullOrEmpty(ofDlg.FileName))
			{
				string fileName = ofDlg.FileName;
				src0PicBox.ImageLocation = fileName;
			}
		}

		private void btnLoad1_Click(object sender, EventArgs e)
		{
			OpenFileDialog ofDlg = new OpenFileDialog();
			ofDlg.Filter = "位图文件(*.BMP) | *.BMP";
			ofDlg.Multiselect = false;

			ofDlg.ShowDialog();
			if (!string.IsNullOrEmpty(ofDlg.FileName))
			{
				string fileName = ofDlg.FileName;
				src1PicBox.ImageLocation = fileName;
			}
		}

		private void btnSyn_Click(object sender, EventArgs e)
		{
			Image img0 = src0PicBox.Image;
			Image img1 = src1PicBox.Image;
			if (img0 == null)
			{
				MessageBox.Show("请装载第一张图！");
				return;
			}
			if (img1 == null)
			{
				MessageBox.Show("请装载第二张图！");
				return;
			}

			if ((double)img0.Width / img0.Height * img1.Height != img1.Width)
			{
				MessageBox.Show("两张比例不一致，无法融合！");
				return;
			}

			Bitmap bmp0 = null;
			Bitmap bmp1 = null;
			Bitmap bmpdest = null;

			if (img0.Width > img1.Width)
			{
				bmp0 = new Bitmap(img0);
				bmp1 = new Bitmap(img1, img0.Size);
				bmpdest = new Bitmap(img0.Width, img0.Height);
			}
			else
			{
				bmp0 = new Bitmap(img0, img1.Size);
				bmp1 = new Bitmap(img1);
				bmpdest = new Bitmap(img1.Width, img1.Height);
			}

			Rectangle rc = new Rectangle(0, 0, bmp0.Width, bmp0.Height);

			//BitmapData bmpData0 = bmp0.LockBits(rc, ImageLockMode.ReadOnly, PixelFormat.Format24bppRgb);
			//BitmapData bmpData1 = bmp1.LockBits(rc, ImageLockMode.ReadOnly, PixelFormat.Format24bppRgb);
			//BitmapData bmpDataDest = bmpdest.LockBits(rc, ImageLockMode.WriteOnly, PixelFormat.Format24bppRgb);

			for (int iY = 0; iY < bmp0.Height; ++iY)
			{
				for (int iX = 0; iX < bmp0.Width; ++iX)
				{
					Color p0 = bmp0.GetPixel(iX, iY);
					Color p1 = bmp1.GetPixel(iX, iY);

					double h0, l0, s0;
					double h1, l1, s1;
					byte r, g, b;

					RGB2HLS(p0.R, p0.G, p0.B, out h0, out l0, out s0);
					RGB2HLS(p1.R, p1.G, p1.B, out h1, out l1, out s1);

					HLS2RGB(h1, l0, s1, out r, out g, out b);

					bmpdest.SetPixel(iX, iY, Color.FromArgb(r, g, b));
				}
			}

			destPicBox.Image = bmpdest;
		}

		private void RGB2HLS(byte r, byte g, byte b, out double h, out double l, out double s)
		{
			byte minval = Math.Min(r, Math.Min(g, b));
			byte maxval = Math.Max(r, Math.Max(g, b));
			double mdiff = (double)maxval - (double)minval;
			double msum = (double)maxval + (double)minval;

			h = l = s = 0.0;

			l = msum / 512.0;
			if (maxval == minval)
			{
				s = 0.0;
				h = 0.0;
			}
			else
			{
				double rnorm = (maxval - r) / mdiff;
				double gnorm = (maxval - g) / mdiff;
				double bnorm = (maxval - b) / mdiff;

				s = (l <= 0.5f) ? (mdiff / msum) : (mdiff / (512.0 - msum));

				if (r == maxval) h = 60.0 * (6.0 + bnorm - gnorm);
				if (g == maxval) h = 60.0 * (2.0 + rnorm - bnorm);
				if (b == maxval) h = 60.0 * (4.0 + gnorm - rnorm);
				if (h > 360.0) h = h - 360.0;
			}
		}

		private void HLS2RGB(double h, double l, double s, out byte r, out byte g, out byte b)
		{
			if (s == 0.0) // Grauton, einfacher Fall
			{
				r = g = b = (byte)(l * 255.0);
			}
			else
			{
				double rm1, rm2;

				if (l <= 0.5f)
				{
					rm2 = l + l * s;
				}
				else
				{
					rm2 = l + s - l * s;
				}

				rm1 = 2.0 * l - rm2;
				r = ToRGB1(rm1, rm2, h + 120.0);
				g = ToRGB1(rm1, rm2, h);
				b = ToRGB1(rm1, rm2, h - 120.0);
			}
		}


		private byte ToRGB1(double rm1, double rm2, double rh)
		{
			if (rh > 360.0) rh -= 360.0;
			else if (rh < 0.0) rh += 360.0;

			if (rh < 60.0) rm1 = rm1 + (rm2 - rm1) * rh / 60.0;
			else if (rh < 180.0) rm1 = rm2;
			else if (rh < 240.0) rm1 = rm1 + (rm2 - rm1) * (240.0 - rh) / 60.0;

			return (byte)(rm1 * 255);
		}

		private void btnSave_Click(object sender, EventArgs e)
		{
			SaveFileDialog sfDlg = new SaveFileDialog();
			sfDlg.Filter = "Bitmap File(*.bmp)|*.bmp";
			sfDlg.ShowDialog();
			if (!String.IsNullOrEmpty(sfDlg.FileName))
			{
				destPicBox.Image.Save(sfDlg.FileName);
			}
		}
	}
}