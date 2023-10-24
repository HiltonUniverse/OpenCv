cmake_minimum_required(VERSION 3.4)

PROJECT(histogram)

set(OpenCV_DIR /Users/Hilton/Desktop/setup/build_opencv)
FIND_PACKAGE(OpenCV REQUIRED)

FIND_PACKAGE(Qt6 REQUIRED Quick)

ADD_EXECUTABLE(${PROJECT_NAME} main.cpp)
TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${OpenCV_LIBS} Qt6::Quick)
