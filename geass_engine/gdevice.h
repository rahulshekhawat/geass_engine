#pragma once

#pragma warning( disable : 4251 )

#include "glib.h"
#include "gtypes.h"
#include <matrix.h>
#include <vector>

namespace Geass
{
#define MAX_PIXELSAMPLER	16
#define MAX_VERTEXSAMPLER	4
#define MAX_IMAGEUNIT		MAX_PIXELSAMPLER+MAX_VERTEXSAMPLER
#define MAX_VERTEXSTREAM	4


// Flags field for Issue
#define RISSUE_END (1 << 0)		// Tells the runtime to issue the end of a query, changing it's state to "non-signaled".
#define RISSUE_BEGIN (1 << 1)	// Tells the runtime to issue the beginng of a query.

#define RCT_CLAMP			0x1
#define RCT_CUBEMAP			0x8
#define RCT_NORMALMAP		0x20
#define RCT_AUTOGENMIPMAP	0x40
#define RCT_RENDERTARGET	0x80
#define RCT_DYNAMIC			0x100
#define RCT_UNREDUCIBLE		0x200
#define RCT_SYSTEMMEM		0x400
#define RCT_DEPTHSTENCIL	0x800

	const int MAX_RENDERTARGET = 4;

	enum class ETextureAddress
	{
		TADDRESS_WRAP = 0,
		TADDRESS_MIRROR,
		TADDRESS_CLAMP,
		TADDRESS_BORDER,
		TADDRESS_MIRRORONCE,
	};

	enum class ETextureStageStateType
	{
		// stage state
		TSS_COLOROP = 0,
		TSS_COLORARG1,
		TSS_COLORARG2,
		TSS_ALPHAOP,
		TSS_ALPHAARG1,
		TSS_ALPHAARG2,
		TSS_BUMPENVMAT00,
		TSS_BUMPENVMAT01,
		TSS_BUMPENVMAT10,
		TSS_BUMPENVMAT11,
		TSS_TEXCOORDINDEX,
		TSS_BUMPENVLSCALE,
		TSS_BUMPENVLOFFSET,
		TSS_TEXTURETRANSFORMFLAGS,
		TSS_COLORARG0,
		TSS_ALPHAARG0,
		TSS_RESULTARG,
		TSS_CONSTANT,

		TSS_MAX
	};

	enum class EBlend
	{
		// Blending constants
		BLEND_ZERO = 0,
		BLEND_ONE,
		BLEND_SRCCOLOR,
		BLEND_INVSRCCOLOR,
		BLEND_DESTCOLOR,
		BLEND_INVDESTCOLOR,
		BLEND_SRCALPHA,
		BLEND_INVSRCALPHA,
		BLEND_DESTALPHA,
		BLEND_INVDESTALPHA,
		BLEND_SRCALPHASAT,
		BLEND_BLENDFACTOR,
		BLEND_INVBLENDFACTOR,

		BLEND_NONE,
	};

	enum class EBlendOP
	{
		// Blending operation
		BLENDOP_ADD = 0,
		BLENDOP_SUBTRACT,
		BLENDOP_REVSUBTRACT,
		BLENDOP_MIN,
		BLENDOP_MAX,
	};

	enum class ECMPFunc
	{
		// depth compare function
		CMP_NEVER = 0,
		CMP_LESS,
		CMP_EQUAL,
		CMP_LESSEQUAL,
		CMP_GREATER,
		CMP_NOTEQUAL,
		CMP_GREATEREQUAL,
		CMP_ALWAYS,
		CMP_END
	};

	enum class ECull
	{
		// Culling
		CULL_NONE = 0,
		CULL_CCW,
		CULL_CW,
	};

	enum class EFillMode
	{
		// wireframe ( triangle line ) , solid
		FILL_POINT = 0,
		FILL_WIRE,
		FILL_SOLID
	};

	enum class ESetTransformType
	{
		ST_WORLD = 0,
		ST_VIEW,
		ST_PROJECTION,
		ST_TEXTURE0,
		ST_TEXTURE1,
		ST_TEXTURE2,
		ST_TEXTURE3,

