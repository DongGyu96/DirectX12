#pragma once
#include "Camera.h"
#include "Mesh.h"

class Rail : public CMesh
{
public:
	Rail(float width = 1.0f, float height = 1.0f, float depth = 2.0f, int count = 5);
	virtual ~Rail();
};

