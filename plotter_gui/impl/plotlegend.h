#ifndef PLOTLEGEND_H
#define PLOTLEGEND_H

#include <QObject>
#include <memory>

class PlotWidget;

class PlotLegend
{

public:
    explicit PlotLegend(PlotWidget *parent = 0);
    ~PlotLegend();

    void setVisible(bool visible);

private:
    struct Pimpl;
    std::unique_ptr<Pimpl> p;
};

#endif // PLOTLEGEND_H
