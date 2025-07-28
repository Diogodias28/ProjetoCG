cmake_minimum_required(VERSION 3.5)

# Project Name
PROJECT(engine)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

add_executable(engine ../engine/engine.cpp)
add_executable(generator ../gen/generator.cpp)

add_library(
	data_structs
	../data_structs/Point.cpp
	../data_structs/Point.hpp
	../data_structs/Model.cpp
	../data_structs/Model.hpp
	../data_structs/Settings.cpp
	../data_structs/Settings.hpp
)

add_library(
	tinyXML
	../TinyXML/tinystr.cpp
	../TinyXML/tinyxmlerror.cpp
	../TinyXML/tinyxmlparser.cpp
	../TinyXML/tinystr.h
	../TinyXML/tinyxml.h
	../TinyXML/tinyxml.cpp
)

target_link_libraries(data_structs tinyXML)

target_link_libraries(generator data_structs)
target_link_libraries(engine data_structs tinyXML)

find_package(OpenGL REQUIRED)
include_directories(${OpenGL_INCLUDE_DIRS})
link_directories(${OpenGL_LIBRARY_DIRS})
add_definitions(${OpenGL_DEFINITIONS})

if(NOT OPENGL_FOUND)
    message(FATAL_ERROR "OpenGL not found!")
endif()

if (WIN32)
    message(STATUS "Toolkits_DIR set to: " ${TOOLKITS_FOLDER})
    set(TOOLKITS_FOLDER "" CACHE PATH "Path to Toolkits folder")

    if (NOT EXISTS "${TOOLKITS_FOLDER}/glut/GL/glut.h" OR NOT EXISTS "${TOOLKITS_FOLDER}/glut/glut32.lib")
        message(FATAL_ERROR "GLUT not found")
    endif()

    include_directories(${TOOLKITS_FOLDER}/glut)
    target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES} ${TOOLKITS_FOLDER}/glut/glut32.lib)

    if (EXISTS "${TOOLKITS_FOLDER}/glut/glut32.dll")
        file(COPY ${TOOLKITS_FOLDER}/glut/glut32.dll DESTINATION ${CMAKE_BINARY_DIR})
    endif()

    set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})

else() # Linux and Mac
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-deprecated -DGL_SILENCE_DEPRECATION")

    find_package(GLUT REQUIRED)
    include_directories(${GLUT_INCLUDE_DIRS})
    link_directories(${GLUT_LIBRARY_DIRS})
    add_definitions(${GLUT_DEFINITIONS})

    target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES})

    if(NOT GLUT_FOUND)
        message(FATAL_ERROR "GLUT not found!")
    endif()
endif()