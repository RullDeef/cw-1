#ifndef ARCH_MESH_HPP
#define ARCH_MESH_HPP

#include <Core/Objects/Mesh.hpp>


class Mesh
{
public:
    explicit Mesh(const Core::Mesh& mesh);
    Mesh(const Mesh&) = delete;
    Mesh(Mesh&& temp) noexcept;
    ~Mesh();

    explicit operator Core::Mesh() const;

    Mesh& operator=(const Mesh&) = delete;
    Mesh& operator=(Mesh&&) = delete;

private:
    Core::Mesh mesh;
};

#endif // ARCH_MESH_HPP
