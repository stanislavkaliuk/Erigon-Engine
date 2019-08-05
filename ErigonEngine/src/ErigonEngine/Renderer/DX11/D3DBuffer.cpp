#include "eepch.h"
#include "D3DBuffer.h"
#include <Windows.h>
#include <d3d11.h>

namespace ErigonEngine
{
	D3DVertexBuffer::D3DVertexBuffer(float* vertices, uint32 size)
	{
		D3D11_SUBRESOURCE_DATA vertexBufferData = { 0 };
		vertexBufferData.pSysMem = vertices;
		vertexBufferData.SysMemPitch = 0;
		vertexBufferData.SysMemSlicePitch = 0;

		CD3D11_BUFFER_DESC vertexBufferDescr(sizeof(vertices), D3D11_BIND_VERTEX_BUFFER);

		
	}
}