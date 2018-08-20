#!/usr/bin/env python3

try:
  import sys
  import traceback
  import os.path
  import optparse
  import Cfg
  import Hurricane
  from   Hurricane import DbU
  from   Hurricane import UpdateSession
  from   Hurricane import Breakpoint
  from   Hurricane import Transformation
  from   Hurricane import Instance
  import Viewer
  import CRL
  from   helpers   import ErrorMessage
 #import Nimbus
 #import Metis
 #import Mauka
  import Etesian
  import Katabatic
  import Kite
  import Unicorn
  import clocktree.ClockTree
  import plugins.ClockTreePlugin
  import plugins.ChipPlugin
  import plugins.RSavePlugin
except ImportError as e:
  serror = str(e)
  if serror.startswith('No module named'):
    module = serror.split()[-1]
    print('[ERROR] The <%s> python module or symbol cannot be loaded.' % module)
    print('        Please check the integrity of the <coriolis> package.')
    sys.exit(1)
  if str(e).find('cannot open shared object file'):
    library = serror.split(':')[0]
    print('[ERROR] The <%s> shared library cannot be loaded.' % library)
    print('        Under RHEL 6, you must be under devtoolset-2.')
    print('        (scl enable devtoolset-2 bash)')
  sys.exit(1)
except Exception as e:
  print('[ERROR] A strange exception occurred while loading the basic Coriolis/Python')
  print('        modules. Something may be wrong at Python/C API level.\n')
  print('        %s' % e)
  sys.exit(2)


DoChip      = 0x0001
DoClockTree = 0x0002
DoPlacement = 0x0004
DoRouting   = 0x0008
ChipStages  = DoChip|DoPlacement|DoRouting

framework   = CRL.AllianceFramework.get()


def ScriptMain ( **kw ):
  success  = False
  doStages = kw['doStages']
  try:
    cell, editor = plugins.kwParseMain( **kw )
  
    if doStages & DoPlacement:
      if doStages & DoChip:
        success = plugins.ChipPlugin.ScriptMain( **kw )
        if not success: return False
      else:
        if cell.getAbutmentBox().isEmpty():
          cellGauge   = framework.getCellGauge()
          spaceMargin = (Cfg.getParamPercentage('etesian.spaceMargin').asPercentage()+5) / 100.0
          aspectRatio =  Cfg.getParamPercentage('etesian.aspectRatio').asPercentage()    / 100.0
          clocktree.ClockTree.computeAbutmentBox( cell, spaceMargin, aspectRatio, cellGauge )
          if editor: editor.fit()

        if doStages & DoClockTree:
          success = plugins.ClockTreePlugin.ScriptMain( **kw )
         #if not success: return False
        else:
          if Cfg.getParamString('clockTree.placerEngine').asString() != 'Etesian':
            mauka = Mauka.MaukaEngine.create( cell )
            mauka.run()
            mauka.destroy()
          else:
            etesian = Etesian.EtesianEngine.create( cell )
            etesian.place()
            etesian.destroy()
      if editor: editor.refresh()

    if doStages & DoRouting:
      routingNets = []
      kite = Kite.KiteEngine.create( cell )
      
      kite.runGlobalRouter  ( Kite.KtBuildGlobalRouting )
      kite.loadGlobalRouting( Katabatic.EngineLoadGrByNet, routingNets )
      kite.layerAssign      ( Katabatic.EngineNoNetLayerAssign )
      kite.runNegociate     ()
      success = kite.getToolSuccess()
      kite.finalizeLayout()
      kite.destroy()
      cell.setName( cell.getName()+'_kite' )
      framework.saveCell( cell, CRL.Catalog.State.Logical )
  
    plugins.RSavePlugin.ScriptMain( **kw )

  except Exception as e:
    print(e)

  return success


if __name__ == '__main__':
  parser = optparse.OptionParser()
  parser.add_option( '-c', '--cell'  , type='string',                      dest='cell'       , help='The name of the chip to build, whithout extension.')
  parser.add_option( '-s', '--script', type='string',                      dest='script'     , help='The name of a Python script, without extension.')
  parser.add_option( '-v', '--verbose'              , action='store_true', dest='verbose'    , help='First level of verbosity.')
  parser.add_option( '-V', '--very-verbose'         , action='store_true', dest='veryVerbose', help='Second level of verbosity.')
  parser.add_option( '-p', '--place'                , action='store_true', dest='doPlacement', help='Perform chip placement step only.')
  parser.add_option( '-r', '--route'                , action='store_true', dest='doRouting'  , help='Perform routing step only.')
  parser.add_option( '-C', '--chip'                 , action='store_true', dest='doChip'     , help='Run place & route on a complete chip.')
  parser.add_option( '-T', '--clock-tree'           , action='store_true', dest='doClockTree', help='In block mode, create a clock-tree.')
  (options, args) = parser.parse_args()

  doStages = 0
  if options.verbose:     Cfg.getParamBool('misc.verboseLevel1').setBool(True)
  if options.veryVerbose: Cfg.getParamBool('misc.verboseLevel2').setBool(True)
  if options.doPlacement: doStages |= DoPlacement
  if options.doRouting:   doStages |= DoRouting
  if options.doChip:      doStages |= DoChip
  if options.doClockTree: doStages |= DoClockTree
  if not doStages:        doStages  = ChipStages

  kw = { 'doStages':doStages }
  if options.script:
    try:
      module = __import__( options.script, globals(), locals() )
      if 'ScriptMain' not in module.__dict__:
          print('[ERROR] Script module <%s> do not contains a ScripMain() function.' % options.script)
          sys.exit(1)

      cell = module.__dict__['ScriptMain']( **kw )
      kw['cell'] = cell

    except ImportError as e:
      module = str(e).split()[-1]

      print('[ERROR] The <%s> script cannot be loaded.' % module)
      print('        Please check your design hierarchy.')
      sys.exit(1)
    except Exception as e:
      print('[ERROR] A strange exception occurred while loading the Python')
      print('        script <%s>. Please check that module for error:\n' % options.script)
      traceback.print_tb(sys.exc_info()[2])
      print('        %s' % e)
      sys.exit(2)
  elif options.cell:
    kw['cell'] = framework.getCell( options.cell, CRL.Catalog.State.Views )

  success = ScriptMain( **kw )
  shellSuccess = 0
  if not success: shellSuccess = 1

  sys.exit( shellSuccess )
