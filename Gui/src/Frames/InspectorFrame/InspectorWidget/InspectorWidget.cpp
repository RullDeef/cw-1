#include "InspectorWidget.hpp"
#include "ui_InspectorWidget.h"


InspectorWidget::InspectorWidget(QWidget *parent) :
        QWidget(parent), ui(new Ui::InspectorWidget)
{
    ui->setupUi(this);
    inspect(nullptr);
}

InspectorWidget::~InspectorWidget()
{
    delete ui;
}

void InspectorWidget::inspect(nullptr_t)
{
    ui->objectGroupBox->setVisible(false);
    ui->materialGroupBox->setVisible(false);
    ui->cameraGroupBox->setVisible(false);
    ui->lightGroupBox->setVisible(false);
}

void InspectorWidget::inspect(const std::shared_ptr<IObject>& newObject)
{
    inspect(nullptr);

    if (!newObject)
        return;

    ui->objectGroupBox->setVisible(true);

    object = newObject;

    ui->idSpinBox->setValue(newObject->getId() % 1000000000);
    ui->nameTextEdit->setPlainText(QString::fromStdString(newObject->getName()));

    auto position = newObject->getPosition();
    ui->positionXSpinBox->setValue(position.getX());
    ui->positionYSpinBox->setValue(position.getY());
    ui->positionZSpinBox->setValue(position.getZ());

    auto rotation = newObject->getRotation();
    ui->rotationXSpinBox->setValue(rotation.getX());
    ui->rotationYSpinBox->setValue(rotation.getY());
    ui->rotationZSpinBox->setValue(rotation.getZ());

    auto scale = newObject->getScale();
    ui->scaleXSpinBox->setValue(scale.getX());
    ui->scaleYSpinBox->setValue(scale.getY());
    ui->scaleZSpinBox->setValue(scale.getZ());

    if (auto meshAdapter = dynamic_cast<ObjectAdapter<Mesh>*>(newObject.get()))
        inspect(*meshAdapter);
}

void InspectorWidget::inspect(ObjectAdapter<Mesh> &object)
{
    ui->materialGroupBox->setVisible(true);

    auto material = object.getAdaptee().getMaterial();

    auto ambient = material.getAmbientColor();
    ui->ambientRedSpinBox->setValue(ambient.getRedByte());
    ui->ambientGreenSpinBox->setValue(ambient.getGreenByte());
    ui->ambientBlueSpinBox->setValue(ambient.getBlueByte());

    auto diffuse = material.getDiffuseColor();
    ui->diffuseRedSpinBox->setValue(diffuse.getRedByte());
    ui->diffuseGreenSpinBox->setValue(diffuse.getGreenByte());
    ui->diffuseBlueSpinBox->setValue(diffuse.getBlueByte());

    auto specular = material.getSpecularColor();
    ui->specularRedSpinBox->setValue(specular.getRedByte());
    ui->specularGreenSpinBox->setValue(specular.getGreenByte());
    ui->specularBlueSpinBox->setValue(specular.getBlueByte());

    ui->specularHightlightSpinBox->setValue(material.getSpecularHighlight());
    ui->opacitySpinBox->setValue(material.getOpacity());
}
