#include "pch.h"
#include "gdevice.h"
#include "gtexture.h"

#include <timeapi.h>

namespace Geass
{
	// stage state arg type
	const int RTA_DIFFUSE = D3DTA_DIFFUSE;
	const int RTA_CURRENT = D3DTA_CURRENT;
	const int RTA_TEXTURE = D3DTA_TEXTURE;
	const int RTA_TFACTOR = D3DTA_TFACTOR;
	const int RTA_SPECULAR = D3DTA_SPECULAR;
	const int RTA_TEMP = D3DTA_TEMP;
	const int RTA_CONSTANT = D3DTA_CONSTANT;
	const int RTA_COMPLEMENT = D3DTA_COMPLEMENT;
	const int RTA_ALPHAREPLICATE = D3DTA_ALPHAREPLICATE;
	const int RTA_NOT_INITIALIZED = 0xffffff;

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
		CurrentRenderTarget[0] =  RT_FRAMEBUFFER;
		CurrentDepthStencilBuffer = RT_FRAMEBUFFER;

		for (int i = 1; i < MAX_RENDERTARGET; ++i)
		{
			CurrentRenderTarget[i] = R_NONE;
			CurrentRenderTargetSurface[i] = 0;
		}

		CurrentVertexFormat = R_NONE;
		memset(CurrentOffset, 0, sizeof(CurrentOffset));
		memset(CurrentFrequencyParameter, 0, sizeof(CurrentFrequencyParameter));
		CurrentIndexBuffer = R_NONE;
		CurrentInstanceCount = 1;

		// alpha blend
		CurrentSrcFactor = EBlend::BLEND_ONE;		/// D3DRS_SRCBLEND : One member of the D3DBLEND enumerated type. The default value is D3DBLEND_ONE.
		CurrentDstFactor = EBlend::BLEND_ZERO;
		CurrentBlendMode = EBlendOP::BLENDOP_ADD;
		bCurrentBlendEnable = false;
		// separate alpha
		CurrentSeparateSrcFactor = EBlend::BLEND_ONE;
		CurrentSeparateDstFactor = EBlend::BLEND_ZERO;
		CurrentSeparateBlendMode = EBlendOP::BLENDOP_ADD;
		bCurrentSeparateBlendEnable = false;

		CurrentDepthFunc = ECMPFunc::CMP_LESSEQUAL;
		bCurrentDepthTestEnable = true;
		bCurrentDepthWriteEnable = true;
		bCurrentColorWriteEnable = true;
		CurrentCullMode = ECull::CULL_CCW;
		bCurrentStencilEnable = false;
		CurrentStencilFunc = ECMPFunc::CMP_ALWAYS;		/// D3DRS_STENCILFUNC : Comparison function for the stencil test. Values are from the D3DCMPFUNC enumerated type. The default value is D3DCMP_ALWAYS. 
		CurrentStencilRef = 0;					/// D3DRS_STENCILREF : An int reference value for the stencil test. The default value is 0. 
		CurrentStencilMask = 0xFFFFFFFF;		/// D3DRS_STENCILMASK : Mask applied to the reference value and each stencil buffer entry to determine the significant bits for the stencil test. The default mask is 0xFFFFFFFF.
		CurrentStencilBackFunc = ECMPFunc::CMP_ALWAYS;
		CurrentClipPlaneEnable = 0;	// false
		bCurrentAlphaTestEnable = false;
		CurrentAlphaFunc = ECMPFunc::CMP_ALWAYS;
		CurrentAlphaRef = 0;
		bCurrentLighting = true;
		bCurrentNormalizeNormals = false;
		CurrentAmbientColor = 0;
		bCurrentClipping = true;
		bCurrentScissorTestEnable = false;
		bCurrentFog = false;
		bCurrentVertexBlendEnable = false;
		bCurrentIndexedVertexBlendEnable = false;
		bCurrentSpecularEnable = false;
		bCurrentColorVertexEnable = true;
		CurrentFillMode = EFillMode::FILL_SOLID;
		CurrentStencilPass = EStencilOP::STENCILOP_KEEP;	/// D3DRS_STENCILPASS : Stencil operation to perform if both the stencil and the depth (z) tests pass. Values are from the D3DSTENCILOP enumerated type. The default value is D3DSTENCILOP_KEEP.
		CurrentStencilFail = EStencilOP::STENCILOP_KEEP;	/// D3DRS_STENCILFAIL : Stencil operation to perform if the stencil test fails. Values are from the D3DSTENCILOP enumerated type. The default value is D3DSTENCILOP_KEEP. 
		CurrentStencilZFail = EStencilOP::STENCILOP_KEEP;	/// D3DRS_STENCILZFAIL : Stencil operation to perform if the stencil test passes and the depth test (z-test) fails. Values are from the D3DSTENCILOP enumerated type. The default value is D3DSTENCILOP_KEEP.
		CurrentDepthBias = 0;					/// D3DRS_DEPTHBIAS : A floating-point value that is used for comparison of depth values. See Depth Bias (Direct3D 9). The default value is 0.
		CurrentSlopeScaleDepthBias = 0;			/// D3DRS_SLOPESCALEDEPTHBIAS : Used to determine how much bias can be applied to co-planar primitives to reduce z-fighting. The default value is 0.

