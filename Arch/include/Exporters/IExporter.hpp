//
// Created by rulldeef on 11/26/21.
//

#ifndef IEXPORTER_HPP
#define IEXPORTER_HPP

#include <ostream>
#include <memory>

class Scene;
class IObject;


class IExporter
{
public:
    virtual ~IExporter() = default;

    virtual void exportScene(std::ostream& stream, std::shared_ptr<Scene> scene) = 0;
};

#endif //IEXPORTER_HPP
