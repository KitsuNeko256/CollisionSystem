#include "collisionObject.h"
#include "CollisionMap.h"

//////////////////////
// COLLISION OBJECT //
//////////////////////

CollisionObject::~CollisionObject() {
	if(active)
		CollisionMap::get()->removeObject(this);
}
CollisionObject::CollisionObject(double _radius, bool _active) :
	type(Type::CIRCLE), radius(_radius), active(_active) {
	if (active) {
		mapPosition = CollisionMap::countMapPosition(position);	
		CollisionMap::get()->addObject(this);
	}
}

////////////////
// GET VALUES //
////////////////

CollisionObject::Type CollisionObject::getType() const {
	return type;
}
bool CollisionObject::getActive() const {
	return active;
}
double CollisionObject::getRadius() const {
	return radius;
}
Vector2 CollisionObject::getPosition() const {
	return position;
}
Vector2int CollisionObject::getMapPosition() const {
	return mapPosition;
}

///////////////////
// CHANGE VALUES //
///////////////////

void CollisionObject::setActive(bool _active) {
	if (active == _active)
		return;
	active = _active;
	if (active) {
		mapPosition = CollisionMap::countMapPosition(position);
		CollisionMap::get()->addObject(this);
	}
	else {
		CollisionMap::get()->removeObject(this);
	}
}
void CollisionObject::setPosition(const Vector2& _position) {
	position = _position;
	if (!active)
		return;
	Vector2int newMapPosition = CollisionMap::countMapPosition(position);
	if (mapPosition != newMapPosition) {
		CollisionMap::get()->removeObject(this);
		mapPosition = newMapPosition;
		CollisionMap::get()->addObject(this);
	}
}

void CollisionObject::shiftPosition(const Vector2& _position) {
	setPosition(position + _position);
}

//////////////////////
// COLLISION CHECKS //
//////////////////////

void CollisionObject::addCollisionEvent(const CollisionObject* target, const Vector2 point) {
	events.push_back(Event(target, point));
}

void CollisionObject::resolveCollisions() {
	for (uint16_t i = 0; i < events.size(); ++i) {
		shiftPosition(-events[i].point);
	}
	events.clear();
}

//////////////////////
//////////////////////
//////////////////////

