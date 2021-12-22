/* *****************************************************************************
 * @ Encoding: UTF-8
 * @ File Name: naughty_descent.cpp
 * @ Author: cal
 * @ Created Time: 2021-Oct-22(Friday) 08:48:15
 * @ SPDX-License-Identifier: Apache-2.0
 * *****************************************************************************/

#include "naughty_descent.hpp"

namespace naughty
{

naughty_descent::naughty_descent(std::shared_ptr<model_base> model_ptr, const std::vector<double>& variable_initial, const std::vector<double>& step_initial, const std::vector<double>& step_increase_rate, const std::vector<double>& step_decrease_rate)
	:   m_model_ptr(model_ptr)
	  , m_dimension(model_ptr->get_dimension())
	  , m_variables(variable_initial)
	  , m_previous_variables(variable_initial)
	  , m_derivates(m_dimension, 0)
	  , m_variable_limits(m_dimension)
	  , m_step_limits(m_dimension, 0)
	  , m_steps(step_initial)
	  , m_step_status(m_dimension, STEP_NORMAL)
	  , m_current_loss(inf_pos_double())
	  , m_status(m_dimension, STATUS_NOT_STARTED)
	  , m_variable_status(m_dimension, VAR_NORMAL)
	  , m_step_increase_rate(step_increase_rate)
	  , m_step_decrease_rate(step_decrease_rate)
{
	for (std::pair<double, double>& limit : m_variable_limits)
	{
		limit.first = inf_neg_double();
		limit.second = inf_pos_double();
	}
	if (m_variables.size() != m_dimension)
	{
		m_variables = std::vector<double>(m_dimension, 0);
	}
	if (m_steps.size() != m_dimension)
	{
		m_steps = std::vector<double>(m_dimension, 0.0001);
	}
	if (m_step_increase_rate.size() != m_dimension)
	{
		m_step_increase_rate = std::vector<double>(m_dimension, 2);
	}
	if (m_step_decrease_rate.size() != m_dimension)
	{
		m_step_decrease_rate = std::vector<double>(m_dimension, 0.5);
	}
}

size_t naughty_descent::get_dimension()
{
	return m_dimension;
}

double naughty_descent::derivate(double delta_y, double delta_x)
{
	if (delta_x == 0)
	{
		throw std::exception();
	}
	return delta_y / delta_x;
}

int32_t naughty_descent::iteration()
{
	for (size_t dimension_cursor = 0; dimension_cursor < m_dimension; dimension_cursor++)
	{
		iteration(dimension_cursor);
	}

	return 0;
}

std::vector<enum naughty_descent::status_t> naughty_descent::get_status()
{
	return m_status;
}

std::vector<double> naughty_descent::get_variables()
{
	return m_variables;
}

std::vector<enum naughty_descent::variable_status_t> naughty_descent::get_variable_status()
{
	return m_variable_status;
}

std::vector<enum naughty_descent::step_status_t> naughty_descent::get_step_status()
{
	return m_step_status;
}

int32_t naughty_descent::iteration(size_t dimension_cursor)
{
	if (std::abs(m_steps[dimension_cursor]) < m_step_limits[dimension_cursor])
	{
		m_step_status[dimension_cursor] = STEP_TOUCH_LIMIT;
		return -2;
	}
	m_previous_variables[dimension_cursor] = m_variables[dimension_cursor];
	m_variables[dimension_cursor] += m_steps[dimension_cursor];
	if (m_variables[dimension_cursor] < m_variable_limits[dimension_cursor].first || m_variables[dimension_cursor] > m_variable_limits[dimension_cursor].second)
	{
		m_variables[dimension_cursor] = m_previous_variables[dimension_cursor];
		return -1;
	}
	double next_step_loss = m_model_ptr->loss(m_variables);

	double delta_loss = next_step_loss - m_current_loss;

	if (delta_loss > 0)
	{
		// Back
		m_variables[dimension_cursor] = m_previous_variables[dimension_cursor];
		m_steps[dimension_cursor] = -m_step_decrease_rate[dimension_cursor] * m_steps[dimension_cursor];
	}
	else
	{
		// Next

		double current_derivate = derivate(delta_loss, m_steps[dimension_cursor]);

		m_derivates[dimension_cursor] = current_derivate;

		m_steps[dimension_cursor] = m_steps[dimension_cursor] * m_step_increase_rate[dimension_cursor];

		m_current_loss = next_step_loss;
	}
	return 0;
}

double naughty_descent::get_current_loss()
{
	return m_current_loss;
}

double naughty_descent::inf_pos_double()
{
	double temp = 0;
	uint64_t *u64_ptr = (uint64_t *)&temp;
	*u64_ptr = 0x7FF0000000000000;

	return temp;
}

double naughty_descent::inf_neg_double()
{
	double temp = 0;
	uint64_t *u64_ptr = (uint64_t *)&temp;
	*u64_ptr = 0xFFF0000000000000;

	return temp;
}

}
