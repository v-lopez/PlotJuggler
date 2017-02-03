SET( SOURCES
    qpieseries.cpp
    piesliceitem.cpp
    piechartitem.cpp
    qpieslice.cpp
    qpiemodelmapper.cpp
    qvpiemodelmapper.cpp
    qhpiemodelmapper.cpp
    )

set ( PRIVATE_HEADERS
    pieslicedata_p.h
    piechartitem_p.h
    piesliceitem_p.h
    qpieslice_p.h
    qpieseries_p.h
    qpiemodelmapper_p.h
    )

SET( PUBLIC_HEADERS
    qpieseries.h
    qpieslice.h
    qpiemodelmapper.h
    qvpiemodelmapper.h
    qhpiemodelmapper.h
    )

file(COPY ${PRIVATE_HEADERS}  DESTINATION  ${QTCHARTS_BUILD_DIR}/QtCharts/private )
file(COPY ${PUBLIC_HEADERS}   DESTINATION  ${QTCHARTS_BUILD_DIR}/QtCharts )

add_library( piechart OBJECT ${PUBLIC_HEADERS} ${PRIVATE_HEADERS} ${SOURCES})

target_include_directories( piechart PRIVATE
    ./
    ${QTCHARTS_BUILD_DIR}/QtCharts
    ${QTCHARTS_BUILD_DIR}/
)
