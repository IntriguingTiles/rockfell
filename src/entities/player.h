#pragma once

#include "base_entity.h"

class CPlayer : public CBaseEntity {
	bool jump = false;
	Uint32 nextAttack = 0;
public:
	using CBaseEntity::CBaseEntity;
	void Update() override;
};