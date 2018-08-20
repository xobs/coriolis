
import Cfg

print("          - Loading Misc. configuration.")

# Misc. parameters.
Cfg.getParamBool("misc.catchCore"    ).setBool(False)
Cfg.getParamBool("misc.info"         ).setBool(True )
Cfg.getParamBool("misc.paranoid"     ).setBool(False)
Cfg.getParamBool("misc.bug"          ).setBool(False)
Cfg.getParamBool("misc.logMode"      ).setBool(True )
Cfg.getParamBool("misc.verboseLevel1").setBool(True )
Cfg.getParamBool("misc.verboseLevel2").setBool(False)
Cfg.getParamInt ("misc.minTraceLevel").setInt (0    )
Cfg.getParamInt ("misc.maxTraceLevel").setInt (0    )
param = Cfg.getParamInt ("misc.minTraceLevel")
param.setMin(0)
param = Cfg.getParamInt ("misc.maxTraceLevel")
param.setMax(0)

# Misc. tab layout.
layout = Cfg.Configuration.get().getLayout()
layout.addTab       ( "Misc.", "misc" )
layout.addTitle     ( "Misc.", "Miscellaneous" )
layout.addParameter ( "Misc.", "misc.catchCore"    , "Catch Core Dumps", 1 )
layout.addParameter ( "Misc.", "misc.verboseLevel1", "Verbose"         , 0 )
layout.addParameter ( "Misc.", "misc.verboseLevel2", "Very Verbose"    , 0 )
layout.addParameter ( "Misc.", "misc.info"         , "Show Infos"      , 0 )
layout.addParameter ( "Misc.", "misc.paranoid"     , "Show Everything" , 0 )
layout.addParameter ( "Misc.", "misc.bug"          , "Show Bugs"       , 0 )
layout.addParameter ( "Misc.", "misc.logMode"      , "Output is a TTY" , 0 )
layout.addParameter ( "Misc.", "misc.minTraceLevel", "Min. Trace Level", 1 )
layout.addParameter ( "Misc.", "misc.maxTraceLevel", "Max. Trace Level", 1 )
