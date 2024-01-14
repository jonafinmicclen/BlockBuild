#ifndef PHYSICSOBJECT_H
#define PHYSICSOBJECT_H

class PhysicsObject {
public:
	virtual void update();
	int existanceTicks = 0;
};

#endif // PHYSICSOBJECT_H