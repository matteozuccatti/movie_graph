cmake_minimum_required(VERSION 3.16.3)
project(movie_graph VERSION 1.0)
add_executable(${PROJECT_NAME} main.cpp)

# ADD SUBDIRECTORY
add_subdirectory(include)
# LET CMAKE LOOK FOR LIBRARIES INSIDE THIS FOLDER 
target_include_directories(${PROJECT_NAME} PUBLIC include)

# LINK THE NEW LIBRARY TO THE MAIN EXECUTABLE 
target_link_libraries(${PROJECT_NAME} PUBLIC SQL_parser mysqlclient)
#target_link_libraries(${PROJECT_NAME} mysqlclient)
