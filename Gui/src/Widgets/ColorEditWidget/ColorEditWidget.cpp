#include <QSpinBox>
#include "ColorEditWidget.hpp"
#include "ui_ColorEditWidget.h"


ColorEditWidget::ColorEditWidget(QWidget *parent) : QWidget(parent), ui(new Ui::ColorEditWidget)
{
    ui->setupUi(this);

    connect(ui->colorPicker, &ColorPickerWidget::colorPicked, this, &ColorEditWidget::colorPickedSlot);
    connect(ui->redSpinBox, qOverload<int>(&QSpinBox::valueChanged), this, &ColorEditWidget::colorChangedSlot);
    connect(ui->greenSpinBox, qOverload<int>(&QSpinBox::valueChanged), this, &ColorEditWidget::colorChangedSlot);
    connect(ui->blueSpinBox, qOverload<int>(&QSpinBox::valueChanged), this, &ColorEditWidget::colorChangedSlot);
}

ColorEditWidget::~ColorEditWidget()
{
    delete ui;
}

void ColorEditWidget::setValue(const Color &color)
{
    int red = color.getRedByte();
    int green = color.getGreenByte();
    int blue = color.getBlueByte();

    ui->redSpinBox->setValue(red);
    ui->greenSpinBox->setValue(green);
    ui->blueSpinBox->setValue(blue);

    ui->colorPicker->setColor(QColor::fromRgb(red, green, blue));
}

Color ColorEditWidget::getValue() const
{
    double red = ui->redSpinBox->value() / 255.0;
    double green = ui->greenSpinBox->value() / 255.0;
    double blue = ui->blueSpinBox->value() / 255.0;

    return Color(red, green, blue);
}

void ColorEditWidget::colorPickedSlot(QColor color)
{
    setValue(Color(color.redF(), color.greenF(), color.blueF()));
}

void ColorEditWidget::colorChangedSlot()
{
    int red = ui->redSpinBox->value();
    int green = ui->greenSpinBox->value();
    int blue = ui->blueSpinBox->value();

    ui->colorPicker->setColor(QColor::fromRgb(red, green, blue));
}
