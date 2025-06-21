cmake_minimum_required(VERSION 3.15)
project(IngestionService CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Path to locally installed protobuf + grpc
list(APPEND CMAKE_PREFIX_PATH "${CMAKE_SOURCE_DIR}/../../grpc/install")

# Find packages
find_package(Protobuf REQUIRED)
find_package(gRPC REQUIRED)

# Include directories
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${Protobuf_INCLUDE_DIRS})
include_directories(${gRPC_INCLUDE_DIRS})

# Protobuf + gRPC generated source files
set(PROTO_SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/permit.pb.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/permit.grpc.pb.cc
)

set(SERVICE_SRCS
    src/ingestion_service.cpp
    src/main.cpp
)

# Define the executable
add_executable(ingestion_service
    ${PROTO_SRCS}
    ${SERVICE_SRCS}
)

# Target include directories for cleaner includes
target_include_directories(ingestion_service PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# Link libraries
target_link_libraries(ingestion_service
    protobuf::libprotobuf
    gRPC::grpc++
)
