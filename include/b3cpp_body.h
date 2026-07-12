// Copyright 2026 Simon Liimatainen. All rights reserved.
// do not include Box3D headers here, to avoid leaking C types into the global scope where this file is included

#pragma once
#include "include/b3cpp_base.h"
#include "include/b3cpp_types.h"
#include <cstdint>
#include <memory>
#include <vector>

namespace b3cpp
{
	class World;
	class Shape;

	class Body : public Wrapper
	{
	public:
		Body(World& world, BodyDef def = BodyDef());

		void addShape(const Shape& shape);

	protected:
		bool isIdValid() override;

		World& world;
		std::vector<std::unique_ptr<Shape>> shapes;
	};
}