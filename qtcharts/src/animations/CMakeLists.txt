SET( SOURCES
    axisanimation.cpp
    xyanimation.cpp
    pieanimation.cpp
    piesliceanimation.cpp
    splineanimation.cpp
    baranimation.cpp
    scatteranimation.cpp
    boxplotanimation.cpp
    boxwhiskersanimation.cpp
    candlestickanimation.cpp
    candlestickbodywicksanimation.cpp
    chartanimation.cpp
    )

SET( PRIVATE_HEADERS
    axisanimation_p.h
    chartanimation_p.h
    xyanimation_p.h
    pieanimation_p.h
    piesliceanimation_p.h
    splineanimation_p.h
    baranimation_p.h
    scatteranimation_p.h
    boxplotanimation_p.h
    boxwhiskersanimation_p.h
    candlestickanimation_p.h
    candlestickbodywicksanimation_p.h
    )

file(COPY ${PRIVATE_HEADERS}  DESTINATION  ${QTCHARTS_BUILD_DIR}/QtCharts/private )

add_library( animations OBJECT ${PRIVATE_HEADERS} ${SOURCES})

target_include_directories( animations PRIVATE
    ./
    ${QTCHARTS_BUILD_DIR}/QtCharts
    ${QTCHARTS_BUILD_DIR}/
)
