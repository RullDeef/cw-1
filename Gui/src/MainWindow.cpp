#include <Frames/InspectorFrame/InspectorFrame.hpp>
#include <Frames/SettingsFrame/SettingsFrame.hpp>
#include <Managers/SelectionManager.hpp>
#include "Managers/QtManagerFactory.hpp"
#include "Frames/ViewportFrame/ViewportFrame.hpp"
#include "Frames/HierarchyFrame/HierarchyFrame.hpp"
#include "MainWindow.hpp"
#include <Builders/CameraBuilders/DefaultCameraBuilder.hpp>
#include <Managers/SceneManager.hpp>
#include <Managers/CameraManager.hpp>
#include <Builders/LightBuilders/LightBuilder.hpp>
#include <Builders/SceneBuidler.hpp>
#include <Managers/PortManager.hpp>
#include <Builders/MeshBuilders/SphereMeshBuilder.hpp>
#include <Builders/DefaultIDGenerator.hpp>
#include <Builders/NameGenerator.hpp>
#include <Builders/MeshBuilders/TorusMeshBuilder.hpp>
#include <Builders/MeshBuilders/CylinderMeshBuilder.hpp>
#include <Builders/MeshBuilders/ConeMeshBuilder.hpp>

MainWindow::MainWindow()
{
    ui.setupUi(this);
    dockManager = new ads::CDockManager(this);
    factory = std::shared_ptr<IManagerFactory>(new QtManagerFactory());

    // setup default frames
    IFrame *frame;

    frame = new HierarchyFrame(*factory, this);
    dockManager->addDockWidget(ads::RightDockWidgetArea, frame);
    frames.push_back(frame);

    frame = new SettingsFrame(*factory, this);
    dockManager->addDockWidget(ads::BottomDockWidgetArea, frame);
    frames.push_back(frame);

    frame = new ViewportFrame(*factory, this);
    dockManager->addDockWidget(ads::LeftDockWidgetArea, frame);
    frames.push_back(frame);

    frame = new InspectorFrame(*factory, this);
    dockManager->addDockWidget(ads::LeftDockWidgetArea, frame);
    frames.push_back(frame);

    setupActions();
    createNewSceneCommand();
}

void MainWindow::setupActions()
{
    connect(ui.loadObject, &QAction::triggered, this, &MainWindow::loadObjectCommand);
    connect(ui.createNewScene, &QAction::triggered, this, &MainWindow::createNewSceneCommand);
    connect(ui.importScene, &QAction::triggered, this, &MainWindow::importSceneCommand);
    connect(ui.exportScene, &QAction::triggered, this, &MainWindow::exportSceneCommand);

    connect(ui.addCamera, &QAction::triggered, this, &MainWindow::addCameraCommand);
    connect(ui.addLightSource, &QAction::triggered, this, &MainWindow::addLightSourceCommand);
    connect(ui.addSphere, &QAction::triggered, this, &MainWindow::addSphereCommand);
    connect(ui.addTorus, &QAction::triggered, this, &MainWindow::addTorusCommand);
    connect(ui.addCylinder, &QAction::triggered, this, &MainWindow::addCylinderCommand);
    connect(ui.addCone, &QAction::triggered, this, &MainWindow::addConeCommand);

    connect(ui.switchFirst, &QAction::triggered, this, &MainWindow::switchViewFirstCommand);
    connect(ui.switchSelected, &QAction::triggered, this, &MainWindow::switchViewSelectedCommand);

    connect(ui.saveRender, &QAction::triggered, this, &MainWindow::saveRenderCommand);

    connect(ui.deleteSelected, &QAction::triggered, this, &MainWindow::deleteSelected);
    connect(ui.selectAll, &QAction::triggered, this, &MainWindow::selectAll);
    connect(ui.invertSelection, &QAction::triggered, this, &MainWindow::invertSelection);
}

void MainWindow::createNewSceneCommand()
{
    factory->getSceneManager()->createEmptyScene();
}

