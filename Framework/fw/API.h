#pragma once

#include "Timer.h"
#include "Input.h"
#include "Device.h"
#include <Keyboard.h>
#include <d3d11.h>
#include <windows.h>

namespace fw
{

class Framework;

class API
{
public:
	API() = delete;
	
	static void initialize(Framework* fw);

	static float getWindowRatio();
	static HWND getWindowHandle();

	static float getTimeSinceStart();
	static float getTimeDelta();

	static DirectX::Keyboard::State getKeyboardState();
	static bool isKeyReleased(DirectX::Keyboard::Keys k);
	static int getMouseX();
	static int getMouseY();
	
	static ID3D11DepthStencilView* getDepthStencilView();

	static void quit();

private:
	static Framework* framework;
	static Device* device;
	static const Timer* timer;
	static const Input* input;	
};

}