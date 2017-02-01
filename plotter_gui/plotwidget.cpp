#include <QDebug>
#include <QDrag>
#include <QMimeData>
#include <QDragEnterEvent>
#include <QAction>
#include <QMessageBox>
#include <QMenu>
#include <QApplication>
#include <QActionGroup>
#include <set>
#include <limits>
#include <memory>

#include "plotwidget.h"
#include "removecurvedialog.h"
#include "curvecolorpick.h"
#include "plotmagnifier.h"
#include "plotlegend.h"
#include "customtracker.h"
#include "plotgrid.h"

PlotWidget::~PlotWidget()
{

}

void PlotWidget::buildActions()
{
    _action_removeCurve = new QAction(tr("&Remove curves"), this);
    _action_removeCurve->setStatusTip(tr("Remove one or more curves from this plot"));
    connect(_action_removeCurve, SIGNAL(triggered()), this, SLOT(launchRemoveCurveDialog()));

    QIcon iconDelete;
    iconDelete.addFile(QStringLiteral(":/icons/resources/checkboxalt.png"), QSize(26, 26), QIcon::Normal, QIcon::Off);
    _action_removeAllCurves = new QAction(tr("&Remove all curves"), this);
    _action_removeAllCurves->setIcon(iconDelete);
    connect(_action_removeAllCurves, SIGNAL(triggered()), this, SLOT(detachAllCurves()));
    connect(_action_removeAllCurves, SIGNAL(triggered()), this, SIGNAL(undoableChange()) );

    QIcon iconColors;
    iconColors.addFile(QStringLiteral(":/icons/resources/office_chart_lines.png"), QSize(26, 26), QIcon::Normal, QIcon::Off);
    _action_changeColors = new QAction(tr("&Change colors"), this);
    _action_changeColors->setIcon(iconColors);
    _action_changeColors->setStatusTip(tr("Change the color of the curves"));
    connect(_action_changeColors, SIGNAL(triggered()), this, SLOT(on_changeColor_triggered()));


    QIcon iconPoints;
    iconPoints.addFile(QStringLiteral(":/icons/resources/line_chart_32px.png"), QSize(26, 26), QIcon::Normal, QIcon::Off);
    _action_showPoints = new QAction(tr("&Show lines and points"), this);
    _action_showPoints->setIcon(iconPoints);
    _action_showPoints->setCheckable( true );
    _action_showPoints->setChecked( false );
    connect(_action_showPoints, SIGNAL(triggered(bool)), this, SLOT(on_showPoints_triggered(bool)));

    QIcon iconZoomH;
    iconZoomH.addFile(QStringLiteral(":/icons/resources/resize_horizontal.png"), QSize(26, 26), QIcon::Normal, QIcon::Off);
    _action_zoomOutHorizontally = new QAction(tr("&Zoom Out Horizontally"), this);
    _action_zoomOutHorizontally->setIcon(iconZoomH);
    connect(_action_zoomOutHorizontally, SIGNAL(triggered()), this, SLOT(on_zoomOutHorizontal_triggered()));
    connect(_action_zoomOutHorizontally, SIGNAL(triggered()), this, SIGNAL(undoableChange()) );

    QIcon iconZoomV;
    iconZoomV.addFile(QStringLiteral(":/icons/resources/resize_vertical.png"), QSize(26, 26), QIcon::Normal, QIcon::Off);
    _action_zoomOutVertically = new QAction(tr("&Zoom Out Vertically"), this);
    _action_zoomOutVertically->setIcon(iconZoomV);
    connect(_action_zoomOutVertically, SIGNAL(triggered()), this, SLOT(on_zoomOutVertical_triggered()));
    connect(_action_zoomOutVertically, SIGNAL(triggered()), this, SIGNAL(undoableChange()) );

    _action_noTransform = new QAction(tr("&NO Transform"), this);
    _action_noTransform->setCheckable( true );
    _action_noTransform->setChecked( true );
    connect(_action_noTransform, SIGNAL(triggered(bool)), this, SLOT(on_noTransform_triggered(bool)));

    _action_1stDerivativeTransform = new QAction(tr("&1st derivative"), this);
    _action_1stDerivativeTransform->setCheckable( true );
    connect(_action_1stDerivativeTransform, SIGNAL(triggered(bool)), this, SLOT(on_1stDerivativeTransform_triggered(bool)));

    _action_2ndDerivativeTransform = new QAction(tr("&2nd Derivative"), this);
    _action_2ndDerivativeTransform->setCheckable( true );
    connect(_action_2ndDerivativeTransform, SIGNAL(triggered(bool)), this, SLOT(on_2ndDerivativeTransform_triggered(bool)));

    auto transform_group = new QActionGroup(this);

    transform_group->addAction(_action_noTransform);
    transform_group->addAction(_action_1stDerivativeTransform);
    transform_group->addAction(_action_2ndDerivativeTransform);
}