		ST_MAX
	};

	enum class EStencilOP
	{
		// stencil operation
		STENCILOP_KEEP = 0,
		STENCILOP_ZERO,
		STENCILOP_REPLACE,
		STENCILOP_INCRSAT,
		STENCILOP_DECRSAT,
		STENCILOP_INVERT,
		STENCILOP_INCR,
		STENCILOP_DECR,
	};

	enum EPrimitiveType
	{	
		// Primitive types
		PT_POINTLIST = 0,
		PT_LINELIST,
		PT_LINESTRIP,
		PT_TRIANGLELIST,
		PT_TRIANGLESTRIP,
		PT_TRIANGLEFAN,
	};

	struct RLOCKED_RECT
	{
		INT Pitch;
		void* pBits;
	};

	struct FDeviceProfileInfo
	{
		// Æú¸®°ï¼ö
		int nDP;	// drawprimitive
		int nDIP;	// drawindexprimitive
		int nDPUP;	// drawprimitiveup
		int nDIPUP;	// drawindexedprimitiveup

		// call ¼ö
		int nDPCall;	// drawprimitive
		int nDIPCall;	// drawindexprimitive
		int nDPUPCall;	// drawprimitiveup
		int nDIPUPCall;	// drawindexedprimitiveup

		unsigned int nReducedDPCall;
		unsigned int nReducedDIPCall;

		void AddDP(int n, unsigned int nInstanceCount) { nDPCall++; nDP += n * nInstanceCount; nReducedDPCall += nInstanceCount - 1; }
		void AddDIP(int n, unsigned int nInstanceCount) { nDIPCall++; nDIP += n * nInstanceCount; nReducedDIPCall += nInstanceCount - 1; }
		void AddDPUP(int n) { nDPUPCall++; nDPUP += n; }
		void AddDIPUP(int n) { nDIPUPCall++; nDIPUP += n; }

		int	GetTotalDrawPolygon() const { return nDP + nDIP + nDPUP + nDIPUP; }
		int	GetTotalDrawCall() const { return nDPCall + nDIPCall + nDPUPCall + nDIPUPCall; }
		int GetTotalReducedDrawCall() const { return nReducedDPCall + nReducedDIPCall; }

		FDeviceProfileInfo()
		{
			Reset();
		}

		void Reset()
		{
			nDP = nDIP = nDPUP = nDIPUP = 0;
			nDPCall = nDIPCall = nDPUPCall = nDIPUPCall = 0;
			nReducedDPCall = nReducedDIPCall = 0;
		}
	};

	class GTexture;
	class GTextureManager;
	class GShaderFX;
	class GVertexAttribute;
	class GVertexAttributeEx;
	class GTextureInfo;
	class LoadingController;
	class GShaderFXPool;
	class GPlane;
	class GImage;
	class GOcculsionQuery;
	class GEventQuery;
	class GD3DQueryManager;

	class GEASS_API GDevice
	{
	public:
		GDevice();
		virtual ~GDevice();

	protected:
		
		GTextureManager*		TextureManager;

		FDeviceProfileInfo		DeviceProfileInfoCurrent;
		FDeviceProfileInfo		DeviceProfileInfoLast;

		GTexture*				CurrentRenderTarget[MAX_RENDERTARGET];
		INT32						CurrentRenderTargetSurface[MAX_RENDERTARGET];
		GTexture*				CurrentDepthStencilBuffer;

		GTexture*				CurrentTextures[MAX_IMAGEUNIT];
		ETextureFilterType		CurrentTextureFilter[MAX_IMAGEUNIT];
		ETextureAddress			CurrentTextureAddress[MAX_IMAGEUNIT][3];	// u,v,w
		unsigned int			CurrentTextureStageSettings[MAX_IMAGEUNIT][(unsigned int)ETextureStageStateType::TSS_MAX];
		DWORD					CurrentMaxAnisotropy[MAX_IMAGEUNIT];
		float					CurrentMipmaplodBias[MAX_IMAGEUNIT];
		DWORD					CurrentTextureBorderColor[MAX_IMAGEUNIT];

