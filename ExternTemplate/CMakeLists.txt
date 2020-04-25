cmake_minimum_required(VERSION 3.16)
project(ExternTemplate)

set(CMAKE_CXX_STANDARD 17)
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


definition(EXTERN "Explicit instantiation declaration" OFF)
definition(CLASS "Use class template instead of function template" OFF)
definition(INLINE "Define member function inside class" OFF)
definition(SHARED "Build shared library" OFF)
set(BUILD_SHARED_LIBS ${SHARED})

add_subdirectory(Calculator)


add_executable(${PROJECT_NAME}
    CalculatorTest.cpp
)

target_link_libraries(${PROJECT_NAME} PUBLIC Calculator)