bool PlotWidget::addCurve(const QString &name, bool do_replot)
{
    auto it = _mapped_data->numeric.find( name.toStdString() );
    if( it == _mapped_data->numeric.end()) {
        return false;
    }

    if( _curve_list.find(name) != _curve_list.end()) {
        return false;
    }

    PlotDataPtr data = it->second;

    auto curve = std::make_shared<PlotCurve>( name, data );

    curve->setStyle( _line_style);

    curve->setColor( data->getColorHint(),  0.7 );
    curve->attach( this );
    _curve_list.insert( std::make_pair(name, curve));

    auto range_X = maximumRangeX();
    auto range_Y = maximumRangeY();

    this->setAxisScale( AXIS_X, range_X->min, range_X->max );
    this->setAxisScale( AXIS_Y, range_Y->min, range_Y->max );

    if( do_replot ) {
        replot();
    }
    return true;
}

void PlotWidget::removeCurve(const QString &name)
{
    auto it = _curve_list.find(name);
    if( it != _curve_list.end() )
    {
        auto curve = it->second;
        curve->detach();
        replot();
        _curve_list.erase( it );
    }
}

bool PlotWidget::isEmpty() const
{
    return _curve_list.empty();
}

const std::map<QString, std::shared_ptr<PlotCurve> > &PlotWidget::curveList() const
{
    return _curve_list;
}

void PlotWidget::dragEnterEvent(QDragEnterEvent *event)
{
    dragEnterEvent_BaseImpl(event);

    const QMimeData *mimeData = event->mimeData();
    QStringList mimeFormats = mimeData->formats();
    foreach(QString format, mimeFormats)
    {
        QByteArray encoded = mimeData->data( format );
        QDataStream stream(&encoded, QIODevice::ReadOnly);

        if( format.contains( "qabstractitemmodeldatalist") )
        {
            event->acceptProposedAction();
        }
        if( format.contains( "plot_area")  )
        {
            QString source_name;
            stream >> source_name;

            if(QString::compare( windowTitle(),source_name ) != 0 ){
                event->acceptProposedAction();
            }
        }
    }
}


void PlotWidget::dropEvent(QDropEvent *event)
{
    dropEvent_BaseImpl(event);

    const QMimeData *mimeData = event->mimeData();
    QStringList mimeFormats = mimeData->formats();

    foreach(QString format, mimeFormats)
    {
        QByteArray encoded = mimeData->data( format );
        QDataStream stream(&encoded, QIODevice::ReadOnly);

        if( format.contains( "qabstractitemmodeldatalist") )
        {
            bool plot_added = false;
            while (!stream.atEnd())
            {
                int row, col;
                QMap<int,  QVariant> roleDataMap;

                stream >> row >> col >> roleDataMap;

                QString curve_name = roleDataMap[0].toString();
                addCurve( curve_name );
                plot_added = true;
            }
            if( plot_added )
            {
                emit undoableChange();
            }
        }
        if( format.contains( "plot_area") )
        {
            QString source_name;
            stream >> source_name;
            PlotWidget* source_plot = static_cast<PlotWidget*>( event->source() );
            emit swapWidgetsRequested( source_plot, this );
        }
    }
}

