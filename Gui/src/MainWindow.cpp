#include <Frames/InspectorFrame/InspectorFrame.hpp>
#include <Frames/SettingsFrame/SettingsFrame.hpp>
#include <Managers/SelectionManager.hpp>
#include "Managers/LoadManager.hpp"
#include "Managers/QtManagerFactory.hpp"
#include "Frames/ViewportFrame/ViewportFrame.hpp"
#include "Frames/HierarchyFrame/HierarchyFrame.hpp"
#include "MainWindow.hpp"
#include <Builders/CameraBuilders/DefaultCameraBuilder.hpp>
#include <Managers/SceneManager.hpp>
#include <Builders/LightBuilders/AmbientLightBuilder.hpp>
#include <Builders/SceneBuidler.hpp>
#include <Managers/PortManager.hpp>
#include <Builders/MeshBuilders/SphereMeshBuilder.hpp>

MainWindow::MainWindow()
{
    ui.setupUi(this);
    dockManager = new ads::CDockManager(this);
    factory = std::shared_ptr<IManagerFactory>(new QtManagerFactory());

    // setup default frames
    if (1) {
        IFrame *frame = new HierarchyFrame(*factory, this);
        dockManager->addDockWidget(ads::RightDockWidgetArea, frame);
        frames.push_back(frame);
    }

    if (1) {
        IFrame *frame = new SettingsFrame(*factory, this);
        dockManager->addDockWidget(ads::BottomDockWidgetArea, frame);
        frames.push_back(frame);
    }

    if (1) {
        IFrame *frame = new ViewportFrame(*factory, this);
        dockManager->addDockWidget(ads::LeftDockWidgetArea, frame);
        frames.push_back(frame);
    }

    if (1) {
        IFrame *frame = new InspectorFrame(*factory, this);
        dockManager->addDockWidget(ads::LeftDockWidgetArea, frame);
        frames.push_back(frame);
    }

    setupActions();
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
    auto camera = DefaultCameraBuilder().build();
    factory->getSceneManager()->addObject(std::move(camera));
}

void MainWindow::addLightSourceCommand()
{
    auto light = AmbientLightBuilder().build();
    factory->getSceneManager()->addObject(std::move(light));
}

void MainWindow::addSphereCommand()
{
    auto mesh = SphereMeshBuilder()
            .setRadius(100)
            .setMeshDensity(6)
            .setSmooth(true)
            .setColor(Color::cyan())
            .build();
    auto object = std::shared_ptr<IObject>(new ObjectAdapter<Mesh>(101020102, std::move(mesh)));

    object->setPosition(Vector(0, 0, 0, 1));
    object->setRotation(Vector(0, 0, 0, 0));
    object->setScale(Vector(1, 1, 1, 0));

    factory->getSceneManager()->addObject(object);
}

void MainWindow::saveRenderCommand()
{
//    for (auto frame : frames)
//    {
//        if (auto viewportFrame = dynamic_cast<ViewportFrame *>(frame))
//            return viewportFrame->saveToImage();
//    }
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
    throw std::runtime_error("not implemented");
}
