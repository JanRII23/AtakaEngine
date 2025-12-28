#pragma once
#include <DX3D/Core/Common.h>
#include <d3d11.h>
#include <bit>

namespace dx3d
{
	namespace GraphicsUtils
	{
		inline const char* GetShaderModelTarget(ShaderType type)
		{
			switch (type)
			{
			case ShaderType::VertexShader: return "vs_5_0";
			case ShaderType::PixelShader: return "ps_5_0";
			default: return "";
			}
		}

        inline DXGI_FORMAT GetDXGIFormatFromMask(D3D_REGISTER_COMPONENT_TYPE type, UINT mask)
        {
            auto componentCount = std::popcount(mask);
            if (componentCount < 1) return DXGI_FORMAT_UNKNOWN;

            switch (type)
            {
            case D3D_REGISTER_COMPONENT_FLOAT32:
                switch (componentCount)
                {
                case 1: return DXGI_FORMAT_R32_FLOAT;
                case 2: return DXGI_FORMAT_R32G32_FLOAT;
                case 3: return DXGI_FORMAT_R32G32B32_FLOAT;
                case 4: return DXGI_FORMAT_R32G32B32A32_FLOAT;
                default: return DXGI_FORMAT_UNKNOWN;
                }
            default:
                return DXGI_FORMAT_UNKNOWN;
            }
        }

        inline UINT GetDXGIFormatSize(DXGI_FORMAT format)
        {
            switch (format)
            {
            case DXGI_FORMAT_R32_FLOAT:           return 4;
            case DXGI_FORMAT_R32G32_FLOAT:        return 8;
            case DXGI_FORMAT_R32G32B32_FLOAT:     return 12;
            case DXGI_FORMAT_R32G32B32A32_FLOAT:  return 16;
            default: return 0;
            }
        }
	}
}
