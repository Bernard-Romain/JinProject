#pragma once
#include "MovingEntity.h"

class LivingEntity : public MovingEntity {
public:
	explicit(false) LivingEntity(pugi::xml_node node);

	std::string dump(std::string const& indent) const override;
	void damage() const;
private:
	int hp;
};