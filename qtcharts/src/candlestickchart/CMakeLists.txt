SET( SOURCES
    candlestick.cpp
    candlestickchartitem.cpp
    qcandlestickseries.cpp
    qcandlestickset.cpp
    qcandlestickmodelmapper.cpp
    qhcandlestickmodelmapper.cpp
    qvcandlestickmodelmapper.cpp
    )

set ( PRIVATE_HEADERS
    candlestick_p.h
    candlestickchartitem_p.h
    candlestickdata_p.h
    qcandlestickseries_p.h
    qcandlestickset_p.h
    qcandlestickmodelmapper_p.h
    )

SET( PUBLIC_HEADERS
    qcandlestickseries.h
    qcandlestickset.h
    qcandlestickmodelmapper.h
    qhcandlestickmodelmapper.h
    qvcandlestickmodelmapper.h
    )

file(COPY ${PRIVATE_HEADERS}  DESTINATION  ${QTCHARTS_BUILD_DIR}/QtCharts/private )
file(COPY ${PUBLIC_HEADERS}   DESTINATION  ${QTCHARTS_BUILD_DIR}/QtCharts )

add_library( candlestickchart OBJECT ${PUBLIC_HEADERS} ${PRIVATE_HEADERS} ${SOURCES})

target_include_directories( candlestickchart BEFORE PRIVATE
    ./
    ${QTCHARTS_BUILD_DIR}/QtCharts
    ${QTCHARTS_BUILD_DIR}/
)