void PlotWidget::detachAllCurves()
{
    for(auto& it: _curve_list)
    {
        it.second->detach();
    }
    _curve_list.erase(_curve_list.begin(), _curve_list.end());
    replot();
}

QDomElement PlotWidget::xmlSaveState( QDomDocument &doc) const
{
    QDomElement plot_el = doc.createElement("plot");

    QDomElement range_el = doc.createElement("range");
    QRectF rect = this->currentBoundingRect();
    range_el.setAttribute("bottom", QString::number(rect.bottom()) );
    range_el.setAttribute("top", QString::number(rect.top()) );
    range_el.setAttribute("left", QString::number(rect.left()) );
    range_el.setAttribute("right", QString::number(rect.right()) );
    plot_el.appendChild(range_el);

    for(auto it=_curve_list.begin(); it != _curve_list.end(); ++it)
    {
        QString name = it->first;
        auto curve = it->second;
        QDomElement curve_el = doc.createElement("curve");
        curve_el.setAttribute( "name",name);
        curve_el.setAttribute( "R", curve->color().red());
        curve_el.setAttribute( "G", curve->color().green());
        curve_el.setAttribute( "B", curve->color().blue());

        plot_el.appendChild(curve_el);
    }

    QDomElement transform  = doc.createElement("transform");
    if( _current_transform == PlotSeries::firstDerivative )
    {
        transform.setAttribute("value", "firstDerivative" );
    }
    else if ( _current_transform == PlotSeries::secondDerivative )
    {
        transform.setAttribute("value", "secondDerivative" );
    }
    else{
        transform.setAttribute("value", "noTransform" );
    }
    plot_el.appendChild(transform);

    return plot_el;
}

bool PlotWidget::xmlLoadState(QDomElement &plot_widget, QMessageBox::StandardButton* answer)
{
    QDomElement curve;

    std::set<QString> added_curve_names;

    for (  curve = plot_widget.firstChildElement( "curve" )  ;
           !curve.isNull();
           curve = curve.nextSiblingElement( "curve" ) )
    {
        QString curve_name = curve.attribute("name");
        int R = curve.attribute("R").toInt();
        int G = curve.attribute("G").toInt();
        int B = curve.attribute("B").toInt();
        QColor color(R,G,B);

        if(  _mapped_data->numeric.find(curve_name.toStdString()) != _mapped_data->numeric.end() )
        {
            addCurve(curve_name, false);
            _curve_list[curve_name]->setColor( color, 1.0);
            added_curve_names.insert(curve_name );
        }
        else{
            if( *answer !=  QMessageBox::YesToAll)
            {
                *answer = QMessageBox::question(
                            0,
                            tr("Warning"),
                            tr("Can't find the curve with name %1.\n Do you want to ignore it? ").arg(curve_name),
                            QMessageBox::Yes | QMessageBox::YesToAll | QMessageBox::Abort ,
                            QMessageBox::Abort );
            }

            if( *answer ==  QMessageBox::Yes || *answer ==  QMessageBox::YesToAll) {
                continue;
            }

            if( *answer ==  QMessageBox::Abort) {
                return false;
            }
        }
    }

    bool curve_removed = true;

    while( curve_removed)
    {
        curve_removed = false;
        for(auto& it: _curve_list)
        {
            QString curve_name = it.first;
            if( added_curve_names.find( curve_name ) == added_curve_names.end())
            {
                removeCurve( curve_name );
                curve_removed = true;
                break;
            }
        }
    }
    //-----------------------------------------
    QDomElement transform = plot_widget.firstChildElement( "transform" );
    if( !transform.isNull()  )
    {
        QString trans_value = transform.attribute("value");
        if( trans_value == "firstDerivative")
        {
            _action_1stDerivativeTransform->trigger();
        }
        else if(trans_value == "secondDerivative")
        {
            _action_2ndDerivativeTransform->trigger();
        }
        else if(trans_value == "noTransform")
        {
            _action_noTransform->trigger();
        }
    }
    //-----------------------------------------
    QDomElement rectangle = plot_widget.firstChildElement( "range" );
    if( !rectangle.isNull()){
        QRectF rect;
        rect.setBottom( rectangle.attribute("bottom").toDouble());
        rect.setTop( rectangle.attribute("top").toDouble());
        rect.setLeft( rectangle.attribute("left").toDouble());
        rect.setRight( rectangle.attribute("right").toDouble());

        this->setScale( rect, false);
    }

    return true;
}


