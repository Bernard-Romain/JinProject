#include "Entity.h"

class MovingEntity : public Entity {
public:
	void move();
private:
	int speed;
};