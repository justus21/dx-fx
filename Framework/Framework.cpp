#include "Framework.h"
#include <iostream>

namespace fw
{

Framework::Framework(LONG windowWidth, LONG windowHeight) :
	window(windowWidth, windowHeight)
{
}

Framework::~Framework()
{	
}

bool Framework::initialize(HINSTANCE hInstance, int nCmdShow)
{
	AllocConsole();
	freopen_s(&consoleStream, "CONOUT$", "w", stdout);
	freopen_s(&consoleStream, "CONOUT$", "w", stderr);

	HRESULT hr = window.initialize(hInstance, nCmdShow);
	if (FAILED(hr)) {
		std::cerr << "ERROR: Failed to initialize window\n";
		return false;
	}

	if (FAILED(device.initialize(window.getWindowHandle()))) {
		std::cerr << "ERROR: Failed to initialize device\n";
		return false;
	}

	return true;
}

bool Framework::setApplication(Application* application)
{
	if (!application) {
		std::cerr << "ERROR: Invalid application pointer\n";
		return false;
	}

	app = application;
	app->initializeAPI(this);
	return app->initialize();
}

int Framework::execute()
{
	timer.start();
	MSG msg = {0};
	while (WM_QUIT != msg.message) {
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		} else {			
			app->update();
			timer.tick();
			app->render();
			app->gui();			
		}
	}
	return static_cast<int>(msg.wParam);
}

const Window& Framework::getWindow() const
{
	return window;
}

const Timer& Framework::getTimer() const
{
	return timer;
}

} // fw