#ifndef INSPECTORWIDGET_HPP
#define INSPECTORWIDGET_HPP

#include <QWidget>


QT_BEGIN_NAMESPACE
namespace Ui
{
    class InspectorWidget;
}
QT_END_NAMESPACE

class InspectorWidget
        : public QWidget
{
    Q_OBJECT

public:
    explicit InspectorWidget(QWidget *parent = nullptr);

    ~InspectorWidget() override;

private:
    Ui::InspectorWidget *ui;
};

#endif // INSPECTORWIDGET_HPP
