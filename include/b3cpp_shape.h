// Copyright 2026 Simon Liimatainen. All rights reserved.
// do not include Box3D headers here, to avoid leaking C types into the global scope where this file is included

#pragma once
#include "include/b3cpp_base.h"
#include "include/b3cpp_types.h"
#include <cstdint>

namespace b3cpp
{
	class Body;

	class Shape : public Wrapper
	{
	private:
		Shape() {};
	public:
		static Shape createSphere(const Body& body, ShapeDef def);
		static Shape createCapsule(const Body& body, ShapeDef def);
		static Shape createHull(const Body& body, ShapeDef def);
		static Shape createTriangles(const Body& body, ShapeDef def);
		static Shape createHeightfield(const Body& body, ShapeDef def);

	protected:
		bool isIdValid() override;

	};
}