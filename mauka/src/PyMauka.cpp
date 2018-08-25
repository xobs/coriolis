
// -*- C++ -*-
//
// This file is part of the Coriolis Software.
// Copyright (c) UPMC/LIP6 2010-2012, All Rights Reserved
//
// +-----------------------------------------------------------------+ 
// |                   C O R I O L I S                               |
// |              M a u k a  -  P l a c e r                          |
// |                                                                 |
// |  Author      :                    Jean-Paul CHAPUT              |
// |  E-mail      :       Jean-Paul.Chaput@asim.lip6.fr              |
// | =============================================================== |
// |  C++ Module  :       "./PyMauka.cpp"                            |
// +-----------------------------------------------------------------+


#include "hurricane/isobar/PyHurricane.h"
#include "hurricane/isobar/PyCell.h"
#include "mauka/PyMaukaEngine.h"
#include "mauka/PyGraphicMaukaEngine.h"


namespace Mauka {

  using std::cerr;
  using std::endl;
  using Hurricane::tab;
  using Isobar::__cs;
  using CRL::PyTypeToolEngine;
  using CRL::PyTypeGraphicTool;


#if !defined(__PYTHON_MODULE__)

// x=================================================================x
// |               "PyMauka" Shared Library Code Part                |
// x=================================================================x


# else // End of PyHurricane Shared Library Code Part.


// x=================================================================x
// |                "PyMauka" Python Module Code Part                |
// x=================================================================x


extern "C" {


  // x-------------------------------------------------------------x
  // |                 "PyMauka" Module Methods                    |
  // x-------------------------------------------------------------x


  static PyMethodDef PyMauka_Methods[] =
    { {NULL, NULL, 0, NULL}     /* sentinel */
    };
  static PyModuleDef PyNimbus_Module;




  // ---------------------------------------------------------------
  // Module Initialization  :  "initMauka ()"

  PyMODINIT_FUNC PyInit_Mauka (void) {
    cdebug_log(40,0) << "initMauka()" << endl;

    PyNimbus_Module.m_base = PyModuleDef_HEAD_INIT;
    PyNimbus_Module.m_name = "Mauka";
    PyNimbus_Module.m_doc = NULL;
    PyNimbus_Module.m_size = -1;
    PyNimbus_Module.m_methods = PyMauka_Methods;

    PyMaukaEngine_LinkPyType ();
    PyGraphicMaukaEngine_LinkPyType ();

    PYTYPE_READY_SUB ( MaukaEngine       , ToolEngine );
    PYTYPE_READY_SUB ( GraphicMaukaEngine, GraphicTool );
   
    // Identifier string can take up to 10 characters.
    __cs.addType ( "mauka", &PyTypeMaukaEngine, "<MaukaEngine>", false );


    PyObject* module = PyModule_Create ( &PyNimbus_Module );
    if ( module == NULL ) {
      cerr << "[ERROR]\n"
           << "  Failed to initialize Mauka module." << endl;
      return NULL;
    }

    Py_INCREF ( &PyTypeMaukaEngine );
    PyModule_AddObject ( module, "MaukaEngine", (PyObject*)&PyTypeMaukaEngine );
    Py_INCREF ( &PyTypeGraphicMaukaEngine );
    PyModule_AddObject ( module, "GraphicMaukaEngine", (PyObject*)&PyTypeGraphicMaukaEngine );
    return module;
  }

  
} // End of extern "C".


#endif // End of Python Module Code Part.


}  // End of Mauka namespace.
