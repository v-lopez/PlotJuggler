

SET( SOURCES
    boxplotchartitem.cpp
    qboxplotseries.cpp
    boxwhiskers.cpp
    qboxset.cpp
    qboxplotmodelmapper.cpp
    qhboxplotmodelmapper.cpp
    qvboxplotmodelmapper.cpp
    )

set ( PRIVATE_HEADERS
    boxplotchartitem_p.h
    qboxplotseries_p.h
    boxwhiskers_p.h
    boxwhiskersdata_p.h
    qboxset_p.h
    qboxplotmodelmapper_p.h
    )

SET( PUBLIC_HEADERS
    qboxplotseries.h
    qboxset.h
    qboxplotmodelmapper.h
    qhboxplotmodelmapper.h
    qvboxplotmodelmapper.h
    )

file(COPY ${PRIVATE_HEADERS}  DESTINATION  ${QTCHARTS_BUILD_DIR}/QtCharts/private )
file(COPY ${PUBLIC_HEADERS}   DESTINATION  ${QTCHARTS_BUILD_DIR}/QtCharts )


add_library( boxplotchart OBJECT ${PUBLIC_HEADERS} ${PRIVATE_HEADERS} ${SOURCES})

target_include_directories( boxplotchart PRIVATE
    ./
    ${QTCHARTS_BUILD_DIR}/QtCharts
    ${QTCHARTS_BUILD_DIR}/
)
