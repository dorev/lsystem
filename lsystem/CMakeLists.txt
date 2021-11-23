project(LSystem C CXX)

file(GLOB_RECURSE
    SOURCES
    *.h
    *.cpp
)

add_library(${PROJECT_NAME} STATIC
    ${SOURCES}
)

target_include_directories(${PROJECT_NAME}
    PUBLIC include/lsystem
)