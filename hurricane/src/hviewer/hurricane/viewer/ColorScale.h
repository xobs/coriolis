
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
// |                  H U R R I C A N E                              |
// |     V L S I   B a c k e n d   D a t a - B a s e                 |
// |                                                                 |
// |  Author      :                    Jean-Paul CHAPUT              |
// |  E-mail      :       Jean-Paul.Chaput@asim.lip6.fr              |
// | =============================================================== |
// |  C++ Header  :       "./ColorScale.h"                           |
// | *************************************************************** |
// |  U p d a t e s                                                  |
// |                                                                 |
// x-----------------------------------------------------------------x


#ifndef  __HURRICANE_COLOR_SCALE__
#define  __HURRICANE_COLOR_SCALE__


#include  <QColor>
#include  <QBrush>
#include  "hurricane/Name.h"


namespace Hurricane {


// -------------------------------------------------------------------
// Class  :  "Hurricane::ColorScale"


  class ColorScale {

    public:
    // Types.
      enum ScaleType { Grey = 1
                     , Fire
                     , Rainbow
                     , Temperature
                     };

    public:
    // Accessors.
             void          qtAllocate   ();
      inline const Name&   getName      () const;
             QBrush        getBrush     ( size_t , int darkening ) const;

    protected:
    // Internal - Attributes.
             const Name    _name;
                   int     _red  [256];
                   int     _green[256];
                   int     _blue [256];
                   QColor *_color[256];
                   QBrush *_brush[256];

    protected:
    // Internal - Constructors & Destructors.
                           ColorScale ( const Name& );
                          ~ColorScale ();
    private:
                           ColorScale ( const ColorScale& );
             ColorScale& operator=    ( const ColorScale& );

  };


// -------------------------------------------------------------------
// Class  :  "Hurricane::FireColorScale"


  class FireColorScale : public ColorScale {
    public:
      FireColorScale ();
  };


// -------------------------------------------------------------------
// Class  :  "Hurricane::RainbowColorScale"


  class RainbowColorScale : public ColorScale {
    public:
      RainbowColorScale ();
  };


// -------------------------------------------------------------------
// Class  :  "Hurricane::TemperatureColorScale"


  class TemperatureColorScale : public ColorScale {
    public:
      TemperatureColorScale ();
  };


// Functions.
  inline const Name& ColorScale::getName () const { return _name; }


} // End of Hurricane namespace.


#endif  // __HURRICANE_COLOR_SCALE__
