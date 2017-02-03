

SET( SOURCES
    qscatterseries.cpp
    scatterchartitem.cpp
    )

SET( PRIVATE_HEADERS
    scatterchartitem_p.h
    qscatterseries_p.h
    )

SET( PUBLIC_HEADERS
    qscatterseries.h
    )

file(COPY ${PRIVATE_HEADERS}  DESTINATION  ${QTCHARTS_BUILD_DIR}/QtCharts/private )
file(COPY ${PUBLIC_HEADERS}   DESTINATION  ${QTCHARTS_BUILD_DIR}/QtCharts )


add_library( scatterchart OBJECT ${PUBLIC_HEADERS} ${PRIVATE_HEADERS} ${SOURCES})

target_include_directories( scatterchart PRIVATE
    ./
    ${QTCHARTS_BUILD_DIR}/QtCharts
    ${QTCHARTS_BUILD_DIR}/
)


