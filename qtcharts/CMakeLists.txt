cmake_minimum_required(VERSION 2.8.8)

project(qtchart_cmake)

find_package(Qt5 REQUIRED COMPONENTS Core Widgets)

add_definitions( -std=c++11
    -DQT_NO_OPENGL -DQT_STATIC
    ${Qt5Widgets_DEFINITIONS} -fPIC)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS}")


SET( SOURCES
    src/chartdataset.cpp
    src/chartpresenter.cpp
    src/chartthememanager.cpp
    src/qchart.cpp
    src/qchartview.cpp
    src/qabstractseries.cpp
    src/chartbackground.cpp
    src/chartelement.cpp
    src/chartitem.cpp
    src/scroller.cpp
    src/charttitle.cpp
    src/qpolarchart.cpp
    )

set ( PRIVATE_HEADERS
    src/chartdataset_p.h
    src/chartitem_p.h
    src/chartpresenter_p.h
    src/chartthememanager_p.h
    src/chartbackground_p.h
    src/chartelement_p.h
    src/chartconfig_p.h
    src/qchart_p.h
    src/qchartview_p.h
    src/scroller_p.h
    src/qabstractseries_p.h
    src/charttitle_p.h
    src/charthelpers_p.h

   # src/glwidget_p.h
)

SET( PUBLIC_HEADERS
    src/qchart.h
    src/qchartglobal.h
    src/qabstractseries.h
    src/qchartview.h
    src/chartsnamespace.h
    src/qpolarchart.h
    )

set(QTCHARTS_BUILD_DIR ${PROJECT_BINARY_DIR})


set(CMAKE_INCLUDE_DIRECTORIES_BEFORE ON)

file(GLOB INCLUDE_QFILES "include/QtCharts*")

message(STATUS "QTCHARTS_BUILD_DIR = ${QTCHARTS_BUILD_DIR} ")

file(COPY ${PRIVATE_HEADERS}  DESTINATION  ${QTCHARTS_BUILD_DIR}/QtCharts/private )
file(COPY ${PUBLIC_HEADERS}   DESTINATION  ${QTCHARTS_BUILD_DIR}/QtCharts )
file(COPY ${INCLUDE_QFILES}   DESTINATION  ${QTCHARTS_BUILD_DIR}/ )

add_subdirectory( src/animations)
add_subdirectory( src/areachart)
add_subdirectory( src/axis)
add_subdirectory( src/barchart)
add_subdirectory( src/boxplotchart)
add_subdirectory( src/candlestickchart)
add_subdirectory( src/domain)
add_subdirectory( src/legend)
add_subdirectory( src/layout)
add_subdirectory( src/linechart)
add_subdirectory( src/piechart)
add_subdirectory( src/scatterchart)
add_subdirectory( src/splinechart)
add_subdirectory( src/themes)
add_subdirectory( src/xychart)


add_library(qtcharts STATIC
    ${PUBLIC_HEADERS}
    ${PRIVATE_HEADERS}
    ${SOURCES}
    $<TARGET_OBJECTS:animations>
    $<TARGET_OBJECTS:areachart>
    $<TARGET_OBJECTS:axis>
    $<TARGET_OBJECTS:barchart>
    $<TARGET_OBJECTS:boxplotchart>
    $<TARGET_OBJECTS:candlestickchart>
    $<TARGET_OBJECTS:domain>
    $<TARGET_OBJECTS:layout>
    $<TARGET_OBJECTS:legend>
    $<TARGET_OBJECTS:linechart>
    $<TARGET_OBJECTS:piechart>
    $<TARGET_OBJECTS:scatterchart>
    $<TARGET_OBJECTS:splinechart>
 #   $<TARGET_OBJECTS:themes>
    $<TARGET_OBJECTS:xychart>
    )

target_include_directories( qtcharts BEFORE PUBLIC
    src
    ${QTCHARTS_BUILD_DIR}/QtCharts
    ${QTCHARTS_BUILD_DIR}/
)

