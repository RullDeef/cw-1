#ifndef ARCH_HPP
#define ARCH_HPP

// Architecture domain entry points

class MainFacade
{
public:
    MainFacade() = default;
    ~MainFacade();

    void doStuff();

private:
    int id = 20;
};

#endif // ARCH_HPP
