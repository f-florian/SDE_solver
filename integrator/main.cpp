#include "equation.h"
#include "testcase.h"
#include <vector>
#include <mpi.h>
#include <cstdio>

using namespace MPI;

int main(int argc, char *argv[])
{
	Init(argc, argv);
	TestCase::outOpen(COMM_WORLD.Get_rank());

	//Start at time 0
	double time_var=0;
	//Init from TestCase
	std::vector<double> point=TestCase::initial();
	Equation eq(TestCase::size());
	eq.setParams(TestCase::beta(), TestCase::potential(), TestCase::getWell());

	//Init equation from parameters above
	eq.setSpace(point);
	eq.setTime(time_var);
	int well=(*TestCase::getWell())(TestCase::initial());
	//Integrate
	for(int numvisit=0;numvisit<TestCase::wellVisits();numvisit++){
		if(COMM_WORLD.Get_rank()==0){
			std::tie(point, time_var)=eq.solve(Equation::LeaveAction::restartCurrent, [](){return false;}, TestCase::step(), TestCase::stepdecorr());
			well=(*TestCase::getWell())(point);
		}
		point.push_back(eq.time());
		COMM_WORLD.Bcast(point.data(), point.size(), DOUBLE, 0);
		eq.setTime(point.back());
		point.pop_back();
		eq.setSpace(point);
		std::tie(point, time_var)=eq.solve(Equation::LeaveAction::restartBegin, [](){return false;}, TestCase::step(), TestCase::stepdephase());
		std::tie(point, time_var)=eq.solve(Equation::LeaveAction::quit, [](){return COMM_WORLD.Iprobe(ANY_SOURCE, ANY_TAG);}, TestCase::step());
		bool errors=true;
		while(errors){
			if(COMM_WORLD.Iprobe(ANY_SOURCE, ANY_TAG))
				COMM_WORLD.Recv(nullptr,0,MPI_INT,ANY_SOURCE,ANY_TAG);
			else
				for(int processorrank=0; processorrank<COMM_WORLD.Get_size();processorrank++)
					if(processorrank!=COMM_WORLD.Get_rank())
						COMM_WORLD.Send(nullptr,0,MPI_INT,processorrank,0);
			point.push_back(time_var);

			errors=false;
			while(COMM_WORLD.Iprobe(ANY_SOURCE, ANY_TAG)){
				COMM_WORLD.Recv(nullptr,0,MPI_INT,ANY_SOURCE,ANY_TAG);
				errors=true;
			}
		}

		if(COMM_WORLD.Get_rank()==0){
			COMM_WORLD.Reduce(IN_PLACE, point.data(), point.size(), MPI_DOUBLE, SUM, 0);
			eq.setTime(eq.time()+point.back());
			TestCase::save(point);
			point.pop_back();
			eq.setSpace(point);
		} else {
			COMM_WORLD.Reduce(point.data(), point.data(), point.size(), MPI_DOUBLE, SUM, 0);
			point.pop_back();
		}
		printf("e");
		fflush(stdout);
	}
		TestCase::outClose();
	Finalize();
}

//int main(int argc, char *argv[])
//{
//	Init(argc, argv);
//	TestCase::outOpen(COMM_WORLD.Get_rank());
////	if(COMM_WORLD.Get_rank()==0)

//	//Start at time 0
//	double time_var=0;
//	//Init from TestCase
//	std::vector<double> point=TestCase::initial();
//	Equation eq(TestCase::size());
//	eq.setParams(TestCase::beta(), TestCase::potential(), TestCase::getWell());

//	//Init equation from parameters above
//	eq.setSpace(point);
//	eq.setTime(time_var);
//	int well=(*TestCase::getWell())(TestCase::initial());

//	//Integrate
//	if(COMM_WORLD.Get_rank()==0){
//		std::tie(point, time_var)=eq.solve(Equation::LeaveAction::restartCurrent, [](){return false;}, TestCase::step(), TestCase::stepdecorr());
//		well=(*TestCase::getWell())(point);
//	}
//	point.push_back(eq.time());
//	COMM_WORLD.Bcast(point.data(), point.size(), DOUBLE, 0);
//	eq.setTime(point.back());
//	point.pop_back();
//	eq.setSpace(point);

//	for(int numvisit=0;numvisit<TestCase::wellVisits();numvisit++){
//		std::tie(point, time_var)=eq.solve(Equation::LeaveAction::restartBegin, [](){return false;}, TestCase::step(), TestCase::stepdephase());
//		TestCase::save(point);
//	}
////	if(COMM_WORLD.Get_rank()	==0)
//		TestCase::outClose();
//	Finalize();
//}
