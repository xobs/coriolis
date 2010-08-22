
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
// |            ACM/SIGDA ISCAS 89 Benchmarks                        |
// |                                                                 |
// |  Author      :                    Jean-Paul CHAPUT              |
// |  E-mail      :       Jean-Paul.Chaput@asim.lip6.fr              |
// | =============================================================== |
// |  C++ Header  :       "./crlcore/AcmSigda.h"                     |
// | *************************************************************** |
// |  U p d a t e s                                                  |
// |                                                                 |
// x-----------------------------------------------------------------x


#ifndef  __CRL_ACM_SIGDA__
#define  __CRL_ACM_SIGDA__

#include  <string>

namespace Hurricane {
  class Cell;
}


namespace CRL {

  using Hurricane::Cell;


  class AcmSigda {
    public:
      static Cell*  load ( std::string benchmark );
  };


} // End of CRL namespace.


#endif  // __CRL_ACM_SIGDA__

