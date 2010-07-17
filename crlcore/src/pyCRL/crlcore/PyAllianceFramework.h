
// -*- C++ -*-
//
// This file is part of the Coriolis Software.
// Copyright (c) UPMC/LIP6 2010-2010, All Rights Reserved
//
// ===================================================================
//
// $Id$
//
// x-----------------------------------------------------------------x 
// |                                                                 |
// |                   C O R I O L I S                               |
// |          Alliance / Hurricane  Interface                        |
// |                                                                 |
// |  Author      :                    Jean-Paul CHAPUT              |
// |  E-mail      :       Jean-Paul.Chaput@asim.lip6.fr              |
// | =============================================================== |
// |  C++ Header  :       "./PyAllianceFramework.cpp"                |
// | *************************************************************** |
// |  U p d a t e s                                                  |
// |                                                                 |
// x-----------------------------------------------------------------x


#ifndef __PY_ALLIANCE_FRAMEWORK__
#define __PY_ALLIANCE_FRAMEWORK__

#include "hurricane/isobar/PyHurricane.h"
#include "crlcore/AllianceFramework.h"


namespace  CRL {


extern "C" {


// -------------------------------------------------------------------
// Python Object  :  "PyAllianceFramework".

  typedef struct {
      PyObject_HEAD
      CRL::AllianceFramework* _object;
  } PyAllianceFramework;


// -------------------------------------------------------------------
// Functions & Types exported to "PyCRL.ccp".

  extern  PyTypeObject  PyTypeAllianceFramework;
  extern  PyMethodDef   PyAllianceFramework_Methods[];

  extern  PyObject* PyAllianceFramework_Link       ( CRL::AllianceFramework* );
  extern  void      PyAllianceFramework_LinkPyType ();


#define IsPyAllianceFramework(v)  ( (v)->ob_type == &PyTypeAllianceFramework )
#define PYALLIANCEFRAMEWORK(v)    ( (PyAllianceFramework*)(v) )
#define PYALLIANCEFRAMEWORK_O(v)  ( PYALLIANCEFRAMEWORK(v)->_object )


}  // End of extern "C".


}  // End of CRL namespace.


#endif  // __PY_ALLIANCE_FRAMEWORK__
