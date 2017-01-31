#include "customtracker.h"
#include "plotcurve.h"
#include "plotwidget.h"

#include <qwt_series_data.h>
#include <qwt_plot.h>
#include <qwt_plot_curve.h>
#include <qwt_event_pattern.h>
#include <qwt_plot_marker.h>
#include <qwt_symbol.h>
#include <qevent.h>

struct CurveTracker::Pimpl
{
    std::vector<QwtPlotMarker*> markers;
    QwtPlotMarker* line_marker;
    QwtPlotMarker* text_marker;
    PlotWidget* plot;
};


CurveTracker::CurveTracker( PlotWidget *parent ):
    QObject(parent),
    p( new Pimpl)
{
    p->line_marker = ( new QwtPlotMarker );
    p->plot = parent;

    p->line_marker->setLinePen(QPen(Qt::red));
    p->line_marker->setLineStyle(QwtPlotMarker::VLine);
    p->line_marker->setValue(0,0);
    p->line_marker->attach( p->plot );

    p->text_marker = ( new QwtPlotMarker );
    p->text_marker->attach( p->plot );
}

CurveTracker::~CurveTracker()
{

}

QPointF CurveTracker::actualPosition() const
{
    return _prev_trackerpoint;
}

void CurveTracker::setEnabled(bool enable)
{
    _visible = enable;
    p->line_marker->setVisible( enable );
    p->text_marker->setVisible( enable );
}

void CurveTracker::setPosition(const QPointF& position)
{
    const auto& curves = p->plot->curveList();

    p->line_marker->setValue( position );

    QRectF rect;
    rect.setBottom( p->plot->canvasMap( QwtPlot::yLeft ).s1() );
    rect.setTop( p->plot->canvasMap( QwtPlot::yLeft ).s2() );
    rect.setLeft( p->plot->canvasMap( QwtPlot::xBottom ).s1() );
    rect.setRight( p->plot->canvasMap( QwtPlot::xBottom ).s2() );

    double tot_Y = 0;
    int visible_points = 0;

    while( p->markers.size() >  curves.size())
    {
        p->markers.back()->detach();
        p->markers.pop_back();
    }

    for (int i = p->markers.size() ; i < curves.size(); i++ )
    {
        p->markers.push_back( new QwtPlotMarker );
        p->markers[i]->attach( p->plot );
        p->markers[i]->setVisible( _visible );
    }

    QString text_marker_info;
    double text_X_offset = 0;

    auto it = curves.begin();
    for (int i = 0; i< curves.size(); i++, it++)
    {
        const std::shared_ptr<PlotCurve>& curve =  it->second;
        QColor color;// = curve->color();

        text_X_offset =  rect.width() * 0.02;

        if( !p->markers[i]->symbol() )
        {
            QwtSymbol *sym = new QwtSymbol(
                        QwtSymbol::Diamond,
                        color,
                        color,
                        QSize(5,5));
            p->markers[i]->setSymbol(sym);
        }
        const QLineF line = curveLineAt( curve.get() , position.x() );

        if( line.isNull() )
        {
            continue;
        }

        QPointF point;
        double middle_X = (line.p1().x() + line.p2().x()) / 2.0;

        if(  position.x() < middle_X )
            point = line.p1();
        else
            point = line.p2();

        p->markers[i]->setValue( point );

        if( rect.contains( point ) &&  _visible)
        {
            tot_Y += point.y();
            visible_points++;

            text_marker_info += QString( "<font color=""%1"">%2</font>" ).arg( color.name() ).arg( point.y() );
            if(  (i+1) < curves.size() ){
                text_marker_info += "<br>";
            }
            p->markers[i]->setVisible( true );
        }
        else{
            p->markers[i]->setVisible( false );
        }
        p->markers[i]->setValue( point );
        i++;
    }

    QwtText mark_text;
    mark_text.setColor( Qt::black );

    QColor c( "#FFFFFF" );
    mark_text.setBorderPen( QPen( c, 2 ) );
    c.setAlpha( 200 );
    mark_text.setBackgroundBrush( c );
    mark_text.setText( text_marker_info );

    p->text_marker->setLabel(mark_text);
    p->text_marker->setLabelAlignment( Qt::AlignRight );
    p->text_marker->setXValue( position.x() + text_X_offset );

    if(visible_points > 0){
        p->text_marker->setYValue( tot_Y/visible_points );
    }
    p->text_marker->setVisible( visible_points > 0 &&  _visible);

    _prev_trackerpoint = position;

}


QLineF CurveTracker::curveLineAt(const PlotCurve* curve, double x ) const
{
    QLineF line;

    if ( curve->series().size() >= 2 )
    {
        int index = curve->series().data()->getIndexFromX(x);

        if ( index > 0 )
        {
            line.setP1( curve->series().sample( index - 1 ) );
            line.setP2( curve->series().sample( index ) );
        }
    }
    return line;
}

