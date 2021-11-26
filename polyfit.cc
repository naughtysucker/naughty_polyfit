/* *****************************************************************************
 * @ Encoding: UTF-8
 * @ File Name: polyfit.cc
 * @ Author: carl
 * @ Email: naughtygeng@qq.com
 * @ Created Time: 2021-Nov-23(Tuesday) 05:32:13
 * @ SPDX-License-Identifier: Apache-2.0
 * *****************************************************************************/

#include "model_polyfit.hpp"

namespace naughty
{

int32_t polyfit(std::vector<std::pair<double, double>> points, size_t polyfit_dimension, size_t random_descent_count, size_t descent_depth, std::vector<double> &variables)
{

	std::shared_ptr<naughty::model_polyfit> model_ptr = std::make_shared<naughty::model_polyfit>(polyfit_dimension);

	model_ptr->set_points(points);

	naughty::naughty_random_descent gd_obj(model_ptr);

	gd_obj.run(random_descent_count, descent_depth);

	std::list<std::pair<double, std::vector<double>>> results = gd_obj.get_results();

	double loss = results.begin()->first;

	variables.clear();

	for (double var : results.begin()->second)
	{
		variables.push_back(var);
	}

	double var_const = -((naughty::model_polyfit *)model_ptr.get())->polyfit_calculate_offset(results.begin()->second);

	variables.push_back(var_const);

	return 0;
}

}
