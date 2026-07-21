// Copyright 2026 Simon Liimatainen. All rights reserved.
// do not include Box3D headers here, to avoid leaking C types into the global scope where this file is included

#pragma once
#include "include/b3cpp_base.h"
#include "include/b3cpp_shape.h"
#include <cstdint>
#include <memory>
#include <vector>
#include <concepts>

namespace b3cpp
{
	class World;

	class Body : public Wrapper
	{
	public:
		Body(World& world, BodyDef def = BodyDef());
		~Body();
		// movable, not copyable
		Body(const Body&) = delete;
		Body& operator=(const Body&) = delete;
		Body(Body&&) noexcept = default;
		Body& operator=(Body&&) noexcept = default;
		
		bool isIdValid() override;

		/*
		* Example:
		* Body b = physWorld.createBody();
		* SphereShape& shape = b.createShape<SphereShape>();
		* shape.radius = 1337.f;
		* shape.activate(shapeDef);
		*/
		template <typename T>
		requires std::derived_from<T, Shape>
		T& createShape()
		{
			shapes.push_back(std::unique_ptr<T>(new T(*this)));
			return *static_cast<T*>(shapes.back().get());
		}

		b3cpp::Vector getPosition() const;
		b3cpp::Vector getRotationQuat() const;
		b3cpp::Vector getRotationAxisAngle() const;
		void setTransform(b3cpp::Vector position, b3cpp::Vector rotationQuat);
		void setPosition(b3cpp::Vector position);
		void setRotationQuat(b3cpp::Vector rotationQuat);
		void applyAngularImpulse(b3cpp::Vector impulse);
		void applyTorque(b3cpp::Vector torque);
        void setLinearVelocity(b3cpp::Vector velocity);
		void setAngularVelocity(b3cpp::Vector velocity);
		
	protected:
		World& world;
		std::vector<std::unique_ptr<Shape>> shapes;
	};
}