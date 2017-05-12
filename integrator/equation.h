#ifndef EQUATION_H
#define EQUATION_H

#include <stdexcept>
#include <vector>
#include <string>

/**
 * @brief The Equation class Model of overdamped Langevin dynamics
 */
class Equation
{
public:
	/**
	 * @brief The LeaveAction enum actions to perform when leaving current well
	 */
	enum class LeaveAction {
		restartCurrent,         //<! Restart from current position (decorrelation step)
		restartBegin,           //<! Restart from starting point (dephasing step)
		quit                    //<! End step and notify (parallel step)
	};

	/**
	 * @brief The Except class Exceptions for the Equation class
	 */
	class Except : public std::runtime_error
	{
	public:
		explicit Except (const std::string& what_arg);
		explicit Except (const char* what_arg);
		const char* what () const noexcept;
	};

	/**
	 * @brief Equation conatructor
	 * @param domain is R^dimension_p
	 */
	Equation(unsigned int dimension_p);
	/**
	 * @brief setParams initialize parameters characterizing the equation
	 * @param beta_p
	 * @param grad_p given a point, returns the gradient of the potential function there
	 * @param getWell_p given a point, returns the well to which the point belongs
	 */
	void setParams(double beta_p, std::vector<double> (* grad_p)(std::vector<double>), int (* getWell_p)(std::vector<double>));
	/**
	 * @brief time get current simulation time
	 * @return simulation clock
	 */
	double time();
	/**
	 * @brief setTime set new time for the simulation
	 * @param newclock new time
	 */
	void setTime(double newclock);
	/**
	 * @brief setSpace set new position in the simulation
	 * @param newpos new position
	 */
	void setSpace(std::vector<double> newpos);
	/**
	 * @brief solve start integration
	 * @param type step type in the parallel replica method
	 * @param abort function called to check if computation should be aborted (mainly useful for parallel integration)
	 * @param step timestep in the integrtion
	 * @param iterations stop after stop steps ignored if type is quit (parallel step)
	 * @return computed solution at leaving time or 0 if aborted before completion, and total simulation time (i.e. stop time-start time)
	 */
	std::pair<std::vector<double>,double> solve(LeaveAction type, bool (*abort)(), double step, int iterations=1);

private:
	unsigned int dimension;                                       //<! Space dimension
	double beta;                                                  //<! Proportional to inverse of temperature
	std::vector<double> (* gradV)(std::vector<double>);           //<! Get the gradient of potential at given position
	int (* getWell)(std::vector<double>);                         //<! Get well assosiated to given position
	double now;                                                   //<! Current time
	std::vector<double> here;                                     //<! Current position
};

#endif // EQUATION_H