		for (int i = 0; i < MAX_IMAGEUNIT; i++)
		{
			CurrentTextures[i] = R_NONE;
			CurrentTextureFilter[i] = ETextureFilterType::TF_POINT;
			CurrentTextureAddress[i][0] = ETextureAddress::TADDRESS_WRAP;
			CurrentTextureAddress[i][1] = ETextureAddress::TADDRESS_WRAP;
			CurrentTextureAddress[i][2] = ETextureAddress::TADDRESS_WRAP;
			CurrentMaxAnisotropy[i] = 1;	/// D3DSAMP_MAXANISOTROPY : DWORD maximum anisotropy. The default value is 1. 
			CurrentMipmaplodBias[i] = 0.0f;
			CurrentTextureBorderColor[i] = 0;	/// D3DSAMP_BORDERCOLOR : Border color or type D3DCOLOR. The default color is 0x00000000. 

			CurrentTextureStageSettings[i][(UINT)ETextureStageStateType::TSS_ALPHAOP] = (UINT)ETextureOP::TOP_DISABLE;	/// D3DTSS_COLOROP : Texture-stage state is a texture color blending operation identified by one member of the D3DTEXTUREOP enumerated type. The default value for the first texture stage (stage 0) is D3DTOP_MODULATE; for all other stages the default is D3DTOP_DISABLE. 
			CurrentTextureStageSettings[i][(UINT)ETextureStageStateType::TSS_COLOROP] = (UINT)ETextureOP::TOP_DISABLE;	/// D3DTSS_ALPHAOP : Texture-stage state is a texture alpha blending operation identified by one member of the D3DTEXTUREOP enumerated type. The default value for the first texture stage (stage 0) is D3DTOP_SELECTARG1, and for all other stages the default is D3DTOP_DISABLE. 
			CurrentTextureStageSettings[i][(UINT)ETextureStageStateType::TSS_ALPHAARG1] = RTA_NOT_INITIALIZED;			/// D3DTSS_ALPHAARG1 : �ؽ��� ���� ���ο� ���� �⺻ ���� �ٸ���. �׷��Ƿ� ��ȿ���� ���� �⺻ ���� ����. ������ �ߺ� ������ ��¿ �� ����. Texture-stage state is the first alpha argument for the stage, identified by by D3DTA. The default argument is D3DTA_TEXTURE. If no texture is set for this stage, the default argument is D3DTA_DIFFUSE. 
			CurrentTextureStageSettings[i][(UINT)ETextureStageStateType::TSS_ALPHAARG2] = RTA_CURRENT;					/// D3DTSS_ALPHAARG2 : Texture-stage state is the second alpha argument for the stage, identified by by D3DTA. The default argument is D3DTA_CURRENT. 
			CurrentTextureStageSettings[i][(UINT)ETextureStageStateType::TSS_COLORARG1] = RTA_TEXTURE;					/// D3DTSS_COLORARG1 : Texture-stage state is the first color argument for the stage, identified by one of the D3DTA. The default argument is D3DTA_TEXTURE. 
			CurrentTextureStageSettings[i][(UINT)ETextureStageStateType::TSS_COLORARG2] = RTA_CURRENT;					/// D3DTSS_COLORARG2 : Texture-stage state is the second color argument for the stage, identified by D3DTA. The default argument is D3DTA_CURRENT.
		}

		CurrentTextureStageSettings[0][(UINT)ETextureStageStateType::TSS_ALPHAOP] = (UINT)ETextureOP::TOP_SELECTARG1;	/// D3DTSS_ALPHAOP : Texture-stage state is a texture alpha blending operation identified by one member of the D3DTEXTUREOP enumerated type. The default value for the first texture stage (stage 0) is D3DTOP_SELECTARG1, and for all other stages the default is D3DTOP_DISABLE. 
		CurrentTextureStageSettings[0][(UINT)ETextureStageStateType::TSS_COLOROP] = (UINT)ETextureOP::TOP_MODULATE;		/// D3DTSS_COLOROP : Texture-stage state is a texture color blending operation identified by one member of the D3DTEXTUREOP enumerated type. The default value for the first texture stage (stage 0) is D3DTOP_MODULATE; for all other stages the default is D3DTOP_DISABLE. 

		for (int i = 0; i < MAX_VERTEXSTREAM; i++)
		{
			CurrentVertexBuffer[i] = R_NONE;
		}

		for (int i = 0; i < (UINT)ESetTransformType::ST_MAX; i++)
		{
			CurrentTransform[i].MakeIdentity();
		}

		LastFPSTime = timeGetTime();
		LastFPSFrameCount = 0;
		FPS = 0;
		LastFlipTime = LastFPSTime;
		LastElapsedTime = 0;
		bCursor = false;

		// REngine::GetResourceProfiler().Reset();

		OnResetDevice();
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
