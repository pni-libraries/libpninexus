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
//  Created on: Jan 21, 2015
//      Author: Eugen Wintersberger
//
#include <boost/test/unit_test.hpp>
#include <pni/io/parsers.hpp>
#include <pni/io/exceptions.hpp>
#include <pni/core/types.hpp>
#include "parser_test_fixture.hpp"

using namespace pni::core;
using namespace pni::io;

struct int16_parser_test_fixture : parser_test_fixture<int16>
{};

BOOST_FIXTURE_TEST_SUITE(int16_parser_test,int16_parser_test_fixture)

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_regular_value)
    {
        BOOST_TEST(p("12") == 12);
        BOOST_TEST(p("0") == 0);
        BOOST_TEST(p("-100") == -100);
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_invalid_input)
    {
        BOOST_CHECK_THROW(p("a10"),parser_error);
        BOOST_CHECK_THROW(p("-10b"),parser_error);
        BOOST_CHECK_THROW(p("10x0"),parser_error);
    }

BOOST_AUTO_TEST_SUITE_END()

