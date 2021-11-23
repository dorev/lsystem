project(Tests)

add_executable(${PROJECT_NAME}
    main.cpp
    tests.cpp
)

target_include_directories(${PROJECT_NAME}
    PUBLIC ${CMAKE_SOURCE_DIR}/lsystem/include
    PUBLIC gtest
    PUBLIC gtest/include
    PUBLIC gmock
    PUBLIC gmock/include
)

target_link_libraries(${PROJECT_NAME} LSystem)