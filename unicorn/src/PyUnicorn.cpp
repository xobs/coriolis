
// -*- C++ -*-
//
// This file is part of the Coriolis Software.
// Copyright (c) UPMC/LIP6 2012-2012, All Rights Reserved
//
// +-----------------------------------------------------------------+ 
// |                   C O R I O L I S                               |
// |          U n i c o r n  -  M a i n   G U I                      |
// |                                                                 |
// |  Author      :                    Jean-Paul CHAPUT              |
// |  E-mail      :       Jean-Paul.Chaput@asim.lip6.fr              |
// | =============================================================== |
// |  C++ Module  :  "./PyUnicorn.cpp"                               |
// +-----------------------------------------------------------------+


#include "unicorn/PyUnicornGui.h"


namespace Unicorn {

  using std::cerr;
  using std::endl;
  using Hurricane::tab;
  using Hurricane::CellViewer;
  using Hurricane::PyTypeCellViewer;
  using Isobar::__cs;


#if !defined(__PYTHON_MODULE__)

// +=================================================================+
// |              "PyUnicorn" Shared Library Code Part               |
// +=================================================================+


# else // End of PyHurricane Shared Library Code Part.


// +=================================================================+
// |               "PyUnicorn" Python Module Code Part               |
// +=================================================================+


extern "C" {


  static PyMethodDef PyUnicorn_Methods[] =
    { {NULL, NULL, 0, NULL}     /* sentinel */
    };
  static PyModuleDef PyUnicorn_Module;




  // ---------------------------------------------------------------
  // Module Initialization  :  "initUnicorn ()"

  PyMODINIT_FUNC PyInit_Unicorn (void) {
    cdebug_log(46,0) << "initUnicorn()" << endl;

    PyUnicorn_Module.m_base = PyModuleDef_HEAD_INIT;
    PyUnicorn_Module.m_name = "Unicorn";
    PyUnicorn_Module.m_doc = NULL;
    PyUnicorn_Module.m_size = -1;
    PyUnicorn_Module.m_methods = PyUnicorn_Methods;

    PyUnicornGui_LinkPyType ();

    PYTYPE_READY_SUB ( UnicornGui, CellViewer );

    PyObject* module = PyModule_Create ( &PyUnicorn_Module );
    if ( module == NULL ) {
      cerr << "[ERROR]\n"
           << "  Failed to initialize Unicorn module." << endl;
      return NULL;
    }

    Py_INCREF ( &PyTypeUnicornGui );
    PyModule_AddObject ( module, "UnicornGui", (PyObject*)&PyTypeUnicornGui );
    return module;
  }

  
} // End of extern "C".

#endif // Python Module Code Part.

}  // Unicorn namespace.
