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
// |  C++ Header  :  "./hurricane/isobar/PyCell.h"                   |
// +-----------------------------------------------------------------+


#ifndef PY_CELL_H
#define PY_CELL_H

#include "hurricane/isobar/PyEntity.h"
#include "hurricane/Cell.h"


namespace  Isobar {

  extern "C" {


// -------------------------------------------------------------------
// Python Object  :  "PyCell".

    typedef struct {
        PyEntity  _baseObject;
    } PyCell;


// -------------------------------------------------------------------
// Functions & Types exported to "PyHurricane.ccp".

    extern  PyTypeObject  PyTypeCell;
    extern  PyMethodDef   PyCell_Methods[];

    extern  PyObject* PyCell_Link       ( Hurricane::Cell* object );
    extern  void      PyCell_LinkPyType ();
  

#define IsPyCell(v)    (Py_TYPE(v) == &PyTypeCell)
#define PYCELL(v)      ((PyCell*)(v))
#define PYCELL_O(v)    (static_cast<Cell*>(PYCELL(v)->_baseObject._object))


  }  // extern "C".

}  // Isobar namespace.
 
#endif  // PY_CELL_H
