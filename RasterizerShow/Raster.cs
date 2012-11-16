using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Drawing;

namespace RasterizerShow
{
	public class Raster
	{
		public Bitmap Bitmap
		{
			get { return bmp; }
		}

		public Color GridColor
		{
			get { return gColor; }
			set { gColor = value; }
		}

		public Color LineColor
		{
			get { return lColor; }
			set { lColor = value; }
		}

		public int CellSize
		{
			get { return cellSize; }
			set { cellSize = value; }
		}

		public int Width
		{
			get { return width; }
			set { width = value; Update(true); }
		}

		public int Height
		{
			get { return height; }
			set { height = value; Update(true); }
		}

		public void ActiveCell(int x, int y)
		{
			actives[y, x] = true;
			DrawCell(x, y);
			DrawTile(x / tileSize, y / tileSize, true);
		}

		public void InactiveCell(int x, int y)
		{
			actives[y, x] = false;
			DrawCell(x, y);
			DrawTile(x / tileSize, y / tileSize, true);
		}

		private void Update( bool updateActive )
		{
			if( width == 0 || height == 0 || cellSize == 0 )
			{
				return;
			}

			int destWidth = width * (cellSize + 2);
			int destHeight = height * (cellSize + 2);
			if ( bmp == null || bmp.Width < destWidth || bmp.Height < destHeight )
			{
				bmp = new Bitmap(destWidth, destHeight);
			}

			if (updateActive)
			{
				actives = new bool[height, width];
			}
			for (int i = 0; i < height; ++i)
			{
				for (int j = 0; j < width; ++j)
				{
					if (updateActive)
					{
						actives[i, j] = false;
					}
					DrawCell(j, i);
					DrawTile(j / tileSize, i / tileSize, false);
				}
			}
		}

		private void DrawCell(int x, int y)
		{
			Graphics g = Graphics.FromImage(bmp);
			Color cColor = actives[y, x] ? aColor : gColor;
			g.FillRectangle(new SolidBrush(cColor), x * ( cellSize + 2 )+1, y * (cellSize + 2)+1, cellSize, cellSize);
			g.DrawRectangle(new Pen(lColor), x * (cellSize + 2), y * (cellSize + 2), cellSize + 1, cellSize + 1);
			g.FillEllipse(new SolidBrush(centerColor),
				x * (cellSize + 2) + cellSize / 2 - centerSize / 2,
				y * (cellSize + 2) + cellSize / 2 - centerSize / 2,
				centerSize,
				centerSize
				);
		}

		private void DrawTile(int x, int y, bool isActive)
		{
			Graphics g = Graphics.FromImage(bmp);
			Color c = isActive ? Color.Red : Color.White;
			g.DrawRectangle(
			    new Pen(c),
			    x * tileSize * (cellSize + 2),
			    y * tileSize * (cellSize + 2),
			    (cellSize + 2) * tileSize - 1,
			    (cellSize + 2) * tileSize - 1
			    );
		}

		private Color gColor = Color.Gray;
		private Color aColor = Color.Blue;
		private Color lColor = Color.Black;
		private Color centerColor = Color.White;

		private Bitmap bmp;

		private int tileSize = 4;
		private int cellSize = 32;
		private int centerSize = 4;
		private int width;
		private int height;
		private bool[,] actives;
	}
}
