

SET( SOURCES
    linechartitem.cpp
    qlineseries.cpp 
    )
    
SET( PRIVATE_HEADERS
    linechartitem_p.h
    qlineseries_p.h
    )
    
SET( PUBLIC_HEADERS    
    qlineseries.h  
    )

file(COPY ${PRIVATE_HEADERS}  DESTINATION  ${QTCHARTS_BUILD_DIR}/QtCharts/private )
file(COPY ${PUBLIC_HEADERS}   DESTINATION  ${QTCHARTS_BUILD_DIR}/QtCharts )


add_library( linechart OBJECT ${PUBLIC_HEADERS} ${PRIVATE_HEADERS} ${SOURCES})

target_include_directories( linechart PRIVATE
    ./
    ${QTCHARTS_BUILD_DIR}/QtCharts
    ${QTCHARTS_BUILD_DIR}/
)
