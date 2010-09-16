from OPENCHAMS import *

circuit = Circuit(Name("design"), Name("myTech"))
# value parameters
circuit.addParameter(Name("temp"), 27.0  )
circuit.addParameter(Name("Vdd") , 1.2   )
circuit.addParameter(Name("Vss") , 0.0   )
circuit.addParameter(Name("L")   , 0.1e-6)
circuit.addParameter(Name("Ids") , 30e-6 )
circuit.addParameter(Name("Veg") , 0.12  )
# equation parameters
circuit.addParameter(Name("complex"), "myEq")

# netlist :
netlist = circuit.createNetlist()
#  instances
#   nmos1
inst_nmos1 = netlist.addInstance("nmos1", "Transistor", "NMOS", True)
inst_nmos1.addConnector("G")
inst_nmos1.addConnector("S")
inst_nmos1.addConnector("D")
tr_nmos1 = inst_nmos1.addTransistor("m1")
tr_nmos1.gate   = "G" # the name of the connector of inst_nmos1
tr_nmos1.source = "S"
tr_nmos1.drain  = "D"
tr_nmos1.bulk   = "S"
#   pmos1
inst_pmos1 = netlist.addInstance("pmos1", "Transistor", "PMOS", True)
inst_pmos1.addConnector("G")
inst_pmos1.addConnector("S")
inst_pmos1.addConnector("D")
tr_pmos1 = inst_pmos1.addTransistor("m1")
tr_pmos1.gate   = "G" # the name of the connector of inst_pmos1
tr_pmos1.source = "S"
tr_pmos1.drain  = "D"
tr_pmos1.bulk   = "S"
#  nets
_vdd = netlist.addNet("vdd", "power"  , True)
_vss = netlist.addNet("vss", "ground" , True)
_in  = netlist.addNet("in" , "logical", True)
_out = netlist.addNet("out", "logical", True)
_vdd.connectTo("pmos1", "S")
_vss.connectTo("nmos1", "S")
_in.connectTo ("nmos1", "G")
_in.connectTo ("pmos1", "G")
_out.connectTo("nmos1", "D")
_out.connectTo("pmos1", "D")
# schematic
schematic = circuit.createSchematic(1.0)
schematic.addInstance("nmos1", 2490, 2600, "ID")
schematic.addInstance("pmos1", 2490, 2300, "ID")
# sizing
sizing = circuit.createSizing()
op_pmos1 = sizing.addOperator("pmos1", "OPVG(Veg)" , "BSIM3V3", 0)
op_pmos1.addConstraint("Temp", "design", "temp")
op_pmos1.addConstraint("Ids" , "design", "Ids" )
op_pmos1.addConstraint("L"   , "design", "L"   )
op_pmos1.addConstraint("Veg" , "design", "Veg" )
op_pmos1.addConstraint("Vd"  , "design", "Vdd", 0.5)
op_pmos1.addConstraint("Vs"  , "design", "Vdd" )
op_nmos1 = sizing.addOperator("nmos1", "OPW(Vg,Vs)", "BSIM3V3", 1)
op_nmos1.addConstraint("Temp", "design", "temp")
op_nmos1.addConstraint("Ids" , "design", "Ids" )
op_nmos1.addConstraint("L"   , "design", "L"   )
op_nmos1.addConstraint("Vs"  , "design", "Vdd" )
op_nmos1.addConstraint("Vg"  , "pmos1" , "Vg"  )
op_nmos1.addConstraint("Vd"  , "pmos1" , "Vd"  )
op_nmos1.addConstraint("another", "myEq", -2.5 )
# layout
layout = circuit.createLayout()
layout.addInstance("pmos1", "Common transistor")
layout.addInstance("nmos1", "Rotate transistor")

circuit.writeToFile("./myInverter.xml")