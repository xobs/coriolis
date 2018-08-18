# -*- mode: CMAKE explicit-buffer-name: "CMakeLists.txt<knik>" -*-

 set(CMAKE_LEGACY_CYGWIN_WIN32 0)
 project(KNIK)

 cmake_minimum_required(VERSION 2.8.9)

 list(INSERT CMAKE_MODULE_PATH 0 "${CMAKE_CURRENT_SOURCE_DIR}/../bootstrap/cmake_modules/")
 list(INSERT CMAKE_MODULE_PATH 0 "${CMAKE_CURRENT_SOURCE_DIR}/../vlsisapd/cmake_modules/")
 list(INSERT CMAKE_MODULE_PATH 0 "${CMAKE_CURRENT_SOURCE_DIR}/../hurricane/cmake_modules/")
 list(INSERT CMAKE_MODULE_PATH 0 "${CMAKE_CURRENT_SOURCE_DIR}/../crlcore/cmake_modules/")
 find_package(Bootstrap REQUIRED)
 setup_project_paths(CORIOLIS)
 print_cmake_module_path()

 set_cmake_policies()
 set_lib_link_mode()
 setup_boost(program_options filesystem python regex)
 setup_qt()
 
 find_package(VLSISAPD REQUIRED)
 find_package(HURRICANE REQUIRED)
 find_package(CORIOLIS REQUIRED)
 
 add_subdirectory(src)
 add_subdirectory(cmake_modules)
