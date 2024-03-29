//
// (c) Copyright 2015 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
//
// This file is part of libpninexus.
//
// libpninexus is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// libpninexus is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with libpninexus.  If not, see <http://www.gnu.org/licenses/>.
// ===========================================================================
//
//  Created on: Feb 2, 2015
//  Authors:
//          Eugen Wintersberger <eugen.wintersberger@desy.de>
//          Jan Kotanski <jan.kotanski@desy.de>
//
#include <boost/test/unit_test.hpp>
#include <vector>
#include <pni/types.hpp>
#include <h5cpp/contrib/nexus/ebool.hpp>
#include <pni/container_io_config.hpp>
#include "../primitive_parsers/parser_test_fixture.hpp"

using namespace pni;

struct bool_vector_parser_test_fixture : parser_test_fixture<std::vector<bool_t>>
{
    result_type ref;
};

struct ebool_vector_parser_test_fixture : parser_test_fixture<std::vector<hdf5::datatype::EBool>>
{
    result_type ref;
};

auto False = hdf5::datatype::EBool::False;
auto True = hdf5::datatype::EBool::True;

BOOST_FIXTURE_TEST_SUITE(bool_vector_parser_test,bool_vector_parser_test_fixture)

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_default)
    {
        auto result = p("true false  true    false  false");

        BOOST_CHECK(result.size() == 5);
        ref = {true,false,true,false,false};
        BOOST_CHECK_EQUAL_COLLECTIONS(result.begin(),result.end(),
                                      ref.begin(),ref.end());
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_start_stop)
    {
        p = parser_type(container_io_config('(',')'));
        auto result = p("( true false false true  true   )");
        BOOST_CHECK(result.size() == 5);

        ref = {true,false,false,true,true};
        BOOST_CHECK_EQUAL_COLLECTIONS(result.begin(),result.end(),
                                      ref.begin(),ref.end());
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_delimiter)
    {
        p = parser_type(container_io_config(';'));
        auto result = p("true;false ;true; true ; false");

        BOOST_CHECK(result.size() == 5);
        ref = {true,false,true,true,false};
        BOOST_CHECK_EQUAL_COLLECTIONS(result.begin(),result.end(),
                                      ref.begin(),ref.end());
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_full)
    {
        p = parser_type(container_io_config('[',']',','));
        auto result = p("[true,false ,false, true  ,  true]");
        BOOST_CHECK(result.size() == 5);
        ref = {true,false,false,true,true};
        BOOST_CHECK_EQUAL_COLLECTIONS(result.begin(),result.end(),
                                      ref.begin(),ref.end());
    }

BOOST_AUTO_TEST_SUITE_END()

BOOST_FIXTURE_TEST_SUITE(ebool_vector_parser_test,ebool_vector_parser_test_fixture)

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_default)
    {
        auto result = p("true false  true    false  false");

        BOOST_CHECK(result.size() == 5);
        ref = {True,False,True,False,False};
        BOOST_CHECK_EQUAL_COLLECTIONS(result.begin(),result.end(),
                                      ref.begin(),ref.end());
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_start_stop)
    {
        p = parser_type(container_io_config('(',')'));
        auto result = p("( true false false true  true   )");
        BOOST_CHECK(result.size() == 5);

        ref = {True,False,False,True,True};
        BOOST_CHECK_EQUAL_COLLECTIONS(result.begin(),result.end(),
                                      ref.begin(),ref.end());
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_delimiter)
    {
        p = parser_type(container_io_config(';'));
        auto result = p("true;false ;true; true ; false");

        BOOST_CHECK(result.size() == 5);
        ref = {True,False,True,True,False};
        BOOST_CHECK_EQUAL_COLLECTIONS(result.begin(),result.end(),
                                      ref.begin(),ref.end());
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_full)
    {
        p = parser_type(container_io_config('[',']',','));
        auto result = p("[true,false ,false, true  ,  true]");
        BOOST_CHECK(result.size() == 5);
        ref = {True,False,False,True,True};
        BOOST_CHECK_EQUAL_COLLECTIONS(result.begin(),result.end(),
                                      ref.begin(),ref.end());
    }

BOOST_AUTO_TEST_SUITE_END()
