# -*- mode: CMAKE explicit-buffer-name: "CMakeLists.txt<metis>" -*-

 set(CMAKE_LEGACY_CYGWIN_WIN32 0)
 project(METIS)

 cmake_minimum_required(VERSION 2.8.9)

 list(INSERT CMAKE_MODULE_PATH 0 "${CMAKE_CURRENT_SOURCE_DIR}/../bootstrap/cmake_modules/")
 list(INSERT CMAKE_MODULE_PATH 0 "${CMAKE_CURRENT_SOURCE_DIR}/../vlsisapd/cmake_modules/")
 list(INSERT CMAKE_MODULE_PATH 0 "${CMAKE_CURRENT_SOURCE_DIR}/../hurricane/cmake_modules/")
 list(INSERT CMAKE_MODULE_PATH 0 "${CMAKE_CURRENT_SOURCE_DIR}/../crlcore/cmake_modules/")
 list(INSERT CMAKE_MODULE_PATH 0 "${CMAKE_CURRENT_SOURCE_DIR}/../nimbus/cmake_modules/")
 find_package(Bootstrap REQUIRED)
 setup_project_paths(CORIOLIS)
 print_cmake_module_path()

 set_cmake_policies()
 set_lib_link_mode()
 setup_boost()
 
 find_package(PythonLibs REQUIRED)
 find_package(PythonSitePackages REQUIRED)
 find_package(VLSISAPD REQUIRED)
 find_package(HURRICANE REQUIRED)
 find_package(CORIOLIS REQUIRED)
 find_package(NIMBUS REQUIRED)
 
 set(HMETIS_INCLUDE_PATH METIS_INCLUDE_PATH)
 find_library(HMETIS_LIBRARY_PATH
   NAMES hmetis
   PATHS ${CORIOLIS_DIR_SEARCH} /opt/coriolis
   PATH_SUFFIXES lib${LIB_SUFFIX}
   # Help the user find it if we cannot.
   DOC "The hmetis static library"
 )
 set_libraries_path(HMETIS HMETIS)
 
 add_subdirectory(src)
 add_subdirectory(cmake_modules)
