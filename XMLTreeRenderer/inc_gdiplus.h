#pragma once

#define NOMINMAX
#include <windows.h>
#include <algorithm>
using ::std::min;
using ::std::max;
#include <gdiplus.h>

namespace Gdiplus{
	inline Rect Round(const RectF& rc){
		return Rect(int(rc.X), int(rc.Y), int(rc.Width), int(rc.Height));
	}

	inline int GetEncoderClsid(const wchar_t* format, CLSID* pClsid)
	{
		UINT  num = 0;          // number of image encoders
		UINT  size = 0;         // size of the image encoder array in bytes

		ImageCodecInfo* pImageCodecInfo = NULL;

		GetImageEncodersSize(&num, &size);
		if(size == 0)
			return -1;  // Failure

		pImageCodecInfo = (ImageCodecInfo*)(malloc(size));
		if(pImageCodecInfo == NULL)
			return -1;  // Failure

		GetImageEncoders(num, size, pImageCodecInfo);

		for(UINT j = 0; j < num; ++j)
		{
			if( wcscmp(pImageCodecInfo[j].MimeType, format) == 0 )
			{
				*pClsid = pImageCodecInfo[j].Clsid;
				free(pImageCodecInfo);
				return j;  // Success
			}    
		}

		free(pImageCodecInfo);
		return -1;  // Failure
	}

}
