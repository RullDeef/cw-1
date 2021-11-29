#ifndef ARCH_MESH_HPP
#define ARCH_MESH_HPP

#include <Core/Objects/Mesh.hpp>
#include "Math/Matrix.hpp"
#include "Math/Ray.hpp"
#include "Objects/Material.hpp"


class Mesh
{
public:
    explicit Mesh(const Core::Mesh& mesh);
    Mesh(const Mesh&) = delete;
    Mesh(Mesh&& temp) noexcept;
    ~Mesh();

    operator Core::Mesh() const;

    Mesh& operator=(const Mesh&) = delete;
    Mesh& operator=(Mesh&&) = delete;

    Material& getMaterial();
    [[nodiscard]] const Material& getMaterial() const;

    void setMaterial(const Material& newMaterial);

    Matrix getModelMatrix() const;
    void setModelMatrix(const Matrix& matrix);

    void setSelected(bool state);
    bool intersects(double& t, const Ray& ray) const;

private:
    Core::Mesh mesh;

    Material material;
};

#endif // ARCH_MESH_HPP
