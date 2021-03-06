# - Try to find the VLSISAPD libraries
# Once done this will define
#
#  VLSISAPD_FOUND       - system has the VLSISAPD library
#  VLSISAPD_INCLUDE_DIR - the VLSISAPD include directory
#  VLSISAPD_LIBRARIES   - The libraries needed to use VLSISAPD

 set(VLSISAPD_FOUND FALSE)
 setup_search_dir(CORIOLIS)

 set(CORIOLIS_DIR_SEARCH "${CMAKE_CURRENT_SOURCE_DIR}/../vlsisapd/")
 if(CORIOLIS_DIR_SEARCH)
  MESSAGE("--   CORIOLIS_DIR_SEARCH: ${CORIOLIS_DIR_SEARCH}")

  # Utilities
   FIND_PATH   (UTILITIES_INCLUDE_DIR NAMES vlsisapd/utilities/Path.h PATHS ${CORIOLIS_DIR_SEARCH} PATH_SUFFIXES include)
   FIND_LIBRARY(UTILITIES_LIBRARY     NAMES vlsisapdutils             PATHS ${CORIOLIS_DIR_SEARCH} PATH_SUFFIXES lib${LIB_SUFFIX})
   SET_FOUND   (UTILITIES)
   MESSAGE("--   Utilities: ${UTILITIES_LIBRARY}")

    # AGDS
    FIND_PATH   (AGDS_INCLUDE_DIR NAMES vlsisapd/agds/GdsLibrary.h PATHS ${CORIOLIS_DIR_SEARCH} PATH_SUFFIXES include)
    FIND_LIBRARY(AGDS_LIBRARY     NAMES agds                       PATHS ${CORIOLIS_DIR_SEARCH} PATH_SUFFIXES lib${LIB_SUFFIX})
    SET_FOUND   (AGDS)
    MESSAGE("--   AGDS: ${AGDS_LIBRARY}")
    
    # CIF
    FIND_PATH   (CIF_INCLUDE_DIR NAMES vlsisapd/cif/Circuit.h PATHS ${CORIOLIS_DIR_SEARCH} PATH_SUFFIXES include)
    FIND_LIBRARY(CIF_LIBRARY     NAMES cif                    PATHS ${CORIOLIS_DIR_SEARCH} PATH_SUFFIXES lib${LIB_SUFFIX})
    SET_FOUND   (CIF)
    MESSAGE("--   Cif: ${CIF_LIBRARY}")
    
    # OPENCHAMS
    FIND_PATH   (OPENCHAMS_INCLUDE_DIR NAMES vlsisapd/openChams/Circuit.h PATHS ${CORIOLIS_DIR_SEARCH} PATH_SUFFIXES include)
    FIND_LIBRARY(OPENCHAMS_LIBRARY     NAMES openChams                    PATHS ${CORIOLIS_DIR_SEARCH} PATH_SUFFIXES lib${LIB_SUFFIX})
    SET_FOUND   (OPENCHAMS)
    MESSAGE("--   OPENCHAMS: ${OPENCHAMS_LIBRARY}")

    # DTR
    FIND_PATH   (DTR_INCLUDE_DIR NAMES vlsisapd/dtr/Techno.h PATHS ${CORIOLIS_DIR_SEARCH} PATH_SUFFIXES include)
    FIND_LIBRARY(DTR_LIBRARY     NAMES dtr                   PATHS ${CORIOLIS_DIR_SEARCH} PATH_SUFFIXES lib${LIB_SUFFIX})
    SET_FOUND   (DTR)
    MESSAGE("--   DTR: ${DTR_LIBRARY}")

    # SPICE
    FIND_PATH   (SPICE_INCLUDE_DIR NAMES vlsisapd/spice/Circuit.h PATHS ${CORIOLIS_DIR_SEARCH} PATH_SUFFIXES include)
    FIND_LIBRARY(SPICE_LIBRARY     NAMES spice                    PATHS ${CORIOLIS_DIR_SEARCH} PATH_SUFFIXES lib${LIB_SUFFIX})
    SET_FOUND   (SPICE)
    MESSAGE("--   SPICE: ${SPICE_LIBRARY}")

    # Bookshelf
    FIND_PATH   (BOOKSHELF_INCLUDE_DIR NAMES vlsisapd/bookshelf/Circuit.h PATHS ${CORIOLIS_DIR_SEARCH} PATH_SUFFIXES include)
    FIND_LIBRARY(BOOKSHELF_LIBRARY     NAMES bookshelf                    PATHS ${CORIOLIS_DIR_SEARCH} PATH_SUFFIXES lib${LIB_SUFFIX})
    SET_FOUND   (BOOKSHELF)
    MESSAGE("--   Bookshelf: ${BOOKSHELF_LIBRARY}")

    # Configuration
    FIND_PATH   (CONFIGURATION_INCLUDE_DIR NAMES vlsisapd/configuration/ConfigurationWidget.h PATHS ${CORIOLIS_DIR_SEARCH} PATH_SUFFIXES include)
    FIND_LIBRARY(CONFIGURATION_LIBRARY     NAMES configuration                                PATHS ${CORIOLIS_DIR_SEARCH} PATH_SUFFIXES lib${LIB_SUFFIX})
    SET_FOUND   (CONFIGURATION)
    MESSAGE("--   Configuration: ${CONFIGURATION_LIBRARY}")
    
    IF(AGDS_FOUND OR CIF_FOUND OR OPENCHAMS_FOUND OR DTR_FOUND OR SPICE_FOUND)
        SET(VLSISAPD_FOUND TRUE)
    ELSE(AGDS_FOUND OR CIF_FOUND OR OPENCHAMS_FOUND OR DTR_FOUND OR SPICE_FOUND)
        SET(VLSISAPD_FOUND FALSE)
    ENDIF(AGDS_FOUND OR CIF_FOUND OR OPENCHAMS_FOUND OR DTR_FOUND OR SPICE_FOUND)
ELSE(CORIOLIS_DIR_SEARCH)
    MESSAGE("-- Cannot find VLSISAPD_LIBRARIES since CORIOLIS_DIR_SEARCH is not defined.")
ENDIF(CORIOLIS_DIR_SEARCH)

IF (NOT VLSISAPD_FOUND)
    SET(VLSISAPD_MESSAGE
    "VLSISAPD libraries were not found. Make sure CORIOLIS_TOP env variable is set.")
    IF (NOT VLSISAPD_FIND_QUIETLY)
        MESSAGE(STATUS "${VLSISAPD_MESSAGE}")
    ELSE(NOT VLSISAPD_FIND_QUIETLY)
        IF(VLSISAPD_FIND_REQUIRED)
            MESSAGE(FATAL_ERROR "${VLSISAPD_MESSAGE}")
        ENDIF(VLSISAPD_FIND_REQUIRED)
    ENDIF(NOT VLSISAPD_FIND_QUIETLY)
ELSE (NOT VLSISAPD_FOUND)
    MESSAGE(STATUS "VLSISAPD library was found in ${CORIOLIS_DIR_SEARCH}")
ENDIF (NOT VLSISAPD_FOUND)

