#include "D3D11Renderable.h"

#include "D3D11Utils.h"

namespace Spritter::Graphics::D3D11
{
    D3D11Renderable::D3D11Renderable(ID3D11Device* device, ID3D11DeviceContext* context,
        const RenderableDefinition& definition)
    {
        _context = context;

        D3D11_BUFFER_DESC bufferDesc{};
        bufferDesc.Usage = definition.Dynamic ? D3D11_USAGE_DYNAMIC : D3D11_USAGE_DEFAULT;
        bufferDesc.CPUAccessFlags = definition.Dynamic ? D3D11_CPU_ACCESS_WRITE : 0;

        D3D11_SUBRESOURCE_DATA bufferData{};

        bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
        bufferDesc.ByteWidth = definition.NumVertices;
        bufferData.pSysMem = definition.Vertices;
        D3D11_CHECK(device->CreateBuffer(&bufferDesc, definition.Vertices ? &bufferData : nullptr, &_vertexBuffer));

        bufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
        bufferDesc.ByteWidth = definition.NumIndices * sizeof(uint32_t);
        bufferData.pSysMem = definition.Indices;
        D3D11_CHECK(device->CreateBuffer(&bufferDesc, definition.Indices ? &bufferData : nullptr, &_indexBuffer));
    }

    D3D11Renderable::~D3D11Renderable()
    {
        _indexBuffer->Release();
        _vertexBuffer->Release();
    }

    void D3D11Renderable::Update(const RenderableUpdateInfo& info)
    {
    }

    void D3D11Renderable::PushUniformData(uint32_t bindPoint, uint32_t dataSize, void* data)
    {
    }

    void D3D11Renderable::PushTexture(uint32_t bindPoint, Texture* texture)
    {
    }

    void D3D11Renderable::Draw(uint32_t numDraws)
    {
    }
}
