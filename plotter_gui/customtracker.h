#ifndef CUSTOMTRACKER_H
#define CUSTOMTRACKER_H

#include <QEvent>
#include <QPointF>
#include <QEvent>
#include <memory>
#include "plotwidget.h"

class PlotWidget;
class PlotSeries;

class CurveTracker: public QObject
{
    Q_OBJECT
public:
    explicit CurveTracker(PlotWidget *parent );
    virtual ~CurveTracker();

    QPointF actualPosition() const;

public slots:

    void setEnabled(bool enable);

    void setPosition(const QPointF & );

private:
    QLineF curveLineAt(const PlotCurve *, double x ) const;

    QPointF _prev_trackerpoint;
    bool _visible;

    struct Pimpl;
    std::unique_ptr<Pimpl> p;
};

#endif // CUSTOMTRACKER_H
