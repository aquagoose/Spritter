#include "D3D11Renderable.h"

namespace Spritter::Graphics::D3D11
{
    D3D11Renderable::D3D11Renderable(ID3D11Device* device, ID3D11DeviceContext* context,
        const RenderableDefinition& definition)
    {
        _context = context;


    }
}
