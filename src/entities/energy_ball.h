#pragma once

#include "base_entity.h"

class CEnergyBall : public CBaseEntity {
public:
	using CBaseEntity::CBaseEntity;
	void Update() override;
};