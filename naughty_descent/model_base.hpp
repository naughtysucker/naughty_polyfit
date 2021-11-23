/* *****************************************************************************
 * @ Encoding: UTF-8
 * @ File Name: model_base.hpp
 * @ Author: carl
 * @ Created Time: 2021-10月-27(星期三) 00:13:16
 * @ All Rights Reserved
 * *****************************************************************************/

#ifndef MODEL_BASE_HPP
#define MODEL_BASE_HPP

#include <cstdint>
#include <cstdio>
#include <vector>
#include <utility>
#include <cmath>

namespace naughty
{

class model_base
{

	private:



	public:

	virtual size_t get_dimension() = 0;
	virtual double loss(const std::vector<double>&) = 0;
	virtual std::vector<std::pair<double, double>> get_init_limits() = 0;
	virtual std::vector<double> get_init_steps() = 0;
	virtual std::vector<double> get_step_increase_rate() = 0;
	virtual std::vector<double> get_step_decrease_rate() = 0;
};

}

#endif
