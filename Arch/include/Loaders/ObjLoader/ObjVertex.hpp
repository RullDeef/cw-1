#ifndef OBJVERTEX_HPP
#define OBJVERTEX_HPP

#include <sstream>


class ObjVertex
{
public:
    static const long npos = -1000000;

    inline explicit ObjVertex(const std::string& str)
    {
        std::stringstream ss(str);

        ss >> posIndex; ss.ignore(1);
        ss >> texIndex; ss.clear(); ss.ignore(1);
        ss >> normIndex;
    }

    explicit ObjVertex(long posIndex, long texIndex = npos, long normIndex = npos)
        : posIndex(posIndex), texIndex(texIndex), normIndex(normIndex) {}

    inline long getPosIndex() const { return posIndex; }
    inline long getTexIndex() const { return texIndex; }
    inline long getNormIndex() const { return normIndex; }

    inline bool hasTexIndex() const { return texIndex != npos; }
    inline bool hasNormIndex() const { return normIndex != npos; }

private:
    long posIndex = npos;
    long texIndex = npos;
    long normIndex = npos;
};

#endif // OBJVERTEX_HPP
