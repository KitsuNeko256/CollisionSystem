#include "ToString.h"


std::string toString(const Vector3& t) {
	return "(" + std::to_string(t.x) + ", " + std::to_string(t.y) + ", " + std::to_string(t.z) + ")";
}

std::string toString(const Vector2& t) {
	return "(" + std::to_string(t.x) + ", " + std::to_string(t.y) + ")";
};

std::string toString(const Vector2int& t) {
	return "(" + std::to_string(t.x) + ", " + std::to_string(t.y) + ")";
};

