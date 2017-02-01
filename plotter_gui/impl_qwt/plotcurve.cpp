#include "plotcurve.h"
#include "plotwidget.h"
#include "qwt_plot_curve.h"
#include "qwt_plot.h"
#include "plotseries.h"

class PlotCurve::Pimpl{
public:
    Pimpl(const QString& name, const PlotDataPtr data):
        curve(name),
        series(data)
    { }

    QwtPlotCurve curve;
    PlotSeries series;
};

PlotCurve::PlotCurve(const QString& name, const PlotDataPtr& data):
    p( new Pimpl(name,data))
{
    p->curve.setPaintAttribute( QwtPlotCurve::ClipPolygons, true );
    p->curve.setRenderHint( QwtPlotItem::RenderAntialiased, true );
    //p->curve.setPaintAttribute( QwtPlotCurve::FilterPointsAggressive, true );

    p->curve.setData( static_cast<QwtSeriesData<QPointF>*>( & p->series ) );
}

PlotCurve::~PlotCurve()
{

}

const PlotSeries &PlotCurve::series() const{
    return p->series;
}

PlotSeries &PlotCurve::series(){
    return p->series;
}

void PlotCurve::attach(PlotWidget *parent)
{
    p->curve.attach( (parent) );
}

void PlotCurve::detach()
{
    p->curve.detach();
}

void PlotCurve::setStyle(PlotCurve::LineStyle style)
{
    if( style == PlotCurve::LINES)
        p->curve.setStyle(  QwtPlotCurve::Lines );
    else
        p->curve.setStyle(  QwtPlotCurve::LinesAndDots );
}

void PlotCurve::setColor(QColor color, double alpha)
{
    p->curve.setPen(color, alpha);
}

QColor PlotCurve::color() const
{
    return p->curve.pen().color();
}
