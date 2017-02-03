#include "../plotcurve.h"
#include <limits>
#include <stdexcept>
#include "../plotwidget.h"
#include <qwt_plot.h>

PlotCurve::PlotCurve(QString name, PlotDataPtr base, PlotWidget *):
	_curve( new QwtPlotCurve(name) ),
	_plot_data(base),
	_subsample(1),
	_transform( noTransform )
{
	_curve->setData(this);
}

void PlotCurve::setStyle(PlotCurve::LineStyle new_style)
{
	if( new_style == LINES)
		_curve->setStyle( QwtPlotCurve::Lines);
	else
		_curve->setStyle( QwtPlotCurve::LinesAndDots);
}

void PlotCurve::attach(PlotWidget *parent){
	_curve->attach(parent);
}

void PlotCurve::detach(){
	_curve->detach();
}

void PlotCurve::updateDataImpl()
{

}


QColor PlotCurve::color() const {
	return _curve->pen().color();
}

void PlotCurve::setColor(QColor color) {
    _curve->setPen(color, 0.7);
}
