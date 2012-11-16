using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace OverviewMapSandBox
{
	public partial class OverviewSandbox : Form
	{
		private OverviewContainer ovCont_ = 
			new OverviewContainer(
				new RectangleF(10, 10, 100, 100),
				new RectangleF(-500, -500, 750, 1000),
				new RectangleF(-250, -250, 700, 900)
			);
		public OverviewSandbox()
		{
			InitializeComponent();
		}

		private void OverviewSandbox_Paint(object sender, PaintEventArgs e)
		{
			Drawer dr = new Drawer(e.Graphics);
			dr.Draw(ovCont_);
		}
	}
}