		INT32					CurrentVertexFormat;
		INT32					CurrentVertexBuffer[MAX_VERTEXSTREAM];
		INT32					CurrentOffset[MAX_VERTEXSTREAM];
		INT32					CurrentFrequencyParameter[MAX_VERTEXSTREAM];
		INT32					CurrentIndexBuffer;
		INT32					CurrentInstanceCount;

		// alpha blend
		bool					bCurrentBlendEnable;
		EBlend					CurrentSrcFactor, CurrentDstFactor;
		EBlendOP				CurrentBlendMode;

		// Seperate alpha blend
		bool					bCurrentSeparateBlendEnable;
		EBlend					CurrentSeparateSrcFactor, CurrentSeparateDstFactor;
		EBlendOP				CurrentSeparateBlendMode;

		DWORD					CurrentBlendFactor;
		DWORD					CurrentTextureFactor;
		ECMPFunc				CurrentDepthFunc;
		bool					bCurrentDepthTestEnable, bCurrentDepthWriteEnable;
		ECMPFunc				CurrentStencilFunc, CurrentStencilBackFunc;
		DWORD					CurrentStencilRef;
		DWORD					CurrentStencilMask;
		bool					bCurrentStencilEnable;
		bool					bCurrentColorWriteEnable;
		ECull					CurrentCullMode;
		EFillMode				CurrentFillMode;
		FMatrix					CurrentTransform[(unsigned int)ESetTransformType::ST_MAX];

		bool					bCurrentLighting;
		bool					bCurrentNormalizeNormals;
		DWORD					bCurrentAmbientColor;
		bool					bCurrentAlphaTestEnable;
		DWORD					CurrentAlphaRef;
		ECMPFunc				CurrentAlphaFunc;
		bool					bCurrentClipping;
		bool					bCurrentScissorTestEnable;
		bool					bCurrentFog;
		DWORD					CurrentFogColor;
		float					CurrentFogNear, CurrentFogFar;
		bool					bCurrentVertexBlendEnable;
		bool					bCurrentIndexedVertexBlendEnable;
		bool					bCurrentSpecularEnable;

		bool					bCurrentColorVertexEnable;
		DWORD					CurrentClipPlaneEnable;

		float					CurrentDepthBias;
		float					CurrentSlopeScaleDepthBias;

		EStencilOP				CurrentStencilPass;
		EStencilOP				CurrentStencilFail;
		EStencilOP				CurrentStencilZFail;

		bool					bCursor;

		int						ScreenWidth;
		int						ScreenHeight;
		EBufferFormat			DepthFormat;

		std::vector<GShaderFX*>	ShaderFXs;

		GTexture*				DefaultTexture;
		GTexture*				DefaultNoiseTexture;

		unsigned int			FrameCount;
		unsigned int			LastFPSFrameCount;

		float					FPS;
		DWORD					LastFPSTime;

		DWORD					LastFlipTime;
		DWORD					LastElapsedTime;

		GViewport				Viewport;
		FVector4				DofParams;

	protected:

		virtual void OnFlip() = 0;
		virtual void OnSetViewport(const GViewport&) = 0;
		virtual void OnResetDevice() { ; }
		virtual void OnShowCursor(bool bShow) { ; }

		unsigned int GetSamplerNumberToSaveIndex(unsigned int nStage);
		unsigned int GetSaveIndexToSamplerNumber(unsigned int nIndex);

		inline void IncreaseFrameCount() { FrameCount++; }
		virtual void SetVertexBufferFreq(UINT stream, UINT FrequencyParameter) = 0;

	public:

		virtual bool Create(HWND hWnd) = 0;
		virtual void Destroy() = 0;

		inline int GetScreenWidth() { return ScreenWidth; }
		inline int GetScreenHeight() { return ScreenHeight; }
		inline EBufferFormat GetDepthFormat() { return DepthFormat; }
		inline DWORD GetLastElapsedTime() { return LastElapsedTime; }
		inline unsigned int GetFrameCount() { return FrameCount; }
		inline float GetFrameRate() { return FPS; }

