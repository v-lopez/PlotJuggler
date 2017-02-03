
SET (SOURCES
    abstractdomain.cpp
    polardomain.cpp
    xydomain.cpp
    xypolardomain.cpp
    xlogydomain.cpp
    xlogypolardomain.cpp
    logxydomain.cpp
    logxypolardomain.cpp
    logxlogydomain.cpp
    logxlogypolardomain.cpp
    )

SET (PRIVATE_HEADERS
    abstractdomain_p.h
    polardomain_p.h
    xydomain_p.h
    xypolardomain_p.h
    xlogydomain_p.h
    xlogypolardomain_p.h
    logxydomain_p.h
    logxypolardomain_p.h
    logxlogydomain_p.h
    logxlogypolardomain_p.h
    )

file(COPY ${PRIVATE_HEADERS}  DESTINATION  ${QTCHARTS_BUILD_DIR}/QtCharts/private )

add_library( domain OBJECT ${PRIVATE_HEADERS} ${SOURCES})

target_include_directories( domain PRIVATE
    ./
    ${QTCHARTS_BUILD_DIR}/QtCharts
    ${QTCHARTS_BUILD_DIR}/
)
