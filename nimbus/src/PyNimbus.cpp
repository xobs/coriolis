
// -*- C++ -*-
//
// This file is part of the Coriolis Software.
// Copyright (c) UPMC/LIP6 2012-2012, All Rights Reserved
//
// +-----------------------------------------------------------------+ 
// |                   C O R I O L I S                               |
// |      N i m b u s  -  Global Routing Framework                   |
// |                                                                 |
// |  Author      :                    Jean-Paul CHAPUT              |
// |  E-mail      :       Jean-Paul.Chaput@asim.lip6.fr              |
// | =============================================================== |
// |  C++ Module  :       "./PyNimbus.cpp"                           |
// +-----------------------------------------------------------------+


#include "hurricane/isobar/PyHurricane.h"
#include "hurricane/isobar/PyCell.h"
#include "nimbus/PyNimbusEngine.h"


namespace Nimbus {

  using std::cerr;
  using std::endl;
  using Hurricane::tab;
  using Isobar::__cs;
  using CRL::PyTypeToolEngine;


#if !defined(__PYTHON_MODULE__)

// x=================================================================x
// |               "PyNimbus" Shared Library Code Part               |
// x=================================================================x


# else // End of PyHurricane Shared Library Code Part.


// x=================================================================x
// |                "PyNimbus" Python Module Code Part               |
// x=================================================================x


extern "C" {


  // x-------------------------------------------------------------x
  // |                 "PyNimbus" Module Methods                   |
  // x-------------------------------------------------------------x


  static PyMethodDef PyNimbus_Methods[] =
    { {NULL, NULL, 0, NULL}     /* sentinel */
    };
  static PyModuleDef PyNimbus_Module;



  // ---------------------------------------------------------------
  // Module Initialization  :  "initNimbus ()"

  PyMODINIT_FUNC PyInit_Nimbus (void) {
    cdebug_log(40,0) << "initNimbus()" << endl;

    PyNimbus_Module.m_base = PyModuleDef_HEAD_INIT;
    PyNimbus_Module.m_name = "Nimbus";
    PyNimbus_Module.m_doc = NULL;
    PyNimbus_Module.m_methods = PyNimbus_Methods;

    PyNimbusEngine_LinkPyType ();

    PYTYPE_READY_SUB ( NimbusEngine, ToolEngine );


    PyObject* module = PyModule_Create ( &PyNimbus_Module );
    if ( module == NULL ) {
      cerr << "[ERROR]\n"
           << "  Failed to initialize Nimbus module." << endl;
      return NULL;
    }

    Py_INCREF ( &PyTypeNimbusEngine );
    PyModule_AddObject ( module, "NimbusEngine", (PyObject*)&PyTypeNimbusEngine );
    return module;
  }

  
} // End of extern "C".

#endif // End of Python Module Code Part.

}  // End of Nimbus namespace.
