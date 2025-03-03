#pragma once

#include <d3d11.h>

#include "Spritter/Graphics/Renderable.h"

namespace Spritter::Graphics::D3D11
{
    class D3D11Renderable final : public Renderable
    {
        ID3D11DeviceContext* _context{};
        ID3D11Buffer* _vertexBuffer{};
        ID3D11Buffer* _indexBuffer;

    public:
        D3D11Renderable(ID3D11Device* device, ID3D11DeviceContext* context, const RenderableDefinition& definition);
        ~D3D11Renderable() override;

        void Update(const RenderableUpdateInfo& info) override;

        void PushUniformData(uint32_t bindPoint, uint32_t dataSize, void* data) override;

        void PushTexture(uint32_t bindPoint, Texture* texture) override;

        void Draw(uint32_t numDraws) override;
    };
}
