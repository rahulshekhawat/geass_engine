#include "pch.h"
#include "gdevice.h"
#include "gtexture.h"

namespace Geass
{
	GDevice::GDevice()
	{
	}

	GDevice::~GDevice()
	{
	}

	unsigned int GDevice::GetSamplerNumberToSaveIndex(unsigned int nStage)
	{
		return 0;
	}

	unsigned int GDevice::GetSaveIndexToSamplerNumber(unsigned int nIndex)
	{
		return 0;
	}

	unsigned int GDevice::GetTextureMemoryUsed()
	{
		return 0;
	}

	bool GDevice::IsCursorVisible()
	{
		return false;
	}

	bool GDevice::ShowCursor(bool bShow)
	{
		return false;
	}

	void GDevice::InitDeviceDefault()
	{
	}

	void GDevice::Flip()
	{
	}

	void GDevice::SetViewport(const GViewport& viewport)
	{
	}

	void GDevice::SetViewport(int x, int y, int nWidth, int nHeight, float fMinZ, float fMaxZ)
	{
	}

	const GTextureInfo* GDevice::GetTextureInfo(GTexture* pTexture)
	{
		return nullptr;
	}

	GTexture* GDevice::CreateTextureForBuildLater(const char* fileName, const ETextureFilterType filter, DWORD flags, EBufferFormat pf, bool bBackground, LoadingController* pController)
	{
		return nullptr;
	}

	GTexture* GDevice::CreateTexture(const char* fileName, const ETextureFilterType filter, DWORD flags, EBufferFormat pf, bool bBackground, LoadingController* pController)
	{
		return nullptr;
	}

	GTexture* GDevice::CreateTexture(int nWidth, int nHeight, EBufferFormat pf, const ETextureFilterType filter, DWORD flags, void* pixels, const char* szName)
	{
		return nullptr;
	}

	GTexture* GDevice::CreateGarbageRenderTargetTexture(int nWidth, int nHeight, EBufferFormat pf)
	{
		return nullptr;
	}

	GTexture* GDevice::CreateRenderTargetTexture(int nWidth, int nHeight, EBufferFormat pf, const ETextureFilterType filter, DWORD flags)
	{
		return nullptr;
	}

	GTexture* GDevice::CreateRenderTargetDepthStencilTexture(int nWidth, int nHeight, EBufferFormat pf, const ETextureFilterType filter, DWORD flags)
	{
		return nullptr;
	}

	void GDevice::DeleteTexture(GTexture* pTexture)
	{
	}

	void GDevice::SafeDeleteTexture(GTexture*& pTexture)
	{
	}

	GTexture* GDevice::GetTexture(const char* pSzTextureName)
	{
		return nullptr;
	}

	GTexture* GDevice::GetDefaultTexture()
	{
		return nullptr;
	}

	GTexture* GDevice::GetDefaultNoiseTexture()
	{
		return nullptr;
	}

	GTexture* GDevice::GetTexture(int nStage)
	{
		return nullptr;
	}

	DWORD GDevice::GetTextureMaxAnisotropy(int nStage)
	{
		return 0;
	}

	GImage* GDevice::CreateImage(int nWidth, int nHeight, EBufferFormat format, void* pSrcPixels, int nSourcePitch, int nSrcX, int nSrcY)
	{
		return nullptr;
	}

	void GDevice::DeleteImage(GImage*)
	{
	}

	bool GDevice::SetCursorProperties(int XHotSpot, int YHotSpot, GImage* pImage)
	{
		return false;
	}
}
