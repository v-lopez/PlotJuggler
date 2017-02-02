#ifndef PLOTZOOMER_H
#define PLOTZOOMER_H

#include <QObject>
#include <QMouseEvent>

#ifdef USE_QWT
#include <qwt_plot_zoomer.h>
class PlotZoomer : public QwtPlotZoomer
{
#else

class PlotZoomer
{
#endif

public:
    PlotZoomer();

    explicit PlotZoomer( QWidget * );

    virtual ~PlotZoomer() = default;
protected:
	 virtual void widgetMouseReleaseEvent( QMouseEvent * );
};

#endif // PLOTZOOMER_H
