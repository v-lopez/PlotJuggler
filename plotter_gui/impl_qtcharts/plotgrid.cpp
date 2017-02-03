#include "../plotgrid.h"
#include "../plotwidget.h"

//#include <qwt_plot_grid.h>

struct PlotGrid::Pimpl{
  //  QwtPlotGrid* grid;
   // QwtPlot* parent;

  //  Pimpl(PlotWidget* _parent):
  //      parent(_parent)
  //  {
  //     grid = new  QwtPlotGrid();
  //     grid->attach( parent );
  //  }
};

PlotGrid::~PlotGrid() {}

PlotGrid::PlotGrid(PlotWidget *parent)//:
   // p( new Pimpl(parent) )
{
   // p->grid->setPen(QPen(Qt::gray, 0.0, Qt::DotLine));
}

void PlotGrid::setVisible(bool active)
{
  /*  p->grid->enableX(active);
    p->grid->enableXMin(active);
    p->grid->enableY(active);
    p->grid->enableYMin(active);
	p->grid->attach( p->parent );*/
}

