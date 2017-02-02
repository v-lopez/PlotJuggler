#ifndef PLOTZOOMER_H
#define PLOTZOOMER_H

#include <QObject>

#ifdef USE_QWT
#include <qwt_plot_zoomer.h>
class PlotZoomer : public QwtPlotZoomer
{
#else

#endif

public:
    PlotZoomer();

    explicit PlotZoomer( QWidget * );

    virtual ~PlotZoomer() = default;
protected:
     virtual void widgetMouseReleaseEvent( QMouseEvent * ) override;
};

#endif // PLOTZOOMER_H
