using System;
using System.Collections.Generic;
using System.Text;

using System.Drawing;
using Sharp3D.Math.Core;

namespace Mesh2D
{
	public class Drawer
	{
		public static void DrawSkeleton(Graphics g, Skeleton sk, int width, int height)
		{
			Pen p = new Pen(Color.Black, 1);
			Vector2D skpos;

			if (sk.Parent == null)
			{
				skpos = sk.Bone.RefPosition;
			}
			else
			{
				skpos = sk.Parent.Bone.TransformPosition(sk.Bone.RefPosition);
			}

			//画出当前骨骼节点

			Font font = new Font("Tahoma", 8);
			g.DrawString(
				sk.Bone.Name,
				font,
				Brushes.Black,
				(float)(width * skpos.X),
				(float)(height * skpos.Y)
				);

			//画个三角形，把骨骼的y朝向表示出来。
			double refPosx = sk.Bone.RefPosition.X;
			double refPosy = sk.Bone.RefPosition.Y;

			Vector2D tri0 = sk.Bone.TransformPosition(
				new Vector2D(refPosx - 0.02, sk.Bone.RefPosition.Y)
				);
			Vector2D tri1 = sk.Bone.TransformPosition(
				new Vector2D(refPosx + 0.02, sk.Bone.RefPosition.Y)
				);
			Vector2D tri2 = sk.Bone.TransformPosition(
				new Vector2D(refPosx, sk.Bone.RefPosition.Y - 0.1)
				);
			g.DrawLine(
				p,
				(float)(width * tri0.X),
				(float)(height * tri0.Y),
				(float)(width * tri1.X),
				(float)(height * tri1.Y)
				);
			g.DrawLine(
				p,
				(float)(width * tri0.X),
				(float)(height * tri0.Y),
				(float)(width * tri2.X),
				(float)(height * tri2.Y)
				);
			g.DrawLine(
				p,
				(float)(width * tri2.X),
				(float)(height * tri2.Y),
				(float)(width * tri1.X),
				(float)(height * tri1.Y)
				);
			//}
		}

		//递归的画出骨架树
		public static void DrawSkeletonDeep(Graphics g, Skeleton sk, int width, int height)
		{
			DrawSkeleton(g, sk, width, height);

			IList<Skeleton> children = sk.Children;
			if(children != null)
			{
				foreach(Skeleton child in children)
				{
					DrawSkeletonDeep(g, child, width, height);
				}
			}
		}

		public static void DrawPoint(Graphics g, Vector2D vec, int width, int height)
		{
			Pen p = new Pen(Color.Red, 1);
			g.DrawEllipse(
				p,
				(float)(width * vec.X - 1.0),
				(float)(height * vec.Y - 1.0),
				3,
				3);
		}

		//画出蒙皮上的顶点
		public static void DrawVertex(Graphics g, Vertex v, int width, int height)
		{
			Vector2D pt = v.GetTransformedPositon();
			DrawPoint(g, pt, width, height);
		}

		public static void DrawVertexList(Graphics g, IList<Vertex> verts, int width, int height)
		{
			foreach(Vertex vert in verts)
			{
				DrawVertex(g, vert, width, height);
			}
		}
	}
}
