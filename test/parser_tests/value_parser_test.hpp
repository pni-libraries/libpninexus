/*
 * (c) Copyright 2013 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 * This file is part of libpniio.
 *
 * libpniio is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * libpniio is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with libpniio.  If not, see <http://www.gnu.org/licenses/>.
 *************************************************************************
 *
 *  Created on: May 06, 2013
 *      Author: Eugen Wintersberger
 */

#pragma once

#include <boost/current_function.hpp>
#include <pni/io/parsers/value_parser.hpp>
#include <pni/core/types.hpp>

#include<cppunit/TestFixture.h>
#include<cppunit/extensions/HelperMacros.h>

#include "../TestHelpers.hpp"

using namespace pni::core;
using namespace pni::io;

class value_parser_test:public CppUnit::TestFixture 
{
	CPPUNIT_TEST_SUITE(value_parser_test);
    CPPUNIT_TEST(test_integer1_parser);
    CPPUNIT_TEST(test_integer2_parser);
    CPPUNIT_TEST(test_float1_parser);
    CPPUNIT_TEST(test_float2_parser);
    CPPUNIT_TEST(test_float3_parser);
    CPPUNIT_TEST(test_float4_parser);
	CPPUNIT_TEST_SUITE_END();

    typedef string::const_iterator iterator_t;
    typedef value_parser<iterator_t> value_parser_t;
    value_parser_t parser;

    iterator_t start_iter,stop_iter;

    string int_str1;
    string int_str2;
    string float_str1;
    string float_str2;
    string float_str3;
    string float_str4;
    value v;
public:
	void setUp();
	void tearDown();
	void test_integer1_parser();
	void test_integer2_parser();
    void test_float1_parser();
    void test_float2_parser();
    void test_float3_parser();
    void test_float4_parser();
};


