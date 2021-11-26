/* *****************************************************************************
 * @ Encoding: UTF-8
 * @ File Name: naughty_random_descent.hpp
 * @ Author: carl
 * @ Created Time: 2021-10月-26(星期二) 22:09:24
 * @ SPDX-License-Identifier: Apache-2.0
 * *****************************************************************************/

#ifndef NAUGHTY_RANDOM_DESCENT_HPP
#define NAUGHTY_RANDOM_DESCENT_HPP

#include "naughty_descent.hpp"

namespace naughty
{

class naughty_random_descent // : public naughty_descent
{

	private:

		std::shared_ptr<model_base> m_model_ptr;
		std::random_device m_random_device;
		std::default_random_engine m_random_engine{m_random_device()};
		std::list<std::pair<double, std::vector<double>>> m_results;

	protected:

	public:

		naughty_random_descent(std::shared_ptr<model_base> model_ptr);

		int32_t run(size_t throw_times, size_t dig_times);

		std::list<std::pair<double, std::vector<double>>> get_results();
};

}

#endif
