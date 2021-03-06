// ****************************************************************************************************
// File: ./hurricane/SharedPathes.h
// Authors: R. Escassut
// Copyright (c) BULL S.A. 2000-2016, All Rights Reserved
//
// This file is part of Hurricane.
//
// Hurricane is free software: you can redistribute it  and/or  modify it under the  terms  of the  GNU
// Lesser General Public License as published by the Free Software Foundation, either version 3 of  the
// License, or (at your option) any later version.
//
// Hurricane is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without  even
// the implied warranty of MERCHANTABILITY or FITNESS FOR A  PARTICULAR  PURPOSE. See  the  Lesser  GNU
// General Public License for more details.
//
// You should have received a copy of the Lesser GNU General Public License along  with  Hurricane.  If
// not, see <http://www.gnu.org/licenses/>.
// ****************************************************************************************************

#ifndef HURRICANE_SHARED_PATHES
#define HURRICANE_SHARED_PATHES

#include "hurricane/Collection.h"

namespace Hurricane {

class SharedPath;



// ****************************************************************************************************
// SharedPathes declaration
// ****************************************************************************************************

typedef GenericCollection<SharedPath*> SharedPathes;



// ****************************************************************************************************
// SharedPathLocator declaration
// ****************************************************************************************************

typedef GenericLocator<SharedPath*> SharedPathLocator;



// ****************************************************************************************************
// SharedPathFilter declaration
// ****************************************************************************************************

typedef GenericFilter<SharedPath*> SharedPathFilter;



// ****************************************************************************************************
// for_each_shared_path declaration
// ****************************************************************************************************

#define for_each_shared_path(sharedPath, sharedPathes)\
/*****************************************************/\
{\
	SharedPathLocator _locator = sharedPathes.getLocator();\
	while (_locator.isValid()) {\
		SharedPath* sharedPath = _locator.getElement();\
		_locator.progress();



} // End of Hurricane namespace.

#endif // HURRICANE_SHARED_PATHES


// ****************************************************************************************************
// Copyright (c) BULL S.A. 2000-2016, All Rights Reserved
// ****************************************************************************************************