		unsigned int GetTextureMemoryUsed();
		virtual unsigned int GetVertexBufferMemoryUsed() = 0;

		inline const GTextureManager* GetTextureManager() { return TextureManager; }
		inline const FDeviceProfileInfo& GetDeviceProfileInfo() { return DeviceProfileInfoLast; }

		bool IsCursorVisible();
		bool ShowCursor(bool bShow);

		virtual void InitDeviceDefault();
		virtual bool ResetDevice() = 0;

		virtual void Flip();
		void SetViewport(const GViewport& viewport);
		void SetViewport(int x, int y, int nWidth, int nHeight, float fMinZ = 0, float fMaxZ = 1);
		inline GViewport GetViewport() const { return Viewport; }

		virtual bool QueryFeature(EQueryFeatureType feature) = 0;
		virtual EDeviceStatus QueryStatus() = 0;

		virtual bool BeginScene() = 0;
		virtual void EndScene() = 0;

		virtual void Clear(bool bTarget = true, bool bDepth = true, bool bStencil = false, DWORD dwColor = 0, float fDepth = 1.f, DWORD dwStencil = 0, DWORD nIdx = 0) = 0;

		//////////////////////////////////////////////////////////////////////////
		// Render Target / Depth Buffer
		virtual GTexture* SetRenderTarget(unsigned int nRenderTargetIndex, GTexture* pTexture, int nSurface = 0) = 0;
		virtual GTexture* GetRenderTarget(unsigned int nRenderTargetIndex) = 0;
		virtual GTexture* SetDepthStencilBuffer(GTexture* pTexture) = 0;
		virtual GTexture* GetDepthStencilBuffer() = 0;

		//////////////////////////////////////////////////////////////////////////
		// Vertex Format
		virtual int CreateVertexFormat(const GVertexAttribute* attribs, const int nAttribs, const int nStream = 0, const int nStartTexCoord = 0) = 0;
		virtual int CreateVertexFormat(const GVertexAttributeEx* attribs, const int nAttribs) = 0;
		virtual void SetFvF(DWORD fvf) = 0;

		//////////////////////////////////////////////////////////////////////////
		// texture 
		virtual GTexture* NewTexture() = 0;
		virtual void ReleaseTexture(GTexture* pTexture) { ; }

		const GTextureInfo* GetTextureInfo(GTexture* pTexture);

		GTexture* CreateTextureForBuildLater(
			const char* fileName,
			const ETextureFilterType filter = ETextureFilterType::TF_LINEAR,
			DWORD flags = RCT_AUTOGENMIPMAP,
			EBufferFormat pf = EBufferFormat::FMT_NONE,
			bool bBackground = false,
			LoadingController* pController = nullptr);

		GTexture* CreateTexture(
			const char* fileName,
			const ETextureFilterType filter = ETextureFilterType::TF_LINEAR,
			DWORD flags = RCT_AUTOGENMIPMAP,
			EBufferFormat pf = EBufferFormat::FMT_NONE,
			bool bBackground = false,
			LoadingController* pController = nullptr);

		GTexture* CreateTexture(
			int nWidth,
			int nHeight,
			EBufferFormat pf,
			const ETextureFilterType filter = ETextureFilterType::TF_LINEAR,
			DWORD flags = 0,
			void* pixels = nullptr,
			const char* szName = nullptr);

		GTexture* CreateGarbageRenderTargetTexture(int nWidth, int nHeight, EBufferFormat pf);

		// create special texture - render target and normal map
		virtual GTexture* CreateRenderTargetTexture(int nWidth, int nHeight, EBufferFormat pf, const ETextureFilterType filter = ETextureFilterType::TF_LINEAR, DWORD flags = 0);
		virtual GTexture* CreateRenderTargetDepthStencilTexture(int nWidth, int nHeight, EBufferFormat pf, const ETextureFilterType filter = ETextureFilterType::TF_LINEAR, DWORD flags = 0);
		virtual GTexture* CreateNormalMapFromHeightMap(GTexture* hHeightMap, float fAttitude) = 0;

