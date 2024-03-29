//
// (c) Copyright 2016 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
//  Created on: Jan 15, 2016
//  Authors:
//          Eugen Wintersberger <eugen.wintersberger@desy.de>
//          Jan Kotanski <jan.kotanski@desy.de>
//
#pragma once

#include <pni/types.hpp>
#include <vector>
#include <h5cpp/contrib/nexus/ebool.hpp>

template<typename ElementT> struct mdim_ref_data
{
    static const std::vector<ElementT> data;
};

#define PNINEXUS_GENERATE_MDIM_REFERENCE_DATA(type,...)\
    template<> struct mdim_ref_data<type>\
    {\
        static const std::vector<type> data;\
    };\
    const std::vector<type> mdim_ref_data<type>::data = {__VA_ARGS__}

PNINEXUS_GENERATE_MDIM_REFERENCE_DATA(pni::uint8,1, 2, 3);
PNINEXUS_GENERATE_MDIM_REFERENCE_DATA(pni::int8,-4, 3, -10);
PNINEXUS_GENERATE_MDIM_REFERENCE_DATA(pni::uint16,200, 300, 400);
PNINEXUS_GENERATE_MDIM_REFERENCE_DATA(pni::int16,-234, 500, -34);
PNINEXUS_GENERATE_MDIM_REFERENCE_DATA(pni::uint32,4000, 2000, 345);
PNINEXUS_GENERATE_MDIM_REFERENCE_DATA(pni::int32,23456, -3453, 40392);
PNINEXUS_GENERATE_MDIM_REFERENCE_DATA(pni::uint64,4013945,39458,14056);
PNINEXUS_GENERATE_MDIM_REFERENCE_DATA(pni::int64,-4013945, 304213, -405982);
PNINEXUS_GENERATE_MDIM_REFERENCE_DATA(pni::float32,2.3455f, -34.e+2f, -42.e-5f);
PNINEXUS_GENERATE_MDIM_REFERENCE_DATA(pni::float64,-1.233e+4, 239e-3, 30495.e-8);
PNINEXUS_GENERATE_MDIM_REFERENCE_DATA(pni::complex32,{34.f,123.e-3f},{34.e-2f,98.3f},{453.98f,-743.29f});
PNINEXUS_GENERATE_MDIM_REFERENCE_DATA(pni::complex64,{-23.,-8.203},{893e+4,-23.12},{9.e-8,732e+3});
PNINEXUS_GENERATE_MDIM_REFERENCE_DATA(pni::bool_t,true,true,false);
PNINEXUS_GENERATE_MDIM_REFERENCE_DATA(hdf5::datatype::EBool,true,true,false);

#ifndef _MSC_VER
PNINEXUS_GENERATE_MDIM_REFERENCE_DATA(pni::float128,123.24354e-4, 40394.e-4, 1.23e+5);
PNINEXUS_GENERATE_MDIM_REFERENCE_DATA(pni::complex128,{123,340},{0.,-34.9},{345.2,0.});
#endif


