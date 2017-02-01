#ifndef PLOTSERIES_H
#define PLOTSERIES_H

#include <QColor>
#include "PlotJuggler/plotdata.h"

#ifndef USE_QTCHARTS
#include <qwt_series_data.h>
class PlotSeries: public QwtSeriesData<QPointF>
{
#else
#include <QtCharts/QLineSeries>
class PlotSeries: public QtCharts::QLineSeries
{
#endif
public:

    PlotSeries(PlotDataPtr base);

    virtual ~PlotSeries() {}

    virtual QPointF sample( size_t i ) const;

    virtual QRectF boundingRect() const;

    virtual size_t size() const;

    QRectF maximumBoundingRect(double min_X, double max_X);

    PlotDataPtr data() const{ return _plot_data; }

    QColor getColorHint() const;
    void setColorHint(QColor color);

    void setSubsampleFactor();

    void updateData(bool force_transform);

    PlotData::RangeTime  getRangeX();

    PlotData::RangeValue getRangeY(int first_index, int last_index );

    typedef enum{
      noTransform,
      firstDerivative,
      secondDerivative
    } Transform;

    void setTransform(Transform trans) { _transform = trans; }
    Transform transform() const { return _transform; }

private:

    PlotDataPtr _plot_data;
    std::vector<QPointF> _cached_transformed_curve;
    int      _preferedColor;
    unsigned _subsample;
    Transform _transform;
};

typedef std::shared_ptr<PlotSeries> PlotSeriesPtr;



#endif // PLOTDATA_H
