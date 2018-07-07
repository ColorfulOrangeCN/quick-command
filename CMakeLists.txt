cmake_minimum_required(VERSION 2.6)

project(quick-command)

aux_source_directory(./src SRC_DIR)

add_executable(qc ${SRC_DIR})
