using System;
using System.Collections.Generic;
using System.Text;
using Sharp3D.Math.Core;

namespace Mesh2D
{
	public class Matrix
	{
		public static Matrix3D Rotate2D(double theta)
		{
			return new Matrix3D(
				Math.Cos(theta), -Math.Sin(theta), 0.0f,
				Math.Sin(theta), Math.Cos(theta), 0.0f,
				0.0f, 0.0f, 1.0f
				);
		}

		public static Matrix3D Transform2D(double offsetx, double offsety)
		{
			return new Matrix3D(
				1.0, 0.0, offsetx,
				0.0, 1.0, offsety,
				0.0, 0.0, 1.0
				);
		}
	}
}
