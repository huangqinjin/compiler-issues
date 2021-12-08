cmake_minimum_required(VERSION 3.20)

set(WINDOWS_SDK "C:/Program Files (x86)/Microsoft SDKs/Windows/v7.1A/")
set(ENV{PATH} "${WINDOWS_SDK}Bin;$ENV{PATH}")

project(XpConCRT)

# On Windows XP, ConCRT initialization during DLL loading causes Loader Deadlock
# To avoid this issue, delay loading the dll and initialize ConCRT in main().
option(DELAY "Delay Loading DLL" ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


include(CMakePrintHelpers)

cmake_print_variables(
    DELAY
    CMAKE_GENERATOR
    MSVC
    MSVC_VERSION
    CMAKE_CXX_COMPILER
    CMAKE_CXX_COMPILER_VERSION
    CMAKE_GENERATOR_PLATFORM
    CMAKE_VS_PLATFORM_NAME
    CMAKE_GENERATOR_TOOLSET
    CMAKE_VS_PLATFORM_TOOLSET
    CMAKE_VS_PLATFORM_TOOLSET_HOST_ARCHITECTURE
    CMAKE_VS_PLATFORM_TOOLSET_VERSION
    CMAKE_CXX_LINKER_WRAPPER_FLAG
    CMAKE_CXX_LINKER_WRAPPER_FLAG_SEP
)

if(NOT CMAKE_CXX_COMPILER_VERSION VERSION_LESS 19.20)
    message(WARNING "Visual Studio 2019+ may not support Windows XP")
endif()

add_compile_definitions(_WIN32_WINNT=0x0501)

if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(SUBSYSTEM_VERSION 5.02)
else()
    set(SUBSYSTEM_VERSION 5.01)
endif()

if(NOT CMAKE_VS_PLATFORM_TOOLSET MATCHES [[_xp$]])
    # "C:\Program Files (x86)\Microsoft Visual Studio\2019\Enterprise\VC\Auxiliary\Build\vcvarsall.bat" x64_x86 -vcvars_ver=14.16
    include_directories(${WINDOWS_SDK}Include)
    link_directories(${WINDOWS_SDK}Lib)
    add_compile_definitions(_USING_V110_SDK71_)
    add_link_options(LINKER:SHELL:/SUBSYSTEM:CONSOLE,${SUBSYSTEM_VERSION})
else()
    # Need to install the following Visual Studio 2019 Components
    #  1. C++ Windows XP Support for VS 2017 (v141) tools
    #  2. MSVC v141 - VS 2017 C++ x64/x86 build tools (v14.16)
    
    # cmake .. -G"Visual Studio 16 2019" -AWin32 -Tv141_xp,host=x64
    # cmake --build . --config RelWithDebInfo
endif()


add_library(${PROJECT_NAME}Init SHARED init.cpp)
add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE ${PROJECT_NAME}Init)

if(DELAY)
    target_link_libraries(${PROJECT_NAME} PRIVATE delayimp)
    target_link_options(${PROJECT_NAME} PRIVATE LINKER:/DELAYLOAD:$<TARGET_FILE_NAME:${PROJECT_NAME}Init>)
endif()

enable_testing()
add_test(NAME "Init ConCRT in DLL" COMMAND ${PROJECT_NAME} 0)
add_test(NAME "Init ConCRT in main" COMMAND ${PROJECT_NAME} 1)
