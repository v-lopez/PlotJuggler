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

inline QPointF CurveTracker::actualPosition() const {
	return _prev_trackerpoint;
}

inline QLineF CurveTracker::curveLineAt(const PlotCurve *curve, double x) const
{
	QLineF line;
	if ( curve->series().size() >= 2 ){
		size_t index = curve->series().data()->getIndexFromX(x);
		if ( index > 0 ){
			line.setP1( curve->series().sample( index - 1 ) );
			line.setP2( curve->series().sample( index ) );
		}
	}
	return line;
}

#endif // CUSTOMTRACKER_H
