#ifndef PLOTCURVE_H
#define PLOTCURVE_H

#include <QObject>
#include <plotseries.h>

class PlotWidget;

class PlotCurve
{
public:

    typedef enum{
        LINES_AND_DOTS,
        LINES
    }LineStyle;

    PlotCurve(const QString& name, const PlotDataPtr &data);
    ~PlotCurve();

    const PlotSeries &series() const;
    PlotSeries &series();

    void attach(PlotWidget* parent);

    void detach();

    void setStyle(LineStyle style);

    void setColor(QColor color, double alpha = 1.0);
    QColor color() const;

private:
    struct Pimpl;
    std::unique_ptr<Pimpl> p;

};

#endif // PLOTCURVE_H
