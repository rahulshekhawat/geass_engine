#pragma once

#include "ge_lib.h"

namespace Geass
{
	class GTexture;

	const int R_NONE = 0;
	extern GTexture* RT_FRAMEBUFFER;

	class GEASSENGINE_API GViewport
	{
	public:
		DWORD       x;
		DWORD       y;            /* Viewport Top left */
		DWORD       nWidth;
		DWORD       nHeight;       /* Viewport Dimensions */
		float       fMinZ;         /* Min/max of clip Volume */
		float       fMaxZ;

		GViewport()
		{
			x = 0;
			y = 0;
			nWidth = 0;
			nHeight = 0;
			fMinZ = 0.f;
			fMaxZ = 0.f;
		}

		GViewport(int _x, int _y, int _nWidth, int _nHeight, float _fMinZ = 0, float _fMaxZ = 1.f)
			: x(_x), y(_y), nWidth(_nWidth), nHeight(_nHeight), fMinZ(_fMinZ), fMaxZ(_fMaxZ)
		{
		}
	};

	enum class ETextureFilterType
	{
		// Single image filters
		TF_POINT = 0,
		TF_LINEAR,

		// Mipmapped image filters
		TF_BILINEAR,
		TF_TRILINEAR,

		// Mipmapped image filters with anisotropic
		TF_BILINEAR_ANISO,
		TF_TRILINEAR_ANISO,

		TF_BILINEAR_ANISO_LINEAR_FOR_FONT,
		TF_COUNT,
	};

	enum class EBufferFormat
	{
		FMT_NONE = 0,
		FMT_RGB16,
		FMT_RGB24,
		FMT_XRGB32,
		FMT_ARGB32,

		FMT_A8,
		FMT_A8R8G8B8,

		FMT_A2R10G10B10,
		FMT_G16R16,

		FMT_R16F,
		FMT_G16R16F,
		FMT_G32R32F,
		FMT_R32F,
		FMT_A16B16G16R16F,
		FMT_A32B32G32R32F,

		// depth stencil buffer
		FMT_D24S8,
		FMT_D24X8,
		FMT_D16,
		FMT_D24FS8,
		FMT_D32F_LOCKABLE,
		FMT_D32,

		FMT_L8,		// 8-bit luminance only.

		// index buffer format
		FMT_INDEX16,
		FMT_INDEX32,

		// bump map format
		FMT_Q8W8V8U8,
		FMT_V16U16,
		FMT_V8U8,

		// compressed texture format
		FMT_DXT1,
		FMT_DXT3,
		FMT_DXT5,

		FMT_END,
	};
	
	enum class EQueryFeatureType {
		QF_HARDWARETNL=0,
		QF_USERCLIPPLANE,
		QF_WFOG,
		QF_VS11,
		QF_VS20,
		QF_PS10,
		QF_PS11,
		QF_PS20,
		QF_PS30,
		QF_R32F,
		QF_A32B32G32R32F,
		QF_A16B16G16R16F,
		QF_R16F,
		QF_RGB16,
		QF_G16R16F,
		QF_G32R32F,
		QF_VERTEXTEXTURE,
		QF_HWSHADOWMAP,	
		QF_MRTINDEPENDENTBITDEPTHS,

		QF_RGB16_RTF,
		QF_R32F_RTF,
		QF_A8R8G8B8_RTF,
		QF_A32B32G32R32F_RTF,
		QF_A16B16G16R16F_RTF,
		QF_R16F_RTF,
		QF_G32R32F_RTF,
		QF_MRTBLEND_R32F,
		QF_MRTBLEND_G16R16F,
		QF_MRTBLEND_A8R8G8B8,
	};
	
	enum class EDeviceStatus {
		DEVICE_OK,
		DEVICE_LOST,
		DEVICE_RESTORED,
	};
}
