#include "MovingEntity.h"

class LivingEntity : public MovingEntity {
public:
	void damage();
private:
	int hp;
};