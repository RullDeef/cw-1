#include "InspectorWidget.hpp"
#include "ui_InspectorWidget.h"


InspectorWidget::InspectorWidget(QWidget *parent) :
        QWidget(parent), ui(new Ui::InspectorWidget)
{
    ui->setupUi(this);
}

InspectorWidget::~InspectorWidget()
{
    delete ui;
}
