

SET( SOURCES
    xychart.cpp
    qxyseries.cpp
    qxymodelmapper.cpp
    qvxymodelmapper.cpp
    qhxymodelmapper.cpp
    glxyseriesdata.cpp
    )

SET( PRIVATE_HEADERS
    xychart_p.h
    qxyseries_p.h
    qxymodelmapper_p.h
    glxyseriesdata_p.h
    )

SET( PUBLIC_HEADERS
    qxyseries.h
    qxymodelmapper.h
    qvxymodelmapper.h
    qhxymodelmapper.h
    )

file(COPY ${PRIVATE_HEADERS}  DESTINATION  ${QTCHARTS_BUILD_DIR}/QtCharts/private )
file(COPY ${PUBLIC_HEADERS}   DESTINATION  ${QTCHARTS_BUILD_DIR}/QtCharts )


add_library( xychart OBJECT ${PUBLIC_HEADERS} ${PRIVATE_HEADERS} ${SOURCES})

target_include_directories( xychart PRIVATE
    ./
    ${QTCHARTS_BUILD_DIR}/QtCharts
    ${QTCHARTS_BUILD_DIR}/
)
