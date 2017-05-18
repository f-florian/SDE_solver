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
#include "randomnumbers.h"
#include <random>

using namespace std;

namespace GaussRnd {
	namespace{
		random_device urandom("/dev/urandom");                          //<! System "true" random number generator
#if URANDOM_ONLY != 1
		default_random_engine prng;                                     //<! Pseudorandom number generator (if configured)
#endif
		normal_distribution<double> distr;                              //<! Normal distribution object
	}

	double getRandom()
	{
#if URANDOM_ONLY != 1
#if AUTO_RESEED == 0
		return distr(prng);
#else
		auto ret=distr(pnrg);
		if(ret%AUTO_RESEED==0)
			reseed();
		return ret;
#endif
#else
		return distr(urandom);
#endif
	}

#if URANDOM_ONLY != 1
	void reseed()
	{
		prng.seed(urandom());
	}
#endif

	void init(double mean, double var)
	{
		normal_distribution<double>::param_type tmp(mean,var);
		distr.param(tmp);
#if URANDOM_ONLY != 1
		reseed();
#endif
	}
}
