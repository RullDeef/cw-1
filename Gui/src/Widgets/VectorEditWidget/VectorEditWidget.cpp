#include "VectorEditWidget.hpp"
#include "ui_VectorEditWidget.h"


VectorEditWidget::VectorEditWidget(QWidget *parent) : QWidget(parent), ui(new Ui::VectorEditWidget)
{
    ui->setupUi(this);
}

VectorEditWidget::~VectorEditWidget()
{
    delete ui;
}

void VectorEditWidget::setValue(const Vector &vector)
{
    ui->xSpinBox->setValue(vector.getX());
    ui->ySpinBox->setValue(vector.getY());
    ui->zSpinBox->setValue(vector.getZ());

    w = vector.getW();
}

Vector VectorEditWidget::getValue() const
{
    double x = ui->xSpinBox->value();
    double y = ui->ySpinBox->value();
    double z = ui->zSpinBox->value();

    return Vector(x, y, z, w);
}
