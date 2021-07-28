#include "Managers/LoadManager.hpp"
#include "Managers/QtManagerFactory.hpp"
#include "Frames/ViewportFrame/ViewportFrame.hpp"
#include "Frames/HierarchyFrame/HierarchyFrame.hpp"
#include "MainWindow.hpp"


MainWindow::MainWindow()
{
    ui.setupUi(this);
    dockManager = new ads::CDockManager(this);
    factory = std::shared_ptr<IManagerFactory>(new QtManagerFactory(this));

    // setup default frames
    if (1) {
        IFrame *frame = new ViewportFrame(*factory, this);
        dockManager->addDockWidget(ads::LeftDockWidgetArea, frame);
        frames.push_back(frame);
    }

    if (1) {
        IFrame *frame = new HierarchyFrame(*factory, this);
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
    for (auto frame : frames)
    {
        if (auto viewportFrame = dynamic_cast<ViewportFrame *>(frame))
            viewportFrame->update();
        else if (auto hierarchyFrame = dynamic_cast<HierarchyFrame*>(frame))
            hierarchyFrame->updateHierarchy();
    }
}

void MainWindow::saveRenderCommand()
{
    for (auto frame : frames)
    {
        if (auto viewportFrame = dynamic_cast<ViewportFrame *>(frame))
            return viewportFrame->saveToImage();
    }
}
