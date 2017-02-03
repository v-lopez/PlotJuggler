
include_directories( ./
    valueaxis
    barcategoryaxis
    categoryaxis
    logvalueaxis
    datetimeaxis
    )

SET( SOURCES
    chartaxiselement.cpp
    cartesianchartaxis.cpp
    qabstractaxis.cpp
    verticalaxis.cpp
    horizontalaxis.cpp
    valueaxis/chartvalueaxisx.cpp
    valueaxis/chartvalueaxisy.cpp
    valueaxis/qvalueaxis.cpp
    barcategoryaxis/chartbarcategoryaxisx.cpp
    barcategoryaxis/chartbarcategoryaxisy.cpp
    barcategoryaxis/qbarcategoryaxis.cpp
    categoryaxis/chartcategoryaxisx.cpp
    categoryaxis/chartcategoryaxisy.cpp
    categoryaxis/qcategoryaxis.cpp
    logvalueaxis/chartlogvalueaxisx.cpp
    logvalueaxis/chartlogvalueaxisy.cpp
    logvalueaxis/qlogvalueaxis.cpp
    )

SET( PRIVATE_HEADERS
    chartaxiselement_p.h
    cartesianchartaxis_p.h
    qabstractaxis_p.h
    verticalaxis_p.h
    horizontalaxis_p.h
    linearrowitem_p.h
    valueaxis/chartvalueaxisx_p.h
    valueaxis/chartvalueaxisy_p.h
    valueaxis/qvalueaxis_p.h
    barcategoryaxis/chartbarcategoryaxisx_p.h
    barcategoryaxis/chartbarcategoryaxisy_p.h
    barcategoryaxis/qbarcategoryaxis_p.h
    categoryaxis/chartcategoryaxisx_p.h
    categoryaxis/chartcategoryaxisy_p.h
    categoryaxis/qcategoryaxis_p.h
    logvalueaxis/chartlogvalueaxisx_p.h
    logvalueaxis/chartlogvalueaxisy_p.h
    logvalueaxis/qlogvalueaxis_p.h
    )

SET (PUBLIC_HEADERS
    qabstractaxis.h
    valueaxis/qvalueaxis.h
    barcategoryaxis/qbarcategoryaxis.h
    categoryaxis/qcategoryaxis.h
    logvalueaxis/qlogvalueaxis.h
    )

SET (SOURCES ${SOURCES}
    datetimeaxis/chartdatetimeaxisx.cpp
    datetimeaxis/chartdatetimeaxisy.cpp
    datetimeaxis/qdatetimeaxis.cpp
    datetimeaxis/polarchartdatetimeaxisangular.cpp
    datetimeaxis/polarchartdatetimeaxisradial.cpp
     )

SET (PRIVATE_HEADERS ${PRIVATE_HEADERS}
    datetimeaxis/chartdatetimeaxisx_p.h
    datetimeaxis/chartdatetimeaxisy_p.h
    datetimeaxis/qdatetimeaxis_p.h
    datetimeaxis/polarchartdatetimeaxisangular_p.h
    datetimeaxis/polarchartdatetimeaxisradial_p.h
     )

SET (PUBLIC_HEADERS ${PUBLIC_HEADERS}
    datetimeaxis/qdatetimeaxis.h
    )

SET (SOURCES ${SOURCES}
   polarchartaxis.cpp
   polarchartaxisangular.cpp
   polarchartaxisradial.cpp
   valueaxis/polarchartvalueaxisangular.cpp
   valueaxis/polarchartvalueaxisradial.cpp
   logvalueaxis/polarchartlogvalueaxisangular.cpp
   logvalueaxis/polarchartlogvalueaxisradial.cpp
   categoryaxis/polarchartcategoryaxisangular.cpp
   categoryaxis/polarchartcategoryaxisradial.cpp
)

SET (PRIVATE_HEADERS ${PRIVATE_HEADERS}
   polarchartaxis_p.h
   polarchartaxisangular_p.h
   polarchartaxisradial_p.h
   valueaxis/polarchartvalueaxisangular_p.h
   valueaxis/polarchartvalueaxisradial_p.h
   logvalueaxis/polarchartlogvalueaxisangular_p.h
   logvalueaxis/polarchartlogvalueaxisradial_p.h
   categoryaxis/polarchartcategoryaxisangular_p.h
   categoryaxis/polarchartcategoryaxisradial_p.h
)

file(COPY ${PRIVATE_HEADERS}  DESTINATION  ${QTCHARTS_BUILD_DIR}/QtCharts/private )
file(COPY ${PUBLIC_HEADERS}   DESTINATION  ${QTCHARTS_BUILD_DIR}/QtCharts )


add_library( axis OBJECT ${PUBLIC_HEADERS} ${PRIVATE_HEADERS} ${SOURCES})

target_include_directories( axis BEFORE PRIVATE
    ./
    ${QTCHARTS_BUILD_DIR}/QtCharts
    ${QTCHARTS_BUILD_DIR}/
)
