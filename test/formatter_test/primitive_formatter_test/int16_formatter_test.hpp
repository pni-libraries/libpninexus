//
// (c) Copyright 2015 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
//  Created on: Feb 11, 2015
//      Author: Eugen Wintersberger
//

#pragma once

#include <boost/current_function.hpp>
#include <pni/io/formatters/formatter.hpp>
#include <pni/io/exceptions.hpp>
#include <pni/core/types.hpp>

#include<cppunit/TestFixture.h>
#include<cppunit/extensions/HelperMacros.h>

#include "../../TestHelpers.hpp"

using namespace pni::core;
using namespace pni::io;

class int16_formatter_test:public CppUnit::TestFixture 
{
        CPPUNIT_TEST_SUITE(int16_formatter_test);
        CPPUNIT_TEST(test_format);
        CPPUNIT_TEST_SUITE_END();

        typedef int16                 input_type; 
        typedef formatter<input_type> formatter_type;
        formatter_type format;

    public:
        void setUp();
        void tearDown();
        void test_format();
};

