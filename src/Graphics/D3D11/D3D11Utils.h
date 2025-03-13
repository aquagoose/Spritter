#pragma once

#include <stdexcept>

#define D3D11_CHECK(Operation) {\
    HRESULT res = Operation;\
    if (FAILED(res))\
        throw std::runtime_error("D3D11 operation failed.");\
}
