
               include ( ${QT_USE_FILE} )

   include_directories ( ${MAUKA_SOURCE_DIR}/src
                         ${CORIOLIS_INCLUDE_DIR} 
                         ${HURRICANE_INCLUDE_DIR} 
                         ${CONFIGURATION_INCLUDE_DIR} 
                       )
                   set ( includes      mauka/Configuration.h
                                       mauka/FeedCells.h
                                       mauka/BBPlacer.h
                                       mauka/Bin.h
                                       mauka/Container.h
                                       mauka/MaukaBox.h
                                       mauka/Move.h
                                       mauka/Row.h
                                       mauka/SimAnnealingPlacer.h
                                       mauka/SubRow.h
                                       mauka/Surface.h
                                       mauka/MaukaEngine.h
                       )
		   set ( mocIncludes   mauka/GraphicMaukaEngine.h )
                   set ( cpps          Configuration.cpp
                                       BBPlacer.cpp
                                       FeedCells.cpp
                                       Bin.cpp
                                       Container.cpp
                                       MaukaBox.cpp
                                       Move.cpp
                                       Row.cpp
                                       SimAnnealingPlacer.cpp
                                       SubRow.cpp
                                       Surface.cpp
                                       MaukaEngine.cpp
                                       GraphicMaukaEngine.cpp
                       )
          qt4_wrap_cpp ( mocCpps       ${mocIncludes} )


           add_library ( mauka         ${cpps} ${mocCpps} )
               install ( TARGETS       mauka                      DESTINATION lib${LIB_SUFFIX} )
               install ( FILES         ${includes} ${mocIncludes} DESTINATION include/coriolis2/mauka ) 