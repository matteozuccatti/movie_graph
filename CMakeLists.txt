cmake_minimum_required(VERSION 3.16.3)
project(movie_graph VERSION 1.0)

# ADD SUBDIRECTORY
add_subdirectory(include)

# ADD EXE
add_executable(${PROJECT_NAME} main.cpp)
# LET CMAKE LOOK FOR LIBRARIES INSIDE THIS FOLDER 
target_include_directories(${PROJECT_NAME} PUBLIC include)

# LINK THE NEW LIBRARY TO THE MAIN EXECUTABLE 

find_package(PkgConfig)
pkg_check_modules(GTKMM gtkmm-3.0)


target_include_directories(${PROJECT_NAME}  PRIVATE ${GTKMM_INCLUDE_DIRS})
target_link_directories(${PROJECT_NAME}  PRIVATE ${GTKMM_LIBRARY_DIRS})
target_link_libraries(${PROJECT_NAME}  PRIVATE ${GTKMM_LIBRARIES})

target_link_libraries(
  ${PROJECT_NAME} PUBLIC 
  SQL_parser canvas actors mysqlclient )