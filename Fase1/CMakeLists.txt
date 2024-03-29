cmake_minimum_required(VERSION 3.5)

project(engine)

find_package(GLUT REQUIRED)
include_directories(${GLUT_INCLUDE_DIR})
link_directories(${GLUT_LIBRARY_DIRS})
add_definitions(${GLUT_DEFINITIONS})

if(NOT GLUT_FOUND)
	message(ERROR " GLUT not found!")
endif(NOT GLUT_FOUND)


if  (WIN32)

	message(STATUS "GLUT_DIR set to: " ${GLUT_DIR})
	set(GLUT_DIR "" CACHE PATH "Path to GLUT folder")
	if (NOT EXISTS "${GLUT_DIR}/GL/glut.h" OR NOT EXISTS "${GLUT_DIR}/glut32.lib")
		message(ERROR ": GLUT not found")
	endif (NOT EXISTS "${GLUT_DIR}/GL/glut.h" OR NOT EXISTS "${GLUT_DIR}/glut32.lib")
	include_directories(${GLUT_DIR})
	link_directories(${GLUT_DIR})
	target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES} ${GLUT_DIR}/glut32.lib )
	if (EXISTS "${GLUT_DIR}/glut32.dll")
		file(COPY ${GLUT_DIR}/glut32.dll DESTINATION ${CMAKE_BINARY_DIR})
	endif(EXISTS "${GLUT_DIR}/glut32.dll")
	set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})

else (WIN32) #Linux and Mac

	set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wno-deprecated")
	set_source_files_properties(${sources} PROPERTIES COMPILE_FLAGS
		"-xobjective-c -Wno-deprecated-declarations")
	find_package(OpenGL REQUIRED)
	include_directories(${OpenGL_INCLUDE_DIRS})
	link_directories(${OpenGL_LIBRARY_DIRS})
	add_definitions(${OpenGL_DEFINITIONS})

	if(NOT OPENGL_FOUND)
		message(ERROR " OPENGL not found!")
	endif(NOT OPENGL_FOUND)
endif(WIN32)

# Project Name
project(engine)

set(ENGINE_FILES ./src/main.cpp ./src/Plane.cpp ./src/Box.cpp ./src/Cone.cpp ./src/Sphere.cpp ./pugixml-1.9/src/pugixml.cpp)

add_executable(engine ${ENGINE_FILES})

target_link_libraries(engine ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} )

project(generator)
set(GENERATOR_FILES ./src/generator.cpp ./src/Plane.cpp ./src/Box.cpp ./src/Cone.cpp ./src/Sphere.cpp)

add_executable(generator ${GENERATOR_FILES} )
target_link_libraries(generator ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} )
