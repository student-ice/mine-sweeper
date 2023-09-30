project(minesweeper LANGUAGES C)
cmake_minimum_required(VERSION 3.10)

include_directories(./)

aux_source_directory(./ SOURCES)

add_executable(${PROJECT_NAME} ${SOURCES})