// -*- C++ -*-
//
// This file is part of the Coriolis Software.
// Copyright (c) UPMC 2006-2016, All Rights Reserved
//
// +-----------------------------------------------------------------+ 
// |                   C O R I O L I S                               |
// |    I s o b a r  -  Hurricane / Python Interface                 |
// |                                                                 |
// |  Author      :                    Jean-Paul CHAPUT              |
// |  E-mail      :            Jean-Paul.Chaput@lip6.fr              |
// | =============================================================== |
// |  C++ Header  :  "./hurricane/isobar/PyPoint.h"                  |
// +-----------------------------------------------------------------+


#ifndef  PY_POINT_H
#define  PY_POINT_H

#include "hurricane/isobar/PyHurricane.h"
#include "hurricane/Point.h"


namespace  Isobar {

  extern "C" {

// -------------------------------------------------------------------
// Python Object  :  "PyPoint".

    typedef struct {
        PyObject_HEAD
        Hurricane::Point* _object;
    } PyPoint;


// -------------------------------------------------------------------
// Functions & Types exported to "PyHurricane.ccp".

    extern  PyTypeObject  PyTypePoint;
    extern  PyMethodDef   PyPoint_Methods[];

    extern  void      PyPoint_LinkPyType();


# define IsPyPoint(v)    ( Py_TYPE(v) == &PyTypePoint )
# define PYPOINT(v)      ( (PyPoint*)(v) )
# define PYPOINT_O(v)    ( PYPOINT(v)->_object )


  }  // extern "C".

}  // Isobar namespace.

#endif  // PY_POINT_H
