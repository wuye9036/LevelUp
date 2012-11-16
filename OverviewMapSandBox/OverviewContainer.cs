using System;
using System.Collections.Generic;
using System.Text;
using System.Drawing;

namespace OverviewMapSandBox
{
	class OverviewContainer
	{
		private OverviewMap ovMap_;
		private RectangleF pos_;

		public RectangleF Position
		{
			get { return pos_; }
			set { pos_ = value; SetOvMapPos(); }
		}

		public RectangleF OvExtent
		{
			get { return ovMap_.MapExtent; }
			set { ovMap_.OvExtent = value; SetOvMapPos(); }
		}

		public OverviewMap OvMap
		{
			get { return ovMap_; }
		}

		public OverviewContainer(RectangleF pos, RectangleF ovExtent, RectangleF mapExtent)
		{
			this.ovMap_ = new OverviewMap(ovExtent, mapExtent);
			this.Position = pos;
			this.OvExtent = ovExtent;
		}

		private void SetOvMapPos()
		{
			//¼ÆËã³¤¿í
			float contHWRatio = pos_.Height / pos_.Width;
			float ovHWRatio = ovMap_.OvExtent.Height / ovMap_.OvExtent.Width;

			RectangleF ovPos = pos_;

			if (contHWRatio > ovHWRatio)
			{
				ovPos.Height = (float)(ovHWRatio * pos_.Width);
				ovPos.Offset(0, (pos_.Height - ovPos.Height) / 2);
			}
			else
			{
				ovPos.Width = (float)(pos_.Height / ovHWRatio);
				ovPos.Offset((pos_.Width - ovPos.Width) / 2, 0);
			}

			ovMap_.OvPos = ovPos;
		}
	}
}
