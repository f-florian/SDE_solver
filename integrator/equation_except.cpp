/****************************************************************************
 * This file is part of SDE_solve
 *
 * Copyright (C) 2017 - Francesco Florian
 *
 * SDE_solve is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * any later version.
 *
 * SDE_solve is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with SDE_solve. If not, see <http://www.gnu.org/licenses/>.
 ***************************************************************************/

#include "equation.h"

Equation::Except::Except (const std::string& what_arg) : runtime_error(what_arg){}
Equation::Except::Except (const char* what_arg) : runtime_error(what_arg){}
const char* Equation::Except::what () const noexcept {return "\0";}
