SET( SOURCES
    qlegend.cpp
    legendlayout.cpp
    qlegendmarker.cpp
    qpielegendmarker.cpp
    legendmarkeritem.cpp
    qbarlegendmarker.cpp
    qxylegendmarker.cpp
    qarealegendmarker.cpp
    legendscroller.cpp
    qboxplotlegendmarker.cpp
    qcandlesticklegendmarker.cpp
    )

SET( PRIVATE_HEADERS
    legendscroller_p.h
    qlegend_p.h
    legendlayout_p.h
    qlegendmarker_p.h
    legendmarkeritem_p.h
    qpielegendmarker_p.h
    qbarlegendmarker_p.h
    qxylegendmarker_p.h
    qarealegendmarker_p.h
    qboxplotlegendmarker_p.h
    qcandlesticklegendmarker_p.h
    )

SET( PUBLIC_HEADERS
    qlegend.h
    qlegendmarker.h
    qpielegendmarker.h
    qbarlegendmarker.h
    qxylegendmarker.h
    qarealegendmarker.h
    qboxplotlegendmarker.h
    qcandlesticklegendmarker.h
    )

file(COPY ${PRIVATE_HEADERS}  DESTINATION  ${QTCHARTS_BUILD_DIR}/QtCharts/private )
file(COPY ${PUBLIC_HEADERS}   DESTINATION  ${QTCHARTS_BUILD_DIR}/QtCharts )


add_library( legend OBJECT ${PUBLIC_HEADERS}  ${PRIVATE_HEADERS} ${SOURCES})

target_include_directories( legend BEFORE PRIVATE
    ./
    ${QTCHARTS_BUILD_DIR}/QtCharts
    ${QTCHARTS_BUILD_DIR}/
)
