#pragma once

#include "CollisionObject.h"
#include "CollisionCircle.h"
#include "CollisionRectSimple.h"

class CollisionMap {
private:
	CollisionMap();
	CollisionMap(const CollisionMap& root) = delete;
	CollisionMap& operator=(const CollisionMap&) = delete;

	std::vector<std::vector<std::vector<CollisionObject*>>> map;

	static const uint16_t width = 100;
	static const uint16_t height = 100;
	static const uint16_t tileSize = 1000;

	void collideCircles(CollisionCircle* left, CollisionCircle* right);
	void collideRectSimples(CollisionRectSimple* left, CollisionRectSimple* right);
//	void collideCircle_RectSimple(CollisionCircle* left, CollisionRectSimple* right);

public:
	static CollisionMap* instance;
	static CollisionMap* get();

	uint16_t getWidth() const;
	uint16_t getHeight() const;
	uint16_t getTileSize() const;
	
	static Vector2int countMapPosition(Vector2 position);

	void addObject(CollisionObject* collider);	
	void removeObject(CollisionObject* collider);

	void collideObjects(CollisionObject* left, CollisionObject* right);
	void checkCollisions(CollisionObject* collider);
	void checkAllCollisions();
};

