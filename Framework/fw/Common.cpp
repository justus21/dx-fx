#include "Common.h"
#include "WcharHelper.h"
#include "imgui/imgui.h"
#include <comdef.h>
#include <sstream>

namespace fw
{
VertexBuffer::~VertexBuffer()
{
    if (releaseOnDestruction)
    {
        release(vertexBuffer);
        release(indexBuffer);
    }
}

void printHresult(HRESULT* hr, std::wostream& os)
{
    if (hr)
    {
        os << "HRESULT: " << _com_error(*hr).ErrorMessage() << "\n";
    }
}

void printError(const std::string& msg, HRESULT* hr)
{
    std::cerr << "ERROR: " << msg << "\n";
    printHresult(hr, std::wcerr);
}

void printWarning(const std::string& msg, HRESULT* hr)
{
    std::cerr << "WARNING: " << msg << "\n";
    printHresult(hr, std::wcerr);
}

bool fileExists(const char* fileName)
{
    if (GetFileAttributes(fileName) == INVALID_FILE_ATTRIBUTES && GetLastError() == ERROR_FILE_NOT_FOUND)
    {
        return false;
    }
    return true;
}

bool fileExists(const WCHAR* fileName)
{
    ToChar helper(fileName);
    return fileExists(helper.getChar());
}

bool compileShaderFromFile(WCHAR* fileName, LPCSTR entryPoint, LPCSTR shaderModel, ID3DBlob** blobOut)
{
    if (!fileExists(fileName))
    {
        ToChar t(fileName);
        std::stringstream ss;
        ss << "File not found: " << t.getChar() << "\n";
        printError(ss.str());
        return false;
    }
    HRESULT hr = S_OK;

    DWORD shaderFlags = D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_PACK_MATRIX_ROW_MAJOR;
#if defined(DEBUG)
    dwShaderFlags |= D3DCOMPILE_DEBUG;
#endif

    ID3DBlob* errorBlob = nullptr;
    hr = D3DCompileFromFile(fileName, nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, entryPoint, shaderModel, shaderFlags, 0, blobOut, &errorBlob);
    if (FAILED(hr))
    {
        if (errorBlob != nullptr)
        {
            printError(static_cast<char*>(errorBlob->GetBufferPointer()), &hr);
        }
    }
    if (errorBlob)
    {
        errorBlob->Release();
    }
    if (!(*blobOut))
    {
        printError("Shader blob is a nullptr. Probably something wrong with the shader file");
        return false;
    }

    return !FAILED(hr);
}

std::vector<float> getVertexData(const fw::Model& model)
{
    std::vector<float> vertexData;
    for (const auto& mesh : model.getMeshes())
    {
        for (unsigned int i = 0; i < mesh.vertices.size(); ++i)
        {
            vertexData.push_back(mesh.vertices[i].x);
            vertexData.push_back(mesh.vertices[i].y);
            vertexData.push_back(mesh.vertices[i].z);
            vertexData.push_back(mesh.normals[i].x);
            vertexData.push_back(mesh.normals[i].y);
            vertexData.push_back(mesh.normals[i].z);
            vertexData.push_back(mesh.uvs[i].x);
            vertexData.push_back(mesh.uvs[i].y);
        }
    }
    return vertexData;
}

void displayVector(const std::string& text, const DirectX::XMVECTOR& vector)
{
    DirectX::XMFLOAT4 f;
    DirectX::XMStoreFloat4(&f, vector);
    ImGui::Text(text.c_str(), f.x, f.y, f.z, f.w);
}

} // namespace fw
