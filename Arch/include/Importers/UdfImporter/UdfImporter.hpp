//
// Created by rulldeef on 11/26/21.
//

#ifndef UDFIMPORTER_HPP
#define UDFIMPORTER_HPP

#include "Importers/IImporter.hpp"


class UdfImporter : public IImporter
{
public:
    std::shared_ptr<Scene> importScene(std::istream& stream) override;
    std::shared_ptr<IObject> importObject(std::istream& stream) override;

    Mesh importMesh(std::istream& stream) override;
    Camera importCamera(std::istream& stream) override;
    Light importLight(std::istream& stream) override;
};

#endif //UDFIMPORTER_HPP
