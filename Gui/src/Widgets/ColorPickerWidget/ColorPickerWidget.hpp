#ifndef COLORPICKERWIDGET_HPP
#define COLORPICKERWIDGET_HPP

#include <QWidget>


class ColorPickerWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ColorPickerWidget(QWidget *parent = nullptr);
    ~ColorPickerWidget() override = default;

    void setColor(QColor newColor);

signals:
    void colorPicked(QColor color);

protected:
    void mouseReleaseEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent* event) override;

private:
    QColor color;
};


#endif //COLORPICKERWIDGET_HPP
