#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QElapsedTimer>
#include <QShortcut>
#include <QCommandLineParser>
#include <QSignalMapper>
#include <set>
#include <deque>
#include <functional>
#include "plotwidget.h"
#include "plotmatrix.h"
#include "filterablelistwidget.h"
#include "tabbedplotwidget.h"
#include "subwindow.h"
#include "PlotJuggler/dataloader_base.h"
#include "PlotJuggler/statepublisher_base.h"
#include "PlotJuggler/datastreamer_base.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(const QCommandLineParser& commandline_parser, QWidget *parent = 0);
    ~MainWindow();

public slots:
    void onUndoableChange();

private slots:

    void onTrackerTimeUpdated(double absolute_time );

    void onTrackerPositionUpdated(QPointF pos );

    void onSplitterMoved(int, int);

    void resizeEvent(QResizeEvent *) ;

    void onPlotAdded(PlotWidget* plot);

    void onPlotMatrixAdded(PlotMatrix* matrix);

    void onActionSaveLayout();

    void onActionLoadLayout(bool reload_previous = false);

    void onActionLoadLayoutFromFile(QString filename, bool load_data);

    void onActionLoadDataFile(bool reload_from_settings = false);

    void onActionLoadDataFileImpl(QString filename, bool reuse_last_timeindex = false );

    void onActionReloadDataFileFromSettings();

    void onActionReloadRecentLayout();

    void onActionLoadStreamer(QString streamer_name);

    void onUndoInvoked();

    void onRedoInvoked();

    void on_tabbedAreaDestroyed(QObject*object);

    void onFloatingWindowDestroyed(QObject*object);

    void onCreateFloatingWindow(PlotMatrix* first_tab = NULL);

    void on_pushButtonAddSubwindow_pressed();

    void onSwapPlots(PlotWidget* source, PlotWidget* destination);

    void on_pushButtonStreaming_toggled(bool checked);

    void updateDataAndReplot();

    void on_streamingSpinBox_valueChanged(int value);

    void onDeleteLoadedData();

    void on_actionAbout_triggered();

    void on_actionStopStreaming_triggered();

    void on_actionExit_triggered();

    void on_actionQuick_Help_triggered();

    void on_horizontalSlider_valueChanged(int value);

    void updateLeftTableValues();

    void deleteLoadedData(const QString &curve_name);

    void on_checkBoxRemoveTimeOffset_toggled(bool checked);

    void on_pushButtonOptions_toggled(bool checked);

    void on_checkBoxUseDateTime_toggled(bool checked);

    void on_pushButtonActivateGrid_toggled(bool checked);

    void on_pushButtonPlay_toggled(bool checked);

private:
    Ui::MainWindow *ui;

    TabbedPlotWidget *      _main_tabbed_widget;
    std::deque<SubWindow*> _floating_window;

    //QAction* _actionUndo;
    //QAction* _actionRedo;

    QShortcut _undo_shortcut;
    QShortcut _redo_shortcut;

    void createActions();

    FilterableListWidget* _curvelist_widget;

    void onLayoutChanged();

    void forEachWidget(std::function<void(PlotWidget*, PlotMatrix*, int, int)> op);

    void forEachWidget(std::function<void(PlotWidget*)> op);

    void updateTimeSlider();

    void buildData();

    PlotDataMap    _mapped_plot_data;

    void rearrangeGridLayout();

    void loadPlugins(QString subdir_name);

    std::map<QString,DataLoader*>      _data_loader;

    std::map<QString,StatePublisher*>  _state_publisher;

    std::map<QString,DataStreamer*>    _data_streamer;

    DataStreamer* _current_streamer;

    QDomDocument xmlSaveState() const;

    bool xmlLoadState(QDomDocument state_document);

    std::deque<QDomDocument> _undo_states;

    std::deque<QDomDocument> _redo_states;

    QElapsedTimer _undo_timer;

    bool _disable_undo_logging;

    bool _test_option;

    double _tracker_time;

    double _min_slider_time;

    double _max_slider_time;

    QString _loaded_datafile;

    std::string _last_load_configuration;

    QSignalMapper *_streamer_signal_mapper;

    void createTabbedDialog(PlotMatrix *first_tab);

    void importPlotDataMap(const PlotDataMap &new_data);

protected:

    double _time_offset;

    QTimer *_replot_timer;
signals:
    void requestRemoveCurveByName(const QString& name);

    void activateStreamingMode( bool active);

    void trackerTimeUpdated(double abs_point);

    void activateTracker(bool active);

};

#endif // MAINWINDOW_H
