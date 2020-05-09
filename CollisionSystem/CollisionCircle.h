#pragma once

#include "CollisionObject.h"

class CollisionCircle : public CollisionObject {
public:
	~CollisionCircle();
	CollisionCircle(double _radius, bool _active = true);
};
