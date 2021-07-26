#ifndef IFRAME_HPP
#define IFRAME_HPP

#include <DockWidget.h>


class IFrame : public ads::CDockWidget
{
    Q_OBJECT

public:
    IFrame(const QString& title, QWidget* parent = nullptr);
    virtual ~IFrame() = default;
};

#endif // IFRAME_HPP
