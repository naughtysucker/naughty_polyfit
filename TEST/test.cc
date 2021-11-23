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
	std::vector<std::pair<double, double>> test_points{{0, 0}, {1, 100}, {2, 202}, {3, 303}, {4, 488}, {5, 505}, {6, 600}};

	std::shared_ptr<naughty::model_polyfit> model_ptr = std::make_shared<naughty::model_polyfit>(4);

	model_ptr->set_points(test_points);

	naughty::naughty_random_descent gd_obj(model_ptr);

	gd_obj.run(100, 100);

	std::list<std::pair<double, std::vector<double>>> results = gd_obj.get_results();

	double loss = results.begin()->first;
	double var0 = results.begin()->second[0];
	double var1 = results.begin()->second[1];
	double var2 = results.begin()->second[2];
	double var3 = results.begin()->second[3];

	double var4 = -((naughty::model_polyfit *)model_ptr.get())->polyfit_calculate_offset(results.begin()->second);

	printf("LOSS: %f | Variables: %f, %f, %f, %f, %f\n", loss, var0, var1, var2, var3, var4);

	printf("\nPolyfit Result:\n");
	printf("y = %fx^4 + %fx^3 + %fx^2 + %fx + %f\n", var0, var1, var2, var3, var4);

	return 0;
}
