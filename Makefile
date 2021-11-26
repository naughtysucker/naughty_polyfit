# * *****************************************************************************
# * @ Encoding: UTF-8
# * @ File Name: Makefile
# * @ Author: carl
# * @ Email: naughtygeng@qq.com
# * @ Created Time: 2021-Nov-24(Wednesday) 05:11:28
# * @ SPDX-License-Identifier: Apache-2.0
# * *****************************************************************************

CC=gcc
CXX=g++
AR=ar
RM=rm

c_source = $(wildcard *.c)
c_header = $(wildcard *.h)
c_header += $(wildcard ./naughty_descent/*.h)
cxx_source = $(wildcard *.cpp)
cxx_source += $(wildcard *.cc)
cxx_header = $(wildcard *.hpp)
cxx_header += $(wildcard *.h)
cxx_header += $(wildcard ./naughty_descent/*.hpp)
cxx_header += $(wildcard ./naughty_descent/*.h)

c_header_path = -I.
c_header_path += -I./naughty_descent
cxx_header_path = -I.
cxx_header_path += -I./naughty_descent
cxx_header_path += -I./eigen_source

objs = $(c_source)
objs += $(cxx_source)
objs += $(wildcard ./naughty_descent/*.c)
objs += $(wildcard ./naughty_descent/*.cc)
objs += $(wildcard ./naughty_descent/*.cpp)
objs := $(patsubst %.c,%.o,$(objs))
objs := $(patsubst %.cc,%.o,$(objs))
objs := $(patsubst %.cpp,%.o,$(objs))

c_flags = -c -fPIC
cxx_flags = -c -fPIC -std=c++11 -DEIGEN_MPL2_ONLY

libnaughty_polyfit.a: $(objs)
	$(if $(objs),$(AR) -r $@ $(objs),)

$(objs): $(c_source) $(c_header) $(cxx_source) $(cxx_header)
	make -C ./naughty_descent
	$(if $(c_source),$(CC) $(c_source) $(c_header_path) $(c_flags),)
	$(if $(cxx_source),$(CXX) $(cxx_source) $(cxx_header_path) $(cxx_flags),)

.PHONY:clean

clean:
	make -C ./naughty_descent clean
	$(if $(wildcard *.o),$(RM) $(wildcard *.o),)
	$(if $(wildcard *.a),$(RM) $(wildcard *.a),)
	$(if $(wildcard *.so),$(RM) $(wildcard *.so),)
