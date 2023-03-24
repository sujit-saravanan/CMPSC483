cmake_minimum_required(VERSION 3.16)
project(learning_factory)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../output)

set(HEADER_FILES 
		../src/rapidcsv.h
		../src/httplib.h
		../src/rang.h
		../src/database.h
		../src/server.h
		../src/logger.h)

set(SOURCE_FILES 
		../src/main.cpp
		../src/logger.cpp
		../src/server.cpp
		../src/database.cpp
		${HEADER_FILES})


include_directories(src)

add_executable(learning_factory ${SOURCE_FILES})

target_precompile_headers(learning_factory PRIVATE ${HEADER_FILES})
