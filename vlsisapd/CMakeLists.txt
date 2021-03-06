# -*- mode: CMAKE explicit-buffer-name: "CMakeLists.txt<vlsisapd>" -*-

 set(CMAKE_LEGACY_CYGWIN_WIN32 0)
 project(VLSISAPD)

 cmake_minimum_required(VERSION 2.8.9)

 list(INSERT CMAKE_MODULE_PATH 0 "${CMAKE_CURRENT_SOURCE_DIR}/../bootstrap/cmake_modules/")
 find_package(Bootstrap REQUIRED)
 list(INSERT CMAKE_MODULE_PATH 0 "${VLSISAPD_SOURCE_DIR}/cmake_modules/")
 print_cmake_module_path()

 message(STATUS "Boost_NO_SYSTEM_PATHS: ${Boost_NO_SYSTEM_PATHS}")
 set_cmake_policies()
 setup_boost(program_options python3 regex)

 find_package(LibXml2 REQUIRED)
 find_package(PythonSitePackages REQUIRED)
 find_package(PythonLibs REQUIRED)
 find_package(BISON REQUIRED)
 find_package(FLEX REQUIRED)
 find_package(Doxygen)

 add_subdirectory(src)
 add_subdirectory(cmake_modules)

 # Required since we're building libraries
 set(CMAKE_POSITION_INDEPENDENT_CODE ON)

 if(BUILD_DOC AND DOXYGEN_FOUND)
   add_subdirectory(doc)
   add_subdirectory(examples)
 endif(BUILD_DOC AND DOXYGEN_FOUND)
