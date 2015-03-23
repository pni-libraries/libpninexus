//
// (c) Copyright 2013 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
//
// This file is part of libpniio.
//
// libpniio is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// libpniio is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with libpniio.  If not, see <http://www.gnu.org/licenses/>.
// ===========================================================================
//
//  Created on: Jul 3, 2013
//      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#pragma once
#include<cppunit/TestFixture.h>
#include<cppunit/extensions/HelperMacros.h>
#include<boost/current_function.hpp>

#include <pni/core/types.hpp>
#include <pni/core/arrays.hpp>
#include <pni/io/nx/nx.hpp>
#include <pni/io/nx/algorithms/create_group.hpp>

using namespace pni::core;
using namespace pni::io::nx;

class create_group_test : public CppUnit::TestFixture
{
        CPPUNIT_TEST_SUITE(create_group_test);
        CPPUNIT_TEST(test_field);
        CPPUNIT_TEST(test_group_name_only);
        CPPUNIT_TEST(test_group_name_and_class);
        CPPUNIT_TEST(test_group_from_path);
        CPPUNIT_TEST(test_attribute);
        CPPUNIT_TEST(test_errors);
        CPPUNIT_TEST_SUITE_END();

        h5::nxfile file;
        h5::nxfield field;
        h5::nxgroup group,root;

        shape_t field_shape,attr_shape;

        
    public:
        void setUp();
        void tearDown();
        
        void test_field();
        void test_group_name_only();
        void test_group_name_and_class();
        void test_group_from_path();
        void test_attribute();
        void test_errors();

};

