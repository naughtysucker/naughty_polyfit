/* *****************************************************************************
 * @ Encoding: UTF-8
 * @ File Name: polyfit.h
 * @ Author: carl
 * @ Email: naughtygeng@qq.com
 * @ Created Time: 2021-Nov-24(Wednesday) 05:06:46
 * @ All Rights Reserved
 * *****************************************************************************/

#ifndef POLYFIT_H
#define POLYFIT_H

#include "model_polyfit.hpp"

namespace naughty
{

int32_t polyfit(std::vector<std::pair<double, double>> points, size_t polyfit_dimension, size_t random_descent_count, size_t descent_depth, std::vector<double> &variables);

}

#endif
