#include "include/b3cpp_body.h"
#include "include/b3cpp_types.h"
#include "include/b3cpp_world.h"
#include "include/b3cpp_shape.h"

#include "private/b3cpp_utils.h"
#include "box3d/include/box3d/box3d.h" // Box3D types used internally

#include <cstdint>
#include <cstring> // for std::memcpy
#include <cassert>

namespace b3cpp
{
	Body::Body(World& world, BodyDef def)
		: world(world)
	{
		b3BodyDef groundBodyDef = b3DefaultBodyDef();
		def.type.applyIfNotNull(groundBodyDef.type, static_cast<b3BodyType>(def.type.val()));
		def.position.applyIfNotNull(groundBodyDef.position, util::vectorToB3Pos(def.position.val()));
		def.rotation.applyIfNotNull(groundBodyDef.rotation, util::vectorToB3Quat(def.position.val()));
		def.linearVelocity.applyIfNotNull(groundBodyDef.linearVelocity, util::vectorToB3(def.position.val()));
		def.angularVelocity.applyIfNotNull(groundBodyDef.angularVelocity, util::vectorToB3(def.position.val()));
		def.linearDamping.applyIfNotNull(groundBodyDef.linearDamping);
		def.angularDamping.applyIfNotNull(groundBodyDef.angularDamping);
		def.gravityScale.applyIfNotNull(groundBodyDef.gravityScale);
		def.sleepThreshold.applyIfNotNull(groundBodyDef.sleepThreshold);
		def.enableSleep.applyIfNotNull(groundBodyDef.enableSleep);
		def.isAwake.applyIfNotNull(groundBodyDef.isAwake);
		def.isBullet.applyIfNotNull(groundBodyDef.isBullet);
		def.isEnabled.applyIfNotNull(groundBodyDef.isEnabled);
		def.allowFastRotation.applyIfNotNull(groundBodyDef.allowFastRotation);
		def.enableContactRecycling.applyIfNotNull(groundBodyDef.enableContactRecycling);
		b3BodyId id = b3CreateBody(util::getId(&world), &groundBodyDef);
		util::setId(this, id);
	}

    Body::~Body()
    {
		// no need to manually destroy shapes here
		if (isIdValid()) b3DestroyBody(util::getId(this));
	}

	bool Body::isIdValid()
	{
		return b3Body_IsValid(util::getId(this));
	}

	b3cpp::Vector Body::getPosition() const
	{
		const b3Vec3 p = b3Body_GetPosition(util::getId(this));
		return b3cpp::Vector(p.x, p.y, p.z);
	}

	b3cpp::Vector Body::getRotationQuat() const
	{
		const b3Quat q = b3Body_GetRotation(util::getId(this));
		return b3cpp::Vector(q.v.x, q.v.y, q.v.z, q.s);
	}

	b3cpp::Vector Body::getRotationAxisAngle() const
	{
		const b3Quat q = b3Body_GetRotation(util::getId(this));
		float rad = 0;
		const b3Vec3 a = b3GetAxisAngle(&rad, q);
		return b3cpp::Vector(a.x * rad, a.y * rad, a.z * rad, 0);
	}

	void Body::setTransform(b3cpp::Vector position, b3cpp::Vector rotationQuat)
	{
		b3Body_SetTransform(util::getId(this), util::vectorToB3Pos(position), util::vectorToB3Quat(rotationQuat));
	}

	void Body::setPosition(b3cpp::Vector position)
	{
		const b3Quat q = b3Body_GetRotation(util::getId(this));
		b3Body_SetTransform(util::getId(this), util::vectorToB3Pos(position), q);
	}

	void Body::setRotationQuat(b3cpp::Vector rotationQuat)
	{
		const b3Pos p = b3Body_GetPosition(util::getId(this));
		b3Body_SetTransform(util::getId(this), p, util::vectorToB3Quat(rotationQuat));
	}

	void Body::applyAngularImpulse(b3cpp::Vector impulse)
	{
		b3Body_ApplyAngularImpulse(util::getId(this), util::vectorToB3(impulse), true);
	}

	void Body::applyTorque(b3cpp::Vector torque)
	{
		b3Body_ApplyTorque(util::getId(this), util::vectorToB3(torque), true);
	}

}