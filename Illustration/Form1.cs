using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Drawing.Imaging;

using System.Text;
using System.Windows.Forms;

namespace Illustration
{
	public partial class Form1 : Form
	{
		public Form1()
		{
			InitializeComponent();
		}

		private void Form1_Load(object sender, EventArgs e)
		{
			Font txtFont = new Font("Times New Roman", 10);
			Font bigFont = new Font("Times New Roman", 14);
			Bitmap bmp = new Bitmap(1000, 1000, PixelFormat.Format32bppArgb);
			Graphics g = Graphics.FromImage(bmp);
			g.Clear(Color.White);

			StringFormat sf = new StringFormat();
			sf.Alignment = StringAlignment.Center;
			sf.LineAlignment = StringAlignment.Center;

			//Rect 1 AND 2
			g.DrawRectangle(Pens.Black, new Rectangle(40, 50, 40, 120));
			g.DrawRectangle(Pens.Black, new Rectangle(80, 50, 40, 120));
			g.DrawString("1", txtFont, Brushes.Black, new Rectangle(40, 50, 40, 120), sf);
			g.DrawString("2", txtFont, Brushes.Black, new Rectangle(80, 50, 40, 120), sf);

			//Operator +
			g.DrawString("+", bigFont, Brushes.Black, new Rectangle(130, 100, 20, 20), sf);

			//Rect A AND B
			g.DrawRectangle(Pens.Black, new Rectangle(160, 70, 120, 40));
			g.DrawRectangle(Pens.Black, new Rectangle(160, 110, 120, 40));
			g.DrawString("A", txtFont, Brushes.Black, new Rectangle(160, 70, 120, 40), sf);
			g.DrawString("B", txtFont, Brushes.Black, new Rectangle(160, 110, 120, 40), sf);

			//Operator =
			g.DrawString("=", bigFont, Brushes.Black, new Rectangle(290, 100, 20, 20), sf);

			//Overlapped
			//Rect 1 AND 2
			//g.DrawRectangle(Pens.Black, new Rectangle(40, 50, 20, 80));
			//g.DrawRectangle(Pens.Black, new Rectangle(60, 50, 20, 80));
			g.DrawRectangle(Pens.Black, new Rectangle(320, 70, 120, 40));
			g.DrawRectangle(Pens.Black, new Rectangle(320, 110, 120, 40));
			g.DrawString("1A", txtFont, Brushes.Black, new Rectangle(340, 70, 40, 40), sf);
			g.DrawString("1B", txtFont, Brushes.Black, new Rectangle(340, 110, 40, 40), sf);
			g.DrawString("2A", txtFont, Brushes.Black, new Rectangle(40, 50, 20, 80), sf);
			g.DrawString("2B", txtFont, Brushes.Black, new Rectangle(60, 50, 20, 80), sf);
			pictureBox1.BackgroundImage = bmp;
		}
	}
}