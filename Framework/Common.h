#pragma once

#include "Framework.h"
#include <d3dx11.h>
#include <d3dcompiler.h>
#include <cstdlib>

namespace fw
{

template <typename T>
inline int executeGenericMain(HINSTANCE hInstance, int nCmdShow)
{
	int ret = EXIT_FAILURE;
	Framework framework;
	if (framework.initialize(hInstance, nCmdShow)) {
		T app;
		if (framework.setApplication(&app)) {
			ret = framework.execute();
		}
	}
	return ret;
}

inline HRESULT compileShaderFromFile(WCHAR* fileName, LPCSTR entryPoint, LPCSTR shaderModel, ID3DBlob** blobOut)
{
	HRESULT hr = S_OK;

	DWORD shaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#if defined(DEBUG)
	dwShaderFlags |= D3DCOMPILE_DEBUG;
#endif

	ID3DBlob* errorBlob;
	hr = D3DX11CompileFromFile(fileName, nullptr, nullptr, entryPoint, shaderModel,
							   shaderFlags, 0, nullptr, blobOut, &errorBlob, nullptr);
	if (FAILED(hr)) {
		if (errorBlob != nullptr) {
			OutputDebugStringA((char*)errorBlob->GetBufferPointer());
		}
	}
	if (errorBlob) {
		errorBlob->Release();
	}

	return hr;
}

template <typename T>
inline void release(T* t)
{
	if (t) {
		t->Release();
	}
}

} // fx