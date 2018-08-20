#!/usr/bin/env python3
#
# This file is part of the Coriolis Software.
# Copyright (c) UPMC 2015-2016, All Rights Reserved
#
# +-----------------------------------------------------------------+
# |                   C O R I O L I S                               |
# |      C u m u l u s  -  P y t h o n   T o o l s                  |
# |                                                                 |
# |  Author      :                    Jean-Paul CHAPUT              |
# |  E-mail      :       Jean-Paul.Chaput@asim.lip6.fr              |
# | =============================================================== |
# |  Python      :       "./plugins/RSavePluginAll.py"              |
# +-----------------------------------------------------------------+


try:
  import sys
  import traceback
  import os.path
  import Cfg
  import CRL
  import helpers
  from   helpers   import ErrorMessage
  from   helpers   import WarningMessage
  import plugins
except ImportError as e:
  serror = str(e)
  if serror.startswith('No module named'):
    module = serror.split()[-1]
    print('[ERROR] The <%s> python module or symbol cannot be loaded.' % module)
    print('        Please check the integrity of the <coriolis> package.')
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


# Write back netlist & layout to disk. Layout is written
# *only* if there is an abutment box otherwise the cell is
# considered as unplaced.
# Must write all the sub-blocks of the core but *not* the
# standard cell (mainly the feed-through).

def rsave ( cell, depth=0 ):
  if cell.isTerminal(): return

  framework = CRL.AllianceFramework.get()
  if depth == 0: print('  o  Recursive Save-Cell.')

  print('     %s+ %s (netlist+layout).' % ( ' '*(depth*2), cell.getName() ))
  flags = CRL.Catalog.State.Logical
  if not cell.getAbutmentBox().isEmpty():
    flags |= CRL.Catalog.State.Physical

  framework.saveCell( cell, flags )

  for instance in cell.getInstances():
    masterCell = instance.getMasterCell()
    if not masterCell.isTerminal():
      rsave( masterCell, depth+1 )
  return


# --------------------------------------------------------------------
# Plugin hook functions, unicornHook:menus, ScritMain:call

def unicornHook ( **kw ):
    plugins.kwUnicornHook( 'plugins.rsaveAll'
                         , 'R-Save Cell (All)'
                         , 'Recursively Save Top Cell and it\'s Instances'
                         , sys.modules[__name__].__file__
                         , **kw
                         )
    return


def ScriptMain ( **kw ):
  try:
    helpers.staticInitialization( quiet=True )
   #helpers.setTraceLevel( 550 )

    cell, editor = plugins.kwParseMain( **kw )

    if not cell:
      print(WarningMessage( 'No Cell loaded in the editor (yet), nothing done.' ))
      return 0

    rsave( cell )
    CRL.destroyAllVHDL()

  except ErrorMessage as e:
    print(e); errorCode = e.code
  except Exception as e:
    print('\n\n', e); errorCode = 1
    traceback.print_tb(sys.exc_info()[2])

  sys.stdout.flush()
  sys.stderr.flush()
      
  return 0
