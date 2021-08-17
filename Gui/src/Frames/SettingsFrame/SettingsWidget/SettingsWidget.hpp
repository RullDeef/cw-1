#ifndef CW_1_SETTINGSWIDGET_HPP
#define CW_1_SETTINGSWIDGET_HPP

#include <QWidget>
#include <RenderSettings/RenderSettings.hpp>


QT_BEGIN_NAMESPACE
namespace Ui
{
    class SettingsWidget;
}
QT_END_NAMESPACE

class SettingsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SettingsWidget(QWidget *parent = nullptr);

    ~SettingsWidget() override;

    void setRenderSettings(RenderSettings settings);

signals:
    void renderSettingsChangedSignal(RenderSettings settings);

protected slots:
    void renderSettingsChanged();

private:
    Ui::SettingsWidget *ui;
};


#endif // CW_1_SETTINGSWIDGET_HPP