		void DeleteTexture(GTexture* pTexture);
		void SafeDeleteTexture(GTexture*& pTexture);
		GTexture* GetTexture(const char* pSzTextureName);

		virtual bool GenerateMipmapLevels(GTexture* pTexture) = 0;
		virtual bool LockRect(GTexture* pTex, int nLevel, RLOCKED_RECT* pLockedRect, const RECT* pRect, DWORD Flags) = 0;
		virtual bool UnlockRect(GTexture* pTex, int nLevel) = 0;
		virtual bool UpdateTexture(GTexture* pTexture, int nLevel, int nDestX, int nDestY, int nSrcWidth, int nSrcHeight, void* pSrcPixels) = 0;
		virtual bool ColorFill(GTexture* pTexture, DWORD dwColor = 0) = 0;

		virtual bool UpdateTexture(GTexture* pTexture, int nLevel, int nDestX, int nDestY, int nDestWidth, int nDestHeight, int nSrcX, int nSrcY, int nSrcWidth, int nSrcHeight, void* pSrcPixels) = 0;

		GTexture* GetDefaultTexture();
		GTexture* GetDefaultNoiseTexture();

		//////////////////////////////////////////////////////////////////////////
		// Vertex Buffer
		virtual int CreateVertexBuffer(const long size, int nVertexSize, const void* data = NULL, unsigned int flags = 0) = 0;
		virtual void DeleteVertexBuffer(int hVertexBuffer) = 0;
		virtual void* LockVertexBuffer(const int hVertexBuffer, const unsigned int flags = 0, const unsigned int nOffsetToLock = 0, const unsigned int nSizeToLock = 0) = 0;
		virtual bool UnlockVertexBuffer(const int hVertexBuffer) = 0;

		//////////////////////////////////////////////////////////////////////////
		// Index Buffer
		virtual int CreateIndexBuffer(const unsigned int nIndices, EBufferFormat inf = EBufferFormat::FMT_INDEX16, const void* data = NULL, unsigned int flags = 0) = 0;
		virtual void DeleteIndexBuffer(int hIndexBuffer) = 0;
		virtual void* LockIndexBuffer(const int hIndexBuffer, const unsigned int flags = 0, const unsigned int nOffsetToLock = 0, const unsigned int nSizeToLock = 0) = 0;
		virtual bool UnlockIndexBuffer(const int hIndexBuffer) = 0;

		//////////////////////////////////////////////////////////////////////////
		// DrawPrimitives
		virtual bool DrawIndexedPrimitiveUP(
			EPrimitiveType primitiveType,
			unsigned int nMinVertexIndex,
			unsigned int nNumVertices,
			unsigned int nPrimitiveCount,
			const void* pIndexData,
			const void* pVertexStreamZeroData,
			unsigned int VertexStreamZeroStride,
			EBufferFormat indexFmt = EBufferFormat::FMT_INDEX16) = 0;

		virtual bool DrawIndexedPrimitive(
			EPrimitiveType primitiveType,
			unsigned int nBaseVertexIndex,
			unsigned int nMinIndex,
			unsigned int nNumVertices,
			unsigned int nStartIndex,
			unsigned int nPrimitiveCount) = 0;

		virtual bool DrawPrimitiveUP(EPrimitiveType primitiveType, unsigned int nPrimitiveCount, const void* pVertexStreamZeroData, unsigned int VertexStreamZeroStride) = 0;
		virtual bool DrawPrimitive(EPrimitiveType primitiveType, unsigned int nStart, unsigned int nPrimitiveCount) = 0;

		//////////////////////////////////////////////////////////////////////////
		// Shader
		virtual void ShaderOff() = 0;

		//////////////////////////////////////////////////////////////////////////
		// ShaderFX
		virtual GShaderFX* CreateShaderFX() = 0;
		virtual GShaderFX* CreateShaderFX(const std::string& stFilename, const std::vector<std::string>& vShaderDefines = std::vector<std::string>(0), GShaderFXPool* pShaderPool = NULL) = 0;
		virtual void DeleteShaderFX(GShaderFX* shader) = 0;

