
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

set(IMPL_DIR impl_qtcharts)

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

    customtracker.h
    plotcurve.h
    plotseries.h
    plotwidget.h

    plotwidget.cpp

    plotlegend.h
    plotmagnifier.h

  #  ${IMPL_DIR}/plotzoomer.h

  #  ${IMPL_DIR}/customtracker.cpp
  #  ${IMPL_DIR}/plotcurve.cpp
  #  ${IMPL_DIR}/plotlegend.cpp
  #  ${IMPL_DIR}/plotseries.cpp
  #  ${IMPL_DIR}/plotmagnifier.cpp
 #   ${IMPL_DIR}/plotwidget.cpp
 #   ${IMPL_DIR}/plotzoomer.cpp

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
    qtcharts
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