void MainWindow::importSceneCommand()
{
    factory->getPortManager()->importScene();
}

void MainWindow::exportSceneCommand()
{
    factory->getPortManager()->exportScene();
}

void MainWindow::loadObjectCommand()
{
    factory->getPortManager()->importMesh();
}

void MainWindow::addCameraCommand()
{
    auto& scene = factory->getSceneManager()->getActiveScene();

    auto camera = DefaultCameraBuilder()
            .setId(DefaultIDGenerator().generate())
            .setName(NameGenerator::uniqueIndexedName("Camera", scene))
            .build();
    factory->getSceneManager()->addObject(std::move(camera));
}

void MainWindow::addLightSourceCommand()
{
    auto& scene = factory->getSceneManager()->getActiveScene();

    auto light = LightBuilder()
            .setId(DefaultIDGenerator().generate())
            .setName(NameGenerator::uniqueIndexedName("Light", scene))
            .build();
    factory->getSceneManager()->addObject(std::move(light));
}

void MainWindow::addSphereCommand()
{
    auto& scene = factory->getSceneManager()->getActiveScene();

    auto object = SphereMeshBuilder()
            .setRadius(100)
            .setMeshDensity(6)
            .setSmooth(true)
            .setColor(Color::cyan())
            .setId(DefaultIDGenerator().generate())
            .setName(NameGenerator::uniqueIndexedName("Sphere", scene))
            .build();
    factory->getSceneManager()->addObject(std::move(object));
}

void MainWindow::addTorusCommand()
{
    auto& scene = factory->getSceneManager()->getActiveScene();

    auto object = TorusMeshBuilder()
            .setOuterRadius(100)
            .setInnerRadius(15)
            .setMeshDensity(96, 32)
            .setSmooth(true)
            .setColor(Color::magenta())
            .setId(DefaultIDGenerator().generate())
            .setName(NameGenerator::uniqueIndexedName("Torus", scene))
            .build();
    factory->getSceneManager()->addObject(std::move(object));
}

void MainWindow::addCylinderCommand()
{
    auto& scene = factory->getSceneManager()->getActiveScene();

    auto object = CylinderMeshBuilder()
            .setRadius(50)
            .setHeight(100)
            .setMeshDensity(32)
            .setSmooth(true)
            .setColor(Color::yellow())
            .setId(DefaultIDGenerator().generate())
            .setName(NameGenerator::uniqueIndexedName("Cylinder", scene))
            .build();
    factory->getSceneManager()->addObject(std::move(object));
}

void MainWindow::addConeCommand()
{
    auto& scene = factory->getSceneManager()->getActiveScene();

    auto object = ConeMeshBuilder()
            .setRadius(40)
            .setHeight(100)
            .setMeshDensity(32)
            .setSmooth(true)
            .setColor(Color::green())
            .setId(DefaultIDGenerator().generate())
            .setName(NameGenerator::uniqueIndexedName("Cone", scene))
            .build();
    factory->getSceneManager()->addObject(std::move(object));
}

void MainWindow::switchViewFirstCommand()
{
    factory->getCameraManager()->switchToFirstCamera();
    factory->getRenderManager()->renderActiveScene();
}

void MainWindow::switchViewSelectedCommand()
{
    factory->getCameraManager()->switchToSelectedCamera();
    factory->getRenderManager()->renderActiveScene();
}

void MainWindow::saveRenderCommand()
{
    for (auto frame : frames)
    {
        if (auto viewportFrame = dynamic_cast<ViewportFrame *>(frame))
            return viewportFrame->saveToImage();
    }
}

void MainWindow::deleteSelected()
{
    factory->getSelectionManager()->deleteSelected();
}

void MainWindow::selectAll()
{
    factory->getSelectionManager()->selectAll();
}

void MainWindow::invertSelection()
{
    factory->getSelectionManager()->invertSelection();
}
