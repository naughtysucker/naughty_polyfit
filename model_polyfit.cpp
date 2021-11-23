/* *****************************************************************************
 * @ Encoding: UTF-8
 * @ File Name: model_polyfit.cpp
 * @ Author: gengjinhong
 * @ Email: 2560295278@qq.com
 * @ Created Time: 2021-Nov-02(Tuesday) 14:42:55
 * @ All Rights Reserved
 * *****************************************************************************/

#include "model_polyfit.hpp"

namespace naughty
{

model_polyfit::model_polyfit(size_t dimension)
{
	m_dimension = dimension;
}

int32_t model_polyfit::set_points(const std::vector<std::pair<double, double>>& points)
{
	m_points = points;

	sort(m_points.begin(), m_points.end());

	// Remove repeated x coords
	for (std::vector<std::pair<double, double>>::iterator left_iter = m_points.begin(); left_iter < m_points.end(); left_iter++)
	{
		std::vector<std::pair<double, double>>::iterator right_iter = left_iter + 1;
		for ( ; right_iter < m_points.end(); right_iter++)
		{
			if (right_iter->first != left_iter->first)
			{
				break;
			}
		}
		if (right_iter != left_iter + 1)
		{
			size_t same_count = right_iter - left_iter;
			double y_sum = 0;
			for (std::vector<std::pair<double, double>>::iterator iter = left_iter; iter < right_iter; iter++)
			{
				y_sum += iter->second;
			}
			left_iter->second = y_sum / same_count;

			m_points.erase(left_iter + 1, right_iter);
		}
	}

	return 0;
}

double model_polyfit::polyfit_func(std::vector<double> vars, double x)
{
	assert(vars.size() == m_dimension);
	double loss = 0;

	for (size_t i = 0; i < vars.size(); i++)
	{
		loss += pow(x, m_dimension - i) * vars[i];
	}

	return loss;
}

std::vector<std::pair<double, double>> model_polyfit::get_average_limits(std::vector<std::vector<double>> vars)
{
	std::vector<std::pair<double, double>> results(vars[0].size(), std::pair<double, double>(naughty::naughty_descent::inf_pos_double(), naughty::naughty_descent::inf_neg_double()));

	for (int i = 0; i < vars.size(); i++)
	{
		for (int j = 0; j < vars[i].size(); j++)
		{
			if (vars[i][j] < results[j].first)
			{
				results[j].first = vars[i][j];
			}
			if (vars[i][j] > results[j].second)
			{
				results[j].second = vars[i][j];
			}
		}
	}

	return results;
}

std::vector<double> model_polyfit::get_result(std::vector<std::pair<double, double>> xys)
{
	// Eigen::Matrix<double, m_dimension + 1, m_dimension + 1> matrix_x;
	// Eigen::Matrix<double, m_dimension + 1, 1> matrix_y;
	Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> matrix_x;
	Eigen::Matrix<double, Eigen::Dynamic, 1> matrix_y;
	matrix_x.resize(m_dimension + 1, m_dimension + 1);
	matrix_y.resize(m_dimension + 1, 1);
	for (int i = 0; i < m_dimension + 1; i++)
	{
		for (int j = 0; j < m_dimension + 1; j++)
		{
			matrix_x(i, j) = pow(xys[i].first, m_dimension - j);
		}
	}
	for (int i = 0; i < m_dimension + 1; i++)
	{
		matrix_y(i, 0) = xys[i].second;
	}

	Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> matrix_inverse_x = matrix_x.inverse();
	Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> matrix_a = matrix_inverse_x * matrix_y;

	std::vector<double> result;

	for (int i = 0; i < m_dimension + 1; i++)
	{
		result.push_back(matrix_a(i, 0));
	}

	return result;
}

double model_polyfit::polyfit_calculate_offset(std::vector<double> vars)
{
	double loss_sum = 0;
	for (std::pair<double, double> point : m_points)
	{
		double y = polyfit_func(vars, point.first);
		loss_sum += y - point.second;
	}

	return loss_sum / m_points.size();
}

size_t model_polyfit::get_dimension()
{
	return m_dimension;
}

std::vector<std::pair<double, double>> model_polyfit::get_init_limits()
{
	std::vector<std::pair<double, double>> limits;
	if (m_points.size() >= m_dimension + 1)
	{
		std::vector<std::pair<double, double>> selected_points;
		std::vector<std::vector<double>> results;
		for(size_t t = 0; t < m_points.size() - m_dimension; t++)
		{
			std::vector<size_t> index_sets(m_points.size());
			for (size_t i = 0; i < m_points.size(); i++)
			{
				index_sets[i] = i;
			}
			for (size_t i = 0; i < m_dimension + 1; i++)
			{
				std::uniform_int_distribution<> random_int_distribution(0, index_sets.size() - 1);
				size_t index = random_int_distribution(m_random_engine);
				selected_points.push_back(m_points[index_sets[index]]);
				index_sets.erase(index_sets.begin() + index);
			}
			std::vector<double> result = get_result(selected_points);
#ifdef _DEBUG
			std::cout << "---------" << std::endl;
			for (double var : result)
			{
				std::cout << var << ", ";
			}
			std::cout << std::endl;
			std::cout << "---------" << std::endl;
#endif
			results.push_back(result);
		}
		limits = get_average_limits(results);
	}
	else
	{
		std::vector<std::vector<double>> results;
		std::vector<std::pair<double, double>> selected_points = m_points;
		sort(selected_points.begin(), selected_points.end());
		std::pair<double, double> temp_point(0, 0);
		if (selected_points.size() > 0)
		{
			temp_point = selected_points[selected_points.size() - 1];
		}
		for (size_t i = selected_points.size(); i < m_dimension + 1; i++)
		{
			temp_point.first += 1;
			temp_point.second += 1;
			selected_points.push_back(temp_point);
		}
		std::vector<double> result = get_result(selected_points);
		results.push_back(result);
		limits = get_average_limits(results);
	}
#ifdef _DEBUG
	std::cout << "limits---------begin" << std::endl;
	for (std::pair<double, double> limit : limits)
	{
		std::cout << limit.first << ", " << limit.second << "|| ";
	}
	std::cout << std::endl;
	std::cout << "limits---------end" << std::endl;
#endif
	return limits;
}

double model_polyfit::loss(const std::vector<double>& vars)
{
	// Variance
	double loss = 0;
	double loss_sum = 0;
	std::vector<double> losses;
	for (std::pair<double, double> point : m_points)
	{
		double x = point.first;
		double y = point.second;

		double single_point_loss = polyfit_func(vars, x) - y;

		losses.push_back(single_point_loss);

		loss_sum += single_point_loss;
	}

	double loss_avg = loss_sum / losses.size();

	for (double loss_per_point : losses)
	{
		double point_square_loss = pow(abs(loss_per_point - loss_avg) + 1, 2) - 1;
		loss += point_square_loss;
	}

	return loss;
}

std::vector<double> model_polyfit::get_init_steps()
{
	return std::vector<double>(0.1, m_dimension);
}

std::vector<double> model_polyfit::get_step_increase_rate()
{
	return std::vector<double>(2, m_dimension);
}

std::vector<double> model_polyfit::get_step_decrease_rate()
{
	return std::vector<double>(0.5, m_dimension);
}

}
