#include "plotlegend.h"
#include "plotwidget.h"
#include <qwt_legend.h>
#include <qwt_plot.h>
#include <qwt_plot_legenditem.h>

struct PlotLegend::Pimpl{
    QwtPlotLegendItem* legend;
    QwtPlot* parent;
};

PlotLegend::PlotLegend(PlotWidget *parent) :
    p( new PlotLegend::Pimpl )
{
    p->legend = new QwtPlotLegendItem();
    p->parent = static_cast<QwtPlot*>(parent);
    p->legend->attach( p->parent );

    p->legend->setRenderHint( QwtPlotItem::RenderAntialiased );
    QColor color( Qt::black );
    p->legend->setTextPen( color );
    p->legend->setBorderPen( color );
    QColor c( Qt::white );
    c.setAlpha( 200 );
    p->legend->setBackgroundBrush( c );

    p->legend->setMaxColumns( 1 );
    p->legend->setAlignment( Qt::Alignment( Qt::AlignTop | Qt::AlignRight ) );
    p->legend->setBackgroundMode( QwtPlotLegendItem::BackgroundMode::LegendBackground   );

    p->legend->setBorderRadius( 6 );
    p->legend->setMargin( 5 );
    p->legend->setSpacing( 0 );
    p->legend->setItemMargin( 0 );

    QFont font = p->legend->font();
    font.setPointSize( 8 );
    p->legend->setFont( font );
    p->legend->setVisible( true );
}

void PlotLegend::setVisible(bool visible)
{
    if( visible ) p->legend->attach(p->parent);
    else          p->legend->detach();
}

PlotLegend::~PlotLegend()
{

}
