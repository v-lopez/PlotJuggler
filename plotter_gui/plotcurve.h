#ifndef PLOT_CURVE__H
#define PLOT_CURVE__H

#include <QColor>
#include "PlotJuggler/plotdata.h"

class PlotWidget;

#ifdef USE_QWT
#include <qwt_series_data.h>
#include <qwt_plot_curve.h>

class PlotCurve: public QwtSeriesData<QPointF>
{
	QwtPlotCurve* _curve;

#else
#include <QtCharts/QLineSeries>
class PlotCurve: public QtCharts::QLineSeries
{
#endif
public:

	PlotCurve(QString name, PlotDataPtr base, PlotWidget *parent);

	virtual ~PlotCurve() {}

	typedef enum{
		LINES_AND_DOTS,
		LINES
	}LineStyle;

	virtual QPointF sample( size_t i ) const;

	virtual QRectF boundingRect() const;

	virtual size_t size() const;

	QRectF maximumBoundingRect(double min_X, double max_X);

	PlotDataPtr data() const{ return _plot_data; }

	QColor color() const;
	void setColor(QColor color);

	QColor getColorHint() const;
	void setColorHint(QColor color);

	void setSubsampleFactor();

	void updateData(bool force_transform);

	void setStyle(LineStyle new_style);

	PlotData::RangeTime  getRangeX()
	{
		if( this->size() < 2 )
			return  PlotData::RangeTime() ;
		else
			return  PlotData::RangeTime( { sample(0).x(), sample( this->size() -1).x() } );
	}
	PlotData::RangeValue getRangeY(int first_index, int last_index );

	typedef enum{
		noTransform,
		firstDerivative,
		secondDerivative,
		undefined
	} Transform;

	void setTransform(Transform trans) { _transform = trans; }
	Transform transform() const { return _transform; }

	void attach(PlotWidget* parent);
	void detach();

private:

	void updateDataImpl();

	PlotDataPtr _plot_data;
	int      _preferedColor;
	unsigned _subsample;
	Transform _transform;
	QVector<QPointF> _cached_transformed_curve;
	PlotWidget *_parent;
};


typedef std::shared_ptr<PlotCurve> PlotSeriesPtr;



#endif // PLOTDATA_H
