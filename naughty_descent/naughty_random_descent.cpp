/* *****************************************************************************
 * @ Encoding: UTF-8
 * @ File Name: naughty_random_descent.cpp
 * @ Author: carl
 * @ Created Time: 2021-10月-26(星期二) 22:13:40
 * @ All Rights Reserved
 * *****************************************************************************/

#include "naughty_random_descent.hpp"

namespace naughty
{

naughty_random_descent::naughty_random_descent(std::shared_ptr<model_base> model_ptr)
	:
		m_model_ptr(model_ptr)
{
}

int32_t naughty_random_descent::run(size_t throw_times, size_t dig_times)
{
	std::list<std::pair<double, std::vector<double>>> results;
	for (size_t th = 0; th < throw_times; th++)
	{
		size_t dimension = m_model_ptr->get_dimension();
		std::vector<double> init_values(dimension);

		std::vector<std::uniform_real_distribution<double>> random_distributions;
		for (std::pair<double, double> limit : m_model_ptr->get_init_limits())
		{
			random_distributions.push_back(std::uniform_real_distribution<double>{limit.first, limit.second});
		}

		for (size_t dimension_cursor = 0; dimension_cursor < dimension; dimension_cursor++)
		{
			init_values[dimension_cursor] = random_distributions[dimension_cursor](m_random_engine);
		}
		naughty_descent gd_obj(m_model_ptr, init_values, m_model_ptr->get_init_steps(), m_model_ptr->get_step_increase_rate(), m_model_ptr->get_step_decrease_rate());
		for (size_t i = 0; i < dig_times; i++)
		{
			gd_obj.iteration();
		}
		results.push_back(std::pair<double, std::vector<double>>(gd_obj.get_current_loss(), gd_obj.get_variables()));
	}
	results.sort();

	m_results = results;

	return 0;
}

std::list<std::pair<double, std::vector<double>>> naughty_random_descent::get_results()
{
	return m_results;
}

}
