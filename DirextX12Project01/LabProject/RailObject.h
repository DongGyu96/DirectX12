#pragma once
#include "GameObject.h"
#include "Rail.h"

class RailObject : public CGameObject
{

	bool pass = false;
public:
	RailObject();
	virtual ~RailObject();
	void PassOn() { pass = true; }
	void PassOff() { pass = false; }
	bool GetPass() { return pass; }

};

