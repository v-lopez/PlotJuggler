

SET( THEMES
    charttheme_p.h
    chartthemesystem_p.h
    chartthemelight_p.h
    chartthemebluecerulean_p.h
    chartthemedark_p.h
    chartthemebrownsand_p.h
    chartthemebluencs_p.h
    chartthemehighcontrast_p.h
    chartthemeblueicy_p.h
    chartthemeqt_p.h )

file(COPY ${THEMES}  DESTINATION  ${QTCHARTS_BUILD_DIR}/QtCharts/private )

include_directories(
    ${QTCHARTS_BUILD_DIR}/QtCharts
    ${QTCHARTS_BUILD_DIR}
    ${Qt5Widgets_INCLUDE_DIRS}
)



