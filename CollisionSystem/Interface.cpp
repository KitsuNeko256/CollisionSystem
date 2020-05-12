#include "Interface.h"

#include "collisionMap.h"
#include "ToString.h"
#include <iostream>
using namespace std;

void mainMenu() {
	string input;
	cout << "Write 'c' to collide two circles" << endl;
	cout << "Write 'r' to collide two rectangles" << endl;
	cout << "Write 'cr' to collide circle with rectangle" << endl;
	cin >> input;
	if (input == "c") {
		double x, y, r;
		cout << "Write x and y coordinates of center and radius of circle 1" << endl;
		cin >> x >> y >> r;
		CollisionCircle c1(r);
		c1.setPosition(Vector2(x, y));
		cout << "Write x and y coordinates of center and radius of circle 2" << endl;
		cin >> x >> y >> r;
		CollisionCircle c2(r);
		c2.setPosition(Vector2(x, y));

		cout << "Positions before check: " << toString(c1.getPosition()) << " " << toString(c2.getPosition()) << endl;
		CollisionMap::get()->checkAllCollisions();
		c1.resolveCollisions();
		c2.resolveCollisions();
		cout << "Positions after check: " << toString(c1.getPosition()) << " " << toString(c2.getPosition()) << endl;
	}
	if (input == "r") {
		double x, y, a, b;
		cout << "Write x and y coordinates of center and width and height of rectangle 1" << endl;
		cin >> x >> y >> a >> b;
		CollisionRectSimple c1(a, b);
		c1.setPosition(Vector2(x, y));
		cout << "Write x and y coordinates of center and width and height of rectangle 2" << endl;
		cin >> x >> y >> a >> b;
		CollisionRectSimple c2(a, b);
		c2.setPosition(Vector2(x, y));

		cout << "Positions before check: " << toString(c1.getPosition()) << " " << toString(c2.getPosition()) << endl;
		CollisionMap::get()->checkAllCollisions();
		c1.resolveCollisions();
		c2.resolveCollisions();
		cout << "Positions after check: " << toString(c1.getPosition()) << " " << toString(c2.getPosition()) << endl;
	}
	if (input == "cr") {
		double x, y, r, a, b;
		cout << "Write x and y coordinates of center and radius of circle" << endl;
		cin >> x >> y >> r;
		CollisionCircle c1(r);
		c1.setPosition(Vector2(x, y));

		cout << "Write x and y coordinates of center and width and height of rectangle" << endl;
		cin >> x >> y >> a >> b;
		CollisionRectSimple c2(a, b);
		c2.setPosition(Vector2(x, y));

		cout << "Positions before check: " << toString(c1.getPosition()) << " " << toString(c2.getPosition()) << endl;
		CollisionMap::get()->checkAllCollisions();
		c1.resolveCollisions();
		c2.resolveCollisions();
		cout << "Positions after check: " << toString(c1.getPosition()) << " " << toString(c2.getPosition()) << endl;
	}
}