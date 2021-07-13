#include "MainWindow.hpp"
#include "Frames/ViewportFrame/ViewportFrame.hpp"
#include "Frames/HierarchyFrame/HierarchyFrame.hpp"


MainWindow::MainWindow()
{
    ui.setupUi(this);
    setCentralWidget(nullptr);

    // setup default frames
    {
        IFrame* frame = new ViewportFrame(this);
        addDockWidget(Qt::LeftDockWidgetArea, frame);
        frames.push_back(frame);
    }

    {
        IFrame* frame = new HierarchyFrame(this);
        addDockWidget(Qt::LeftDockWidgetArea, frame);
        frames.push_back(frame);
    }
}
