#include <Widgets/VectorEditWidget/VectorEditWidget.hpp>
#include "InspectorWidget.hpp"
#include "ui_InspectorWidget.h"


InspectorWidget::InspectorWidget(QWidget *parent) : QWidget(parent), ui(new Ui::InspectorWidget)
{
    ui->setupUi(this);

    connect(ui->renameButton, &QPushButton::clicked, this, &InspectorWidget::renameObject);
    connect(ui->applyTransformButton, &QPushButton::clicked, this, &InspectorWidget::applyTransform);

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

    ui->positionEdit->setValue(newObject->getPosition());
    ui->rotationEdit->setValue(newObject->getRotation());
    ui->scaleEdit->setValue(newObject->getScale());

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

void InspectorWidget::renameObject()
{
    if (auto obj = object.lock())
    {
        obj->setName(ui->nameTextEdit->toPlainText().toStdString());

        emit objectChangedSignal();
    }
}

void InspectorWidget::applyTransform()
{
    if (auto obj = object.lock())
    {
        obj->setPosition(ui->positionEdit->getValue());
        obj->setRotation(ui->rotationEdit->getValue());
        obj->setScale(ui->scaleEdit->getValue());

        emit objectChangedSignal();
    }
}
