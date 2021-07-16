#ifndef HEIRARCHYFRAME_HPP
#define HEIRARCHYFRAME_HPP

#include <list>
#include "IFrame.hpp"


class HierarchyFrame : public IFrame
{
    Q_OBJECT

public:
    HierarchyFrame(QWidget* parent = nullptr);
    virtual ~HierarchyFrame() = default;
};

#endif // HEIRARCHYFRAME_HPP
