

// -*- C++ -*-
//
// This file is part of the Hurricane Software.
// Copyright (c) BULL S.A. 2000-2004, All Rights Reserved
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
// |  Author      :                       Remy Escassut              |
// |  E-mail      :            Jean-Paul.Chaput@lip6.fr              |
// | =============================================================== |
// |  C++ Module  :       "./Layer.cpp"                              |
// | *************************************************************** |
// |  U p d a t e s                                                  |
// |                                                                 |
// x-----------------------------------------------------------------x


# include  "hurricane/Layer.h"
# include  "hurricane/BasicLayer.h"
# include  "hurricane/Technology.h"
# include  "hurricane/Error.h"


namespace Hurricane {


// -------------------------------------------------------------------
// Class :  "Hurricane::Layer".


  Layer::Layer ( Technology* technology
               , const Name& name
               , const DbU::Unit& minimalSize
               , const DbU::Unit& minimalSpacing
               , const DbU::Unit& pitch
               ) : DBo()
                 , _technology(technology)
                 , _name(name)
                 , _mask(0)
                 , _extractMask(0)
                 , _minimalSize(minimalSize)
                 , _minimalSpacing(minimalSpacing)
                 , _pitch(pitch)
                 , _nextOfTechnologyLayerMap(NULL)
                 , _working(false)
  {
    if ( !_technology )
      throw Error ( "Can't create " + _TName("Layer") + " : null technology" );

    if ( _name.isEmpty() )
      throw Error ( "Can't create " + _TName("Layer") + " : empty name" );

    if ( _technology->getLayer(_name) )
      throw Error ( "Can't create " + _TName("Layer") + " " + getString(_name) + " : already exists" );
  }


  Layer* Layer::getConnectorLayer () const
  { return NULL; }


  Layer* Layer::getObstructionLayer () const
  { return NULL; } 


  const Layer* Layer::getTop () const
  { return NULL; } 


  const Layer* Layer::getBottom () const
  { return NULL; } 


  const Layer* Layer::getOpposite ( const Layer* ) const
  { return NULL; } 


  Layer* Layer::getMetalAbove ( bool useWorking ) const
  { return _technology->getMetalAbove(this,useWorking); }


  Layer* Layer::getMetalBelow ( bool useWorking ) const
  { return _technology->getMetalBelow(this,useWorking); }


  Layer* Layer::getCutAbove ( bool useWorking ) const
  { return _technology->getCutAbove(this,useWorking); }


  Layer* Layer::getCutBelow ( bool useWorking ) const
  { return _technology->getCutBelow(this,useWorking); }


  DbU::Unit  Layer::getEnclosure () const
  { return 0; }


  DbU::Unit  Layer::getExtentionCap () const
  { return 0; }


  DbU::Unit  Layer::getExtentionWidth () const
  { return 0; }


  DbU::Unit  Layer::getEnclosure ( const BasicLayer* layer ) const
  { return 0; }


  DbU::Unit  Layer::getExtentionCap ( const BasicLayer* layer ) const
  { return 0; }


  DbU::Unit  Layer::getExtentionWidth ( const BasicLayer* layer ) const
  { return 0; }


  bool Layer::contains ( const Layer* layer ) const
  {
    return ( layer && ((_mask & layer->getMask()) == layer->getMask()) );
  }


  bool Layer::intersect ( const Layer* layer ) const
  {
    return ( layer->getMask().contains(_mask) );
  }


  void Layer::setName ( const Name& name )
  {
    if ( name != _name ) {
      if ( name.isEmpty() )
        throw Error ( "Can't change layer name : empty name" );

      if ( _technology->getLayer(name) )
        throw Error ( "Can't change layer name : already exists" );

      _technology->_getLayerMap()._remove(this);
      _name = name;
      _technology->_getLayerMap()._insert(this);
    }
  }


  void Layer::setMinimalSize ( const DbU::Unit& minimalSize )
  {
    _minimalSize = minimalSize;
  }


  void Layer::setMinimalSpacing ( const DbU::Unit& minimalSpacing )
  {
    _minimalSpacing = minimalSpacing;
  }


  void Layer::setPitch ( const DbU::Unit& pitch )
  {
    _pitch = pitch;
  }


  void  Layer::setEnclosure ( const BasicLayer* layer, DbU::Unit )
  {
    cerr << "[WARNING] Layer::setEnclosure() musn't be called on "
         << _getTypeName() << ": dummy implementation." << endl;
  }


  void  Layer::setExtentionCap ( const BasicLayer* layer, DbU::Unit )
  {
    cerr << "[WARNING] Layer::setExtentionCap() musn't be called on "
         << _getTypeName() << ": dummy implementation." << endl;
  }


  void  Layer::setExtentionWidth ( const BasicLayer* layer, DbU::Unit )
  {
    cerr << "[WARNING] Layer::setExtentionWidth() musn't be called on "
         << _getTypeName() << ": dummy implementation." << endl;
  }
  

  void Layer::_postCreate ()
  {
    _technology->_getLayerMap()._insert(this);
    _technology->_insertInLayerMaskMap(this);

    DBo::_postCreate();
  }


  void Layer::_preDestroy ()
  {
    DBo::_preDestroy();

    _technology->_getLayerMaskMap().erase(_mask);
    _technology->_getLayerMap()._remove(this);
  }


  string Layer::_getString() const
  {
    string s = DBo::_getString();
    s.insert(s.length() - 1, " " + getString(_name));
    return s;
  }


  Record* Layer::_getRecord() const
  {
    Record* record = DBo::_getRecord();
    if (record) {
      record->add(getSlot("Technology"    , _technology     ));
      record->add(getSlot("Name"          , &_name          ));
      record->add(getSlot("Mask"          , &_mask          ));
      record->add(getSlot("ExtractMask"   , &_extractMask   ));
      record->add(getSlot("MinimalSize"   , &_minimalSize   ));
      record->add(getSlot("MinimalSpacing", &_minimalSpacing));
      record->add(getSlot("Pitch"         , &_pitch         ));
    }
    return record;
  }


} // End of Hurricane namespace.
