cmake_minimum_required(VERSION 3.16)
project(Calculator)

add_library(${PROJECT_NAME}
    Calculator.cpp
    SumDefault.cpp
)

get_target_property(TYPE ${PROJECT_NAME} TYPE)
target_compile_definitions(${PROJECT_NAME} PUBLIC ${PROJECT_NAME}_${TYPE} PRIVATE ${PROJECT_NAME}_EXPORTS)
