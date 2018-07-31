
cmake_minimum_required(VERSION 3.8 FATAL_ERROR)

set(CMAKE_SYSTEM_VERSION 8.1)

project(MeshAnalyser)

find_package(Qt5 REQUIRED
    Core
    Gui
    Widgets
	3DRender
	3DExtras
	openGL
)

find_package(OpenGL REQUIRED)

include_directories( ${OPENGL_INCLUDE_DIRS})

ADD_LIBRARY( LogicLib STATIC
             LogicLib/logic.cpp )

file(GLOB MESHSOURCES
	${CMAKE_CURRENT_SOURCE_DIR}/Mesh/*.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/Mesh/*.h
	${CMAKE_CURRENT_SOURCE_DIR}/Mesh/*.qrc
	${CMAKE_CURRENT_SOURCE_DIR}/Mesh/*.ui)

file(GLOB TESTSOURCES
	${CMAKE_CURRENT_SOURCE_DIR}/Tests/*.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/Tests/*.h
	${CMAKE_CURRENT_SOURCE_DIR}/Tests/*.qrc
	${CMAKE_CURRENT_SOURCE_DIR}/Tests/*.ui)

add_executable(MeshAnalyser WIN32 ${MESHSOURCES})

add_executable(Tester ${TESTSOURCES})

target_link_libraries(MeshAnalyser Qt5::Widgets Qt5::Core Qt5::3DRender Qt5::OpenGL Qt5::3DExtras LogicLib ${OPENGL_LIBRARIES}) 

target_link_libraries(Tester LogicLib)

target_link_libraries(LogicLib Qt5::Widgets Qt5::Core Qt5::3DRender Qt5::OpenGL Qt5::3DExtras)

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
