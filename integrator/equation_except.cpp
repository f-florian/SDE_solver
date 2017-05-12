#include "equation.h"

Equation::Except::Except (const std::string& what_arg) : runtime_error(what_arg){}
Equation::Except::Except (const char* what_arg) : runtime_error(what_arg){}
const char* Equation::Except::what () const noexcept {return "\0";}
