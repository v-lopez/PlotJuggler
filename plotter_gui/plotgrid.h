#ifndef PLOTGRID_H
#define PLOTGRID_H

#include <memory>

class PlotWidget;

class PlotGrid
{
public:
    PlotGrid(PlotWidget* parent);
    ~PlotGrid();

    void setVisible(bool active);
private:
    struct Pimpl;
    std::unique_ptr<Pimpl> p;
};

#endif // PLOTGRID_H

