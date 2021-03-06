#pragma once

#include <d3d11.h>
#include <vector>

namespace fw
{
class VertexShader
{
public:
    VertexShader();
    ~VertexShader();

    bool create(WCHAR* fileName, LPCSTR entryPoint, LPCSTR shaderModel, std::vector<D3D11_INPUT_ELEMENT_DESC> layout);
    bool create(WCHAR* fileName, LPCSTR entryPoint, LPCSTR shaderModel);
    ID3D11VertexShader* get() const;
    ID3D11InputLayout* getVertexLayout() const;

private:
    ID3D11VertexShader* vertexShader = nullptr;
    ID3D11InputLayout* vertexLayout = nullptr;
};

} // namespace fw
