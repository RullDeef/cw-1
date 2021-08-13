#ifndef COLOREDITWIDGET_HPP
#define COLOREDITWIDGET_HPP

#include <Math/Color.hpp>
#include <QWidget>


QT_BEGIN_NAMESPACE
namespace Ui
{
    class ColorEditWidget;
}
QT_END_NAMESPACE

class ColorEditWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ColorEditWidget(QWidget *parent = nullptr);
    ~ColorEditWidget() override;

    void setValue(const Color& color);
    [[nodiscard]] Color getValue() const;

protected slots:
    void colorPickedSlot(QColor color);

private:
    Ui::ColorEditWidget *ui;
};


#endif //COLOREDITWIDGET_HPP
