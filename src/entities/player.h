#pragma once

#include "base_entity.h"

class CPlayer : public CBaseEntity {
	bool jump = false;
public:
	using CBaseEntity::CBaseEntity;
	void Update() override;
};