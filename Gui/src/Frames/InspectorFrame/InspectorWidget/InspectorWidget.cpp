#include <Widgets/VectorEditWidget/VectorEditWidget.hpp>
#include "InspectorWidget.hpp"
#include "ui_InspectorWidget.h"


InspectorWidget::InspectorWidget(QWidget *parent) : QWidget(parent), ui(new Ui::InspectorWidget)
{
    ui->setupUi(this);

    connect(ui->renameButton, &QPushButton::clicked, this, &InspectorWidget::renameObject);
    connect(ui->applyTransformButton, &QPushButton::clicked, this, &InspectorWidget::applyTransform);
    connect(ui->applyMaterialButton, &QPushButton::clicked, this, &InspectorWidget::applyMaterial);
    connect(ui->applyLightButton, &QPushButton::clicked, this, &InspectorWidget::applyLight);

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
    ui->nameTextEdit->setText(QString::fromStdString(newObject->getName()));

    ui->positionEdit->setValue(newObject->getPosition());
    ui->rotationEdit->setValue(newObject->getRotation());
    ui->scaleEdit->setValue(newObject->getScale());

    if (auto meshAdapter = dynamic_cast<ObjectAdapter<Mesh>*>(newObject.get()))
        inspect(*meshAdapter);
    else if (auto lightAdapter = dynamic_cast<ObjectAdapter<Light>*>(newObject.get()))
        inspect(*lightAdapter);
}

void InspectorWidget::inspect(ObjectAdapter<Mesh> &object)
{
    ui->materialGroupBox->setVisible(true);

    auto material = object.getAdaptee().getMaterial();

    ui->ambientEdit->setValue(material.getAmbientColor());
    ui->diffuseEdit->setValue(material.getDiffuseColor());
    ui->specularEdit->setValue(material.getSpecularColor());

    ui->specularHightlightSpinBox->setValue(material.getSpecularHighlight());
    ui->opacitySpinBox->setValue(material.getOpacity());
}

void InspectorWidget::inspect(ObjectAdapter<Light>& object)
{
    ui->lightGroupBox->setVisible(true);

    auto light = object.getAdaptee();

    ui->lightTypeComboBox->setCurrentIndex((int)light.getType());
    ui->lightColorEdit->setValue(light.getColor());
    ui->intensitySpinBox->setValue(light.getIntensity());
}

void InspectorWidget::renameObject()
{
    if (auto obj = object.lock())
    {
        obj->setName(ui->nameTextEdit->text().toStdString());

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

void InspectorWidget::applyMaterial()
{
    if (auto obj = object.lock())
    {
        if (auto meshAdapter = dynamic_cast<ObjectAdapter<Mesh>*>(obj.get()))
        {
            Mesh& mesh = meshAdapter->getAdaptee();
            Material material = mesh.getMaterial();

            material.setAmbientColor(ui->ambientEdit->getValue());
            material.setDiffuseColor(ui->diffuseEdit->getValue());
            material.setSpecularColor(ui->specularEdit->getValue());
            material.setSpecularHighlight(ui->specularHightlightSpinBox->value());
            material.setOpacity(ui->opacitySpinBox->value());

            mesh.setMaterial(material);

            emit objectChangedSignal();
        }
    }
}

void InspectorWidget::applyLight()
{
    if (auto obj = object.lock())
    {
        if (auto lightAdapter = dynamic_cast<ObjectAdapter<Light>*>(obj.get()))
        {
            Light& light = lightAdapter->getAdaptee();

            light.setType((Light::Type)ui->lightTypeComboBox->currentIndex());
            light.setColor(ui->lightColorEdit->getValue());
            light.setIntensity(ui->intensitySpinBox->value());

            emit objectChangedSignal();
        }
    }
}
