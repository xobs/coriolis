PROJECT(KITE)

OPTION(BUILD_DOC      "Build the documentation (doxygen)" OFF)
OPTION(CHECK_DATABASE "Run database in full check mode (very slow)" OFF)

CMAKE_MINIMUM_REQUIRED(VERSION 2.4.0)

SET(CMAKE_C_FLAGS_DEBUG             "-g -Wall" CACHE STRING "Debug options." FORCE)
SET(CMAKE_CXX_FLAGS_DEBUG           "-g -Wall" CACHE STRING "Debug options." FORCE)
#SET(CMAKE_LINKER_FLAGS_DEBUG        "-pg"          CACHE STRING "Debug options." FORCE)
#SET(CMAKE_SHARED_LINKER_FLAGS_DEBUG "-pg"          CACHE STRING "Debug options." FORCE)
#SET(CMAKE_MODULE_LINKER_FLAGS_DEBUG "-pg"          CACHE STRING "Debug options." FORCE)
#SET(CMAKE_EXE_LINKER_FLAGS_DEBUG    "-pg"          CACHE STRING "Debug options." FORCE)
SET(CMAKE_C_FLAGS_RELEASE           "-O3 -DNDEBUG -Wall" CACHE STRING "Release options." FORCE)
SET(CMAKE_CXX_FLAGS_RELEASE         "-O3 -DNDEBUG -Wall" CACHE STRING "Release options." FORCE)

IF(COMMAND CMAKE_POLICY)
  CMAKE_POLICY(SET CMP0003 NEW)
ENDIF(COMMAND CMAKE_POLICY)

SET(CMAKE_MODULE_PATH "$ENV{HURRICANE_TOP}/share/cmake_modules/")

SET(QT_USE_QTXML "true")

IF(BUILD_DOC)
  FIND_PACKAGE(Doxygen)
ENDIF(BUILD_DOC)
FIND_PACKAGE(Boost 1.33.1 COMPONENTS program_options REQUIRED)
FIND_PACKAGE(Qt4 REQUIRED) # find and setup Qt4 for this project
FIND_PACKAGE(Boost 1.33.1 REQUIRED)
FIND_PACKAGE(IO REQUIRED)
FIND_PACKAGE(LEFDEF REQUIRED)
FIND_PACKAGE(HURRICANE REQUIRED)
FIND_PACKAGE(CORIOLIS REQUIRED)
FIND_PACKAGE(KNIK REQUIRED)
FIND_PACKAGE(KATABATIC REQUIRED)

SET_LIB_LINK_MODE()

IF(CHECK_DATABASE)
  ADD_DEFINITIONS(-DCHECK_DATABASE)
ENDIF(CHECK_DATABASE)
IF(CHECK_DETERMINISM)
  ADD_DEFINITIONS(-DCHECK_DETERMINISM)
ENDIF(CHECK_DETERMINISM)

ADD_SUBDIRECTORY(src)
ADD_SUBDIRECTORY(cmake_modules)
IF(BUILD_DOC AND DOXYGEN_FOUND)
  ADD_SUBDIRECTORY(doc)
ENDIF(BUILD_DOC AND DOXYGEN_FOUND)