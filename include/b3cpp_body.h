// Copyright 2026 Simon Liimatainen. All rights reserved.
// do not include Box3D headers here, to avoid leaking C types into the global scope where this file is included

#pragma once
#include "include/b3cpp_base.h"
#include "include/b3cpp_types.h"
#include "include/b3cpp_world.h"
#include <cstdint>

namespace b3cpp
{
	class Body : public Wrapper
	{
	public:
		Body(World& world, BodyDef def = BodyDef());

	protected:
		bool isIdValid() override;
	};
}