#include "include/b3cpp_world.h"
#include "include/b3cpp_types.h"
#include "include/b3cpp_body.h"

#include "private/b3cpp_utils.h"
#include "box3d/include/box3d/box3d.h" // Box3D types used internally

#include <cstdint>

namespace 
{
	b3ShapeDef getShapeDef(b3cpp::ShapeDef def)
	{
		b3ShapeDef shapeDef = b3DefaultShapeDef();
		// TODO: apply values
		return shapeDef;
	}
}

namespace b3cpp
{
	Shape Shape::createSphere(const Body& body, ShapeDef def)
	{
		b3ShapeId id = b3CreateSphereShape(util::getId(&body), def)


		b3MakeSphere

		b3BoxHull groundBox = b3MakeBoxHull(50.0f, 10.0f, 50.0f);
		b3ShapeDef groundShapeDef = b3DefaultShapeDef();
		b3ShapeId id = b3CreateHullShape(util::getId(this), &groundShapeDef, &groundBox.base);
	}

	Shape Shape::createCapsule(const Body& body, ShapeDef def)
	{

	}

	Shape Shape::createHull(const Body& body, ShapeDef def)
	{

	}

	Shape Shape::createTriangles(const Body& body, ShapeDef def)
	{

	}

	Shape Shape::createHeightfield(const Body& body, ShapeDef def)
	{

	}

	bool Shape::isIdValid()
	{
		return b3Shape_IsValid(util::getId(this));
	}
}