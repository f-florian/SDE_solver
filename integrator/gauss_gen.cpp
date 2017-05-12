#include <random>

using namespace std;

namespace GaussRnd {
	namespace{
		random_device urandom("/dev/urandom");
		default_random_engine prng;
		normal_distribution<double> distr;
	}

	double getRandom()
	{
		return distr(urandom);
	}

	void init(double mean, double var)
	{
		normal_distribution<double>::param_type tmp(mean,var);
		distr.param(tmp);
	}
}
