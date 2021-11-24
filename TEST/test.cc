/* *****************************************************************************
 * @ Encoding: UTF-8
 * @ File Name: test.cc
 * @ Author: carl
 * @ Email: naughtygeng@qq.com
 * @ Created Time: 2021-Nov-23(Tuesday) 05:32:13
 * @ All Rights Reserved
 * *****************************************************************************/

#include "polyfit.h"

int main()
{
	// std::vector<std::pair<double, double>> test_points{{0, 0}, {1, 100}, {2, 202}, {3, 303}, {4, 488}, {5, 505}, {6, 600}};
	std::vector<std::pair<double, double>> test_points{{0, 11234}, {1, 11694.09}, {20, 539702}, {303, 26523517954.43}, {4.4, 14614.196864}, {-5, 10725.75}, {-600, 406505950634}};

	std::vector<double> result;
	
	naughty::polyfit(test_points, 4, 100, 100, result);

	double var0 = result[0];
	double var1 = result[1];
	double var2 = result[2];
	double var3 = result[3];
	double var4 = result[4];

	printf(" Variables: %f, %f, %f, %f, %f\n", var0, var1, var2, var3, var4);

	printf("\nPolyfit Result:\n");
	printf("y = %fx^4 + %fx^3 + %fx^2 + %fx + %f\n", var0, var1, var2, var3, var4);

	return 0;
}
