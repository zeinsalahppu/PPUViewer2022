cmake_minimum_required(VERSION 3.0.2)

project(PPUViewer)

INCLUDE_DIRECTORIES (
   D:/Develope/Libs/Glut/include
)

find_package(Qt6 COMPONENTS Core Gui Widgets OpenGL OpenGLWidgets REQUIRED)

find_package(OpenGL)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

SET( PPUViewer_SRCS
   main.cpp   
   PPUViewer.cpp
   PPUViewer.h
   RenderWidget.cpp
   RenderWidget.h
)

LINK_LIBRARIES(
   D:/Develope/Libs/Glut/Lib/glut32.lib
   ${OPENGL_glu_LIBRARY}
   ${OPENGL_LIBRARY}
)

add_executable(PPUViewer ${PPUViewer_SRCS})

target_link_libraries(PPUViewer PRIVATE Qt::Core Qt::Widgets Qt::OpenGL Qt::OpenGLWidgets ${OPENGL_LIBRARIES})
