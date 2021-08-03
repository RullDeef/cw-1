//
// Created by rulldeef on 8/3/21.
//

#ifndef CW_1_SETTINGSWIDGET_HPP
#define CW_1_SETTINGSWIDGET_HPP

#include <QWidget>


QT_BEGIN_NAMESPACE
namespace Ui
{
    class SettingsWidget;
}
QT_END_NAMESPACE

class SettingsWidget
        : public QWidget
{
    Q_OBJECT

public:
    explicit SettingsWidget(QWidget *parent = nullptr);

    ~SettingsWidget() override;

private:
    Ui::SettingsWidget *ui;
};


#endif //CW_1_SETTINGSWIDGET_HPP
