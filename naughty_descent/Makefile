# * *****************************************************************************
# * @ Encoding: UTF-8
# * @ File Name: naughty_descent/Makefile
# * @ Author: carl
# * @ Email: naughtygeng@qq.com
# * @ Created Time: 2021-Nov-24(Wednesday) 06:21:25
# * @ SPDX-License-Identifier: Apache-2.0
# * *****************************************************************************

c_source = $(wildcard *.c)
c_header = $(wildcard *.h)
cxx_source = $(wildcard *.cpp)
cxx_source += $(wildcard *.cc)
cxx_header = $(wildcard *.hpp)
cxx_header += $(wildcard *.h)

c_header_path = -I.
cxx_header_path = -I.

objs = $(c_source)
objs += $(cxx_source)
objs := $(patsubst %.c,%.o,$(objs))
objs := $(patsubst %.cc,%.o,$(objs))
objs := $(patsubst %.cpp,%.o,$(objs))

c_flags = -c -fPIC
cxx_flags = -c -fPIC -std=c++11

$(objs): $(c_source) $(cxx_source) $(c_header) $(cxx_header)
	$(if $(c_source),$(CC) $(c_source) $(c_header_path) $(c_flags),)
	$(if $(cxx_source),$(CXX) $(cxx_source) $(cxx_header_path) $(cxx_flags),)

.PHONY:clean

clean:
	$(if $(objs),$(RM) $(objs),)

