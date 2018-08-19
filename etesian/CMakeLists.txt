# -*- explicit-buffer-name: "CMakeLists.txt<etesian>" -*-

 set(CMAKE_LEGACY_CYGWIN_WIN32 0)
 project(ETESIAN)

 option(BUILD_DOC      "Build the documentation (doxygen)" OFF)
 
 cmake_minimum_required(VERSION 2.8.9)

 list(INSERT CMAKE_MODULE_PATH 0 "${CMAKE_CURRENT_SOURCE_DIR}/../bootstrap/cmake_modules/")
 list(INSERT CMAKE_MODULE_PATH 0 "${CMAKE_CURRENT_SOURCE_DIR}/../vlsisapd/cmake_modules/")
 list(INSERT CMAKE_MODULE_PATH 0 "${CMAKE_CURRENT_SOURCE_DIR}/../crlcore/cmake_modules/")
 list(INSERT CMAKE_MODULE_PATH 0 "${CMAKE_CURRENT_SOURCE_DIR}/../hurricane/cmake_modules/")
 list(INSERT CMAKE_MODULE_PATH 0 "${CMAKE_CURRENT_SOURCE_DIR}/../coloquinte/cmake_modules/")
 list(INSERT CMAKE_MODULE_PATH 0 "${CMAKE_CURRENT_SOURCE_DIR}/../katabatic/cmake_modules/")
 list(INSERT CMAKE_MODULE_PATH 0 "${CMAKE_CURRENT_SOURCE_DIR}/../kite/cmake_modules/")
find_package(Bootstrap  REQUIRED)
 setup_project_paths(CORIOLIS)
 setup_qt()
 
 set_cmake_policies()
 set_lib_link_mode()
 setup_boost(program_options python regex)
 
 find_package(PythonLibs         REQUIRED)
 find_package(PythonSitePackages REQUIRED)
 find_package(VLSISAPD           REQUIRED)
 find_package(HURRICANE          REQUIRED)
 find_package(KATABATIC          REQUIRED)
 find_package(CORIOLIS           REQUIRED)
 find_package(KITE               REQUIRED)
 find_package(COLOQUINTE         REQUIRED)
 find_package(Libexecinfo        REQUIRED)
 
 add_subdirectory(src)
 add_subdirectory(cmake_modules)

 if(BUILD_DOC)
   find_package(Doxygen)
#  if(DOXYGEN_FOUND)
#    add_subdirectory(doc)
#  endif()
 endif()
