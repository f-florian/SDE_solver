#include "equation.h"
#include <vector>
#include <cmath>
#include <cstdio>

using namespace std;

vector<double> operator* (const double op1, const vector<double> op2) noexcept
{
	auto ret=op2;
	for(auto &a:ret)
		a*=op1;
	return ret;
}

vector<double> operator+ (const vector<double> op1, const vector<double> op2)
{
	if (op1.size()!=op2.size())
		throw(Equation::Except("Dimension mismatch in vector addition "+to_string(op1.size())+" and "+to_string(op2.size())));
	vector<double> ret;
	ret.resize(op1.size());
	if(op1.size()==op2.size())
		for(unsigned int id=0; id<op1.size(); id++)
			ret[id]=op1[id]+op2[id];
	return ret;
}

namespace GaussRnd
{
	double getRandom();
	void init(double mean, double var);
}

vector<double> getRandomV(unsigned int size)
{
	vector<double> ret;
	ret.reserve(size);
	while(ret.size()<size)
		ret.push_back(GaussRnd::getRandom());
	return ret;
}

Equation::Equation(unsigned int dimension_p)
{
	dimension=dimension_p;
}

void Equation::setParams(double beta_p, vector<double> (* grad_p)(vector<double>), int (* getWell_p)(vector<double>))
{
	now=0;
	beta=beta_p;
	gradV=grad_p;
	getWell=getWell_p;
}

void Equation::setSpace(std::vector<double> newpos)
{
	if(newpos.size()!=dimension)
		throw (Except("Trying to set a point with wrong dimension in `Equation::setSpace': is "+to_string(newpos.size())+", should be "+to_string(dimension)));
	here=newpos;
}

void Equation::setTime(double newclock)
{
	now=newclock;
}

double Equation::time()
{
	return now;
}

std::pair<std::vector<double>, double> Equation::solve(LeaveAction type, bool (*abort)(), double step, int iterations)
{
	//set variance
	GaussRnd::init(0,sqrt(step*2/beta));

	//duplicate initial condition for restarting
	auto current=here;
	auto clock=now;

	//stop time, used if required by type
	auto stopclock=clock+iterations*step;

	// `next' vector, check transitions
	auto next=here;

	//integration loop
	for(;true;clock+=step) {
		//compute next position
		next=current+((-step)*(*gradV)(current))+getRandomV(next.size());
		current.swap(next);

		//check for abortion
		if((*abort)()){
			vector<double> tmp_var;
			tmp_var.resize(dimension,0);
//			printf("aborting\n");
//			fflush(stdout);
			return {tmp_var,clock-now};
		}

		//check if changed well
		if((*getWell)(next)!=(*getWell)(current)){
			switch (type) {
				case LeaveAction::restartCurrent:
					// restart simulation from current position
					stopclock=clock+iterations*step;
					break;
				case LeaveAction::restartBegin:
					// restart simulation from initial conditions
					current=next=here;
					clock=now;
					break;
				case LeaveAction::quit:
					// return result; don't advance clock for parallel step
					here=current;
					return {here, clock-now};
					break;
			}
		} else {
			if (clock>=stopclock)   //return if appropriate
				switch (type) {
					case LeaveAction::quit:
						break;
					case LeaveAction::restartBegin:
						// simulation step works without clock advance
						clock=now;
					case LeaveAction::restartCurrent:
						here=current;
						swap(now, clock);
						// return position and simulation time
						return {here, (now-clock)};
						break;
				}
		}
	}
}
