#include <utility>
#include <QFileDialog>
#include "Managers/LoadManager.hpp"
#include "Managers/QtManagerFactory.hpp"
#include "Frames/ViewportFrame/ViewportFrame.hpp"
#include "Frames/HierarchyFrame/HierarchyFrame.hpp"
#include "MainWindow.hpp"


MainWindow::MainWindow()
{
    factory = std::shared_ptr<IManagerFactory>(new QtManagerFactory(this));
    ui.setupUi(this);
    // setCentralWidget(nullptr);

    dockManager = new ads::CDockManager(this);

    // setup default frames
    if (1) {
        IFrame *frame = new ViewportFrame(*factory, this);
        dockManager->addDockWidget(ads::LeftDockWidgetArea, frame);
        frames.push_back(frame);
    }

    if (1) {
        IFrame *frame = new HierarchyFrame(this);
        dockManager->addDockWidget(ads::RightDockWidgetArea, frame);
        frames.push_back(frame);
    }

    setupActions();
}

void MainWindow::setupActions()
{
    connect(ui.loadObject, &QAction::triggered, this, &MainWindow::loadObjectCommand);
    connect(ui.saveRender, &QAction::triggered, this, &MainWindow::saveRenderCommand);
}

void MainWindow::loadObjectCommand()
{
    factory->getLoadManager()->loadMesh();
}

void MainWindow::saveRenderCommand()
{
    for (auto frame : frames)
        if (auto viewportFrame = dynamic_cast<ViewportFrame *>(frame))
            return viewportFrame->saveToImage();
}
