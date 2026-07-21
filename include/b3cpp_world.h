// Copyright 2026 Simon Liimatainen. All rights reserved.
// do not include Box3D headers here, to avoid leaking C types into the global scope where this file is included

#pragma once
#include "include/b3cpp_base.h"
#include <cstdint>
#include <memory>

namespace b3cpp
{
	class Body;

	class World : public Wrapper
	{
	public:
		World(WorldDef def = WorldDef());
		~World();
		bool isIdValid() override;

		std::unique_ptr<Body> createBody(BodyDef def = BodyDef());
		void step(float timeStep, int subStepCount);
		void step();
		void setGravity(Vector g);
		void explode(ExplosionDef def);
		void setContactRecycleDistance(float distance);
		void setContactTuning(float hertz, float dampingRatio, float contactSpeed);
		void setHitEventThreshold(float value);
		void setMaximumLinearSpeed(float maximumLinearSpeed);
		void setRestitutionThreshold(float value);
		void enableContinuous(bool flag);
		void enableSleeping(bool flag);
		void enableSpeculative(bool flag);
	};
}