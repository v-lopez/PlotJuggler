#include "../plotcurve.h"
#include <limits>
#include <stdexcept>
#include "../plotwidget.h"
#include <QtCharts/QLineSeries>

PlotCurve::PlotCurve(QString name, PlotDataPtr base,  PlotWidget *parent):
	QLineSeries(parent),
	_plot_data(base),
	_subsample(1),
	_transform( noTransform )
{
	setColor( getColorHint() );
}

void PlotCurve::setStyle(PlotCurve::LineStyle new_style)
{
	/*if( new_style == LINES)
		_curve->setStyle( QwtPlotCurve::Lines);
	else
		_curve->setStyle( QwtPlotCurve::LinesAndDots);*/
}

void PlotCurve::attach(PlotWidget *parent){
	_parent = parent;
  _parent->chart()->addSeries(this);
  _parent->chart()->createDefaultAxes();
}

void PlotCurve::detach(){

	_parent->chart()->removeSeries(this);
}

void PlotCurve::updateDataImpl()
{
	this->replace( _cached_transformed_curve );
}


QColor PlotCurve::color() const {
	return QtCharts::QLineSeries::color();
}

void PlotCurve::setColor(QColor color)
{
	QPen pen = this->pen();
	pen.setWidthF( 0.6 );
	pen.setColor(color);
	this->setPen( pen );
}
