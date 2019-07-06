#pragma once

enum class ETextureFilterType
{
	// Single image filters
	RTF_POINT = 0,
	RTF_LINEAR,

	// Mipmapped image filters
	RTF_BILINEAR,
	RTF_TRILINEAR,

	// Mipmapped image filters with anisotropic
	RTF_BILINEAR_ANISO,
	RTF_TRILINEAR_ANISO,

	RTF_BILINEAR_ANISO_LINEAR_FOR_FONT,
	RTF_COUNT,
};


