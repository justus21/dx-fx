#include "CameraController.h"
#include "Transformation.h"
#include "API.h"
#include "Common.h"
#include <DirectXMath.h>
#include <iostream>
#include <algorithm>

using namespace DirectX;

namespace
{

const float ROTATION_LIMIT = XMConvertToRadians(87.0f);

} // anonymous

namespace fw
{

CameraController::CameraController()
{
	setMovementSpeed(1.0f);
	setSensitivity(0.5f);
}

CameraController::~CameraController()
{
}

void CameraController::setCamera(Camera* c)
{
	camera = c;
}

void CameraController::setMovementSpeed(float s)
{
	movementSpeed = s;
}

void CameraController::setSensitivity(float s)
{
	sensitivity = XMConvertToRadians(s);
}

void CameraController::setResetPosition(std::array<float, 3> position)
{
	resetPosition = position;
}

void CameraController::setResetRotation(std::array<float, 3> rotation)
{
	resetRotation = rotation;
}

void CameraController::update()
{
	if (!camera) {
		printWarning("Camera is not set for camera controller");
		return;
	}

	const Keyboard::State& kb = API::getKeyboardState();
	if (kb.LeftShift) {
		return;
	}

	Transformation& t = camera->getTransformation();
	float speed = movementSpeed * API::getTimeDelta();
	
	if (kb.W) {
		t.move(t.getForward() * speed);
	}
	if (kb.S) {
		t.move(-t.getForward() * speed);
	}
	if (kb.A) {
		t.move(t.getLeft() * speed);
	}
	if (kb.D) {
		t.move(-t.getLeft() * speed);
	}

	if (API::getMouseState().leftButton == Mouse::ButtonStateTracker::HELD) {
		t.rotate(Transformation::UP, API::getDeltaX() * sensitivity);
		t.rotate(Transformation::LEFT, -API::getDeltaY() * sensitivity);
		XMFLOAT3 r;
		XMStoreFloat3(&r, t.rotation);
		r.x = std::min(r.x, ROTATION_LIMIT);
		r.x = std::max(r.x, -ROTATION_LIMIT);
		t.rotation = XMLoadFloat3(&r);
	}

	if (API::isKeyReleased(Keyboard::R)) {
		t.rotation = XMVectorSet(resetRotation[0], resetRotation[1], resetRotation[2], 0.0f);
		t.position = XMVectorSet(resetPosition[0], resetPosition[1], resetPosition[2], 0.0f);
	}
}

} // fw
