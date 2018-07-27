
cmake_minimum_required(VERSION 3.8 FATAL_ERROR)

set(CMAKE_SYSTEM_VERSION 8.1)

project(MeshAnalyser)

find_package(Qt5 REQUIRED
    Core
    Gui
    Widgets
)




file(GLOB_RECURSE SOURCES
	${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/*.h
	${CMAKE_CURRENT_SOURCE_DIR}/*.qrc
	${CMAKE_CURRENT_SOURCE_DIR}/*.ui)
	
add_executable(MeshAnalyser WIN32 ${SOURCES})

target_link_libraries(MeshAnalyser Qt5::Widgets Qt5::Core)

set_target_properties(MeshAnalyser PROPERTIES
							AUTOMOC ON
							AUTOUIC ON
							AUTORCC ON)