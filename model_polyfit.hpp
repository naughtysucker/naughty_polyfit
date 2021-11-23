/* *****************************************************************************
 * @ Encoding: UTF-8
 * @ File Name: model_polyfit.hpp
 * @ Author: gengjinhong
 * @ Email: 2560295278@qq.com
 * @ Created Time: 2021-Nov-02(Tuesday) 14:41:42
 * @ All Rights Reserved
 * *****************************************************************************/

#ifndef MODEL_POLYFIT_HPP
#define MODEL_POLYFIT_HPP

#include "model_base.hpp"
#include "naughty_random_descent.hpp"
#include <cassert>
#include "Eigen/Core"
#include "Eigen/Dense"

class model_polyfit : public naughty::model_base
{

	private:

		std::vector<std::pair<double, double>> m_points;

		size_t m_dimension;

		std::random_device m_random_device;
		std::default_random_engine m_random_engine{m_random_device()};
		std::uniform_int_distribution<> m_random_int_distribution;

	public:

		model_polyfit(size_t);
		size_t get_dimension() override;
		double loss(const std::vector<double>&) override;
		std::vector<std::pair<double, double>> get_init_limits() override;
		std::vector<double> get_init_steps() override;
		std::vector<double> get_step_increase_rate() override;
		std::vector<double> get_step_decrease_rate() override;

		int32_t set_points(const std::vector<std::pair<double, double>>& points);
		double polyfit_func(std::vector<double> vars, double x);
		double polyfit_calculate_offset(std::vector<double> vars);
		std::vector<std::pair<double, double>> get_average_limits(std::vector<std::vector<double>> vars);
		std::vector<double> get_result(std::vector<std::pair<double, double>> xys);
};

#endif
