cmake_minimum_required(VERSION 3.16)
project(learning_factory)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-lhttplib -lsqlite3")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../output)

set(PRECOMPILED_HEADER_FILES 
		../src/rapidcsv.h
		../src/logger.h
		../src/database.h
		../src/server.h)

set(HEADER_FILES )

set(SOURCE_FILES 
		../src/logger.cpp
		../src/database.cpp
		../src/server.cpp
		../src/main.cpp
		${PRECOMPILED_HEADER_FILES}
		${HEADER_FILES})


include_directories(src)
include_directories(src/compiled)

add_executable(learning_factory ${SOURCE_FILES})

target_precompile_headers(learning_factory PRIVATE ${PRECOMPILED_HEADER_FILES})
