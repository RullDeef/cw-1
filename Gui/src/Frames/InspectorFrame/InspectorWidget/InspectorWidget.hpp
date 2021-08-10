#ifndef INSPECTORWIDGET_HPP
#define INSPECTORWIDGET_HPP

#include <QWidget>
#include <Objects/IObject.hpp>
#include <Objects/Mesh.hpp>
#include <Objects/ObjectAdapter.hpp>


QT_BEGIN_NAMESPACE
namespace Ui
{
    class InspectorWidget;
}
QT_END_NAMESPACE

class InspectorWidget : public QWidget
{
    Q_OBJECT

public:
    explicit InspectorWidget(QWidget *parent = nullptr);
    ~InspectorWidget() override;

    void inspect(nullptr_t);
    void inspect(const std::shared_ptr<IObject>& newObject);

protected:
    void inspect(ObjectAdapter<Mesh>& object);

private:
    Ui::InspectorWidget *ui;

    std::weak_ptr<IObject> object;
};

#endif // INSPECTORWIDGET_HPP
