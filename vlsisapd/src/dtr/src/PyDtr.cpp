using namespace std;

#include <boost/python.hpp>
using namespace boost::python;

#include "vlsisapd/dtr/Techno.h"
#include "vlsisapd/dtr/Rules.h"
#include "vlsisapd/dtr/DTRException.h"

namespace DTR {
void translator(DTRException const& e) {
    PyErr_SetString(PyExc_UserWarning, e.what());
}


// specify that Techno::getRule & Techno::getValue & Techno::getValueAsString methods have optional arguments
BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(getRule_overloads         , getRule         , 1, 3);
BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(getValue_overloads        , getValue        , 1, 3);
BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(getValueAsString_overloads, getValueAsString, 1, 3);
// specify that Techno::addRule method has optional arguments
BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(addRule_overloads, addRule, 3, 5);

BOOST_PYTHON_MODULE(DTR) {
    // class DTR::Name
    class_<Name>("Name", init<std::string>())
        .def("getString", &Name::getString, return_value_policy<copy_const_reference>()) // return_value_policy because this method return a reference on string
        .def(self == self)
        .def(self == std::string())
        .def(self != self)
        .def(self != std::string())
        .def(self < self)
    ;

    implicitly_convertible<std::string, Name>();

    // class DTR::Rule
    class_<Rule>("Rule", init<Name, double, Name, Name, Name>())
        // accessors
        .def("getName"         , &Rule::getName         )
        .def("getType"         , &Rule::getType         )
        .def("getValue"        , &Rule::getValue        )
        .def("getValueAsString", &Rule::getValueAsString, return_value_policy<copy_const_reference>())
        .def("getRef"          , &Rule::getRef          )
        .def("getLayer1"       , &Rule::getLayer1       )
        .def("getLayer2"       , &Rule::getLayer2       )

        // modifiers
        .def("setType"         , &Rule::setType         )
        .def("setValue"        , &Rule::setValue        )
        .def("setRef"          , &Rule::setRef          )
    ; 

    // class DTR::ARule derived from DTR::Rule
    class_<ARule, bases<Rule> >("ARule", init<Name, double, Name, Name, Name>())
    ;

    // class DTR::Techno
    class_<Techno>("Techno", init<Name, Name, Name>())
        // accessors
        .def("getName"         , &Techno::getName)
        .def("getUnit"         , &Techno::getUnit)
        .def("getVersion"      , &Techno::getVersion)
        .def("getRule"         , &Techno::getRule         , getRule_overloads()[return_value_policy<reference_existing_object>()])
        .def("getValue"        , &Techno::getValue        , getValue_overloads())
        .def("getValueAsString", &Techno::getValueAsString, getValueAsString_overloads()[return_value_policy<copy_const_reference>()])
        
        // modifiers
        .def("setName"         , &Techno::setName)
        .def("setUnit"         , &Techno::setUnit)
        .def("setVersion"      , &Techno::setVersion)
        .def("addRule"         , &Techno::addRule , addRule_overloads()[return_value_policy<reference_existing_object>()])
        .def("addARule"        , &Techno::addARule, return_value_policy<reference_existing_object>())

        // others
        .def("readFromFile", &Techno::readFromFile, return_value_policy<reference_existing_object>())
        .staticmethod("readFromFile")
        .def("writeToFile" , &Techno::writeToFile)
    ;

    // DTRException translator
    register_exception_translator<DTRException>(translator)
    ;
}
}
