#include "Objects/Camera.hpp"
#include "Objects/Adapters/CameraAdapter.hpp"
#include "Builders/CameraBuilders/DefaultCameraBuilder.hpp"
#include "Builders/DefaultIDGenerator.hpp"


DefaultCameraBuilder::DefaultCameraBuilder()
    : eye(0, 20, 30, 1), pitch(-atan2(20, 30)), yaw(M_PI)
{
}

DefaultCameraBuilder::DefaultCameraBuilder(const Vector &eye, double pitch, double yaw)
    : eye(eye), pitch(pitch), yaw(yaw)
{
}

std::unique_ptr<IObject> DefaultCameraBuilder::build()
{
    size_t id = DefaultIDGenerator().generate();
    Camera camera(eye, pitch, yaw);

    auto adapter = new ObjectAdapter<Camera>(id, camera);
    return std::unique_ptr<IObject>(adapter);
}