const CurveTracker * PlotWidget::tracker() const
{
    return _tracker;
}

CurveTracker* PlotWidget::tracker()
{
    return _tracker;
}

void PlotWidget::setScale(QRectF rect, bool emit_signal)
{
    this->setAxisScale( AXIS_X, rect.left(), rect.right());
    this->setAxisScale( AXIS_Y, rect.bottom(), rect.top());

    if( emit_signal) {
        emit rectChanged(this, rect);
    }
}

void PlotWidget::activateLegent(bool activate)
{
    _legend->setVisible(activate);
}

void PlotWidget::activateGrid(bool activate)
{
    _grid->setVisible(activate);
}

PlotData::RangeTime PlotWidget::maximumRangeX() const
{
    double left   = 0;
    double right  = 0;

    if( _curve_list.size() == 0){
        return PlotData::RangeTime();
    }

    bool first = true;
    for(auto it = _curve_list.begin(); it != _curve_list.end(); ++it)
    {
        PlotSeries& plot = ( it->second->series() );
        plot.updateData(false);
        auto range_X = plot.getRangeX();

        if( !range_X ) continue;

        if( first ){
            first = false;
            left  = range_X->min;
            right = range_X->max;
        }
        else{
            if( left  > range_X->min )    left  = range_X->min;
            if( right < range_X->max )    right = range_X->max;
        }
    }

    if( fabs(right - left) <= std::numeric_limits<double>::epsilon() )
    {
        right += 0.1;
        left  -= 0.1;
    }

    _magnifier->setAxisLimits( AXIS_X, left, right);
    return PlotData::RangeTime( { left, right } );
}

//TODO report failure for empty dataset
PlotData::RangeValue PlotWidget::maximumRangeY() const
{
    double top    = 0;
    double bottom = 0;

    bool first = true;
    for(auto it = _curve_list.begin(); it != _curve_list.end(); ++it)
    {
        PlotSeries& plot = ( it->second->series() );
        plot.updateData(false);

        auto max_range_X = maximumRangeX();
        auto range_X = plot.getRangeX();

        if( !range_X ) continue;

        int X0 = plot.data()->getIndexFromX(std::max(range_X->min, max_range_X->min));
        int X1 = plot.data()->getIndexFromX(std::min(range_X->max, max_range_X->max));

        if( X0<0 || X1 <0)
        {
            qDebug() << " invalid X0/X1 range in PlotWidget::maximumRangeY";
            continue;
        }
        else{
            auto range_Y = plot.getRangeY(X0, X1);
            if( !range_Y )
            {
                qDebug() << " invalid range_Y in PlotWidget::maximumRangeY";
                continue;
            }

            if( first ){
                first = true;
                top    = range_Y->max;
                bottom = range_Y->min;
                first = false;
            }
            else{
                if( top <    range_Y->max )    top    = range_Y->max;
                if( bottom > range_Y->min )    bottom = range_Y->min;
            }
        }
    }

    if( fabs(top - bottom) <= std::numeric_limits<double>::epsilon() )
    {
        top    += 0.1;
        bottom -= 0.1;
    }
    else{
        auto margin = (top-bottom) * 0.05;
        top    += margin;
        bottom -= margin;
    }

    _magnifier->setAxisLimits( AXIS_Y, bottom, top);
    return PlotData::RangeValue( { bottom,  top} );
}


