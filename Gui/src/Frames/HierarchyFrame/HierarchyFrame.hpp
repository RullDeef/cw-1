#ifndef HEIRARCHYFRAME_HPP
#define HEIRARCHYFRAME_HPP

#include <list>
#include "Managers/IManagerFactory.hpp"
#include "Frames/IFrame.hpp"
#include "Objects/IObject.hpp"


class HierarchyFrame : public IFrame
{
    Q_OBJECT

public:
    HierarchyFrame(IManagerFactory& managerFactory, QWidget* parent = nullptr);
    virtual ~HierarchyFrame() = default;

    void updateHierarchy();

private:
    void displayObject(std::shared_ptr<IObject> object);

    void clearLayout(QLayout* layout);

    IManagerFactory& managerFactory;
};

#endif // HEIRARCHYFRAME_HPP
