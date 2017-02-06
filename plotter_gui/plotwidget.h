#ifndef PLOT_Widget_H
#define PLOT_Widget_H

#include <map>
#include <QObject>
#include <QTextEdit>
#include <QDomDocument>
#include <deque>
#include <QMessageBox>
#include <QTime>
#include <QTimer>
#include <memory>
#include "plotcurve.h"

class CurveTracker;
class PlotGrid;
class PlotLegend;
class PlotMagnifier;
class PlotZoomer;

#ifdef USE_QWT

#include <qwt_plot_curve.h>
#include <qwt_plot.h>

class PlotWidget : public QwtPlot
{
  typedef QwtPlot BaseClass;
#else

#include <QtCharts/QChartView>
class PlotWidget : public QtCharts::QChartView
{
  typedef QtCharts::QChartView BaseClass;
  QTimer _replot_timer;

  void replotHandle();

#endif

  Q_OBJECT

public:
  PlotWidget(PlotDataMap* datamap, QWidget *parent=0);
  virtual ~PlotWidget();

  typedef enum{
    AXIS_X,
    AXIS_Y
  } Axis;

  bool addCurve(const QString&  name, bool do_replot = true);

  bool isEmpty() const;

  const std::map<QString, std::shared_ptr<PlotCurve> > &curveList() const;

  QDomElement xmlSaveState(QDomDocument &doc) const;

  bool xmlLoadState(QDomElement &element, QMessageBox::StandardButton* answer);


  PlotData::RangeTimeOpt maximumRangeX() const;

  PlotData::RangeValueOpt maximumRangeY(const PlotData::RangeTime& range_X) const;

  const CurveTracker *tracker() const;
  CurveTracker *tracker();

  QRectF boundingRect() const;
  void setBoundingRect( QRectF rect, bool emit_signal = true );

  void setTitle(QString text);

  QPointF canvasToPlot(QPoint  pos);
  QPoint  plotToCanvas(QPointF pos);

protected:
  virtual void dragEnterEvent(QDragEnterEvent *event) override;
  virtual void dropEvent(QDropEvent *event)override ;
  virtual void mousePressEvent(QMouseEvent *event) override;
  virtual void mouseReleaseEvent(QMouseEvent *event) override;
  virtual bool eventFilter(QObject *obj, QEvent *event) override;

signals:
  void swapWidgetsRequested(PlotWidget* source, PlotWidget* destination);
  void rectChanged(PlotWidget* self, QRectF rect );
  void undoableChange();
  void trackerMoved(QPointF pos);

public slots:

  void replot() ;

  void detachAllCurves();

  void zoomOut(bool emit_signal = true);

  void on_zoomOutHorizontal_triggered(bool emit_signal = true);

  void on_zoomOutVertical_triggered(bool emit_signal = true);

  void on_noTransform_triggered(bool checked );
  void on_1stDerivativeTransform_triggered(bool checked);
  void on_2ndDerivativeTransform_triggered(bool checked);

  void removeCurve(const QString& name);

  void activateLegent(bool activate);

  void activateGrid(bool activate);

private slots:
  void launchRemoveCurveDialog();
  void canvasContextMenuTriggered(const QPoint &pos);
  void on_changeColor_triggered();
  void on_showPoints_triggered(bool checked);
  void on_externallyResized(const QRectF &new_rect);

private:
  std::map<QString, std::shared_ptr<PlotCurve> > _curve_list;

  QAction *_action_removeCurve;
  QAction *_action_removeAllCurves;
  QAction *_action_changeColors;
  QAction *_action_showPoints;
  QAction *_action_zoomOutHorizontally;
  QAction *_action_zoomOutVertically;
  QAction *_action_noTransform;
  QAction *_action_1stDerivativeTransform;
  QAction *_action_2ndDerivativeTransform;

  void setAxisScale(Axis axisId, double min, double max, double step = 0 );

  PlotDataMap* _mapped_data;
  PlotCurve::Transform _current_transform;

  void buildActions();

  int   _fps_counter;
  QTime _fps_timeStamp;
  PlotCurve::LineStyle _line_style;

  CurveTracker*  _tracker;
  PlotLegend*    _legend;
  PlotGrid*      _grid;
  PlotMagnifier* _magnifier;
  PlotZoomer*    _zoomer;
};

#endif
