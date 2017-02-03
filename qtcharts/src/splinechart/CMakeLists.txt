

SET( SOURCES
    qsplineseries.cpp
    splinechartitem.cpp
    )

set ( PRIVATE_HEADERS
    splinechartitem_p.h
    qsplineseries_p.h
    )

SET( PUBLIC_HEADERS
    qsplineseries.h
    )

file(COPY ${PRIVATE_HEADERS}  DESTINATION  ${QTCHARTS_BUILD_DIR}/QtCharts/private )
file(COPY ${PUBLIC_HEADERS}   DESTINATION  ${QTCHARTS_BUILD_DIR}/QtCharts )


add_library( splinechart OBJECT ${PUBLIC_HEADERS} ${PRIVATE_HEADERS} ${SOURCES})

target_include_directories( splinechart PRIVATE
    ./
    ${QTCHARTS_BUILD_DIR}/QtCharts
    ${QTCHARTS_BUILD_DIR}/
)
