cmake_minimum_required(VERSION 3.15)

project(chickengame)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(PROJECT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(PROJECT_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set(PROJECT_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR})

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB_RECURSE SOURCES ${PROJECT_SOURCE_DIR}/src/*.cpp)
add_executable(${PROJECT_NAME} ${SOURCES}
        include/TextureEnumImplementation.h
)

add_subdirectory(engine)

target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_INCLUDE_DIR})

target_link_libraries(${PROJECT_NAME} PRIVATE
    #SDL2::SDL2main # this fixes compilation issues on windows... but why?
    engine
)

if(CMAKE_BUILD_TYPE MATCHES "Debug")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
endif()

if(EXISTS ${PROJECT_SOURCE_DIR}/assets)
    file(COPY ${PROJECT_SOURCE_DIR}/assets DESTINATION ${PROJECT_BINARY_DIR})
endif()

# link/copy compile commands to root dir
if(EXISTS ${PROJECT_BINARY_DIR}/compile_commands.json)
    file(CREATE_LINK
        ${PROJECT_BINARY_DIR}/compile_commands.json
        ${PROJECT_SOURCE_DIR}/compile_commands.json
        COPY_ON_ERROR SYMBOLIC
    )
endif()