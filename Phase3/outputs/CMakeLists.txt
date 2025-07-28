cmake_minimum_required(VERSION 3.10)

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
    ../data_structs/Group.cpp
    ../data_structs/Group.hpp
    ../data_structs/Transform.cpp
    ../data_structs/Transform.hpp
    ../data_structs/Matrix.cpp
    ../data_structs/Matrix.hpp
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

find_package(OpenGL REQUIRED)
include_directories(${OpenGL_INCLUDE_DIRS})
link_directories(${OpenGL_LIBRARY_DIRS})
add_definitions(${OpenGL_DEFINITIONS})

if (WIN32)
    set(TOOLKITS_FOLDER "${CMAKE_SOURCE_DIR}/toolkits/toolkits")
    message(STATUS "Toolkits_DIR set to: " ${TOOLKITS_FOLDER})

    if (NOT EXISTS "${TOOLKITS_FOLDER}/glut/GL/glut.h" OR NOT EXISTS "${TOOLKITS_FOLDER}/glut/glut32.lib")
        message(FATAL_ERROR "GLUT not found")
    endif()

    include_directories(${TOOLKITS_FOLDER}/glut)
    target_link_libraries(engine ${OPENGL_LIBRARIES} ${TOOLKITS_FOLDER}/glut/glut32.lib)
    target_link_libraries(generator ${OPENGL_LIBRARIES} ${TOOLKITS_FOLDER}/glut/glut32.lib)

    if (EXISTS "${TOOLKITS_FOLDER}/glut/glut32.dll")
        file(COPY ${TOOLKITS_FOLDER}/glut/glut32.dll DESTINATION ${CMAKE_BINARY_DIR})
    endif()

    set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT engine)
else() # Linux and Mac

    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-deprecated")
    
    find_package(GLUT REQUIRED)
    include_directories(${GLUT_INCLUDE_DIR})
    
    if(NOT GLUT_FOUND)
        message(FATAL_ERROR "GLUT not found!")
    endif()

    if(APPLE)
        target_link_libraries(engine ${OPENGL_LIBRARIES} "-framework GLUT")
        target_link_libraries(generator ${OPENGL_LIBRARIES} "-framework GLUT")
    else()
        target_link_libraries(engine ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES})
        target_link_libraries(generator ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES})
    endif()
endif()

target_link_libraries(generator data_structs)
target_link_libraries(engine data_structs tinyXML)