#ifndef OBJLOADER_HPP
#define OBJLOADER_HPP

#include <string>
#include <vector>
#include "Math/Vector.hpp"
#include "Objects/Mesh.hpp"
#include "Loaders/ILoader.hpp"
#include "Loaders/ObjLoader/ObjVertex.hpp"
#include "Loaders/ObjLoader/ObjFace.hpp"


class ObjLoader : public ILoader
{
public:
    using ObjFaceList = std::vector<ObjFace>;
    using ObjObject = std::pair<std::string, ObjFaceList>;

    std::unique_ptr<Scene> loadScene(const std::string& filename) override;

    std::unique_ptr<IObject> loadMesh(const std::string& filename) override;
    std::unique_ptr<IObject> loadCamera(const std::string& filename) override;
    std::unique_ptr<IObject> loadLight(const std::string& filename) override;

private:
    static std::vector<Vector> extractGeometry(std::ifstream& file);
    static std::vector<Vector> extractTextureUV(std::ifstream& file);
    static std::vector<Vector> extractNormals(std::ifstream& file);

    static std::list<ObjObject> extractMeshesList(std::ifstream& file);

    static Mesh constructMesh(const ObjFaceList &faces, const std::vector<Vector> &positions,
                              const std::vector<Vector> &textures, const std::vector<Vector> &normals);

    static Vector extractVector2(const std::string& str);
    static Vector extractVector3(const std::string& str, double w);

    static bool acceptWhenToken(std::string& line, const char* token);

    static std::string trim(const std::string& str);


    /// TODO: static std::map<std::string, Core::Material> loadMaterials(const std::string& filename);
};

#endif // OBJLOADER_HPP
