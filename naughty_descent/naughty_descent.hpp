/* *****************************************************************************
 * @ Encoding: UTF-8
 * @ File Name: naughty_descent.hpp
 * @ Author: cal
 * @ Created Time: 2021-Oct-22(Friday) 08:47:28
 * @ SPDX-License-Identifier: Apache-2.0
 * *****************************************************************************/

#ifndef NAUGHTY_DESCENT_HPP
#define NAUGHTY_DESCENT_HPP

#include <cstdint>
#include <vector>
#include <memory>
#include <thread>
#include <random>
#include <utility>
#include <deque>
#include <algorithm>
#include <tuple>
#include <list>

#include "model_base.hpp"

#ifdef _DEBUG
#include <iostream>
#include <cstdio>
#endif

namespace naughty
{

class naughty_descent
{
	public:

	enum variable_status_t
	{
		VAR_NORMAL,
		VAR_TOUCH_FLOOR,
		VAR_TOUCH_CEILING,
	};

	enum status_t
	{
		STATUS_NOT_STARTED,
		STATUS_NOT_BACK,
		STATUS_BACK,
		STATUS_TWICE_BACK,
	};

	enum step_status_t
	{
		STEP_NORMAL,
		STEP_TOUCH_LIMIT,
	};

	private:

		std::shared_ptr<model_base> m_model_ptr;
		size_t m_dimension;

		std::vector<double> m_variables;
		std::vector<double> m_previous_variables;
		std::vector<enum variable_status_t> m_variable_status;
		std::vector<std::pair<double, double>> m_variable_limits;

		std::vector<double> m_derivates;
		std::vector<double> m_step_limits;
		std::vector<double> m_steps;
		std::vector<enum step_status_t> m_step_status;
		std::vector<double> m_step_increase_rate;
		std::vector<double> m_step_decrease_rate;

		std::vector<enum status_t> m_status;

		double m_current_loss;

		double derivate(double delta_y, double delta_x);
		int32_t iteration(size_t dimension_cursor);

	protected:

	public:

		naughty_descent(std::shared_ptr<model_base> model_ptr, const std::vector<double>& variable_initial = {}, const std::vector<double>& step_initial = {}, const std::vector<double>& step_increase_rate = {}, const std::vector<double>& step_decrease_rate = {});

		int32_t iteration();

		// virtual double loss(const std::vector<double>& variables) = 0;

		// 获取Back状态
		std::vector<enum status_t> get_status();
		// 获取变量是否越过极限
		std::vector<enum variable_status_t> get_variable_status();
		// 获取步长是否越过极限
		std::vector<enum step_status_t> get_step_status();

		std::vector<double> get_variables();

		size_t get_dimension();

		double get_current_loss();

		static double inf_pos_double();
		static double inf_neg_double();

};

}

#endif
