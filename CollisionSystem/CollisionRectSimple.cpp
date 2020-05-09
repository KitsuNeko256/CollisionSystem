#include "CollisionRectSimple.h"
#include "CollisionMap.h"

CollisionRectSimple::~CollisionRectSimple() {
	if (active)
		CollisionMap::get()->removeObject(this);
}
CollisionRectSimple::CollisionRectSimple(double _x, double _y, bool _active) :
	CollisionObject(sqrt(_x* _x + _y * _y), _active),
	x(_x),
	y(_y)
{
	type = Type::SIMPLE_RECTANGLE;
}

double CollisionRectSimple::getX() const {
	return x;
}
double CollisionRectSimple::getY() const {
	return y;
}