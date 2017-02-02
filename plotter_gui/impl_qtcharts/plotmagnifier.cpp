#include "../plotmagnifier.h"
#include <QDebug>
#include <limits>
#include <QWheelEvent>
/*
#include <qwt_plot.h>
PlotMagnifier::PlotMagnifier( QWidget *canvas) : QwtPlotMagnifier(canvas)
{
	_bound.setLeft( std::numeric_limits<double>::min());
	_bound.setRight( std::numeric_limits<double>::max() );

	_bound.setBottom( std::numeric_limits<double>::min());
	_bound.setTop( std::numeric_limits<double>::max()  );

}

PlotMagnifier::~PlotMagnifier() {}

void PlotMagnifier::setAxisLimits(PlotWidget::Axis axis, double lower, double upper)
{
	if( axis == PlotWidget::AXIS_X)
	{
		_bound.setLeft( lower);
		_bound.setRight( upper );
	}
	else{
		_bound.setBottom( lower);
		_bound.setTop( upper );
	}
}

void PlotMagnifier::rescale( double factor )
{
	factor = qAbs( factor );

	QwtPlot* plt = plot();
	if ( plt == NULL || factor == 1.0 ){
		return;
	}

	bool doReplot = false;

	const bool autoReplot = plt->autoReplot();
	plt->setAutoReplot( false );

	QRectF new_rect;

	for ( int i = 0; i <2; i++ )
	{
		int axisId         = (i==0 ? QwtPlot::xBottom : QwtPlot::yLeft );
		double lower_bound = (i==0 ? _bound.left()  : _bound.bottom() );
		double upper_bound = (i==0 ? _bound.right() : _bound.top() );

		if ( isAxisEnabled( axisId ) )
		{
			const QwtScaleMap scaleMap = plt->canvasMap( axisId );

			double v1 = scaleMap.s1();
			double v2 = scaleMap.s2();
			double center = _mouse_position.x();

			if( axisId == QwtPlot::yLeft){
				center = _mouse_position.y();
			}

			if ( scaleMap.transformation() )
			{
				// the coordinate system of the paint device is always linear
				v1 = scaleMap.transform( v1 ); // scaleMap.p1()
				v2 = scaleMap.transform( v2 ); // scaleMap.p2()
			}

			const double width = ( v2 - v1 );
			const double ratio = (v2-center)/ (width);

			v1 = center - width*factor*(1-ratio);
			v2 = center + width*factor*(ratio);

			if( v1 > v2 ) std::swap( v1, v2 );

			if ( scaleMap.transformation() )
			{
				v1 = scaleMap.invTransform( v1 );
				v2 = scaleMap.invTransform( v2 );
			}

			if( v1 < lower_bound) v1 = lower_bound;
			if( v2 > upper_bound) v2 = upper_bound;

			plt->setAxisScale( axisId, v1, v2 );

			if( axisId == QwtPlot::xBottom)
			{
				new_rect.setLeft(  v1 );
				new_rect.setRight( v2 );
			}
			else{
				new_rect.setBottom( v1 );
				new_rect.setTop( v2 );
			}

			doReplot = true;
		}
	}

	plt->setAutoReplot( autoReplot );

	if ( doReplot ){
		emit rescaled( new_rect );
	}
}

QPointF PlotMagnifier::invTransform(QPoint pos)
{
	QwtScaleMap xMap = plot()->canvasMap( QwtPlot::xBottom );
	QwtScaleMap yMap = plot()->canvasMap( QwtPlot::yLeft );
	return QPointF ( xMap.invTransform( pos.x() ), yMap.invTransform( pos.y() ) );
}

void PlotMagnifier::widgetWheelEvent(QWheelEvent *event)
{
	_mouse_position = invTransform(event->pos());
	QwtPlotMagnifier::widgetWheelEvent(event);
}
*/
