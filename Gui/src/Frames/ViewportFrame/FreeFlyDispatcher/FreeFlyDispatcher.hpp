//
// Created by rulldeef on 7/28/21.
//

#ifndef CW_1_FREEFLYDISPATCHER_HPP
#define CW_1_FREEFLYDISPATCHER_HPP


#include <Managers/IManagerFactory.hpp>

class FreeFlyDispatcher
{
public:
    explicit FreeFlyDispatcher(IManagerFactory& managerFactory);
    virtual ~FreeFlyDispatcher() = default;

    void enable();
    void disable();

    void update();

    void keyPressed(int key);
    void keyReleased(int key);

    void mousePressed(double x, double y);
    void mouseMoved(double x, double y);
    void mouseReleased();

private:
    IManagerFactory& managerFactory;
    bool enabled = false;

    int forward = 0;
    int right = 0;
    int up = 0;

    bool dragging = false;
    double x_prev;
    double y_prev;

    double flySpeed = 1.0;
    double dragSpeed = 0.025;
};


#endif //CW_1_FREEFLYDISPATCHER_HPP