		//////////////////////////////////////////////////////////////////////////
		// State ����
		virtual void SetVertexBuffer(const int hVertexBuffer, const int stream, const unsigned int offset) = 0;
		virtual void SetVertexFormat(int hVertexFormat) = 0;

		virtual void SetupForRenderInstancing(const int hVertexBuffer, UINT nCnt, unsigned int offset = 0) = 0;
		virtual void RestoreForRenderInstancing() = 0;

		virtual void SetIndexBuffer(int hIndexBuffer) = 0;

		virtual void SetTexture(int nStage, GTexture* pTexture) = 0;
		GTexture* GetTexture(int nStage);
		virtual void SetTextureStageState(int nStage, ETextureStageStateType nStageStateType, unsigned int value) = 0;
		virtual void SetTextureFilter(int nSampler, ETextureFilterType type) = 0;
		virtual void SetTextureMipmapLodBias(int nStage, float fBias) = 0;
		virtual void SetTextureMaxAnisotropy(int nStage, DWORD dwValue) = 0;
		virtual DWORD GetTextureMaxAnisotropy(int nStage);
		inline float GetTextureMipmapLodBias(int nStage);
		virtual void SetTextureAddress(int nSampler, ETextureAddress u, ETextureAddress v, ETextureAddress w) = 0;
		virtual void SetTextureBorderColor(int nSampler, const DWORD dwColor) = 0;
		inline void SetTextureAddressClamp(int nSampler);
		inline void SetTextureAddressWrap(int nSampler);

		virtual void SetTransform(const ESetTransformType type, const FMatrix& matrix) = 0;
		virtual FMatrix GetTransform(const ESetTransformType type) const = 0;

		// blending
		virtual void SetBlending(EBlend srcFactor, EBlend dstFactor = EBlend::BLEND_NONE, EBlendOP blendMode = EBlendOP::BLENDOP_ADD) = 0;
		virtual void SetSeparateBlending(EBlend srcFactor, EBlend dstFactor = EBlend::BLEND_NONE, EBlendOP blendMode = EBlendOP::BLENDOP_ADD) = 0;
		virtual void SetBlendFactor(const DWORD dwColor) = 0;
		virtual void SetTextureFactor(const DWORD dwColor) = 0;

		// alpha test
		virtual void SetAlphaTestEnable(bool bEnable) = 0;
		virtual void SetAlphaRef(DWORD dwRef) = 0;
		virtual void SetAlphaFunc(ECMPFunc Func) = 0;
		virtual bool GetAlphaTestEnable() = 0;
		virtual DWORD GetAlphaRef() = 0;
		virtual ECMPFunc GetAlphaFunc() = 0;

		virtual void SetDepthFunc(ECMPFunc depthFunc) = 0;
		virtual void SetDepthEnable(bool bEnable, bool bWriteEnable = true) = 0;
		virtual void SetColorWriteEnable(bool bEnable) = 0;
		virtual void SetCullMode(ECull cullMode) = 0;
		virtual void SetFillMode(EFillMode fillMode) = 0;
		inline EFillMode GetFillMode();

		virtual void SetClipPlanes(const GPlane* pPlanes, int nCount) = 0;
		virtual void SetDepthBias(float fDepthBias = 0, float fSlopeScaleDepthBias = 0) = 0;

		// stencil
		virtual void SetStencilEnable(bool bEnable) = 0;
		virtual void SetStencilTwoSide(bool bEnable) = 0;
		virtual void SetStencilRef(DWORD dwValue) = 0;
		virtual void SetStencilMask(DWORD dwValue) = 0;
		virtual void SetStencilWriteMask(DWORD dwValue) = 0;
		virtual void SetStencilFunc(ECMPFunc stencilFunc) = 0;
		virtual void SetStencilOp(EStencilOP opPass, EStencilOP opFail, EStencilOP opZFail) = 0;
		virtual void SetStencilCCWFunc(ECMPFunc stencilFunc) = 0;	// twoside�� �޸�
		virtual void SetStencilCCWOp(EStencilOP opPass, EStencilOP opFail, EStencilOP opZFail) = 0;

