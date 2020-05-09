#pragma once

#include "CollisionObject.h"

class CollisionRectSimple : public CollisionObject {
private:
	double x;
	double y;

public:
	~CollisionRectSimple();
	CollisionRectSimple(double _x, double _y, bool _active = true);

	double getX() const;
	double getY() const;
};
