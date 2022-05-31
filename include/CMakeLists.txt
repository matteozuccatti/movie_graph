add_library(SQL_parser "${PROJECT_SOURCE_DIR}/src/SQL_parser.cpp")
add_library(actors "${PROJECT_SOURCE_DIR}/src/actors.cpp")
add_library(canvas  "${PROJECT_SOURCE_DIR}/src/canvas.cpp")


find_package(PkgConfig)
pkg_check_modules(GTKMM gtkmm-3.0)

target_include_directories(canvas PRIVATE ${GTKMM_INCLUDE_DIRS})
target_link_directories(canvas PRIVATE ${GTKMM_LIBRARY_DIRS})
target_link_libraries(canvas PRIVATE ${GTKMM_LIBRARIES})

