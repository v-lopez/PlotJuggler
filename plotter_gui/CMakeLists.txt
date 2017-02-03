
include_directories( ./ ../  ../include  ../common)

QT5_ADD_RESOURCES (RES_SRC  resource.qrc)

QT5_WRAP_UI ( UI_SRC
    mainwindow.ui
    removecurvedialog.ui
    busydialog.ui
    curvecolorpick.ui
    filterablelistwidget.ui
    tabbedplotwidget.ui
    ../common/selectlistdialog.ui
    )

SET( PLOTTER_SRC
    busydialog.cpp
    busytaskdialog.cpp
    curvecolorpick.cpp
    main.cpp
    mainwindow.cpp
    filterablelistwidget.cpp
    plotmatrix.cpp
    removecurvedialog.cpp
    tabbedplotwidget.cpp
    subwindow.cpp
    plotwidget.cpp
    plotcurve.cpp

    customtracker.h
    plotcurve.h
    plotwidget.h
    plotlegend.h
    plotmagnifier.h
    plotzoomer.h

    ${IMPL_DIR}/customtracker.cpp
    ${IMPL_DIR}/plotcurve_impl.cpp
    ${IMPL_DIR}/plotgrid.cpp
    ${IMPL_DIR}/plotlegend.cpp
    ${IMPL_DIR}/plotmagnifier.cpp
    ${IMPL_DIR}/plotwidget_impl.cpp
    ${IMPL_DIR}/plotzoomer.cpp

    ../common/selectlistdialog.h
    ../include/PlotJuggler/plotdata.h
    )

add_executable(PlotJuggler ${PLOTTER_SRC} ${RES_SRC} ${UI_SRC})


target_link_libraries(PlotJuggler
    ${Qt5Core_QTMAIN_LIBRARIES}
    ${Qt5Widgets_LIBRARIES}
    ${Qt5PrintSupport_LIBRARIES}
    ${Qt5Xml_LIBRARIES}
    ${Qt5Concurrent_LIBRARIES}
    colorwidgets
    ${CHART_LIB}
    )

if(catkin_FOUND)
    install(TARGETS PlotJuggler
        ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
        LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
        RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
        )
else()
    install(TARGETS PlotJuggler DESTINATION bin  )
endif()
