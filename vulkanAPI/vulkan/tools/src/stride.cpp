#include "headers.h"

#include "tools\include\stride.h"

namespace vkVert
{




	uint8_t enumerate_pos_stride(PosStride stride)
	{
		switch (stride)
		{
		case PosStride::NONE:
			return 0;

		case PosStride::STRIDE_2D:
			return 2;

		case PosStride::STRIDE_3D:
			return 3;
		default:
			return 0;
		}
	}


	uint8_t enumerate_color_stride(ColorStride stride) 
	{
		switch (stride)
		{
		case ColorStride::NONE:
			return 0;

		case ColorStride::RGB:
			return 2;

		case ColorStride::RGBA:
			return 3;
		default:
			return 0;
		}
	}



	uint8_t enumerate_tex_stride(TextureStride texStride)
	{
		switch (texStride)
		{
		case TextureStride::NONE:
			return 0;

		case TextureStride::STRIDE_2D:
			return 2;

		case TextureStride::STRIDE_3D:
			return 3;
		default:
			return 0;
		}
	}



	uint8_t enumerate_normal_stride(NormalStride normStride)
	{

		switch (normStride)
		{
		case NormalStride::NONE:
			return 0;

		case NormalStride::STRIDE_2D:
			return 2;

		case NormalStride::STRIDE_3D:
			return 3;
		default:
			return 0;
		}

	}

}