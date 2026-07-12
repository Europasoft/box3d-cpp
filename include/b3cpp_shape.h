// Copyright 2026 Simon Liimatainen. All rights reserved.
// do not include Box3D headers here, to avoid leaking C types into the global scope where this file is included

#pragma once
#include "include/b3cpp_base.h"
#include "include/b3cpp_types.h"
#include <cstdint>
#include <vector>

namespace b3cpp
{
	class Body;
	class World;

	class Shape : public Wrapper
	{
	public:
		Shape(ShapeDef shapeDef) : def(shapeDef) {};
		~Shape() { destroy(); }

	protected:
		friend class Body;

		virtual void addToBody(Body& body) = 0;
		virtual void destroy();

		bool isIdValid() override;

		ShapeDef def;
		void* data = nullptr;
	};

	class BoxHullShape : public Shape
	{
	public:
		float halfWidthX = 100.f;
		float halfWidthY = 100.f;
		float halfWidthZ = 100.f;
		virtual void addToBody(Body& body) override;
	};

	class SphereShape : public Shape
	{
	public:
		Vector localCenter;
		float radius = 100.f;
		virtual void addToBody(Body& body) override;
	};

	class CapsuleShape : public Shape
	{
	public:
		Vector center1;
		Vector center2;
		float radius = 100.f;
		virtual void addToBody(Body& body) override;
	};

	class HullShape : public Shape
	{
	public:
		std::vector<Vector> vertices;
		virtual void addToBody(Body& body) override;
		virtual void destroy() override;
	};

	class HeightfieldShape : public Shape
	{
	public:
		virtual void addToBody(Body& body) override;
		virtual void destroy() override;
	};

	class MeshShape : public Shape
	{
	public:
		virtual void addToBody(Body& body) override;
		virtual void destroy() override;
	};
}