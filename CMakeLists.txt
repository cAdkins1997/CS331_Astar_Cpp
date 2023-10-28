cmake_minimum_required(VERSION 3.26)
project(AStarShortestPath)

set(CMAKE_CXX_STANDARD 23)

add_executable(AStarShortestPath source/main.cpp
        source/Node.h
        source/NodeGrid.h
        source/Pathfinding.h
        source/aStarUtility.h
)
