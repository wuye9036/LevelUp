using System;
using System.Collections.Generic;
using System.Text;
using System.Drawing;
using System.Drawing.Imaging;

namespace SwarmExperimentalAnalyser.UI.Plotters {
	public struct ColorValuePair: IComparable<ColorValuePair>{
		public Color Color;
		public double Value;

		public static ColorValuePair Create( Color c, double v){
			ColorValuePair ret;
			ret.Color = c;
			ret.Value = v;
			return ret;
		}

		public int CompareTo(ColorValuePair other) {
			double diff = other.Value - Value;
			if (diff < -float.Epsilon) {
				return 1;
			}
			if (float.Epsilon < diff) {
				return -1;
			}
			return 0;
		}
	}

	class ColorMapGenerator {
		private ColorMapGenerator() {
		}

		static public ColorMapGenerator Instance {
			get {
				if (instance_ == null) {
					instance_ = new ColorMapGenerator();
				}
				return instance_;
			}
		}

		public ColorMap GenerateLinearColorMap(Color fromColor, Color toColor, double min, double max) {
			List<ColorValuePair> cMap = new List<ColorValuePair>(
				new ColorValuePair[] { ColorValuePair.Create(fromColor, min), ColorValuePair.Create(toColor, max) }
				);
			return new LinearColorMap(cMap);
		}

		static ColorMapGenerator instance_;
	}

	public interface ColorMap {
		Color Lookup(double value);
	}

	class LinearColorMap: ColorMap {
		public LinearColorMap(List<ColorValuePair> colorMap) {
			colorMap_ = colorMap;
			colorMap_.Sort();
		}

		public Color Lookup(double value) {
			int startId = LookupSegment(0, colorMap_.Count - 1, value);
			int endId = startId + 1;
			if (startId == -1) {
				return colorMap_[0].Color;
			}
			if (endId == colorMap_.Count) {
				return colorMap_[endId - 1].Color;
			}

			//线性插值一下
			ColorValuePair startCV = colorMap_[startId];
			ColorValuePair endCV = colorMap_[endId];
			double t = 0.5;
			if ( Math.Abs(startCV.Value - endCV.Value) > float.Epsilon) {
				t = (endCV.Value - value) / (endCV.Value - startCV.Value);
			}
			double one_t = 1.0 - t;
			return Color.FromArgb(
				(int)(startCV.Color.R * t + endCV.Color.R * one_t),
				(int)(startCV.Color.G * t + endCV.Color.G * one_t),
				(int)(startCV.Color.B * t + endCV.Color.B * one_t)
				);
		}

		public int LookupSegment(int minId, int maxId, double value) {
			if (colorMap_[minId].Value > value) {
				return minId - 1;
			}

			if (colorMap_[maxId].Value < value) {
				return maxId;
			}

			if (maxId - minId < 2) {
				return minId;
			}

			int midId = (maxId + minId) / 2;
			if (colorMap_[midId].Value > value) {
				return LookupSegment(minId, midId, value);
			} else {
				return LookupSegment(midId, maxId, value);
			}
		}

		private List<ColorValuePair> colorMap_;
	}

	public class Array2DPlotter {
		public Array2DPlotter(object[,] arr2d) {
			cMap_ = null;
			data_ = arr2d;

			int xLength = data_.GetLength(0);
			int yLength = data_.GetLength(1);

			double min = Convert.ToDouble(data_[0, 0]);
			double max = Convert.ToDouble(data_[0, 0]);

			for (int x = 0; x < xLength; ++x) {
				for (int y = 0; y < yLength; ++y) {
					min = Math.Min(Convert.ToDouble(data_[x, y]), min);
					max = Math.Max(Convert.ToDouble(data_[x, y]), max);
				}
			}

			cMap_ = ColorMapGenerator.Instance.GenerateLinearColorMap(Color.Black, Color.Yellow, min, max);

		}
		
		public Array2DPlotter(ColorMap cMap) {
			cMap_ = cMap;
		}

		public ColorMap ColorMap {
			get { return cMap_; }
			set { cMap_ = value; }
		}

		public void ResetData(object[,] data) {
			data_ = data;
			if (bmp_ != null) {
				ResetData(data, bmp_.Width, bmp_.Height);
			}
		}

		public void ResetData( object[,] data, int destW, int destH ) {
			data_ = data;

			int xLength = data_.GetLength(0);
			int yLength = data_.GetLength(1);

			int xScale = (destW + xLength - 1) / xLength;
			int yScale = (destH + yLength - 1) / yLength;

			int scale = Math.Min(xScale, yScale);

			int bitmapWidth = xLength * scale;
			int bitmapHeight = yLength * scale;

			if (bmp_ == null || bmp_.Width != bitmapWidth || bmp_.Height != bitmapHeight ) {
				bmp_ = new Bitmap(bitmapWidth, bitmapHeight, PixelFormat.Format24bppRgb);	
			}

			BitmapData lockedData = bmp_.LockBits(Rectangle.FromLTRB(0, 0, bitmapWidth, bitmapHeight), System.Drawing.Imaging.ImageLockMode.WriteOnly, System.Drawing.Imaging.PixelFormat.Format24bppRgb);
			IntPtr lineP = lockedData.Scan0;
			for (int x = 0; x < bitmapWidth; ++x) {
				IntPtr p = lineP;
				for (int y = 0; y < bitmapHeight; ++y) {
					Color c = cMap_.Lookup(Convert.ToDouble(data_[x/scale, y/scale]));
					byte[] cBytes = new byte[3] { c.B, c.G, c.R };
					System.Runtime.InteropServices.Marshal.Copy(cBytes, 0, p, 3);
					p = new IntPtr(p.ToInt64() + 3);
				}
				lineP = new IntPtr(lineP.ToInt64() + lockedData.Stride);
			}
			
			bmp_.UnlockBits(lockedData);
		}

		public Image GetPlottedImage(int w, int h) {
			if (bmp_ == null || bmp_.Width < w || bmp_.Height < h || ( bmp_.Width > 2 * w && bmp_.Height > 2 * h ) ) {
				ResetData(data_, w, h);
			}
			return bmp_;
		}

		private object[,] data_;
		private ColorMap cMap_;
		private Bitmap bmp_;
	}
}
