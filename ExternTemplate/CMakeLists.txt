cmake_minimum_required(VERSION 3.21)
project(ExternTemplate)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_VISIBILITY_PRESET hidden)
set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

macro(definition option) # doc default
    option(${ARGV})
    message(STATUS "${option} ${${option}}")
    if(${option})
        # -D or this set the macro to 1 (not only define it)
        add_compile_definitions(${option})
    endif()
endmacro()


definition(MODULE "Build as C++20 module" OFF)
definition(EXTERN "Explicit instantiation declaration" OFF)
definition(CLASS "Use class template instead of function template" OFF)
definition(INLINE "Define member function inside class" OFF)
definition(SHARED "Build shared library" OFF)
set(BUILD_SHARED_LIBS ${SHARED})

add_library(Calculator
    SumDefault.cpp
)

if(MODULE)
    target_sources(Calculator PRIVATE Calculator.ixx)
else()
    target_sources(Calculator PRIVATE Calculator.cpp)
endif()

get_target_property(TYPE Calculator TYPE)
target_compile_definitions(Calculator PUBLIC Calculator_${TYPE} PRIVATE Calculator_EXPORTS)


add_executable(${PROJECT_NAME}
    CalculatorTest.cpp
)

target_link_libraries(${PROJECT_NAME} PUBLIC Calculator)

file(GENERATE OUTPUT $<CONFIG>/object-files.txt CONTENT "$<TARGET_OBJECTS:Calculator>;$<TARGET_OBJECTS:${PROJECT_NAME}>")

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_LIST_DIR}/stat.cmake
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/$<CONFIG>
)
