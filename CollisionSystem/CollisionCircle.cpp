#include "CollisionCircle.h"
#include "CollisionMap.h"

CollisionCircle::~CollisionCircle() {
	if (active)
		CollisionMap::get()->removeObject(this);
}
CollisionCircle::CollisionCircle(double _radius, bool _active) : CollisionObject(_radius, _active){
}
