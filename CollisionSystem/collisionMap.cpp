#include "CollisionMap.h"

///////////////////
// COLLISION MAP //
///////////////////

CollisionMap* CollisionMap::instance;


CollisionMap::CollisionMap() {
	map.resize(height);
	for (uint16_t i = 0; i < map.size(); ++i)
		map[i].resize(width);
}
CollisionMap* CollisionMap::get() {
	if(instance == nullptr)
		instance = new CollisionMap();
	return instance;
}

uint16_t CollisionMap::getWidth() const {
	return width;
}
uint16_t CollisionMap::getHeight() const {
	return height;
}
uint16_t CollisionMap::getTileSize() const {
	return tileSize;
}

Vector2int CollisionMap::countMapPosition(Vector2 position) {
	Vector2int pos = Vector2int(position.x / tileSize, position.y / tileSize);
	pos.x = getInRange(0, pos.x, width);
	pos.y = getInRange(0, pos.y, height);
	return pos;
}

void CollisionMap::addObject(CollisionObject* collider) {
	Vector2int pos = collider->getMapPosition();
	if (!isInRange(0, pos.x, width) || !isInRange(0, pos.y, height))
		return;
	map[pos.x][pos.y].push_back(collider);
}   
void CollisionMap::removeObject(CollisionObject* collider) {
	Vector2int pos = collider->getMapPosition();
	if (!isInRange(0, pos.x, width) || !isInRange(0, pos.y, height))
		return;
	std::vector<CollisionObject*>& object = map[pos.x][pos.y];
	for (uint16_t i = 0; i < object.size(); ++i)
		if (object[i] == collider) {
			std::swap(object[i], object[object.size() - 1]);
			object.pop_back();
			return;
		}
}

void CollisionMap::checkAllCollisions() {
	for (uint16_t x1 = 0; x1 < width; ++x1) {
		for (uint16_t y1 = 0; y1 < height; ++y1) {
			for (uint16_t i = 0; i < map[x1][y1].size(); ++i) {
				if (!map[x1][y1][i]->getActive())
					continue;
				Vector2int pos = map[x1][y1][i]->getMapPosition();
				uint16_t left = max(0, pos.x - 1);
				uint16_t right = min(pos.x + 1, width - 1);
				uint16_t down = min(pos.y + 1, height - 1);
				for (uint16_t j = i + 1; j < map[x1][y1].size(); ++j) {
					collideObjects(map[x1][y1][i], map[x1][y1][j]);
				}
				for (uint16_t x2 = x1 + 1; x2 <= right; ++x2) {
					for(uint16_t j = 0; j < map[x2][y1].size(); ++j)
						collideObjects(map[x1][y1][i], map[x2][y1][j]);
				}
				for (uint16_t x2 = left; x2 <= right; ++x2) {
					for (uint16_t y2 = y1 + 1; y2 <= down; ++y2) {
						for (uint16_t j = 0; j < map[x2][y2].size(); ++j)
							collideObjects(map[x1][y1][i], map[x2][y2][j]);
					}
				}
			}
		}
	}
}

void CollisionMap::checkCollisions(CollisionObject* object) {
	if (!object->getActive())
		return;
	Vector2int pos = object->getMapPosition();
	uint16_t left = max(0, pos.x - 1);
	uint16_t right = min(pos.x + 1, width - 1);
	uint16_t top = max(0, pos.y - 1);
	uint16_t down = min(pos.y + 1, height - 1);
	for (uint16_t x = left; x <= right; ++x)
		for (uint16_t y = top; y <= down; ++y)
			for (uint16_t i = 0; i < map[x][y].size(); ++i) {
				collideObjects(object, map[x][y][i]);
			}
}

void CollisionMap::collideObjects(CollisionObject* left, CollisionObject* right) {
	if (left == right || !left->getActive() || !right->getActive())
		return;
	Vector2 midLine = right->getPosition() - left->getPosition();
	double distance = midLine.length() - (left->getRadius() + right->getRadius());
	if (distance > 0)
		return;
	switch (left->getType()) {
	case CollisionObject::Type::CIRCLE:
		switch (right->getType()) {
		case CollisionObject::Type::CIRCLE:
			collideCircles((CollisionCircle*)left, (CollisionCircle*)right);
			break;
		case CollisionObject::Type::SIMPLE_RECTANGLE:
			collideCircle_RectSimple((CollisionCircle*)left, (CollisionRectSimple*)right);
			break;
		}
		break;
	case CollisionObject::Type::SIMPLE_RECTANGLE:
		switch (right->getType()) {
		case CollisionObject::Type::CIRCLE:
			collideCircle_RectSimple((CollisionCircle*)right, (CollisionRectSimple*)left);
			break;
		case CollisionObject::Type::SIMPLE_RECTANGLE:
			collideRectSimples((CollisionRectSimple*)left, (CollisionRectSimple*)right);
			break;
		}
		break;
	}
}

void CollisionMap::collideCircles(CollisionCircle* left, CollisionCircle* right) {
	Vector2 midLine = right->getPosition() - left->getPosition();
	midLine /= 2;
	midLine.setLength(left->getRadius() - midLine.length());
	left->addCollisionEvent(right, midLine);
	right->addCollisionEvent(left, -midLine);
}


void CollisionMap::collideRectSimples(CollisionRectSimple* left, CollisionRectSimple* right) {
	Vector2 midLine = right->getPosition() - left->getPosition();
	midLine -= Vector2(left->getX() + right->getX(), left->getY() + right->getY());
	if (midLine.x > 0 || midLine.y > 0)
		return;
	midLine /= 2;
	left->addCollisionEvent(right, -midLine);
	right->addCollisionEvent(left, midLine);
}
void CollisionMap::collideCircle_RectSimple(CollisionCircle* left, CollisionRectSimple* right) {
	Vector2 midLine = right->getPosition() - left->getPosition();
	midLine -= Vector2(min(midLine.x, right->getX()), min(midLine.y, right->getY()));
	if (midLine.length() > left->getRadius())
		return;
	midLine.setLength(midLine.length() - left->getRadius());
	midLine /= 2;
	left->addCollisionEvent(right, -midLine);
	right->addCollisionEvent(left, midLine);
}
