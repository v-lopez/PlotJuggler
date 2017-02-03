#include "plotcurve.h"
#include <limits>
#include <stdexcept>
#include "plotwidget.h"

QPointF PlotCurve::sample(size_t i) const
{
	return _cached_transformed_curve[i];
}

QRectF PlotCurve::boundingRect() const
{
	qDebug() << "boundingRect not implemented";
	return QRectF(0,0,1,1);
}


size_t PlotCurve::size() const
{
	return _cached_transformed_curve.size();
}

void PlotCurve::setSubsampleFactor()
{
	//  _subsample = (_plot_data->size() / 2000) + 1;
}

void PlotCurve::updateData(bool force_transform)
{
	bool updated = _plot_data->flushAsyncBuffer();

	if(updated || force_transform)
	{
	//	qDebug() << "updateData";

		if(_transform == noTransform)
		{
			_cached_transformed_curve.resize( _plot_data->size());

			for (size_t i=0; i< _plot_data->size() ; i++ )
			{
				auto p = _plot_data->at( i );
				_cached_transformed_curve[i] = QPointF(p.x, p.y);
			}
		}
		else if(_transform == firstDerivative)
		{
			if( _plot_data->size() < 1){
				_cached_transformed_curve.clear();
			}
			else{
				_cached_transformed_curve.resize( _plot_data->size() - 1 );
			}

			for (size_t i=0; i< _plot_data->size() -1; i++ )
			{
				const auto& p0 = _plot_data->at( i );
				const auto& p1 = _plot_data->at( i+1 );
				const auto delta = p1.x - p0.x;
				const auto vel = (p1.y - p0.y) /delta;
				_cached_transformed_curve[i] = QPointF( (p1.x + p0.x)*0.5, vel) ;
			}
		}
		else if(_transform == secondDerivative)
		{
			if( _plot_data->size() < 2){
				_cached_transformed_curve.clear();
			}
			else{
				_cached_transformed_curve.resize( _plot_data->size() - 2 );
			}

			for (size_t i=0; i< _cached_transformed_curve.size(); i++ )
			{
				const auto& p0 = _plot_data->at( i );
				const auto& p1 = _plot_data->at( i+1 );
				const auto& p2 = _plot_data->at( i+2 );
				const auto delta = (p2.x - p0.x) *0.5;
				const auto acc = ( p2.y - 2.0* p1.y + p0.y)/(delta*delta);
				_cached_transformed_curve[i] =  QPointF( (p2.x + p0.x)*0.5, acc ) ;
			}
		}
		updateDataImpl();
	}
}

PlotData::RangeValueOpt PlotCurve::getRangeY(int first_index, int last_index)
{
	if( first_index < 0 || last_index < 0 || first_index > last_index)
	{
		return PlotData::RangeValueOpt();
	}

	const double first_Y = sample(first_index).y();
	double y_min = first_Y;
	double y_max = first_Y;

	for (int i = first_index+1; i < last_index; i++)
	{
		const double Y = sample(i).y();

		if( Y < y_min )      y_min = Y;
		else if( Y > y_max ) y_max = Y;
	}
	return PlotData::RangeValueOpt( { y_min, y_max } );
}

QRectF PlotCurve::maximumBoundingRect(double min_X, double max_X)
{
	int x1 = _plot_data->getIndexFromX( min_X );
	int x2 = _plot_data->getIndexFromX( max_X );

	if( x1 <0 || x2 <0){
		return QRectF();
	}

	auto range_X = getRangeX();

	if( !range_X ){
		return QRectF();
	}

	auto range_Y = getRangeY( x1, x2  );
	if( !range_Y){
		return QRectF();
	}

	QRectF rect ( range_X->min,  range_Y->min,
				  range_X->max - range_X->min,
				  range_Y->max - range_Y->min );
	return rect;
}

QColor PlotCurve::getColorHint() const {
	return _plot_data->getColorHint() ;
}

void PlotCurve::setColorHint(QColor color) {
	_plot_data->setColorHint(color) ;
}






