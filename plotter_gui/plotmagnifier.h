#ifndef PLOTMAGNIFIER_H
#define PLOTMAGNIFIER_H

#include <QPointF>
#include <QTimer>
#include "plotwidget.h"

#ifdef USE_QWT
#include <qwt_plot_magnifier.h>
class PlotMagnifier : public QwtPlotMagnifier {
#else
class PlotMagnifier: QObject
{
#endif
    Q_OBJECT

public:
    explicit PlotMagnifier( QWidget *canvas);
    virtual ~PlotMagnifier();

	void setAxisLimits(PlotWidget::Axis axis, double lower, double upper);

protected:
    virtual void rescale( double factor );
    virtual void widgetWheelEvent( QWheelEvent *event );

	QRectF _bound;
    QPointF _mouse_position;

signals:
    void rescaled(QRectF new_size);

private:
    QPointF invTransform(QPoint pos);
    QTimer _future_emit;

};

#endif // PLOTMAGNIFIER_H
