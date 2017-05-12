#ifndef TESTCASE_H
#define TESTCASE_H

#include<vector>

namespace TestCase {
	int wellVisits();
	double step();
	double beta();
	int stepdecorr();
	int stepdephase();
	unsigned int size();
	std::vector<double> initial();
	int (*getWell ())(std::vector<double>);
	std::vector<double> (*potential())(std::vector<double>);
	void outOpen(int proc);
	void outClose();
	void save(std::vector<double> point);
	void save(int well, double time);
	void save(double point);
}

#endif // TESTCASE_H
