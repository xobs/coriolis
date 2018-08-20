import sys

from SPICE import *

def printContents(circuit):
  print("+", circuit.title)

  if len(circuit.getIncludes()):
    print("| + includes")
    for include in circuit.getIncludes():
      print("| |", include)

  if len(circuit.getLibraries()):
    print("| + libraries")
    for (lib, typ) in circuit.getLibraries():
      print("| |", lib, typ)

  if len(circuit.getParameters()):
    print("| + parameters")
    for (name, value) in list(circuit.getParameters().items()):
      print("| | %s=%s"%(name, value))

  if len(circuit.getOptions()):
    print("| + options")
    for (name, value) in list(circuit.getOptions().items()):
      print("| | %s=%s"%(name, value))

  if len(circuit.getSources()):
    print("| + sources")
    for source in circuit.getSources():
      print("| |", source.getName(), source.getPositive(), source.getNegative(), source.getValue())

  if len(circuit.getSubckts()):
    print("| + subckts")
    for sub in circuit.getSubckts():
      print("| | +", sub.getName(), end=' ')
      for interf in sub.getInterfaces():
        print(interf, end=' ')
      if len(sub.getParameters()):
          print("param:", end=' ')
          for (name, value) in list(sub.getParameters().items()):
            print("%s=%s"%(name,value), end=' ')
      print()
      for inst in sub.getInstances():
          print("| | | +", inst.getName(), end=' ')
          if isinstance(inst, Mosfet):
            print(inst.getDrain(), inst.getGrid(), inst.getSource(), inst.getBulk(), inst.getModel(), end=' ')
            i = 0
            for (name, value) in list(inst.getParameters().items()):
              if i%6 == 0:
                print() 
                print("| | | | +", end=' ')
              print("%s=%s"%(name, value), end=' ')
              i += 1
          elif isinstance(inst, Resistor):
            print(inst.getFirst(), inst.getSecond(), inst.getValue(), end=' ')
          elif isinstance(inst, Capacitor):
            print(inst.getPositive(), inst.getNegative(), inst.getValue(), end=' ')
          else:
            for conn in inst.getConnectors():
              print(conn, end=' ')
            print(inst.getModel(), end=' ')
            i = 0
            for (name, value) in list(inst.getParameters().items()):
              if i%6 == 0:
                print() 
                print("| | | | +", end=' ')
              print("%s=%s"%(name, value), end=' ')
              i += 1
          print()

  if len(circuit.getInstances()):
    print("| + instances")
    for inst in circuit.getInstances():
      print("| | | +", inst.getName(), end=' ')
      if isinstance(inst, Mosfet):
        print(inst.getDrain(), inst.getGrid(), inst.getSource(), inst.getBulk(), inst.getModel(), end=' ')
        i = 0
        for (name, value) in list(inst.getParameters().items()):
          if i%6 == 0:
            print() 
            print("| | | | +", end=' ')
          print("%s=%s"%(name, value), end=' ')
          i += 1
      elif isinstance(inst, Resistor):
        print(inst.getFirst(), inst.getSecond(), inst.getValue(), end=' ')
      elif isinstance(inst, Capacitor):
        print(inst.getPositive(), inst.getNegative(), inst.getValue(), end=' ')
      else:
        for conn in inst.getConnectors():
          print(conn, end=' ')
        print(inst.getModel(), end=' ')
        i = 0
        for (name, value) in list(inst.getParameters().items()):
          if i%6 == 0:
            print() 
            print("| | | | +", end=' ')
          print("%s=%s"%(name, value), end=' ')
          i += 1
      print()

def usage():
    print("usage:", sys.argv[0], "[filename]")
    sys.exit(48)

def main():
  if len(sys.argv) == 1:
    filename = "./OTA_miller.spi"
  elif len(sys.argv) == 2:
    filename = sys.argv[1]
  else:
    usage()

  circuit = Circuit.readFromFile(filename)
  printContents(circuit)


if __name__ == "__main__":
  main()

