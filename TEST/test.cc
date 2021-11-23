/* *****************************************************************************
 * @ Encoding: UTF-8
 * @ File Name: test.cc
 * @ Author: carl
 * @ Email: naughtygeng@qq.com
 * @ Created Time: 2021-Nov-23(Tuesday) 05:32:13
 * @ All Rights Reserved
 * *****************************************************************************/

#include "model_polyfit.hpp"

int main()
{
	std::vector<std::pair<double, double>> test_points{{0, 0}, {1, 4}, {2, 16}, {3, 256}, {5, 2215}, {6, 3323}};

	std::shared_ptr<model_polyfit> model_ptr = std::make_shared<model_polyfit>(4);

	model_ptr->set_points(test_points);

	naughty::naughty_random_descent gd_obj(model_ptr);

	gd_obj.run(100, 100);

	std::list<std::pair<double, std::vector<double>>> results = gd_obj.get_results();

	double loss = results.begin()->first;
	double var0 = results.begin()->second[0];
	double var1 = results.begin()->second[1];
	double var2 = results.begin()->second[2];

	double var3 = -((model_polyfit *)model_ptr.get())->polyfit_calculate_offset(results.begin()->second);

	printf("LOSS: %f | %f, %f, %f, %f\n", loss, var0, var1, var2, var3);

	return 0;
}
