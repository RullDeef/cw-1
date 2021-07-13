#ifndef VIEWPORTFRAME_HPP
#define VIEWPORTFRAME_HPP

#include "IFrame.hpp"

class QPaintEvent;


class ViewportFrame : public IFrame
{
    Q_OBJECT

public:
    ViewportFrame(QWidget* parent = nullptr);
    virtual ~ViewportFrame() = default;

protected:
    virtual void paintEvent(QPaintEvent* event) override;
};

#endif // VIEWPORTFRAME_HPP
