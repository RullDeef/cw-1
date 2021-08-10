#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <memory>
#include <QMainWindow>
#include <DockManager.h>
#include "Managers/IManagerFactory.hpp"
#include "Frames/IFrame.hpp"
#include "ui_MainWindow.h"


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();
    ~MainWindow() = default;

protected slots:
    void createNewSceneCommand();

    void loadObjectCommand();

    void addCameraCommand();
    void addLightSourceCommand();

    void saveRenderCommand();

private:
    void setupActions();

    ads::CDockManager* dockManager;

    std::shared_ptr<IManagerFactory> factory;
    std::list<IFrame*> frames;

    Ui::MainWindow ui{};
};

#endif // MAINWINDOW_HPP
