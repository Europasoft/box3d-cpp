## Code example
```cpp
#include "box3d-cpp/include/b3cpp.h"
using namespace b3cpp;

WorldDef worldDef;
worldDef.gravity = b3cpp::Vector{ 0, 0, -1 };
std::unique_ptr<World> world = std::make_unique<b3cpp::World>(worldDef);

BodyDef bodyDef;
bodyDef.type = EBodyType::DynamicBody;
physicsBody = world->createBody(bodyDef);
SphereShape& sphereShape = physicsBody->createShape<SphereShape>();
sphereShape.radius = 1.f;
ShapeDef shapeDef;
sphereShape.activate(shapeDef);

const b3cpp::Vector position = physicsBody->getPosition();
```

## RAII Lifetime rules
- After a b3cpp::World gets destroyed, all b3cpp::Body objects created from it will be unsafe to use. Do not keep references to a Body after its World is destroyed.

- An object of the b3cpp::World type will tear down its physics state when it goes out of scope, keep the instance (or a smart pointer to it) to keep the World active.

- The same goes for b3cpp::Body, i.e. it must be kept in memory; the lifetime of the internal physics body is directly coupled to the lifetime of the b3cpp::Body object.

- References to b3cpp::Shape objects are non-owning. The shapes themselves are owned by the Body they are attached to, meaning you may safely "forget" a shape after adding it to a body (but don't forget to call Shape::activate()).

- A b3cpp::Shape only lives as long as the Body it as attached to, after which it becomes unsafe to use.
