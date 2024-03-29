//
// (c) Copyright 2015 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
//
// This file is part of pninexus.
//
// pninexus is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// pninexus is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with pninexus.  If not, see <http://www.gnu.org/licenses/>.
//
// ===========================================================================
//
//  Created on: Oct 15, 2015
//  Authors:
//          Eugen Wintersberger <eugen.wintersberger@desy.de>
//          Jan Kotanski <jan.kotanski@desy.de>
//
#ifdef __GNUG__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#endif
#include <boost/test/unit_test.hpp>
#ifdef __GNUG__
#pragma GCC diagnostic pop
#endif
#include <pni/types.hpp>
#include <h5cpp/contrib/nexus/ebool.hpp>
#include <iostream>

using namespace pni;

BOOST_AUTO_TEST_SUITE(id_type_map_test)

    //========================================================================
    BOOST_AUTO_TEST_CASE(test_id_type_map_uint8)
    {
        typedef id_type_map<type_id_t::UInt8> map_type;
        BOOST_CHECK((std::is_same<map_type::type,uint8>::value));
    }

    //========================================================================
    BOOST_AUTO_TEST_CASE(test_id_type_map_int8)
    {
        typedef id_type_map<type_id_t::Int8> map_type;
        BOOST_CHECK((std::is_same<map_type::type,int8>::value));
    }

    //========================================================================
    BOOST_AUTO_TEST_CASE(test_id_type_map_uint16)
    {
        typedef id_type_map<type_id_t::UInt16> map_type;
        BOOST_CHECK((std::is_same<map_type::type,uint16>::value));
    }

    //========================================================================
    BOOST_AUTO_TEST_CASE(test_id_type_map_int16)
    {
        typedef id_type_map<type_id_t::Int16> map_type;
        BOOST_CHECK((std::is_same<map_type::type,int16>::value));
    }

    //========================================================================
    BOOST_AUTO_TEST_CASE(test_id_type_map_uint32)
    {
        typedef id_type_map<type_id_t::UInt32> map_type;
        BOOST_CHECK((std::is_same<map_type::type,uint32>::value));
    }

    //========================================================================
    BOOST_AUTO_TEST_CASE(test_id_type_map_int32)
    {
        typedef id_type_map<type_id_t::Int32> map_type;
        BOOST_CHECK((std::is_same<map_type::type,int32>::value));
    }

    //========================================================================
    BOOST_AUTO_TEST_CASE(test_id_type_map_uint64)
    {
        typedef id_type_map<type_id_t::UInt64> map_type;
        BOOST_CHECK((std::is_same<map_type::type,uint64>::value));
    }

    //========================================================================
    BOOST_AUTO_TEST_CASE(test_id_type_map_int64)
    {
        typedef id_type_map<type_id_t::Int64> map_type;
        BOOST_CHECK((std::is_same<map_type::type,int64>::value));
    }

    //========================================================================
    BOOST_AUTO_TEST_CASE(test_id_type_map_float32)
    {
        typedef id_type_map<type_id_t::Float32> map_type;
        BOOST_CHECK((std::is_same<map_type::type,float32>::value));
    }

    //========================================================================
    BOOST_AUTO_TEST_CASE(test_id_type_map_float64)
    {
        typedef id_type_map<type_id_t::Float64> map_type;
        BOOST_CHECK((std::is_same<map_type::type,float64>::value));
    }

    //========================================================================
    BOOST_AUTO_TEST_CASE(test_id_type_map_float128)
    {
        typedef id_type_map<type_id_t::Float128> map_type;
        BOOST_CHECK((std::is_same<map_type::type,float128>::value));
    }

    //========================================================================
    BOOST_AUTO_TEST_CASE(test_id_type_map_complex32)
    {
        typedef id_type_map<type_id_t::Complex32> map_type;
        BOOST_CHECK((std::is_same<map_type::type,complex32>::value));
    }

    //========================================================================
    BOOST_AUTO_TEST_CASE(test_id_type_map_complex64)
    {
        typedef id_type_map<type_id_t::Complex64> map_type;
        BOOST_CHECK((std::is_same<map_type::type,complex64>::value));
    }

    //========================================================================
    BOOST_AUTO_TEST_CASE(test_id_type_map_complex128)
    {
        typedef id_type_map<type_id_t::Complex128> map_type;
        BOOST_CHECK((std::is_same<map_type::type,complex128>::value));
    }
    
    //========================================================================
    BOOST_AUTO_TEST_CASE(test_id_type_map_string)
    {
        typedef id_type_map<type_id_t::String> map_type;
        BOOST_CHECK((std::is_same<map_type::type,string>::value));
    }

    //========================================================================
    BOOST_AUTO_TEST_CASE(type_id_type_map_binary)
    {
        typedef id_type_map<type_id_t::Binary> map_type;
        BOOST_CHECK((std::is_same<map_type::type,binary>::value));
    }

    //========================================================================
    BOOST_AUTO_TEST_CASE(type_id_type_map_bool)
    {
        typedef id_type_map<type_id_t::Bool> map_type;
        BOOST_CHECK((std::is_same<map_type::type,bool_t>::value));
    }

    //========================================================================
    BOOST_AUTO_TEST_CASE(type_id_type_map_ebool)
    {
        typedef id_type_map<type_id_t::EBool> map_type;
        BOOST_CHECK((std::is_same<map_type::type,hdf5::datatype::EBool>::value));
    }

    //========================================================================
    BOOST_AUTO_TEST_CASE(type_id_type_map_none)
    {
        typedef id_type_map<type_id_t::None> map_type;
        BOOST_CHECK((std::is_same<map_type::type,none>::value));
    }


BOOST_AUTO_TEST_SUITE_END()
