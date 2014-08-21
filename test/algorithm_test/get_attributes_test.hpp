//
// (c) Copyright 2014 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
//  Created on: Aug 21, 2014
//      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#pragma once
#include<vector>
#include<cppunit/TestFixture.h>
#include<cppunit/extensions/HelperMacros.h>
#include<boost/current_function.hpp>

#include <pni/core/types.hpp>
#include <pni/io/nx/nx.hpp>
#include <pni/io/nx/algorithms/get_attributes.hpp>

using namespace pni::core;
using namespace pni::io::nx;

class get_attributes_test : public CppUnit::TestFixture
{
        CPPUNIT_TEST_SUITE(get_attributes_test);
        CPPUNIT_TEST(test_field);
        CPPUNIT_TEST(test_group);
        CPPUNIT_TEST(test_attribute);
        CPPUNIT_TEST(test_errors);
        CPPUNIT_TEST_SUITE_END();

        h5::nxfile file;
        h5::nxfield field;
        h5::nxgroup root;
        h5::nxattribute attr;

        typedef nxobject_trait<nximp_code::HDF5>::object_type object_type;
        typedef std::vector<object_type> vector_type;
        
    public:
        void setUp();
        void tearDown();
        
        void test_field();
        void test_group();
        void test_attribute();
        void test_errors();

};
