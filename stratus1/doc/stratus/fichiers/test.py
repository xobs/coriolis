#!/usr/bin/env python3

from stratus import *
from addaccu import addaccu

nbit = Param ( "n" )

dict = { 'nbit' : nbit }

inst_addaccu = addaccu ( "inst_addaccu", dict )

inst_addaccu.Interface()
inst_addaccu.Netlist()
inst_addaccu.Layout()
inst_addaccu.View()

inst_addaccu.Save ( PHYSICAL )


