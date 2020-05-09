#pragma once

#include "..\Vector3\Vector3\Vector3.h"
#include "..\Vector2\Vector2\Vector2.h"
#include "..\Vector2\Vector2\Vector2int.h"
#include "General.h"
#include <vector>

class CollisionObject {
public:
	enum class Type {
		CIRCLE,
		SIMPLE_RECTANGLE
	};

protected:
	struct Event {
		const CollisionObject* target;
		const Vector2 point;
		Event(const CollisionObject* _target, const Vector2 _point) :
			target(_target), point(_point) {}
	};
	std::vector<Event> events;

	Type type;
	bool active;
	double radius;
	Vector2 position;
	Vector2int mapPosition;

	CollisionObject(double _radius, bool _active = true);

public:
	~CollisionObject();

	Type getType() const;
	bool getActive() const;
	double getRadius() const;
	Vector2 getPosition() const;
	Vector2int getMapPosition() const;

	void setActive(bool _active);
	void setPosition(const Vector2& _position);

	void shiftPosition(const Vector2& _position);

	void addCollisionEvent(const CollisionObject* target, const Vector2 point);
	void resolveCollisions();
};
