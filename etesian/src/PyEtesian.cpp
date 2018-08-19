
// -*- C++ -*-
//
// This file is part of the Coriolis Software.
// Copyright (c) UPMC/LIP6 2014-2016, All Rights Reserved
//
// +-----------------------------------------------------------------+ 
// |                   C O R I O L I S                               |
// |   E t e s i a n  -  A n a l y t i c   P l a c e r               |
// |                                                                 |
// |  Author      :                    Jean-Paul CHAPUT              |
// |  E-mail      :       Jean-Paul.Chaput@asim.lip6.fr              |
// | =============================================================== |
// |  C++ Module  :       "./PyEtesian.cpp"                          |
// +-----------------------------------------------------------------+


#include "hurricane/isobar/PyHurricane.h"
#include "hurricane/isobar/PyCell.h"
#include "etesian/PyEtesianEngine.h"
#include "etesian/PyGraphicEtesianEngine.h"


namespace Etesian {

  using std::cerr;
  using std::endl;
  using Hurricane::tab;
  using Isobar::__cs;
  using CRL::PyTypeToolEngine;
  using CRL::PyTypeGraphicTool;


#if !defined(__PYTHON_MODULE__)

// +=================================================================+
// |              "PyEtesian" Shared Library Code Part               |
// +=================================================================+


# else // End of PyHurricane Shared Library Code Part.


// +=================================================================+
// |               "PyEtesian" Python Module Code Part               |
// +=================================================================+


extern "C" {


  // +-------------------------------------------------------------+
  // |                "PyEtesian" Module Methods                   |
  // +-------------------------------------------------------------+


  static PyMethodDef PyEtesian_Methods[] =
    { {NULL, NULL, 0, NULL}     /* sentinel */
    };
  static PyModuleDef PyEtesian_Module;



  // ---------------------------------------------------------------
  // Module Initialization  :  "initEtesian ()"

  PyMODINIT_FUNC initEtesian (void) {
    cdebug_log(34,0) << "initEtesian()" << endl;

    PyEtesian_Module.m_base = PyModuleDef_HEAD_INIT;
    PyEtesian_Module.m_name = "Etesian";
    PyEtesian_Module.m_doc = NULL;
    PyEtesian_Module.m_methods = PyEtesian_Methods;

    PyEtesianEngine_LinkPyType();
    PyGraphicEtesianEngine_LinkPyType();

    PYTYPE_READY_SUB( EtesianEngine       , ToolEngine  );
    PYTYPE_READY_SUB( GraphicEtesianEngine, GraphicTool );


    PyObject* module = PyModule_Create( &PyEtesian_Module );
    if (module == NULL) {
      cerr << "[ERROR]\n"
           << "  Failed to initialize Etesian module." << endl;
      return NULL;
    }

    Py_INCREF( &PyTypeEtesianEngine );
    PyModule_AddObject( module, "EtesianEngine", (PyObject*)&PyTypeEtesianEngine );
    Py_INCREF( &PyTypeGraphicEtesianEngine );
    PyModule_AddObject( module, "GraphicEtesianEngine", (PyObject*)&PyTypeGraphicEtesianEngine );

    PyEtesianEngine_postModuleInit();
    return module;
  }

  
} // End of extern "C".


#endif // End of Python Module Code Part.


}  // End of Etesian namespace.
