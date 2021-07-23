#include <utility>
#include <Managers/QtManagerFactory.hpp>
#include "MainWindow.hpp"
#include "Frames/ViewportFrame/ViewportFrame.hpp"
#include "Frames/HierarchyFrame/HierarchyFrame.hpp"

#include "LoadManager.hpp"


MainWindow::MainWindow()
{
    factory = std::shared_ptr<IManagerFactory>(new QtManagerFactory(this));
    ui.setupUi(this);
    setCentralWidget(nullptr);

    // setup default frames
    {
        IFrame* frame = new ViewportFrame(factory->getRenderManager(), this);
        addDockWidget(Qt::LeftDockWidgetArea, frame);
        frames.push_back(frame);
    }

    {
        IFrame* frame = new HierarchyFrame(this);
        addDockWidget(Qt::LeftDockWidgetArea, frame);
        frames.push_back(frame);
    }

    setupActions();
}

void MainWindow::setupActions()
{
    connect(ui.loadObject, &QAction::triggered, this, &MainWindow::loadObjectCommand);
}

void MainWindow::loadObjectCommand()
{
    factory->getLoadManager()->loadMesh();
}
