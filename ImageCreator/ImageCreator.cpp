// ImageCreator.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "windows.h"
#include "gdiplus.h"

using namespace Gdiplus;

int GetEncoderClsid(const WCHAR* format, CLSID* pClsid)
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

int _tmain(int argc, _TCHAR* argv[])
{
	GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR           gdiplusToken;
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

	Bitmap bmp(512, 512, PixelFormat32bppARGB);
	BitmapData data;
	Rect rc(0, 0, bmp.GetWidth(), bmp.GetHeight());
	bmp.LockBits(&rc, ImageLockModeWrite, PixelFormat32bppARGB, &data);

	BYTE* psl = (BYTE*)data.Scan0;

	for(int i = 0; i < data.Height; ++i)
	{
		for(int j = 0; j < data.Width; ++j){
			if( (i / 32 + j / 32) % 2 == 0)
			{
				*(ARGB*)&psl[4*j] = Color(255, 255, 255, 255).GetValue();
			}
			else
			{
				*(ARGB*)&psl[4*j] = Color(255, 0, 0, 0).GetValue();
			}
		}
		psl += data.Stride;
	}

	bmp.UnlockBits(&data);

	CLSID pngClsid;
	GetEncoderClsid(L"image/png", &pngClsid);
	bmp.Save(L"C:\\2.png", &pngClsid, NULL);

	GdiplusShutdown(gdiplusToken);
	return 0;
}

