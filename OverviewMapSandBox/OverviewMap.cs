using System;
using System.Collections.Generic;
using System.Text;

using System.Drawing;
namespace OverviewMapSandBox
{
	class OverviewMap
	{
		//abstract position
		private RectangleF mapExtent_;
		//abstract position
		private RectangleF ovExtent_;
		//abstract position
		private RectangleF ovPos_;
		//abstract position
		private RectangleF fovPos_;
		//abstract position
		private RectangleF clippedFovPos_;

		public OverviewMap(RectangleF ovExt, RectangleF mapExt)
		{
			ovExtent_ = ovExt;
			mapExtent_ = mapExt;
			ovPos_ = new RectangleF(0, 0, 1, 1);
		}

		public RectangleF OvPos
		{
			get { return ovPos_; }
			set { ovPos_ = value; FOVPosFromMapExtent(); }
		}

		public RectangleF FOVPos
		{
			get { return fovPos_; }
			set { fovPos_ = value; MapExtentFromFOVPos(); }
		}

		public RectangleF ClippedFovPos
		{
			get{return clippedFovPos_;}
		}

		public RectangleF OvExtent
		{
			get { return ovExtent_; }
			set	
			{
				ovExtent_ = value;
				FOVPosFromMapExtent();
			}
		}

		public RectangleF MapExtent
		{
			get { return mapExtent_; }
			set
			{
				mapExtent_ = value;
				FOVPosFromMapExtent();
			}
		}

		public void MoveFOVPos(Point dir)
		{
			fovPos_.Offset(dir);
			MapExtentFromFOVPos();
		}

		/// <summary>
		/// 
		/// </summary>
		/// <param name="ltPt">×óÉÏ½ÇµÄµã</param>
		public void MoveFOVTo(Point ltPt)
		{
			fovPos_.Offset(ltPt.X - fovPos_.Left, ltPt.Y-fovPos_.Top);
			MapExtentFromFOVPos();
		}

		private RectangleF clippedFov()
		{
			RectangleF fovRect = fovPos_;

			float Left = Math.Max(fovRect.Left, ovPos_.Left);
			float Right = Math.Min(fovRect.Right, ovPos_.Right);
			float Top = Math.Max(fovRect.Top, ovPos_.Top);
			float Bottom = Math.Min(fovRect.Bottom, ovPos_.Bottom);

			fovRect.X = Left;
			fovRect.Y = Top;
			fovRect.Width = Right - Left;
			fovRect.Height = Bottom - Top;

			return fovRect;
		}

		private void FOVPosFromMapExtent()
		{
			float ratioOvExtDivView = ovExtent_.Width / ovPos_.Width;

			
			float Left = (mapExtent_.Left - ovExtent_.Left) / ratioOvExtDivView;
			float Right = (mapExtent_.Right - ovExtent_.Left) / ratioOvExtDivView;
			float Top = (mapExtent_.Top - ovExtent_.Top) / ratioOvExtDivView;
			float Bottom = (mapExtent_.Bottom - ovExtent_.Top) / ratioOvExtDivView;

			fovPos_.X = (float)Left;
			fovPos_.Y = (float)Top;
			fovPos_.Width = (float)(Right - Left);
			fovPos_.Height = (float)(Bottom - Top);

			fovPos_.Offset(ovPos_.X, ovPos_.Y);

			clippedFovPos_ = clippedFov();
		}

		private void MapExtentFromFOVPos()
		{
			float ratioOvExtDivView = ovExtent_.Width / ovPos_.Width;
			
			float Left = (fovPos_.Left - ovPos_.Left) * ratioOvExtDivView + ovExtent_.Left;
			float Right = (fovPos_.Right - ovPos_.Left) * ratioOvExtDivView + ovExtent_.Left;
			float Top = (fovPos_.Top - ovPos_.Top) * ratioOvExtDivView + ovExtent_.Top;
			float Bottom = (fovPos_.Bottom - ovPos_.Top) * ratioOvExtDivView + ovExtent_.Top;

			mapExtent_.X = (float)Left;
			mapExtent_.Y = (float)Top;
			mapExtent_.Width = (float)(Right - Left);
			mapExtent_.Height = (float)(Bottom - Top);
		}
	}
}
