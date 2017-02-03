#include "../plotwidget.h"
#include "../plotlegend.h"
#include "../plotgrid.h"
#include "../plotmagnifier.h"
#include "../customtracker.h"
#include "../plotzoomer.h"

#include <qwt_plot_canvas.h>
#include <qwt_scale_engine.h>
#include <qwt_plot_layout.h>
#include <qwt_plot_panner.h>

PlotWidget::PlotWidget(PlotDataMap *datamap, QWidget *parent):
	QwtPlot(parent),
	_magnifier(0 ),
	_tracker ( 0 ),
	_legend( 0 ),
	_grid( 0 ),
	_mapped_data( datamap ),
	_line_style( PlotCurve::LINES),
	_current_transform( PlotCurve::noTransform )
{
	this->setAcceptDrops( true );
	this->setMinimumWidth( 100 );
	this->setMinimumHeight( 100 );

	this->sizePolicy().setHorizontalPolicy( QSizePolicy::Expanding);
	this->sizePolicy().setVerticalPolicy( QSizePolicy::Expanding);

	QwtPlotCanvas *canvas = new QwtPlotCanvas(this);

	canvas->setFrameStyle( QFrame::NoFrame );
	canvas->setPaintAttribute( QwtPlotCanvas::BackingStore, true );

	this->setCanvas( canvas );
	this->setCanvasBackground( QColor( 250, 250, 250 ) );
	this->setAxisAutoScale(0, true);

	this->axisScaleEngine(QwtPlot::xBottom)->setAttribute(QwtScaleEngine::Floating,true);
	this->plotLayout()->setAlignCanvasToScales( true );

	this->canvas()->installEventFilter( this );

	//--------------------------
	_grid = new PlotGrid( this );
	_magnifier = ( new PlotMagnifier( this->canvas() ) );
	_tracker = ( new CurveTracker( this ) );
	_legend = new PlotLegend(this);
	_zoomer = ( new PlotZoomer( this->canvas() ) );
	QwtPlotPanner* panner = ( new QwtPlotPanner( this->canvas() ) );

	_zoomer->setRubberBandPen( QColor( Qt::red , 1, Qt::DotLine) );
	_zoomer->setTrackerPen( QColor( Qt::green, 1, Qt::DotLine ) );
	_zoomer->setMousePattern( QwtEventPattern::MouseSelect1, Qt::LeftButton, Qt::NoModifier );
	connect(_zoomer, SIGNAL(zoomed(const QRectF&)), this, SLOT(on_externallyResized(const QRectF&)) );

	_magnifier->setAxisEnabled( AXIS_X, false);
	_magnifier->setAxisEnabled( AXIS_Y, false);

	// disable right button. keep mouse wheel
	_magnifier->setMouseButton( Qt::NoButton );
	connect(_magnifier, SIGNAL(rescaled(const QRectF&)), this, SLOT(on_externallyResized(const QRectF&)) );
	connect(_magnifier, SIGNAL(rescaled(const QRectF&)), this, SLOT(replot()) );

	panner->setMouseButton(  Qt::MiddleButton, Qt::NoModifier);

	this->canvas()->setContextMenuPolicy( Qt::ContextMenuPolicy::CustomContextMenu );
	connect( canvas, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(canvasContextMenuTriggered(QPoint)) );
	//-------------------------

	buildActions();

	this->canvas()->setMouseTracking(true);
	this->canvas()->installEventFilter(this);

	// this->axisScaleDraw( QwtPlot::xBottom )->enableComponent( QwtAbstractScaleDraw::Labels, false );
	//  this->axisScaleDraw( QwtPlot::yLeft   )->enableComponent( QwtAbstractScaleDraw::Labels, false );
}

QRectF PlotWidget::currentBoundingRect() const
{
	QRectF rect;
	rect.setBottom( this->canvasMap( yLeft ).s1() );
	rect.setTop(    this->canvasMap( yLeft ).s2() );
	rect.setLeft(   this->canvasMap( xBottom ).s1() );
	rect.setRight(  this->canvasMap( xBottom ).s2() );
	return rect;
}

QPointF PlotWidget::canvasToPlot(QPoint point)
{
	return QPointF( invTransform( xBottom, point.x()),
					invTransform( yLeft, point.y()) );
}

QPoint PlotWidget::plotToCanvas(QPointF point)
{
	return QPoint( transform( xBottom, point.x()),
				   transform( yLeft,   point.y()) );
}

void PlotWidget::replot()
{
	if( _zoomer) _zoomer->setZoomBase( false );

	for(auto it = _curve_list.begin(); it != _curve_list.end(); ++it)
	{
		PlotCurve* series = static_cast<PlotCurve*>( it->second.get());
		series->updateData(false);
	}
	QwtPlot::replot();
}


void PlotWidget::setTitle(QString text)
{
	QFont font_title;
	font_title.setPointSize(9);
	QwtText qwt_text(text);
	qwt_text.setFont(font_title);
	QwtPlot::setTitle(qwt_text);
}

void PlotWidget::setAxisScale(Axis axisId, double min, double max, double step)
{
	if (axisId == AXIS_X)
	{
		for(auto it = _curve_list.begin(); it != _curve_list.end(); ++it)
		{
			PlotCurve* series = static_cast<PlotCurve*>( it->second.get());
			series->setSubsampleFactor( );
		}
		QwtPlot::setAxisScale( QwtPlot::xBottom, min, max, step);
	}
	else{
		QwtPlot::setAxisScale( QwtPlot::yLeft, min, max, step);
	}
}







