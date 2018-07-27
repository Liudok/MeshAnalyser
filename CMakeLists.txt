
cmake_minimum_required(VERSION 3.8 FATAL_ERROR)

set(CMAKE_SYSTEM_VERSION 8.1)

project(MeshAnalyser)

find_package(Qt5 REQUIRED
    Core
    Gui
    Widgets
	3DRender
	openGL
)




file(GLOB_RECURSE SOURCES
	${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/*.h
	${CMAKE_CURRENT_SOURCE_DIR}/*.qrc
	${CMAKE_CURRENT_SOURCE_DIR}/*.ui)
	
add_executable(MeshAnalyser WIN32 ${SOURCES})

target_link_libraries(MeshAnalyser Qt5::Widgets Qt5::Core Qt5::3DRender Qt5::OpenGL)

set_target_properties(MeshAnalyser PROPERTIES
							AUTOMOC ON
							AUTOUIC ON
							AUTORCC ON)
							
							
add_custom_command(TARGET MeshAnalyser
    		   POST_BUILD

    		   COMMAND    ${CMAKE_COMMAND}
    		   ARGS       -E copy $<TARGET_FILE:Qt5::Core> $<TARGET_FILE_DIR:MeshAnalyser>

    		   COMMAND    ${CMAKE_COMMAND}
    		   ARGS       -E copy $<TARGET_FILE:Qt5::Gui> $<TARGET_FILE_DIR:MeshAnalyser>

    		   COMMAND    ${CMAKE_COMMAND}
    		   ARGS       -E copy $<TARGET_FILE:Qt5::Widgets> $<TARGET_FILE_DIR:MeshAnalyser>

			   COMMAND    ${CMAKE_COMMAND}
    		   ARGS       -E copy $<TARGET_FILE:Qt5::3DRender> $<TARGET_FILE_DIR:MeshAnalyser>


    		   COMMAND    ${CMAKE_COMMAND}
    		   ARGS       -E make_directory $<TARGET_FILE_DIR:MeshAnalyser>/platforms
 
    		   COMMAND    ${CMAKE_COMMAND}
    		   ARGS       -E copy ${Qt5_DIR}/../../../plugins/platforms/qwindows$<$<CONFIG:DEBUG>:d>.dll $<TARGET_FILE_DIR:MeshAnalyser>/platforms)
