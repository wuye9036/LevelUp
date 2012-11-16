using System;
using System.Collections.Generic;
using System.Text;

using System.Drawing;

namespace OverviewMapSandBox
{
	class Drawer
	{
		private Graphics g_;
		public Drawer(Graphics g)
		{
			g_ = g;
		}

		public void Draw(OverviewContainer ovCont)
		{
			g_.DrawRectangle(Pens.Black, Rectangle.Round(ovCont.Position));
			g_.DrawRectangle(Pens.Aqua, Rectangle.Round(ovCont.OvMap.OvPos));
			g_.DrawRectangle(Pens.Red, Rectangle.Round(ovCont.OvMap.ClippedFovPos));
		}
	}
}