		virtual void SetPointSpriteEnable(bool bEnable) = 0;
		virtual void SetPointSizeAndScale(float fSize, float fMin, float fMax, bool bScaleEnable, float fScaleA, float fScaleB, float fScaleC) = 0;

		// light
		virtual void SetLight(int index, void* pLight) = 0;
		virtual void SetLightEnable(int index, bool bEnable) = 0;
		virtual void SetLighting(bool bEnable) = 0;

		// material 
		virtual void SetMaterial(void* pMtrl) = 0;

		// fog
		virtual void SetFogEnable(bool bEnable) = 0;
		virtual void SetFog(bool bLinearFog, DWORD dwColor, float fNear, float fFar, float fDensity, bool bPixelFog, bool bRangeFog) { ; }

		virtual void SetFogColor(DWORD dwColor) {}
		virtual void SetFogVertexMode(bool bPixelFog, bool bRangeFog) {}
		inline bool GetFogEnable();
		inline float GetFogNear();
		inline float GetFogFar();
		inline DWORD GetFogColor();

		// etc
		virtual void SetNormalizeNormals(bool bEnable) = 0;
		virtual void SetAmbient(DWORD dwColor) = 0;
		virtual void SetClipping(bool bEnable) = 0;

		virtual void SetScissorTestEnable(bool bEnable) = 0;
		virtual void SetScissorRect(const RECT* pRect) = 0;

		virtual void SetPointSize(DWORD nSize) = 0;

		virtual void SetVertexBlendEnable(bool bEnable) = 0;
		virtual void SetIndexedVertexBlendEnable(bool bEnable) = 0;
		virtual void SetSpecularEnable(bool bEnable) = 0;

		virtual void SetColorVertex(bool bEnable) = 0;

		virtual GImage* CreateImage(int nWidth, int nHeight, EBufferFormat format, void* pSrcPixels, int nSourcePitch, int nSrcX, int nSrcY);
		virtual void DeleteImage(GImage*);

		virtual bool SetCursorProperties(int XHotSpot, int YHotSpot, GImage* pImage);

		inline void SetDofParams(FVector4& vParams);
		inline const FVector4& GetDofParams() const;

		virtual bool IsCurrentDisplayModeSupportFullScreenMode() = 0;

		//Query
		virtual	GOcculsionQuery* CreateOcclusionQuery(void) = 0;
		virtual void ReleaseOcclusionQuery(GOcculsionQuery* pQuery) = 0;
		virtual GEventQuery* CreateEventQuery(void) = 0;
		virtual void ReleaseEventQuery(GEventQuery* pEventQuery) = 0;
		virtual GD3DQueryManager* GetQueryManager(void) { return NULL; }

		// Profile Marker
		virtual void SetProfileMarker(LPCWSTR wszName) = 0;
		virtual void BeginProfileMarker(LPCWSTR wszName) = 0;
		virtual void EndProfileMarker() = 0;

		virtual void* GetLPDIRECT3DDEVICE9() { return NULL; }

		virtual void* GetD3DPRESENT_PARAMETERS() { return NULL; }

		virtual bool SaveScreenShot(const char* szFileName) { return false; }
		virtual GImage* GetSaveScreenImage() { return NULL; }

	};

	inline float GDevice::GetTextureMipmapLodBias(int nStage)
	{
		return 0.0f;
	}

	inline void GDevice::SetTextureAddressClamp(int nSampler)
	{
	}

	inline void GDevice::SetTextureAddressWrap(int nSampler)
	{
	}

	inline bool GDevice::GetFogEnable()
	{
		return false;
	}

	inline float GDevice::GetFogNear()
	{
		return 0.0f;
	}

	inline float GDevice::GetFogFar()
	{
		return 0.0f;
	}

	inline DWORD GDevice::GetFogColor()
	{
		return 0;
	}

	inline void GDevice::SetDofParams(FVector4& vParams)
	{
		DofParams = vParams;
	}

	inline const FVector4& GDevice::GetDofParams() const
	{
		return DofParams;
	}

	inline EFillMode GDevice::GetFillMode()
	{
		return EFillMode();
	}
}
