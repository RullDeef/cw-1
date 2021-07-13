#ifndef IFRAME_HPP
#define IFRAME_HPP

#include <QDockWidget>


class IFrame : public QDockWidget
{
    Q_OBJECT

public:
    IFrame(const QString& title, QWidget* parent = nullptr);
    virtual ~IFrame() = default;
};

#endif // IFRAME_HPP
