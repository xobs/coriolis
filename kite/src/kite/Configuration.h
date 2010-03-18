
// -*- C++ -*-
//
// This file is part of the Coriolis Software.
// Copyright (c) UPMC/LIP6 2008-2009, All Rights Reserved
//
// ===================================================================
//
// $Id$
//
// x-----------------------------------------------------------------x
// |                                                                 |
// |                   C O R I O L I S                               |
// |      K i t e  -  D e t a i l e d   R o u t e r                  |
// |                                                                 |
// |  Author      :                    Jean-Paul CHAPUT              |
// |  E-mail      :       Jean-Paul.Chaput@asim.lip6.fr              |
// | =============================================================== |
// |  C++ Header  :       "./Configuration.h"                        |
// | *************************************************************** |
// |  U p d a t e s                                                  |
// |                                                                 |
// x-----------------------------------------------------------------x


#ifndef  __KITE_CONFIGURATION__
#define  __KITE_CONFIGURATION__

#include  <boost/function.hpp>

#include  "katabatic/Configuration.h"


namespace Kite {

  using  std::string;
  using  Hurricane::Record;
  using  Hurricane::Layer;
  using  Hurricane::DbU;
  using  CRL::RoutingGauge;
  using  CRL::RoutingLayerGauge;


// -------------------------------------------------------------------
// Class  :  "Kite::Configuration".


  class Configuration : public Katabatic::Configuration {
    public:
      typedef  boost::function< void(void) >  PostEventCb_t;
    public:
      enum RipupTable  { BorderRipupLimit    =0
                       , StrapRipupLimit     =1
                       , LocalRipupLimit     =2
                       , GlobalRipupLimit    =3
                       , LongGlobalRipupLimit=4
                       , RipupLimitsTableSize=5
                       };
    public:
      static  void                      setDefaultEdgeCapacity ( float );
    public:
    // Constructor & Destructor.
                                         Configuration          ( Katabatic::Configuration* );
                                        ~Configuration          ();
    // Decorateds.                                              
      virtual bool                       isGMetal               ( const Layer* ) const;
      virtual size_t                     getDepth               () const;
      virtual size_t                     getLayerDepth          ( const Layer* ) const;
      virtual RoutingGauge*              getRoutingGauge        () const;
      virtual RoutingLayerGauge*         getLayerGauge          ( size_t depth ) const;
      virtual const Layer*               getRoutingLayer        ( size_t depth ) const;
      virtual Layer*                     getContactLayer        ( size_t depth ) const;
      virtual DbU::Unit                  getExtensionCap        () const;
      virtual float                      getSaturateRatio       () const;
      virtual DbU::Unit                  getGlobalThreshold     () const;
      virtual void                       setSaturateRatio       ( float );
      virtual void                       setGlobalThreshold     ( DbU::Unit );
    // Methods.
      inline  Katabatic::Configuration*  base                   ();
      inline  PostEventCb_t&             getPostEventCb         ();
      inline  float                      getExpandStep          () const;
      inline  unsigned int               getRipupCost           () const;
              unsigned int               getRipupLimit          ( unsigned int type ) const;
      inline  float                      getEdgeCapacityPercent () const;
      inline  void                       setExpandStep          ( float );
      inline  void                       setRipupCost           ( unsigned int );
              void                       setRipupLimit          ( unsigned int type, unsigned int limit );
      inline  void                       setPostEventCb         ( PostEventCb_t );
      inline  void                       setEdgeCapacityPercent ( float );
      virtual Record*                    _getRecord             () const;
      virtual string                     _getString             () const;
      virtual string                     _getTypeName           () const;

    private:
    // Static Attributes.
      static float                       _defaultEdgeCapacity;
    // Attributes.
             Katabatic::Configuration*   _base;
             PostEventCb_t               _postEventCb;
             float                       _edgeCapacityPercent;
             float                       _expandStep;
             unsigned int                _ripupLimits[RipupLimitsTableSize];
             unsigned int                _ripupCost;
    private:
                     Configuration ( const Configuration& );
      Configuration& operator=     ( const Configuration& );
  };


// Inline Functions.
  inline Katabatic::Configuration*     Configuration::base                   () { return _base; }
  inline Configuration::PostEventCb_t& Configuration::getPostEventCb         () { return _postEventCb; }
  inline unsigned int                  Configuration::getRipupCost           () const { return _ripupCost; }
  inline float                         Configuration::getExpandStep          () const { return _expandStep; }
  inline float                         Configuration::getEdgeCapacityPercent () const { return _edgeCapacityPercent; }
  inline void                          Configuration::setRipupCost           ( unsigned int cost ) { _ripupCost = cost; }
  inline void                          Configuration::setExpandStep          ( float step ) { _expandStep = step; }
  inline void                          Configuration::setPostEventCb         ( PostEventCb_t cb ) { _postEventCb = cb; }
  inline void                          Configuration::setEdgeCapacityPercent ( float percent ) { _edgeCapacityPercent = percent; }


}  // End of Kite namespace.


INSPECTOR_P_SUPPORT(Kite::Configuration);


#endif  // __KITE_CONFIGURATION__