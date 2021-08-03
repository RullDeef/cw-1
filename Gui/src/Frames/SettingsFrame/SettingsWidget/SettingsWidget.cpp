//
// Created by rulldeef on 8/3/21.
//

// You may need to build the project (run Qt uic code generator) to get "ui_SettingsWidget.h" resolved

#include "SettingsWidget.hpp"
#include "ui_SettingsWidget.h"


SettingsWidget::SettingsWidget(QWidget *parent) :
        QWidget(parent), ui(new Ui::SettingsWidget)
{
    ui->setupUi(this);
}

SettingsWidget::~SettingsWidget()
{
    delete ui;
}

