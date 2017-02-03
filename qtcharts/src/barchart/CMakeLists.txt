#Subdirectiores are defined here, because qt creator doesn't handle nested include(foo.pri) chains very well.

include_directories(
    src
    ${QTCHARTS_BUILD_DIR}/QtCharts/private
    ${QTCHARTS_BUILD_DIR}/QtCharts
    ${Qt5Widgets_INCLUDE_DIRS}
    vertical/bar
    vertical/stacked
    vertical/percent
    horizontal/bar
    horizontal/stacked
    horizontal/percent
    )

SET( SOURCES
    bar.cpp
    abstractbarchartitem.cpp
    qabstractbarseries.cpp
    qbarset.cpp
    qbarmodelmapper.cpp
    qvbarmodelmapper.cpp
    qhbarmodelmapper.cpp
    vertical/bar/qbarseries.cpp
    vertical/bar/barchartitem.cpp
    vertical/stacked/qstackedbarseries.cpp
    vertical/stacked/stackedbarchartitem.cpp
    vertical/percent/qpercentbarseries.cpp
    vertical/percent/percentbarchartitem.cpp
    horizontal/bar/qhorizontalbarseries.cpp
    horizontal/bar/horizontalbarchartitem.cpp
    horizontal/stacked/qhorizontalstackedbarseries.cpp
    horizontal/stacked/horizontalstackedbarchartitem.cpp
    horizontal/percent/qhorizontalpercentbarseries.cpp
    horizontal/percent/horizontalpercentbarchartitem.cpp
    )

set ( PRIVATE_HEADERS
    bar_p.h
    qbarset_p.h
    abstractbarchartitem_p.h
    qabstractbarseries_p.h
    qbarmodelmapper_p.h
    vertical/bar/qbarseries_p.h
    vertical/bar/barchartitem_p.h
    vertical/stacked/qstackedbarseries_p.h
    vertical/stacked/stackedbarchartitem_p.h
    vertical/percent/qpercentbarseries_p.h
    vertical/percent/percentbarchartitem_p.h
    horizontal/bar/qhorizontalbarseries_p.h
    horizontal/bar/horizontalbarchartitem_p.h
    horizontal/stacked/qhorizontalstackedbarseries_p.h
    horizontal/stacked/horizontalstackedbarchartitem_p.h
    horizontal/percent/qhorizontalpercentbarseries_p.h
    horizontal/percent/horizontalpercentbarchartitem_p.h
    )

SET( PUBLIC_HEADERS
    qabstractbarseries.h
    qbarset.h
    qbarmodelmapper.h
    qvbarmodelmapper.h
    qhbarmodelmapper.h
    vertical/bar/qbarseries.h
    vertical/stacked/qstackedbarseries.h
    vertical/percent/qpercentbarseries.h
    horizontal/bar/qhorizontalbarseries.h
    horizontal/stacked/qhorizontalstackedbarseries.h
    horizontal/percent/qhorizontalpercentbarseries.h
    )

file(COPY ${PRIVATE_HEADERS}  DESTINATION  ${QTCHARTS_BUILD_DIR}/QtCharts/private )
file(COPY ${PUBLIC_HEADERS}   DESTINATION  ${QTCHARTS_BUILD_DIR}/QtCharts )

add_library( barchart OBJECT ${PUBLIC_HEADERS} ${PRIVATE_HEADERS} ${SOURCES})

target_include_directories( barchart BEFORE PRIVATE
    ./
    ${QTCHARTS_BUILD_DIR}/QtCharts
    ${QTCHARTS_BUILD_DIR}/
)
