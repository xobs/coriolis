
// -*- C++ -*-
//
// This file is part of the Coriolis Software.
// Copyright (c) UPMC/LIP6 2008-2008, All Rights Reserved
//
// ===================================================================
//
// $Id$
//
// x-----------------------------------------------------------------x
// |                                                                 |
// |                   C O R I O L I S                               |
// |        K a t a b a t i c  -  Routing Toolbox                    |
// |                                                                 |
// |  Author      :                    Jean-Paul CHAPUT              |
// |  E-mail      :       Jean-Paul.Chaput@asim.lip6.fr              |
// | =============================================================== |
// |  C++ Header  :       "./GCellGrid.h"                            |
// | *************************************************************** |
// |  U p d a t e s                                                  |
// |                                                                 |
// x-----------------------------------------------------------------x


#ifndef  __KATABATIC_GCELL_GRID__
#define  __KATABATIC_GCELL_GRID__

namespace Hurricane {
  class Cell;
}

#include  "katabatic/Grid.h"
#include  "katabatic/GCell.h"


namespace Katabatic {


  using Hurricane::Cell;
  using Hurricane::_TName;

  class KatabaticEngine;


// -------------------------------------------------------------------
// Class  :  "Katabatic::GCellGrid".

 
  class GCellGrid : public Grid<GCell> {

    public:
              Cell*   getCell             () const;
              void    updateContacts      ( bool openSession=true );
              size_t  checkDensity        () const;
              size_t  updateDensity       ();
              bool    checkEdgeSaturation ( float threshold ) const;
              void    _xmlWrite           ( ostream& );
      virtual Record* _getRecord          () const;
      virtual string  _getString          () const;
      virtual string  _getTypeName        () const;

    // Attributes.
    protected:
      KatabaticEngine* _katabatic;

    // Constructors & Destructors.
    protected:
                         GCellGrid   ( KatabaticEngine* );
      virtual           ~GCellGrid   ();
              void       _postCreate ();
              void       _preDestroy ();
      static  GCellGrid* create      ( KatabaticEngine* );
    private:                          
                         GCellGrid   ( const GCellGrid& );
              GCellGrid& operator=   ( const GCellGrid& );

    // Friends.
    friend class KatabaticEngine;
  };


} // End of Katabatic namespace.


INSPECTOR_P_SUPPORT(Katabatic::GCellGrid);



#endif  // __KATABATIC_GCELL_GRID__