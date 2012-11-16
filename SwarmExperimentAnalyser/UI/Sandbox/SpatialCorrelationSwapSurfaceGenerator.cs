using System;
using System.Collections.Generic;
using System.Text;

namespace SwarmExperimentalAnalyser.UI.Sandbox {
	class SpatialCorrelationSwapSurfaceGenerator: SurfaceGenerator {
		public SpatialCorrelationSwapSurfaceGenerator() {
		}

		public override double[,] Generate(int size) {
			double[,] data = InitializeDataArray(size);
			int count = 0;
			for (; ; ) {
				int orgX = 0, orgY = 0;
				RandomPoint(size, out orgX, out orgY);
				data[orgX, orgY] = 0.0f;
				for (int iCount = 0; iCount < 12000; ++iCount) {
					int destX0 = 0, destY0 = 0;
					RandomPoint(size, orgX, orgY, out destX0, out destY0);
					int destX1 = 0, destY1 = 0;
					RandomPoint(size, orgX, orgY, out destX1, out destY1);
					int distSqr0 = DistanceSqr(orgX, orgY, destX0, destY0);
					int distSqr1 = DistanceSqr(orgX, orgY, destX1, destY1);
					double orgValue = Convert.ToDouble(data[orgX, orgY]);
					double diff0 = Math.Abs(Convert.ToDouble(data[destX0, destY0]) - orgValue);
					double diff1 = Math.Abs(Convert.ToDouble(data[destX1, destY1]) - orgValue);
					if (
						((distSqr0 > distSqr1) && (diff0 < diff1))
						|| ((distSqr0 < distSqr1) && (diff1 < diff0))
						) {
						Swap(ref data[destX0, destY0], ref data[destX1, destY1]);
					}
				}

				if (count % 10 == 0) {
					if (!NotifyOnTrack(data)) {
						return data;
					}
				}
				++count;
			}
		}

		private void Swap(ref double x, ref double y) {
			double t = x;
			x = y;
			y = t;
		}
		private int DistanceSqr(int x0, int y0, int x1, int y1) {
			return (x0 - x1) * (x0 - x1) + (y0 - y1) * (y0 - y1);
		}

		private void RandomPoint(int size, out int x, out int y) {
			x = rand.Next(0, size);
			y = rand.Next(0, size);
		}
		private void RandomPoint(int size, int cx, int cy, out int x, out int y) {
			int r = rand.Next(size);
			
			int left = Math.Max(0, cx - r);
			int right = Math.Min(size - 1, cx + r);
			int top = Math.Max(0, cy - r);
			int bottom = Math.Min(size - 1, cy + r);

			x = rand.Next(left, right);
			y = rand.Next(top, bottom);
		}

		private double[,] InitializeDataArray(int size) {
			double[,] data = new double[size, size];
			for (int x = 0; x < size; ++x) {
				for (int y = 0; y < size; ++y) {
					data[x, y] = rand.NextDouble();
				}
			}
			return data;
		}

		private Random rand;
	}
}
