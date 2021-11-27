//
// Created by rulldeef on 11/26/21.
//

#ifndef IIMPORTER_HPP
#define IIMPORTER_HPP

#include <istream>
#include <memory>

class Scene;
class IObject;
class Mesh;
class Camera;
class Light;


class IImporter
{
public:
    virtual ~IImporter() = default;

    virtual std::shared_ptr<Scene> importScene(std::istream& stream) = 0;
    virtual std::shared_ptr<IObject> importObject(std::istream& stream) = 0;

    virtual Mesh importMesh(std::istream& stream) = 0;
    virtual Camera importCamera(std::istream& stream) = 0;
    virtual Light importLight(std::istream& stream) = 0;
};

#endif //IIMPORTER_HPP
