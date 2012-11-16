using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace RasterizerShow
{
	public partial class Form1 : Form
	{
		public Form1()
		{
			InitializeComponent();
		}

		private void Form1_Load(object sender, EventArgs e)
		{

		}

		private void DrawTriangle( PointF pt0, PointF pt1, PointF pt2 )
		{
			pt0.X *= (ras.CellSize + 2);
			pt0.Y *= (ras.CellSize + 2);

			pt1.X *= (ras.CellSize + 2);
			pt1.Y *= (ras.CellSize + 2);

			pt2.X *= (ras.CellSize + 2);
			pt2.Y *= (ras.CellSize + 2);

			Bitmap bmp = new Bitmap(ras.Bitmap);
			Graphics g = Graphics.FromImage(bmp);
			g.DrawPolygon( Pens.Yellow, new PointF[]{pt0, pt1, pt2} );

			this.BackgroundImage = bmp;
			this.BackgroundImageLayout = ImageLayout.Center;
		}

		private void DrawHorizontalSplitter( PointF pt0, PointF pt1, PointF pt2 )
		{
		}

		private bool PositiveOfLine(int x, int y, PointF pt0, PointF pt1)
		{
			float diffY = pt1.Y - pt0.Y;
			float diffX = pt1.X - pt0.X;

			return ((float)y + 0.5F) * diffX - pt0.Y * diffX - ((float)x + 0.5F - pt0.X) * diffY < 0;
		}

		private void Form1_MouseClick(object sender, MouseEventArgs e)
		{
			
			ras = new Raster();
			ras.Width = rWidth;
			ras.Height = rHeight;

			for (int i = 0; i < rWidth; ++i)
			{
				for (int j = 0; j < rHeight; ++j)
				{
					if ( PositiveOfLine(i, j, pt0, pt1) && PositiveOfLine(i, j, pt1, pt2) && PositiveOfLine(i, j, pt2, pt0) )
					{
						if( )
						ras.ActiveCell(i, j);
					}
				}
			}

			DrawTriangle(pt0, pt1, pt2);
		}

		private PointF pt0 = new PointF(9.7F, 1.8F);
		private PointF pt1 = new PointF(1.3F, 7.6F);
		private PointF pt2 = new PointF(13.1F, 14.8F);

		private Raster ras;
		private int rWidth = 16;
		private int rHeight = 16;
	}
}
