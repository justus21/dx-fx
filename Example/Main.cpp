#include "ExampleApp.h"
#include <Common.h>
#include <windows.h>

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPWSTR /*lpCmdLine*/, int nCmdShow)
{
	return fw::executeGenericMain<ExampleApp>(hInstance, nCmdShow);
}