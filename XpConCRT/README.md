# Concurrency Runtime on Windows XP

In Visual Studio 2010, 2012 and 2013, the Concurrency Runtime was incorporated within `msvcr100.dll`, `msvcr110.dll` and 
`msvcr120.dll`, respectively. `concrt140.dll` is the Concurrency Runtime, shipped via Visual Studio 2015 and later. 
Required for parallel containers and algorithms such as `concurrency::parallel_for`. Also, the C++11 STL requires this 
DLL on Windows XP to power synchronization primitives, because Windows XP does not have condition variables.


### Loader Deadlock

A bug about ConCRT on Windows XP is that, initializing ConCRT during DLL loading will cause loader deadlock. ConCRT uses
`RegisterWaitForSingleObject` and it will create the thread pool for the first time (`QueueUserWorkItem` and 
`BindIoCompletionCallback` also create the thread pool). Creating the thread pool during DLL loading cause deadlock 
on Windows XP (only). To avoid this issue, delay loading the DLL and create the thread pool in main function.


### References

- [Concurrency Runtime implementation history](https://docs.microsoft.com/en-us/cpp/parallel/concrt/overview-of-the-concurrency-runtime#dlls)
- [Dynamic-Link Library Best Practices](https://docs.microsoft.com/en-us/windows/win32/dlls/dynamic-link-library-best-practices)
- [Windows XP thread pool](https://docs.microsoft.com/en-us/windows/win32/procthread/thread-pooling)
- [C++11 std::mutex in Visual Studio 2012 deadlock when locked from DllMain()](https://stackoverflow.com/questions/14711263)
- [Hang and loader lock on WinXP](https://github.com/weidai11/cryptopp/issues/373)
- [OpenCV core: Is GlobalLoggingInitCall necessary?](https://github.com/opencv/opencv/issues/21248)


## Windows XP Targeting in Visual Studio and CMake

Visual Studio 2012, 2013, 2015 and 2017 contain toolset `v110_xp`, `v120_xp` , `v140_xp` and `v141_xp`, respectively,
to target Windows XP. 

Visual Studio 2019 still supports targeting Windows XP by setting subsystem minimum version to 5.01 for x86 or 5.02 for 
x64 by using `/SUBSYSTEM` linker option. But the STL it shipped has removed Windows XP support. `14.27` is the last 
version that still supports Windows XP, but it is in "happens to work" territory, not "supported" territory.

CMake `CMAKE_GENERATOR_TOOLSET` doesn't support `CMAKE_VS_PLATFORM_TOOLSET_VERSION` at all when using `v141_xp`, i.e. 
the following command line will result in `invalid version specification`.

```shell
cmake -G"Visual Studio 16 2019" -AWin32 -Tv141_xp,host=x64,version=14.16
```

But without `version` specification, using `v141_xp` in Visual Studio 2019, it will always select the latest toolset 
installed (e.g. `14.28`, which doesn't support XP), unless toolset `14.16` is installed. To use tollset `v142,version=14.27`,
option `/SUBSYSTEM:CONSOLE,5.01` or `/SUBSYSTEM:CONSOLE,5.02` must be passed to linker when linking executables.


### References

- [Windows XP Targeting with C++ in Visual Studio 2012](https://devblogs.microsoft.com/cppblog/windows-xp-targeting-with-c-in-visual-studio-2012)
- [Configuring Programs for Windows XP](https://docs.microsoft.com/en-us/cpp/build/configuring-programs-for-windows-xp)
- [Remove XP (and Server 2003) support from STL.](https://github.com/microsoft/STL/pull/1194)
- https://github.com/microsoft/STL/pull/1200
- [Windows XP platform tools support in Visual studio 2019](https://developercommunity.visualstudio.com/t/windows-xp-platform-tools-support-in-visual-studio-2019/1196734)
- [CMake: Failed generating 2017 sln with -T v141_xp,version=14.15](https://gitlab.kitware.com/cmake/cmake/-/issues/19672)
- [CMake: Pass subsystem version](https://gitlab.kitware.com/cmake/cmake/-/issues/21300)
- [Specify the Windows subsystem targeted by the executable.](https://docs.microsoft.com/en-us/cpp/build/reference/subsystem-specify-subsystem)


## Windows XP Targeting in Vcpkg

Vcpkg doesn't support targeting Windows XP officially. To targeting Windows XP, a workable triplet `x86-xp.cmake` can be

```cmake
set(VCPKG_CMAKE_SYSTEM_VERSION 5.1)
set(VCPKG_TARGET_ARCHITECTURE x86)
set(VCPKG_CRT_LINKAGE dynamic)
set(VCPKG_LIBRARY_LINKAGE dynamic)
set(VCPKG_PLATFORM_TOOLSET_VERSION 14.27)  # The last toolset that supports targeting Windows XP
# set(VCPKG_PLATFORM_TOOLSET v141)  # Toolset 14.16 must be installed
set(VCPKG_C_FLAGS "/D_WIN32_WINNT=0x0501 /D_USING_V110_SDK71_ /I\\\"C:/Program Files (x86)/Microsoft SDKs/Windows/v7.1A/Include\\\"")
set(VCPKG_CXX_FLAGS ${VCPKG_C_FLAGS})
set(VCPKG_LINKER_FLAGS "/SUBSYSTEM:CONSOLE,5.01 /LIBPATH:\\\"C:/Program Files (x86)/Microsoft SDKs/Windows/v7.1A/Lib\\\"")
set(ENV{PATH} "C:/Program Files (x86)/Microsoft SDKs/Windows/v7.1A/Bin;$ENV{PATH}")
```


### References

- [PR: Windows XP support](https://github.com/microsoft/vcpkg/pull/1732)
- [PR: Allow specification of msvc toolset version in triplet file](https://github.com/microsoft/vcpkg-tool/pull/199)
