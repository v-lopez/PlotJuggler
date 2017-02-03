SET( SOURCES
    areachartitem.cpp
    qareaseries.cpp
    )
    
set ( PRIVATE_HEADERS
    areachartitem_p.h
    qareaseries_p.h
    )
    
SET( PUBLIC_HEADERS
    qareaseries.h
    )

file(COPY ${PRIVATE_HEADERS}  DESTINATION  ${QTCHARTS_BUILD_DIR}/QtCharts/private )
file(COPY ${PUBLIC_HEADERS}   DESTINATION  ${QTCHARTS_BUILD_DIR}/QtCharts )

add_library( areachart OBJECT ${PUBLIC_HEADERS} ${PRIVATE_HEADERS} ${SOURCES})

target_include_directories( areachart PRIVATE
    ./
    ${QTCHARTS_BUILD_DIR}/QtCharts
    ${QTCHARTS_BUILD_DIR}/
)
