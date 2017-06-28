#include "OrthographicCamera.h"

using namespace DirectX;

namespace fw
{

OrthographicCamera::OrthographicCamera()
{
	updateViewMatrix();
	updateProjectionMatrix();
}

OrthographicCamera::~OrthographicCamera()
{
}

void OrthographicCamera::setWidth(float w)
{
	width = w;
}

void OrthographicCamera::setHeight(float h)
{
	height = h;
}

const XMMATRIX& OrthographicCamera::updateProjectionMatrix()
{
	projectionMatrix = XMMatrixOrthographicLH(width, height, getNearClipDistance(), getFarClipDistance());
	return projectionMatrix;
}

const DirectX::XMMATRIX& OrthographicCamera::getProjectionMatrix() const
{
	return projectionMatrix;
}

} // fw
