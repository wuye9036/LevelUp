using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

using Sharp3D.Math.Core;

namespace Mesh2D
{
	public partial class Animation2DDemo : Form
	{
		private Skeleton root;
		private Skeleton c00;
		private Skeleton c10;
		private Skeleton c20;

		private List<Vertex> verts;

		public Animation2DDemo()
		{
			InitializeComponent();
			PrepareData();
		}

		private void btnDraw_Click(object sender, EventArgs e)
		{
			DrawDemo();
		}

		private void sbBone00_ValueChanged(object sender, EventArgs e)
		{
			double angle = (double)this.sbBone00.Value / 100.0;
			c00.Bone.SetLocalMatrix(Matrix.Rotate2D(angle));

			DrawDemo();
		}

		private void sbBone10_ValueChanged(object sender, EventArgs e)
		{
			double angle = (double)this.sbBone10.Value / 100.0;
			c10.Bone.SetLocalMatrix(Matrix.Rotate2D(angle));

			DrawDemo();
		}

		private void sbBone20_ValueChanged(object sender, EventArgs e)
		{
			double angle = (double)this.sbBone20.Value / 100.0;
			c20.Bone.SetLocalMatrix(Matrix.Rotate2D(angle));

			DrawDemo();
		}

		private void DrawDemo()
		{
			Graphics g = this.panelDraw.CreateGraphics();

			g.Clear(Color.LightGray);

			root.UpdateDeep();
			Drawer.DrawSkeletonDeep(g, c00, this.panelDraw.Width, this.panelDraw.Height);
			Drawer.DrawVertexList(g, verts, this.panelDraw.Width, this.panelDraw.Height);
		}

		private void PrepareData()
		{
			//构造骨架
			root = new Skeleton(new Bone("root"), null);
			root.Bone.RefPosition = new Vector2D(0.5, 0.5);
			root.Bone.SetLocalMatrix(Matrix.Transform2D(0.5, 0.5));

			c00 = new Skeleton(new Bone("c00"), root);
			c00.Bone.RefPosition = new Vector2D(0.5, 0.5);

			c10 = new Skeleton(new Bone("c10"), c00);
			c10.Bone.RefPosition = new Vector2D(0.5, 0.35);

			c20 = new Skeleton(new Bone("c20"), c10);
			c20.Bone.RefPosition = new Vector2D(0.5, 0.2);

			IList<Bone> bones = new List<Bone>();
			bones.Add(c00.Bone);
			bones.Add(c10.Bone);
			bones.Add(c20.Bone);

			IList<double> weights;
			
			double w0, w1, w2, totalw;

			//生成蒙皮
			//生成两根蒙皮的竖线，权重矩阵为反距离平方
			verts = new List<Vertex>();
			for(int i = 0; i < 48; ++i)
			{
				Vector2D posl = new Vector2D(0.49, 0.51 - i * 0.01);
				Vector2D posr = new Vector2D(0.51, 0.51 - i * 0.01);

				weights = new List<double>();

				w0 = 1.0 / Vector2D.Subtract(posl, c00.Bone.RefPosition).GetLengthSquared();
				w1 = 1.0 / Vector2D.Subtract(posl, c10.Bone.RefPosition).GetLengthSquared();
				w2 = 1.0 / Vector2D.Subtract(posl, c20.Bone.RefPosition).GetLengthSquared();

				totalw = w0 + w1 + w2;
				w0 /= totalw;
				w1 /= totalw;
				w2 /= totalw;

				weights.Add(w0);
				weights.Add(w1);
				weights.Add(w2);

				Vertex vertl = new Vertex(posl, bones, weights);
				Vertex vertr = new Vertex(posr, bones, weights);

				verts.Add(vertl);
				verts.Add(vertr);
			}
		}

		private void panelDraw_Paint(object sender, PaintEventArgs e)
		{
			DrawDemo();
		}
	}
}