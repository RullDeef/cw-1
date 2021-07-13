#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <memory>
#include <QMainWindow>
#include "ui_MainWindow.h"
#include "Frames/IFrame.hpp"


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();
    ~MainWindow() = default;

private:
    std::list<IFrame*> frames;

    Ui::MainWindow ui;
};

#endif // MAINWINDOW_HPP
