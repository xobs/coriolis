// -*- C++ -*-
//
// This file is part of the Coriolis Software.
// Copyright (c) UPMC/LIP6 2012-2016, All Rights Reserved
//
// +-----------------------------------------------------------------+ 
// |                   C O R I O L I S                               |
// |        K a t a b a t i c  -  Routing Toolbox                    |
// |                                                                 |
// |  Author      :                    Jean-Paul CHAPUT              |
// |  E-mail      :            Jean-Paul.Chaput@lip6.fr              |
// | =============================================================== |
// |  C++ Module  :  "./PyKatabatic.cpp"                             |
// +-----------------------------------------------------------------+


#include "hurricane/isobar/PyHurricane.h"
#include "katabatic/KatabaticEngine.h"


namespace Katabatic {

  using std::cerr;
  using std::endl;
  using Hurricane::tab;
  using Isobar::__cs;


#if !defined(__PYTHON_MODULE__)

// x=================================================================x
// |             "PyKatabatic" Shared Library Code Part              |
// x=================================================================x


# else // PyHurricane Shared Library Code Part.


// x=================================================================x
// |              "PyKatabatic" Python Module Code Part              |
// x=================================================================x

extern "C" {


  static PyMethodDef PyKatabatic_Methods[] =
    { {NULL, NULL, 0, NULL}     /* sentinel */
    };
  static PyModuleDef PyKatabatic_Module;


  // ---------------------------------------------------------------
  // Module Initialization  :  "initKatabatic ()"

  PyMODINIT_FUNC initKatabatic (void) {
    cdebug_log(38,0) << "initKatabatic()" << endl;

    PyKatabatic_Module.m_base = PyModuleDef_HEAD_INIT;
    PyKatabatic_Module.m_name = "Katabatic";
    PyKatabatic_Module.m_doc = NULL;
    PyKatabatic_Module.m_methods = PyKatabatic_Methods;

    PyObject* module = PyModule_Create ( &PyKatabatic_Module );
    if ( module == NULL ) {
      cerr << "[ERROR]\n"
           << "  Failed to initialize Katabatic module." << endl;
      return NULL;
    }

    PyObject* dictionnary = PyModule_GetDict(module);
    PyObject* constant;

    LoadObjectConstant(dictionnary,EngineLoadGrByNet        ,"EngineLoadGrByNet"        );
    LoadObjectConstant(dictionnary,EngineLoadGrByGCell      ,"EngineLoadGrByGCell"      );
    LoadObjectConstant(dictionnary,EngineLayerAssignByLength,"EngineLayerAssignByLength");
    LoadObjectConstant(dictionnary,EngineLayerAssignByTrunk ,"EngineLayerAssignByTrunk" );
    LoadObjectConstant(dictionnary,EngineNoNetLayerAssign   ,"EngineNoNetLayerAssign"   );
    return module;
  }

  
} // extern "C".

#endif // Python Module Code Part.

}  // Katabatic namespace.
