#include "testcase.h"
#include <vector>
#include <stdexcept>
#include <cstdio>
#include <string>

using namespace std;

namespace TestCase {
	namespace {
		FILE *positions, *times;

		vector<double> potential1d (vector<double> x) //d_x (x^2-1)^2=4x(x^2-1)
		{
			if(x.size()!=1)
				throw(runtime_error("Wrong vector dimension in potential 1d"));
			vector<double> ret;
			ret.resize(1,4*x.front()*(x.front()*x.front()-1));
			return ret;
		}

		int getWell1d (vector<double> x)
		{
			if(x.size()!=1)
				throw(runtime_error("Wrong vector dimension in well 1d"));
			//	printf("%lf ", x.front());
			if(x.front()<0){
				//		printf("0\t");
				return 0;
			}
			//	printf("1\t");
			return 1;
		}

		vector<double> potential2d (vector<double> x) //\grad (y^2+1)((x^2-1)^2 +1)= [ 4(y^2+1)x(x^2-1) , 2y((x^2-1)^2 +1) ]
		{
			vector<double> ret;
			if(x.size()!=2)
				throw(runtime_error("Wrong vector dimension in potential 2d"));

			ret.resize(2);
			ret[0]=4*(x[1]*x[1]+1)*x[0]*(x[0]*x[0]-1);
			ret[1]=2*x[1]*((x[0]*x[0]-1)*(x[0]*x[0]-1)+1);
			return ret;
		}

		int getWell2d (vector<double> x)
		{
			if(x.size()!=2)
				throw(runtime_error("Wrong vector dimension in well 2d"));
			if(x.front()<0)
				return 0;
			return 1;
		}
	}

	int wellVisits() {return 1000;}
	double step() {return 0.01;}
	double beta() {return 1;}
	int stepdecorr() {return 300;}
	int stepdephase() {return 500;}
	unsigned int size() {return 2;}
	vector<double> initial() {vector<double> pos; pos.resize(size(),0); return pos;}
	int (*getWell ())(vector<double>) {return &getWell2d;}
	vector<double> (*potential())(vector<double>) {return &potential2d;}
	void outOpen(int proc)
	{
		positions=fopen(("positions0"+to_string(proc)).data(), "w");
		times=fopen(("times1d"+to_string(proc)).data(), "w");
	}
	void outClose()
	{
		fclose(positions);
		fclose(times);
	}

	void save(vector<double> point)
	{
//		for(auto &x:point)
//		printf("w");
//		fflush(stdout);
		fprintf(positions, "%lf ", point.back());
		point.pop_back();
		fprintf(positions, "%lf\n", point.back());
//		fprintf(positions,"\n");
	}

	void save(double t)
	{
		fprintf(times, "%lf\n", t);
	}

	void save(int well, double time)
	{
		fprintf(times,"%d %lf\n", well, time);
	}
}
