

SET( SOURCES
    abstractchartlayout.cpp
    cartesianchartlayout.cpp
    polarchartlayout.cpp
    )

SET( PRIVATE_HEADERS
    abstractchartlayout_p.h
    cartesianchartlayout_p.h
    polarchartlayout_p.h
    )

file(COPY ${PRIVATE_HEADERS}  DESTINATION  ${QTCHARTS_BUILD_DIR}/QtCharts/private )


add_library( layout OBJECT ${PRIVATE_HEADERS} ${SOURCES})

target_include_directories( layout BEFORE PRIVATE
    ./
    ${QTCHARTS_BUILD_DIR}/QtCharts
    ${QTCHARTS_BUILD_DIR}/
)
