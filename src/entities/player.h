#pragma once

#include "base_entity.h"

class CPlayer : public CBaseEntity {
public:
	using CBaseEntity::CBaseEntity;
	void Update() override;
};