void PlotWidget::launchRemoveCurveDialog()
{
    RemoveCurveDialog* dialog = new RemoveCurveDialog(this);
    auto prev_curve_count = _curve_list.size();

    for(auto it = _curve_list.begin(); it != _curve_list.end(); ++it)
    {
        dialog->addCurveName( it->first );
    }

    dialog->exec();

    if( prev_curve_count != _curve_list.size() )
    {
        emit undoableChange();
    }
}

void PlotWidget::on_changeColor_triggered()
{
    std::map<QString,QColor> color_by_name;

    for(auto it = _curve_list.begin(); it != _curve_list.end(); ++it)
    {
        const QString& curve_name = it->first;
        auto curve = it->second;
        color_by_name.insert(std::make_pair( curve_name, curve->color() ));
    }

    CurveColorPick* dialog = new CurveColorPick(&color_by_name, this);
    dialog->exec();

    bool modified = false;

    for(auto it = _curve_list.begin(); it != _curve_list.end(); ++it)
    {
        const QString& curve_name = it->first;
        auto curve = it->second;
        QColor new_color = color_by_name[curve_name];
        if( curve->color() != new_color)
        {
            curve->setColor( color_by_name[curve_name], 1.0 );
            modified = true;
        }
    }
    if( modified){
        emit undoableChange();
    }
}

void PlotWidget::on_showPoints_triggered(bool checked)
{
    _line_style = checked ? PlotCurve::LINES_AND_DOTS : PlotCurve::LINES ;

    for(auto& it: _curve_list)
    {
        it.second->setStyle(_line_style);
    }
    replot();
}

void PlotWidget::on_externallyResized(const QRectF& rect)
{
    emit rectChanged( this, rect);
}


void PlotWidget::zoomOut(bool emit_signal)
{
    QRectF rect = currentBoundingRect();
    auto rangeX = maximumRangeX();

    rect.setLeft(  rangeX->min );
    rect.setRight( rangeX->max );

    auto rangeY = maximumRangeY();

    rect.setBottom( rangeY->min );
    rect.setTop( rangeY->max );
    this->setScale(rect);
}

void PlotWidget::on_zoomOutHorizontal_triggered(bool emit_signal)
{
    QRectF act = currentBoundingRect();
    auto rangeX = maximumRangeX();

    act.setLeft( rangeX->min );
    act.setRight( rangeX->max );
    this->setScale(act, emit_signal);
}

void PlotWidget::on_zoomOutVertical_triggered(bool emit_signal)
{
    QRectF act = currentBoundingRect();
    auto rangeY = maximumRangeY();

    act.setBottom( rangeY->min );
    act.setTop(    rangeY->max );
    this->setScale(act, emit_signal);
}

void PlotWidget::on_noTransform_triggered(bool checked )
{
    if(_current_transform ==  PlotSeries::noTransform) return;

    for(auto it = _curve_list.begin(); it != _curve_list.end(); ++it)
    {
        PlotSeries& plot = ( it->second->series() );
        plot.setTransform( PlotSeries::noTransform );
        plot.updateData(true);
    }
    this->setTitle("");
    _current_transform = ( PlotSeries::noTransform );

    on_zoomOutVertical_triggered(false);
    replot();
    emit undoableChange();
}

void PlotWidget::on_1stDerivativeTransform_triggered(bool checked)
{
    if(_current_transform ==  PlotSeries::firstDerivative) return;

    for(auto it = _curve_list.begin(); it != _curve_list.end(); ++it)
    {
        PlotSeries& plot = ( it->second->series() );
        plot.setTransform( PlotSeries::firstDerivative );
        plot.updateData(true);
    }

    setTitle("1st derivative");

    _current_transform = ( PlotSeries::firstDerivative );

    on_zoomOutVertical_triggered(false);
    replot();
    emit undoableChange();
}

