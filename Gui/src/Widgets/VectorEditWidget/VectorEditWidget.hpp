#ifndef VECTOREDITWIDGET_HPP
#define VECTOREDITWIDGET_HPP

#include <QWidget>
#include <Math/Vector.hpp>


QT_BEGIN_NAMESPACE
namespace Ui
{
    class VectorEditWidget;
}
QT_END_NAMESPACE

class VectorEditWidget : public QWidget
{
    Q_OBJECT

public:
    explicit VectorEditWidget(QWidget *parent = nullptr);
    ~VectorEditWidget() override;

    void setValue(const Vector& vector);
    [[nodiscard]] Vector getValue() const;

private:
    Ui::VectorEditWidget *ui;
};


#endif //VECTOREDITWIDGET_HPP
