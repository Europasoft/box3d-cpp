#include "include/b3cpp_world.h"
#include "include/b3cpp_types.h"
#include "include/b3cpp_body.h"

#include "private/b3cpp_utils.h"
#include "box3d/include/box3d/box3d.h" // Box3D types used internally

#include <cstdint>

namespace b3cpp
{
	World::World(WorldDef def)
	{
		b3WorldDef worldDef = b3DefaultWorldDef();
		def.gravity.applyIfNotNull(worldDef.gravity, util::vectorToB3(def.gravity.val()));
		def.restitutionThreshold.applyIfNotNull(worldDef.restitutionThreshold);
		def.hitEventThreshold.applyIfNotNull(worldDef.hitEventThreshold);
		def.contactHertz.applyIfNotNull(worldDef.contactHertz);
		def.contactDampingRatio.applyIfNotNull(worldDef.contactDampingRatio);
		def.contactSpeed.applyIfNotNull(worldDef.contactSpeed);
		def.maximumLinearSpeed.applyIfNotNull(worldDef.maximumLinearSpeed);
		def.enableSleep.applyIfNotNull(worldDef.enableSleep);
		def.enableContinuous.applyIfNotNull(worldDef.enableContinuous);
		b3WorldId id = b3CreateWorld(&worldDef);
		util::setId(this, id);
	}

	World::~World()
	{
		b3DestroyWorld(util::getId(this));
	}

	bool World::isIdValid()
	{
		return b3World_IsValid(util::getId(this));
	}

	std::unique_ptr<Body> World::createBody(BodyDef def)
	{
		return std::make_unique<Body>(*this, def);
	}

	void World::step(float timeStep, int subStepCount)
	{
		b3World_Step(util::getId(this), timeStep, subStepCount);
	}

	void World::step()
	{
		b3World_Step(util::getId(this), 0.01666f, 4);
	}

	void World::setGravity(Vector g)
	{
		b3World_SetGravity(util::getId(this), util::vectorToB3(g));
	}

    void World::explode(ExplosionDef def)
    {
		b3ExplosionDef explDef = b3DefaultExplosionDef();
		def.falloff.applyIfNotNull(explDef.falloff);
		def.position.applyIfNotNull(explDef.position, util::vectorToB3(def.position.val()));
		def.radius.applyIfNotNull(explDef.radius);
		def.maskBits.applyIfNotNull(explDef.maskBits);
		def.impulsePerArea.applyIfNotNull(explDef.impulsePerArea);
		b3World_Explode(util::getId(this), &explDef);
	}

	void World::setContactRecycleDistance(float distance)
	{
		b3World_SetContactRecycleDistance(util::getId(this), distance);
	}

	void World::setContactTuning(float hertz, float dampingRatio, float contactSpeed)
	{
		b3World_SetContactTuning(util::getId(this), hertz, dampingRatio, contactSpeed);
	}

	void World::setHitEventThreshold(float value)
	{
		b3World_SetHitEventThreshold(util::getId(this), value);
	}

	void World::setMaximumLinearSpeed(float maximumLinearSpeed)
	{
		b3World_SetMaximumLinearSpeed(util::getId(this), maximumLinearSpeed);
	}

	void World::setRestitutionThreshold(float value)
	{
		b3World_SetRestitutionThreshold(util::getId(this), value);
	}

	void World::enableContinuous(bool flag)
	{
		b3World_EnableContinuous(util::getId(this), flag);
	}

	void World::enableSleeping(bool flag)
	{
		b3World_EnableSleeping(util::getId(this), flag);
	}

	void World::enableSpeculative(bool flag)
	{
		b3World_EnableSpeculative(util::getId(this), flag);
	}

}