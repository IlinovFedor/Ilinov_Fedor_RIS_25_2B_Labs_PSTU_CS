cmake_minimum_required(VERSION 4.2)
project(QTBSTVisualization)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


find_package(Qt6 COMPONENTS
  Core
  Gui
  Widgets
  REQUIRED)

add_executable(QTBSTVisualization main.cpp
        MainWindow.cpp
        MainWindow.h
        BST.cpp
        BST.h
        UiVertex.cpp
        UiVertex.h
        GraphWorker.cpp
        GraphWorker.h
)
target_link_libraries(QTBSTVisualization
  Qt::Core
  Qt::Gui
  Qt::Widgets
)
