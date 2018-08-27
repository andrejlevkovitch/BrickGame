# cmake

find_package(Qt5Widgets REQUIRED)

set(CMAKE_AUTORCC ON)

set(QRES_LIB "q_res")
set(QRES_SRC "qresources.qrc")
set(LIST_TARGETS "${LIST_TARGETS};${QRES_LIB}" CACHE STRING "add datas" FORCE)

add_library(${QRES_LIB} ${QRES_SRC})
