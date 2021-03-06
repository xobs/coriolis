# -*- mode: CMAKE explicit-buffer-name: "CMakeLists.txt<ispd>" -*-

 set(CMAKE_LEGACY_CYGWIN_WIN32 0)
 project(ISPD)
 
 cmake_minimum_required(VERSION 2.4.0)

 list(INSERT CMAKE_MODULE_PATH 0 "${CMAKE_CURRENT_SOURCE_DIR}/../bootstrap/cmake_modules/")
 list(INSERT CMAKE_MODULE_PATH 0 "${CMAKE_CURRENT_SOURCE_DIR}/../vlsisapd/cmake_modules/")
 list(INSERT CMAKE_MODULE_PATH 0 "${CMAKE_CURRENT_SOURCE_DIR}/../hurricane/cmake_modules/")
 list(INSERT CMAKE_MODULE_PATH 0 "${CMAKE_CURRENT_SOURCE_DIR}/../crlcore/cmake_modules/")
 list(INSERT CMAKE_MODULE_PATH 0 "${CMAKE_CURRENT_SOURCE_DIR}/../knik/cmake_modules/")
 list(INSERT CMAKE_MODULE_PATH 0 "${CMAKE_CURRENT_SOURCE_DIR}/../vlsisapd/cmake_modules/")
 find_package(Bootstrap REQUIRED)
 setup_project_paths(CORIOLIS)
 
 set_cmake_policies()
 set_lib_link_mode()
#setup_apple()
 setup_boost(program_options filesystem python3 regex)
 
 find_package(LibXml2 REQUIRED)
 set(QT_USE_QTXML "true")
 find_package(Qt4 REQUIRED)
 find_package(PythonLibs REQUIRED)
 find_package(PythonSitePackages REQUIRED)
 find_package(VLSISAPD REQUIRED)
 find_package(HURRICANE REQUIRED)
 find_package(CORIOLIS REQUIRED)
 find_package(KNIK REQUIRED)
 find_package(LEFDEF REQUIRED)
#find_package(KATABATIC REQUIRED)
#find_package(KITE REQUIRED)
#find_package(EQUINOX REQUIRED)
#find_package(SOLSTICE REQUIRED)
 
 add_subdirectory(src)
