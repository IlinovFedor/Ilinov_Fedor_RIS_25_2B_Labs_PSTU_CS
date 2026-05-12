cmake_minimum_required(VERSION 4.2)
project(QTGraphVisualization)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


find_package(Qt6 COMPONENTS
  Core
  Gui
  Widgets
  REQUIRED)

add_executable(QTGraphVisualization main.cpp
        MainWindow.cpp
        MainWindow.h
        Graph.cpp
        Graph.h
        UiVertex.cpp
        UiVertex.h
        UiEdge.cpp
        UiEdge.h
        GraphWorker.cpp
        GraphWorker.h
        MatrixEditor.cpp
        MatrixEditor.h)
target_link_libraries(QTGraphVisualization
  Qt::Core
  Qt::Gui
  Qt::Widgets
)

