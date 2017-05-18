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
#ifndef RANDOMNUMBERS_H
#define RANDOMNUMBERS_H

/**
 * Collection of functions for getting samples of a normal random variable
 *
 * The preprocessor variable URANDOM_ONLY is used to control wether to use system random numbers generator (if set to 1)
 * or a pseudorandom number generator (otherwise).
 *
 * If the pseudorandom number generator is used the preprocessor variable AUTO_RESEED controls how often the generator seed is reset using the
 */
namespace GaussRnd {
	/**
	 * @brief getRandom get a sample of the normal distribution.
	 * @return a sample of the normal distribution
	 */
	double getRandom();
#if URANDOM_ONLY != 1
	/**
	 * @brief reseed reset the seed of the pseudorandom number generator using a system random number
	 *
	 * Not compiled if URANDOM_ONLY is 1
	 */
	void reseed();
#endif

	/**
	 * @brief init set the parameters of the normal distribution
	 *
	 * This function also seeds the pseudorandom number generator if it is used
	 * @param mean mean value
	 * @param var variance
	 */
	void init(double mean, double var);
}

#endif
