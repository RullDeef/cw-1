#include "SettingsWidget.hpp"
#include "ui_SettingsWidget.h"


SettingsWidget::SettingsWidget(QWidget *parent)
    : QWidget(parent), ui(new Ui::SettingsWidget)
{
    ui->setupUi(this);

    connect(ui->renderingTypeComboBox, qOverload<int>(&QComboBox::currentIndexChanged), this,
            &SettingsWidget::renderSettingsChanged);
    connect(ui->lightingModelComboBox, qOverload<int>(&QComboBox::currentIndexChanged), this,
            &SettingsWidget::renderSettingsChanged);
    connect(ui->occlusionCullingCheckBox, &QCheckBox::stateChanged, this, &SettingsWidget::renderSettingsChanged);
    connect(ui->backFaceCullingCheckBox, &QCheckBox::stateChanged, this, &SettingsWidget::renderSettingsChanged);
}

SettingsWidget::~SettingsWidget()
{
    delete ui;
}

void SettingsWidget::setRenderSettings(RenderSettings settings)
{
    ui->renderingTypeComboBox->setCurrentIndex((int)settings.getRenderType());
    ui->lightingModelComboBox->setCurrentIndex((int)settings.getLightingType());

    if (settings.getFaceCullingType() & RenderSettings::OcclusionCulling)
        ui->occlusionCullingCheckBox->setCheckState(Qt::Checked);
    else
        ui->occlusionCullingCheckBox->setCheckState(Qt::Unchecked);

    if (settings.getFaceCullingType() & RenderSettings::BackFaceCulling)
        ui->backFaceCullingCheckBox->setCheckState(Qt::Checked);
    else
        ui->backFaceCullingCheckBox->setCheckState(Qt::Unchecked);
}

void SettingsWidget::renderSettingsChanged()
{
    RenderSettings renderSettings;

    renderSettings.setRenderType((RenderSettings::RenderType)ui->renderingTypeComboBox->currentIndex());
    renderSettings.setLightingType((RenderSettings::LightingType)ui->lightingModelComboBox->currentIndex());

    RenderSettings::FaceCullingType faceCulling = RenderSettings::NoCulling;
    if (ui->occlusionCullingCheckBox->isChecked())
        faceCulling |= RenderSettings::OcclusionCulling;
    if (ui->backFaceCullingCheckBox->isChecked())
        faceCulling |= RenderSettings::BackFaceCulling;
    renderSettings.setFaceCullingType(faceCulling);

    emit renderSettingsChangedSignal(renderSettings);
}

