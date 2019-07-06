#pragma once

#pragma warning( disable : 4251 )

#include "glib.h"
#include "gtypes.h"
#include <matrix.h>

#define MAX_PIXELSAMPLER	16
#define MAX_VERTEXSAMPLER	4
#define MAX_IMAGEUNIT		MAX_PIXELSAMPLER+MAX_VERTEXSAMPLER
#define MAX_VERTEXSTREAM	4


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

namespace Geass
{
	class GTexture;
	class GTextureManager;

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

		// RMatrix			currentTransform[RST_MAX];

		/*




		bool			currentLighting;
		bool			currentNormalizeNormals;
		DWORD			currentAmbientColor;
		//bool			currentAlphaBlendEnable;
		bool			currentAlphaTestEnable;
		DWORD			currentAlphaRef;
		RCMPFUNC		currentAlphaFunc;
		bool			currentClipping;
		bool			currentScissorTestEnable;
		bool			currentFog;
		DWORD			currentFogColor;
		float			currentFogNear, currentFogFar;
		bool			currentVertexBlendEnable;
		bool			currentIndexedVertexBlendEnable;
		bool			currentSpecularEnable;

		bool			currentColorVertexEnable;
		DWORD			currentClipPlaneEnable;

		float			currentDepthBias;
		float			currentSlopeScaleDepthBias;

		RSTENCILOP		currentStencilPass;
		RSTENCILOP		currentStencilFail;
		RSTENCILOP		currentStencilZFail;

		// ��Ÿ
		bool			m_bCursor;
		//	RConfiguration	m_currentConfig;
		int				m_nScreenWidth;
		int				m_nScreenHeight;
		RFORMAT			m_depthFormat;

		vector<RShaderFX*>	m_vShaderFXs;

		RTexture* m_pDefaultTexture;
		RTexture* m_pDefaultNoiseTexture;

		// flip����
		unsigned int	m_nFrameCount;
		unsigned int	m_nLastFPSFrameCount;

		float			m_fFPS;
		DWORD			m_dwLastFPSTime;

		DWORD			m_dwLastFlipTime;
		DWORD			m_dwLastElapsedTime;

		RViewport		m_viewport;

		RVector4		m_vDofParams;

	protected:
		virtual void OnFlip() = 0;
		virtual void OnSetViewport(const RViewport&) = 0;
		virtual void OnResetDevice() {}
		virtual void OnShowCursor(bool bShow) {}

		// sampler ��ȣ -> ���� ����� index �� ��ȯ
		unsigned int GetSamplerNumberToSaveIndex(unsigned int nStage);
		//  ���� ����� index -> sampler ��ȣ �� ��ȯ
		unsigned int GetSaveIndexToSamplerNumber(unsigned int nIndex);

		void IncreaseFrameCount() { m_nFrameCount++; }

		virtual void SetVertexBufferFreq(UINT stream, UINT FrequencyParameter) = 0;

	public:
		RDevice();
		virtual ~RDevice() {}

		virtual bool Create(HWND hWnd) = 0;
		virtual void Destroy() = 0;

		int				GetScreenWidth() { return m_nScreenWidth; }
		int				GetScreenHeight() { return m_nScreenHeight; }
		RFORMAT			GetDepthFormat() { return m_depthFormat; }
		DWORD			GetLastElapsedTime() { return m_dwLastElapsedTime; }
		unsigned int	GetFrameCount() { return m_nFrameCount; }
		float			GetFrameRate() { return m_fFPS; }
		unsigned int	GetTextureMemoryUsed();
		virtual unsigned int	GetVertexBufferMemoryUsed() = 0;

		const RTextureManager* GetTextureManager() { return m_pTextureManager; }

		const RDeviceProfileInfo& GetDeviceProfileInfo() { return m_deviceProfileInfoLast; }

		bool	IsCursorVisible();
		bool	ShowCursor(bool bShow);

		virtual void InitDeviceDefault();
		virtual bool ResetDevice() = 0;	// rs3::config�κ��� ������ �ٽ� �о ����̽��� reset�Ѵ�

		virtual void Flip();
		void SetViewport(const RViewport& viewport);
		void SetViewport(int x, int y, int nWidth, int nHeight, float fMinZ = 0, float fMaxZ = 1);
		RViewport GetViewport() const { return m_viewport; }

		virtual bool QueryFeature(RQUERYFEATURETYPE feature) = 0;
		virtual RDEVICESTATUS QueryStatus() = 0;

		virtual bool BeginScene() = 0;
		virtual void EndScene() = 0;

		virtual void Clear(bool bTarget = true, bool bDepth = true, bool bStencil = false, DWORD dwColor = 0, float fDepth = 1.f, DWORD dwStencil = 0, DWORD nIdx = 0) = 0;	// �������� ���� �߰� - 090625, OZ

		//////////////////////////////////////////////////////////////////////////
		// Render Target / Depth Buffer
		// ���ϰ��� ���� ���̹���/����Ÿ��
		virtual RTexture* SetRenderTarget(unsigned int nRenderTargetIndex, RTexture* pTexture, int nSurface = 0) = 0;
		virtual RTexture* GetRenderTarget(unsigned int nRenderTargetIndex) = 0;
		virtual RTexture* SetDepthStencilBuffer(RTexture* pTexture) = 0;
		virtual RTexture* GetDepthStencilBuffer() = 0;

		//////////////////////////////////////////////////////////////////////////
		// Vertex Format
		virtual HVERTEXFORMAT CreateVertexFormat(const RVertexAttribute* attribs, const int nAttribs, const int nStream = 0, const int nStartTexCoord = 0) = 0;
		virtual HVERTEXFORMAT	CreateVertexFormat(const RVertexAttributeEx* attribs, const int nAttribs) = 0;
		virtual void SetFvF(DWORD fvf) = 0;

		//////////////////////////////////////////////////////////////////////////
		// texture 
		virtual RTexture* NewTexture() = 0;
		virtual void		ReleaseTexture(RTexture* pTexture) {} //TODO_ignore444 : ������ �����ǵ� �������� �ȵǾ ����

		const RTextureInfo* GetTextureInfo(RTexture* pTexture);

		RTexture* CreateTextureForBuildLater(const char* fileName, const RTEXTUREFILTERTYPE filter = RTF_LINEAR,
			DWORD flags = RCT_AUTOGENMIPMAP, RFORMAT pf = RFMT_NONE, bool bBackground = false, RResource::LoadingController* pController = NULL);
		RTexture* CreateTexture(const char* fileName, const RTEXTUREFILTERTYPE filter = RTF_LINEAR,
			DWORD flags = RCT_AUTOGENMIPMAP, RFORMAT pf = RFMT_NONE, bool bBackground = false, RResource::LoadingController* pController = NULL);
		RTexture* CreateTexture(int nWidth, int nHeight, RFORMAT pf, const RTEXTUREFILTERTYPE filter = RTF_LINEAR, DWORD flags = 0, void* pixels = NULL, const char* szName = NULL);
		//	RTexture* CreateTextureByName(const char *pSzTextureName, RTexture* pDefaultPixelSrcTexture, const RTEXTUREFILTERTYPE filter = RTF_LINEAR, DWORD flags = 0, RFORMAT pf = RFMT_NONE);
		RTexture* CreateGarbageRenderTargetTexture(int nWidth, int nHeight, RFORMAT pf);

		// GetTextureByName �� CreateTextureByName �� �и��ϴ°� ������ �մϴ�
	//	RTexture* GetTextureByName( const char* pSzTextureName, bool bCreateIfNotExist = true, RTexture* pSrcDefaultPixelTexture = NULL);

		// create special texture - render target and normal map
		virtual RTexture* CreateRenderTargetTexture(int nWidth, int nHeight, RFORMAT pf, const RTEXTUREFILTERTYPE filter = RTF_LINEAR, DWORD flags = 0);
		virtual RTexture* CreateRenderTargetDepthStencilTexture(int nWidth, int nHeight, RFORMAT pf, const RTEXTUREFILTERTYPE filter = RTF_LINEAR, DWORD flags = 0);	// D3DUSAGE_DEPTHSTENCIL�� ����ϴ� - 090622, OZ
		virtual RTexture* CreateNormalMapFromHeightMap(RTexture* hHeightMap, float fAttitude) = 0;
		//	TODO: file in memory ���� �ؽ��� �����ϴ� ��� �ʿ�
		//	virtual HTEXTURE CreateCubeMapTexture();
		//	virtual HTEXTURE CreateDepthStencil();

		void DeleteTexture(RTexture* pTexture);
		void SafeDeleteTexture(RTexture*& pTexture); ///< SAFE_DELETE ��ũ�ο� ����� ������ �ϵ��� ������� �Լ�
		RTexture* GetTexture(const char* pSzTextureName);


		virtual bool GenerateMipmapLevels(RTexture* pTexture) = 0;
		virtual bool LockRect(RTexture* pTex, int nLevel, RLOCKED_RECT* pLockedRect, const RECT* pRect, DWORD Flags) = 0;
		virtual bool UnlockRect(RTexture* pTex, int nLevel) = 0;
		virtual bool UpdateTexture(RTexture* pTexture, int nLevel, int nDestX, int nDestY, int nSrcWidth, int nSrcHeight, void* pSrcPixels) = 0;
		virtual bool ColorFill(RTexture* pTexture, DWORD dwColor = 0) = 0;

		/// nSrcWidth, nSrcHeight ũ���� SrcPixel��, nSrcX, nSrcY �� �������� nDestWidth, nDestHeight ũ�⸸ŭ nDestX, nDestY�� �����Ѵ�.
		virtual bool UpdateTexture(RTexture* pTexture, int nLevel, int nDestX, int nDestY, int nDestWidth, int nDestHeight, int nSrcX, int nSrcY, int nSrcWidth, int nSrcHeight, void* pSrcPixels) = 0;

		RTexture* GetDefaultTexture();
		RTexture* GetDefaultNoiseTexture();

		//////////////////////////////////////////////////////////////////////////
		// Vertex Buffer
		virtual HVERTEXBUFFER CreateVertexBuffer(const long size, int nVertexSize, const void* data = NULL, unsigned int flags = 0) = 0;
		virtual void DeleteVertexBuffer(HVERTEXBUFFER hVertexBuffer) = 0;
		virtual void* LockVertexBuffer(const HVERTEXBUFFER hVertexBuffer, const unsigned int flags = 0, const unsigned int nOffsetToLock = 0, const unsigned int nSizeToLock = 0) = 0;
		virtual bool UnlockVertexBuffer(const HVERTEXBUFFER hVertexBuffer) = 0;

		//////////////////////////////////////////////////////////////////////////
		// Index Buffer
		virtual HINDEXBUFFER CreateIndexBuffer(const unsigned int nIndices, RFORMAT inf = RFMT_INDEX16, const void* data = NULL, unsigned int flags = 0) = 0;
		virtual void DeleteIndexBuffer(HINDEXBUFFER hIndexBuffer) = 0;
		virtual void* LockIndexBuffer(const HINDEXBUFFER hIndexBuffer, const unsigned int flags = 0, const unsigned int nOffsetToLock = 0, const unsigned int nSizeToLock = 0) = 0;
		virtual bool UnlockIndexBuffer(const HINDEXBUFFER hIndexBuffer) = 0;

		//////////////////////////////////////////////////////////////////////////
		// DrawPrimitives
		virtual bool DrawIndexedPrimitiveUP(RPRIMITIVETYPE primitiveType, unsigned int nMinVertexIndex, unsigned int nNumVertices, unsigned int nPrimitiveCount,
			const void* pIndexData, const void* pVertexStreamZeroData, unsigned int VertexStreamZeroStride, RFORMAT indexFmt = RFMT_INDEX16) = 0;
		virtual bool DrawIndexedPrimitive(RPRIMITIVETYPE primitiveType, unsigned int nBaseVertexIndex, unsigned int nMinIndex, unsigned int nNumVertices,
			unsigned int nStartIndex, unsigned int nPrimitiveCount) = 0;
		virtual bool DrawPrimitiveUP(RPRIMITIVETYPE primitiveType, unsigned int nPrimitiveCount, const void* pVertexStreamZeroData, unsigned int VertexStreamZeroStride) = 0;
		virtual bool DrawPrimitive(RPRIMITIVETYPE primitiveType, unsigned int nStart, unsigned int nPrimitiveCount) = 0;

		// TODO:
			// FileManager ���� �е��� �����ʿ� + �����ϵ� ���̴� ���ϵ� �е��� ����
			// ���̴� ���� ���� vs ps �ĺ����� �̸��� �ٲ��ֱ�

			// ogl �� d3d ������ �ٸ� �����ڵ�
			// asm file ���� �б�..
			// hlsl file ���� �б�..

		//	virtual HSHADER CreateShader( char* vsShaderBuffer,char* psShaderBuffer, char *extraDefines = NULL,const int vsLine = 0,const int psLine = 0, const char **attribs = NULL, const int nAttribs = 0) = 0;
		//	        HSHADER CreateShaders( const char *vsFileName, const char *psFileName, char *extraDefines = NULL, const char** attribs = NULL, const int nAttribs = 0);
		//	        HSHADER CreateShader( const char *shaderFile, const char **attribs = NULL, const int nAttribs = 0, char *extraDefines = NULL);
		//	        HSHADER CreateShader( const char *shaderFile, char *extraDefines) { return CreateShader(shaderFile, NULL, 0, extraDefines); }

			//////////////////////////////////////////////////////////////////////////
			// Shader ����
		virtual void ShaderOff() = 0;

		//////////////////////////////////////////////////////////////////////////
		// ShaderFX
		virtual RShaderFX* CreateShaderFX() = 0;
		virtual RShaderFX* CreateShaderFX(const string& stFilename, const vector<string>& vShaderDefines = vector<string>(0), RShaderFXPool* pShaderPool = NULL) = 0;
		virtual void DeleteShaderFX(RShaderFX* shader) = 0;

		//////////////////////////////////////////////////////////////////////////
		// State ����
		virtual void SetVertexBuffer(const HVERTEXBUFFER hVertexBuffer, const int stream, const unsigned int offset) = 0;
		virtual void SetVertexFormat(HVERTEXFORMAT hVertexFormat) = 0;

		virtual void SetupForRenderInstancing(const HVERTEXBUFFER hVertexBuffer, UINT nCnt, unsigned int offset = 0) = 0;
		virtual void RestoreForRenderInstancing() = 0;

		virtual void SetIndexBuffer(HINDEXBUFFER hIndexBuffer) = 0;

		virtual void SetTexture(int nStage, RTexture* pTexture) = 0;
		RTexture* GetTexture(int nStage);
		virtual void SetTextureStageState(int nStage, RTEXTURESTAGESTATETYPE nStageStateType, unsigned int value) = 0;
		virtual void SetTextureFilter(int nSampler, RTEXTUREFILTERTYPE type) = 0;
		virtual void SetTextureMipmapLodBias(int nStage, float fBias) = 0;
		virtual void SetTextureMaxAnisotropy(int nStage, DWORD dwValue) = 0;
		virtual DWORD GetTextureMaxAnisotropy(int nStage);
		inline float GetTextureMipmapLodBias(int nStage);
		virtual void SetTextureAddress(int nSampler, RTEXTUREADDRESS u, RTEXTUREADDRESS v, RTEXTUREADDRESS w) = 0;
		virtual void SetTextureBorderColor(int nSampler, const DWORD dwColor) = 0;
		inline void SetTextureAddressClamp(int nSampler);
		inline void SetTextureAddressWrap(int nSampler);

		virtual void SetTransform(const RSETTRANSFORMTYPE type, const RMatrix& matrix) = 0;
		virtual RMatrix GetTransform(const RSETTRANSFORMTYPE type) const = 0;

		// blending
		virtual void SetBlending(RBLEND srcFactor, RBLEND dstFactor = RBLEND_NONE, RBLENDOP blendMode = RBLENDOP_ADD) = 0;
		virtual void SetSeparateBlending(RBLEND srcFactor, RBLEND dstFactor = RBLEND_NONE, RBLENDOP blendMode = RBLENDOP_ADD) = 0;
		virtual void SetBlendFactor(const DWORD dwColor) = 0;
		virtual void SetTextureFactor(const DWORD dwColor) = 0;

		// alpha test
		virtual void SetAlphaTestEnable(bool bEnable) = 0;
		virtual void SetAlphaRef(DWORD dwRef) = 0;
		virtual void SetAlphaFunc(RCMPFUNC Func) = 0;
		virtual bool GetAlphaTestEnable() = 0;
		virtual DWORD GetAlphaRef() = 0;
		virtual RCMPFUNC GetAlphaFunc() = 0;

		virtual void SetDepthFunc(RCMPFUNC depthFunc) = 0;
		virtual void SetDepthEnable(bool bEnable, bool bWriteEnable = true) = 0;
		virtual void SetColorWriteEnable(bool bEnable) = 0;
		virtual void SetCullMode(RCULL cullMode) = 0;
		virtual void SetFillMode(RFILLMODE fillMode) = 0;
		inline RFILLMODE GetFillMode();

		virtual void SetClipPlanes(const RPlane* pPlanes, int nCount) = 0;
		virtual void SetDepthBias(float fDepthBias = 0, float fSlopeScaleDepthBias = 0) = 0;

		// stencil
		virtual void SetStencilEnable(bool bEnable) = 0;
		virtual void SetStencilTwoSide(bool bEnable) = 0;
		virtual void SetStencilRef(DWORD dwValue) = 0;
		virtual void SetStencilMask(DWORD dwValue) = 0;
		virtual void SetStencilWriteMask(DWORD dwValue) = 0;
		virtual void SetStencilFunc(RCMPFUNC stencilFunc) = 0;
		virtual void SetStencilOp(RSTENCILOP opPass, RSTENCILOP opFail, RSTENCILOP opZFail) = 0;
		virtual void SetStencilCCWFunc(RCMPFUNC stencilFunc) = 0;	// twoside�� �޸�
		virtual void SetStencilCCWOp(RSTENCILOP opPass, RSTENCILOP opFail, RSTENCILOP opZFail) = 0;

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
		virtual void SetFog(bool bLinearFog, DWORD dwColor, float fNear, float fFar, float fDensity,
			bool bPixelFog, bool bRangeFog)
		{
		}
		virtual void SetFogColor(DWORD dwColor) {}
		virtual void SetFogVertexMode(bool bPixelFog, bool bRangeFog) {}
		inline bool GetFogEnable();
		inline float GetFogNear();
		inline float GetFogFar();
		inline DWORD GetFogColor();

		// etc
		virtual void SetNormalizeNormals(bool bEnable) = 0;
		virtual void SetAmbient(DWORD dwColor) = 0;
		virtual void SetClipping(bool bEnable) = 0;		// Direct3D Ŭ����(���������Ҹ�)�� �Ѱų� ����.

		virtual void SetScissorTestEnable(bool bEnable) = 0;
		virtual void SetScissorRect(const RECT* pRect) = 0;

		virtual void SetPointSize(DWORD nSize) = 0;

		virtual void SetVertexBlendEnable(bool bEnable) = 0;
		virtual void SetIndexedVertexBlendEnable(bool bEnable) = 0;
		virtual void SetSpecularEnable(bool bEnable) = 0;

		virtual void SetColorVertex(bool bEnable) = 0;

		virtual RImage* CreateImage(int nWidth, int nHeight, RFORMAT format, void* pSrcPixels, int nSourcePitch, int nSrcX, int nSrcY);
		virtual void DeleteImage(RImage*);

		virtual bool SetCursorProperties(int XHotSpot, int YHotSpot, RImage* pImage);

		inline void			SetDofParams(RVector4& vParams);
		inline const RVector4& GetDofParams() const;

		virtual bool IsCurrentDisplayModeSupportFullScreenMode() = 0;

		//Query
		virtual	ROcclusionQuery* CreateOcclusionQuery(void) = 0;
		virtual void				ReleaseOcclusionQuery(ROcclusionQuery* pQuery) = 0;
		virtual REventQuery* CreateEventQuery(void) = 0;
		virtual void				ReleaseEventQuery(REventQuery* pEventQuery) = 0;
		virtual RD3DQueryManager* GetQueryManager(void) { return NULL; }

		// Profile Marker
		virtual void				SetProfileMarker(LPCWSTR wszName) = 0;
		virtual void				BeginProfileMarker(LPCWSTR wszName) = 0;
		virtual void				EndProfileMarker() = 0;


		//////////////////////////////////////////////////////////////////////////
		// �ܺο����� �����Ҷ� �ʿ��� �Լ���,
		// �̵������� ���� �̿��� �뵵�� ������� ����.

		// �ܺ� ���̺귯������ �������� ������ LPDIRECT3DDEVICE9 �� ��� ������ �̰ɷ� �� ĳ�����ؼ� ������
		virtual void* GetLPDIRECT3DDEVICE9() { return NULL; }

		virtual void* GetD3DPRESENT_PARAMETERS() { return NULL; }

		/// ��ũ���� ����
		virtual bool SaveScreenShot(const char* szFileName) { return false; }
		virtual RImage* GetSaveScreenImage() { return NULL; }
		*/

	};
}
