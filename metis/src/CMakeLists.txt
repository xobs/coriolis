# -*- mode: CMAKE explicit-buffer-name: "CMakeLists.txt<metis/src>" -*-

if ( HMETIS_FOUND )
  add_definitions ( -DHAVE_HMETIS_LIB )
endif ( HMETIS_FOUND )

#              include ( ${QT_USE_FILE} )

   include_directories ( ${METIS_SOURCE_DIR}/src
                         ${CORIOLIS_INCLUDE_DIR} 
                         ${HURRICANE_INCLUDE_DIR} 
                         ${CONFIGURATION_INCLUDE_DIR} 
                         ${Boost_INCLUDE_DIRS}
                         ${PYTHON_INCLUDE_PATH}
                       )
                   set ( includes      metis/hmetis.h
                                       metis/MetisGraph.h
                                       metis/Configuration.h
                                       metis/MetisEngine.h
                       )
                   set ( pyIncludes    metis/PyMetisEngine.h
                       )
                   set ( cpps          MetisGraph.cpp
                                       Configuration.cpp
                                       MetisEngine.cpp
                       )
                   set ( pyCpps        PyMetis.cpp
                                       PyMetisEngine.cpp
                       )

           add_library ( metis         SHARED ${cpps} ${pyCpps} )
 set_target_properties ( metis         PROPERTIES VERSION 1.0 SOVERSION 1 POSITION_INDEPENDENT_CODE ON )
 target_link_libraries ( metis         ${HMETIS_LIBRARIES}
                                       ${NIMBUS_LIBRARIES}
                                       ${CORIOLIS_LIBRARIES}
                                       ${HURRICANE_PYTHON_LIBRARIES}
                                       ${HURRICANE_GRAPHICAL_LIBRARIES}
                                       ${HURRICANE_LIBRARIES}
                                       ${CONFIGURATION_LIBRARY}
                                       ${CIF_LIBRARY}
                                       ${AGDS_LIBRARY}
                                       ${LEFDEF_LIBRARIES}
                                       ${OA_LIBRARIES}
                                       ${QT_LIBRARIES}
                                       ${Boost_LIBRARIES}
                                       ${LIBXML2_LIBRARIES}
                                       ${PYTHON_LIBRARIES} -lutil
                       )

           add_library ( pyMetis       SHARED MODULE ${pyCpps} )
 set_target_properties ( pyMetis       PROPERTIES COMPILE_FLAGS "${COMPILE_FLAGS} -D__PYTHON_MODULE__=1"
                                                  PREFIX        ""
                                                  OUTPUT_NAME   "Metis"
                                                  POSITION_INDEPENDENT_CODE ON
                       )
 target_link_libraries ( pyMetis       metis 
                                       ${CORIOLIS_PYTHON_LIBRARIES}
                       )

               install ( TARGETS       metis           DESTINATION lib${LIB_SUFFIX} )
               install ( TARGETS       pyMetis         DESTINATION ${PYTHON_SITE_PACKAGES} )
               install ( FILES         ${includes}
                                       ${pyIncludes}   DESTINATION include/coriolis2/metis ) 
