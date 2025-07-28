cmake_minimum_required(VERSION 3.10)

# Project Name
PROJECT(engine)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

add_executable(engine ../engine/engine.cpp)
add_executable(generator 
    ../gen/generator.cpp
    ../gen/primitives/cone.cpp
    ../gen/primitives/cone.hpp
    ../gen/primitives/box.cpp
    ../gen/primitives/box.hpp
    ../gen/primitives/plane.cpp
    ../gen/primitives/plane.hpp
    ../gen/primitives/sphere.cpp
    ../gen/primitives/sphere.hpp
    ../gen/primitives/ring.cpp
    ../gen/primitives/ring.hpp
    ../gen/primitives/bezierPatches.cpp
    ../gen/primitives/bezierPatches.hpp
    )

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
    ../data_structs/Light.cpp
    ../data_structs/Light.hpp
    ../data_structs/Color.cpp
    ../data_structs/Color.hpp
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
    if (NOT EXISTS "${TOOLKITS_FOLDER}/glew/glew32.lib" OR NOT EXISTS "${TOOLKITS_FOLDER}/glew/GL/glew.h")
        message(FATAL_ERROR "GLEW not found")
    endif()
    if (NOT EXISTS "${TOOLKITS_FOLDER}/devil/DevIL.lib" OR NOT EXISTS "${TOOLKITS_FOLDER}/devil/IL/il.h")
        message(FATAL_ERROR "DevIL not found")
    endif()

    include_directories(
        ${TOOLKITS_FOLDER}/glut
        ${TOOLKITS_FOLDER}/glew
        ${TOOLKITS_FOLDER}/devil
        )

    target_link_libraries(engine 
        ${OPENGL_LIBRARIES} 
        ${TOOLKITS_FOLDER}/glut/glut32.lib
        ${TOOLKITS_FOLDER}/glew/glew32.lib
        ${TOOLKITS_FOLDER}/devil/DevIL.lib
        )

    target_link_libraries(generator 
        ${OPENGL_LIBRARIES} 
        ${TOOLKITS_FOLDER}/glut/glut32.lib)

    if (EXISTS "${TOOLKITS_FOLDER}/glut/glut32.dll")
        file(COPY ${TOOLKITS_FOLDER}/glut/glut32.dll DESTINATION ${CMAKE_BINARY_DIR})
    endif()
    if (EXISTS "${TOOLKITS_FOLDER}/glew/glew32.dll")
        file(COPY ${TOOLKITS_FOLDER}/glew/glew32.dll DESTINATION ${CMAKE_BINARY_DIR})
    endif()
    if (EXISTS "${TOOLKITS_FOLDER}/devil/DevIL.dll")
        file(COPY ${TOOLKITS_FOLDER}/devil/DevIL.dll DESTINATION ${CMAKE_BINARY_DIR})
    endif()

    set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT engine)
else() # Linux and Mac

    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-deprecated")
    
    find_package(GLUT REQUIRED)
    find_package(GLEW REQUIRED)
    find_package(DevIL REQUIRED)

    include_directories(
        ${GLUT_INCLUDE_DIR}
        )
    
    if(NOT GLUT_FOUND)
        message(FATAL_ERROR "GLUT not found!")
    endif()

    if(APPLE)
        include_directories(/opt/homebrew/include)
        link_directories(/opt/homebrew/lib)
        
        find_library(IL_LIBRARY NAMES IL PATHS /opt/homebrew/lib REQUIRED)
        find_library(ILU_LIBRARY NAMES ILU PATHS /opt/homebrew/lib REQUIRED)
        find_library(ILUT_LIBRARY NAMES ILUT PATHS /opt/homebrew/lib REQUIRED)

        if(TARGET GLEW::GLEW)
            target_link_libraries(engine 
                ${OPENGL_LIBRARIES} 
                "-framework GLUT"
                "-framework OpenGL"
                GLEW::GLEW
                ${IL_LIBRARY}
                ${ILU_LIBRARY}
                ${ILUT_LIBRARY}
                )
        else()
            include_directories(${GLEW_INCLUDE_DIRS})
            target_link_libraries(engine 
                ${OPENGL_LIBRARIES} 
                "-framework GLUT"
                "-framework OpenGL"
                ${GLEW_LIBRARIES}
                ${IL_LIBRARY}
                ${ILU_LIBRARY}
                ${ILUT_LIBRARY}
            )
        endif()

        target_link_libraries(generator 
            ${OPENGL_LIBRARIES} 
            "-framework GLUT"
            "-framework OpenGL"
            ${IL_LIBRARY}
            ${ILU_LIBRARY}
            ${ILUT_LIBRARY}
            )
    else()
        include_directories(
            ${GLEW_INCLUDE_DIRS}
            ${IL_INCLUDE_DIR}
        )
        
        if(NOT GLEW_FOUND)
            message(FATAL_ERROR "GLEW not found!")
        endif()
        if(NOT IL_FOUND)
            message(FATAL_ERROR "DevIL not found!")
        endif()

        target_link_libraries(engine 
            ${OPENGL_LIBRARIES} 
            ${GLUT_LIBRARIES}
            ${GLEW_LIBRARIES}
            ${IL_LIBRARIES}
            )
        target_link_libraries(generator ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES})
    endif()
endif()

target_link_libraries(generator data_structs)
target_link_libraries(engine data_structs tinyXML)