void PlotWidget::on_2ndDerivativeTransform_triggered(bool checked)
{
    if(_current_transform ==  PlotSeries::secondDerivative) return;

    for(auto it = _curve_list.begin(); it != _curve_list.end(); ++it)
    {
        PlotSeries& plot = ( it->second->series() );
        plot.setTransform( PlotSeries::secondDerivative );
        plot.updateData(true);
    }
    this->setTitle("2nd derivative");
    _current_transform = ( PlotSeries::secondDerivative );

    on_zoomOutVertical_triggered(false);
    replot();
    emit undoableChange();
}

void PlotWidget::canvasContextMenuTriggered(const QPoint &pos)
{
    QMenu menu(this);
    menu.addAction(_action_removeCurve);
    menu.addAction(_action_removeAllCurves);
    menu.addSeparator();
    menu.addAction(_action_changeColors);
    menu.addAction(_action_showPoints);
    menu.addSeparator();
    menu.addAction(_action_zoomOutHorizontally);
    menu.addAction(_action_zoomOutVertically);
    menu.addSeparator();
    menu.addAction( _action_noTransform );
    menu.addAction( _action_1stDerivativeTransform );
    menu.addAction( _action_2ndDerivativeTransform );

    _action_removeCurve->setEnabled( ! _curve_list.empty() );
    _action_removeAllCurves->setEnabled( ! _curve_list.empty() );
    _action_changeColors->setEnabled(  ! _curve_list.empty() );

    //  menu.exec( canvas()->mapToGlobal(pos) );
    menu.exec( pos );
}

void PlotWidget::mousePressEvent(QMouseEvent *event)
{
    if( event->button() == Qt::LeftButton)
    {
        if (event->modifiers() & Qt::ControlModifier )
        {
            QDrag *drag = new QDrag(this);
            QMimeData *mimeData = new QMimeData;

            QByteArray data;
            QDataStream dataStream(&data, QIODevice::WriteOnly);

            dataStream << this->windowTitle();

            mimeData->setData("plot_area", data );
            drag->setMimeData(mimeData);
            drag->exec();
        }
        else if( event->modifiers() == Qt::NoModifier)
        {
            QApplication::setOverrideCursor(QCursor(QPixmap(":/icons/resources/zoom_in_32px.png")));
        }
    }

    if( event->button() == Qt::MiddleButton && event->modifiers() == Qt::NoModifier)
    {
        QApplication::setOverrideCursor(QCursor(QPixmap(":/icons/resources/move.png")));
    }

    mousePressEvent_BaseImpl(event);
}

void PlotWidget::mouseReleaseEvent(QMouseEvent *event )
{
    QApplication::restoreOverrideCursor();
    mouseReleaseEvent_BaseImpl(event);
}



bool PlotWidget::eventFilter(QObject *obj, QEvent *event)
{
    static bool isPressed = true;

    if ( event->type() == QEvent::MouseButtonPress)
    {
        QMouseEvent *mouse_event = static_cast<QMouseEvent*>(event);

        if( mouse_event->button() == Qt::LeftButton &&
                (mouse_event->modifiers() & Qt::ShiftModifier) )
        {
            isPressed = true;
            QPointF pointF = canvasToPlot( mouse_event->pos() );
            emit trackerMoved(pointF);
        }
    }

    if ( event->type() == QEvent::MouseButtonRelease)
    {
        QMouseEvent *mouse_event = static_cast<QMouseEvent*>(event);

        if( mouse_event->button() == Qt::LeftButton ) {
            isPressed = false;
        }
    }

    if ( event->type() == QEvent::MouseMove )
    {
        // special processing for mouse move
        QMouseEvent *mouse_event = static_cast<QMouseEvent*>(event);

        if ( isPressed && mouse_event->modifiers() & Qt::ShiftModifier )
        {
            QPointF pointF = canvasToPlot( mouse_event->pos() );
            emit trackerMoved(pointF);
        }
    }
    return eventFilter_BaseImpl( obj, event );
}

