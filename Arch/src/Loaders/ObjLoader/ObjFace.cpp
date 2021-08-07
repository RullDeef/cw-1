#include <sstream>
#include <algorithm>
#include "Loaders/ObjLoader/ObjFace.hpp"


ObjFace::ObjFace(const std::string &str)
{
    std::stringstream ss(str);
    std::string vertStr;

    while (ss >> vertStr)
        vertexList.emplace_back(vertStr);
}

std::vector<ObjFace> ObjFace::triangulate() const
{
    if (vertexList.size() == 3)
        return { *this };

    size_t i = 0, j = 1, k = 2;
    std::vector<ObjFace> result;
    while (k < vertexList.size())
    {
        result.push_back(getTriangle(i, j, k));
        j = k;
        k++;
    }

    return result;
}

ObjFace::ObjFace(const ObjVertex &v1, const ObjVertex &v2, const ObjVertex &v3)
{
    vertexList.push_back(v1);
    vertexList.push_back(v2);
    vertexList.push_back(v3);
}

ObjFace ObjFace::getTriangle(size_t i, size_t j, size_t k) const
{
    return ObjFace(vertexList[i], vertexList[j], vertexList[k]);
}

bool ObjFace::hasTexIndex() const
{
    return std::all_of(vertexList.begin(), vertexList.end(), [](const ObjVertex& v) { return v.hasTexIndex(); });
}

bool ObjFace::hasNormIndex() const
{
    return std::all_of(vertexList.begin(), vertexList.end(), [](const ObjVertex& v) { return v.hasNormIndex(); });
}
