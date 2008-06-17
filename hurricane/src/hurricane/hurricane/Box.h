// ****************************************************************************************************
// File: Box.h
// Authors: R. Escassut
// Copyright (c) BULL S.A. 2000-2004, All Rights Reserved
// ****************************************************************************************************

#ifndef HURRICANE_BOX
#define HURRICANE_BOX

#include "hurricane/Point.h"

namespace Hurricane {



// ****************************************************************************************************
// Box declaration
// ****************************************************************************************************

class Box {
// ******

// Attributes
// **********


    private: DbU::Unit _xMin;
    private: DbU::Unit _yMin;
    private: DbU::Unit _xMax;
    private: DbU::Unit _yMax;

// constructors
// ************

    public: Box();

    public: Box(const DbU::Unit& x, const DbU::Unit& y);
    public: Box(const Point& point);
    public: Box(const DbU::Unit& x1, const DbU::Unit& y1, const DbU::Unit& x2, const DbU::Unit& y2);
    public: Box(const Point& point1, const Point& point2);

    public: Box(const Box& box);

// Operators
// *********

    public: Box& operator=(const Box& box);

    public: bool operator==(const Box& box) const;
    public: bool operator!=(const Box& box) const;

// Accessors
// *********

    public: const DbU::Unit& getXMin() const {return _xMin;};
    public: const DbU::Unit& getYMin() const {return _yMin;};
    public: const DbU::Unit& getXMax() const {return _xMax;};
    public: const DbU::Unit& getYMax() const {return _yMax;};

    public: DbU::Unit getXCenter() const {return ((_xMin + _xMax) / 2);};
    public: DbU::Unit getYCenter() const {return ((_yMin + _yMax) / 2);};
    public: Point getCenter() const {return Point(getXCenter(), getYCenter());};

    public: DbU::Unit getWidth() const {return (_xMax - _xMin);};
    public: DbU::Unit getHalfWidth() const {return (getWidth() / 2);};
    public: DbU::Unit getHeight() const {return (_yMax - _yMin);};
    public: DbU::Unit getHalfHeight() const {return (getHeight() / 2);};

    public: Box getUnion(const Box& box) const;

    public: Box getIntersection(const Box& box) const;
    public: DbU::Unit manhattanDistance(const Point& pt) const;
    public: DbU::Unit manhattanDistance(const Box& box) const;

// Predicates
// **********

    public: bool isEmpty() const;
    public: bool isFlat() const;
    public: bool isPonctual() const;

    public: bool contains(const DbU::Unit& x, const DbU::Unit& y) const;
    public: bool contains(const Point& point) const;
    public: bool contains(const Box& box) const;

    public: bool intersect(const Box& box) const;

    public: bool isConstrainedBy(const Box& box) const;

// Updators
// ********

    public: Box& makeEmpty();

    public: Box& inflate(const DbU::Unit& d);
    public: Box& inflate(const DbU::Unit& dx, const DbU::Unit& dy);
    public: Box& inflate(const DbU::Unit& dxMin, const DbU::Unit& dyMin, const DbU::Unit& dxMax, const DbU::Unit& dyMax);
    public: Box  getInflated(const DbU::Unit& d) const;
    public: Box& shrinkByFactor(double factor);   // 0 <= factor <= 1

    public: Box& merge(const DbU::Unit& x, const DbU::Unit& y);
    public: Box& merge(const Point& point);
    public: Box& merge(const DbU::Unit& x1, const DbU::Unit& y1, const DbU::Unit& x2, const DbU::Unit& y2);
    public: Box& merge(const Box& box);

    public: Box& translate(const DbU::Unit& dx, const DbU::Unit& dy);

// Others
// ******


    public: string _getTypeName() const { return _TName("Box"); };
    public: string _getString() const;
    public: Record* _getRecord() const;

};



} // End of Hurricane namespace.


INSPECTOR_PV_SUPPORT(Hurricane::Box);


#endif // HURRICANE_BOX

// ****************************************************************************************************
// Copyright (c) BULL S.A. 2000-2004, All Rights Reserved
// ****************************************************************************************************