#pragma once

#include "Transformation.h"
#include <DirectXMath.h>

namespace fw
{

class Camera
{
public:	
	Camera();
	virtual ~Camera();

	float getNearClipDistance() const;
	float setNearClipDistance(float near);

	float getFarClipDistance() const;
	float setFarClipDistance(float far);

	const DirectX::XMMATRIX& updateViewMatrix();
	virtual const DirectX::XMMATRIX& updateProjectionMatrix() = 0;

	const DirectX::XMMATRIX& getViewMatrix() const;
	virtual const DirectX::XMMATRIX& getProjectionMatrix() const = 0;
	
	Transformation& getTransformation();

private:	
	float nearClipDistance = 0.1f;
	float farClipDistance = 100.0f;

	DirectX::XMMATRIX viewMatrix;	
	Transformation transformation;
};

} // fw
