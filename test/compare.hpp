//!
//! (c) Copyright 2013 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
//!
//! This file is part of pninexus.
//!
//! pninexus is free software: you can redistribute it and/or modify
//! it under the terms of the GNU General Public License as published by
//! the Free Software Foundation, either version 2 of the License, or
//! (at your option) any later version.
//!
//! pninexus is distributed in the hope that it will be useful,
//! but WITHOUT ANY WARRANTY; without even the implied warranty of
//! MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//! GNU General Public License for more details.
//!
//! You should have received a copy of the GNU General Public License
//! along with pninexus.  If not, see <http://www.gnu.org/licenses/>.
//!
//! ===========================================================================
//!
//!  Created on: Oct 29, 2013
//!      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//!
#pragma once
#include <type_traits>
#include <complex>
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include <pni/types.hpp>
#include <pni/arrays.hpp>
#include <pni/type_erasures.hpp>

using namespace pni;
/*
What is all this fuzz about:
When we want to check the equality with CPPUNIT typically the macro 
CPPUNIT_ASSERT('expression') will be called. However, for floating point numbers
CPPUNIT_ASSERT_DOUBLES_EQUAL(a,b,error) shoud be used. We thus need a special
overload for this situation which should be rather easy to do. 

For all types implementing the == operator a simple CPPUNIT_ASSERT will do 
except for floating point values.

*/


//----------------------------------------------------------------------------
template< 
         typename OperandAT,
         typename OperandBT,
         bool is_float
        >
struct comperator;

//----------------------------------------------------------------------------
template<
         typename OperandAT,
         typename OperandBT
        >
struct comperator<OperandAT,OperandBT,false>
{
    static void compare(const OperandAT &a,const OperandBT &b)
    {
        CPPUNIT_ASSERT(a==b);
    }
};

//----------------------------------------------------------------------------
template<
         typename OperandAT,
         typename OperandBT
        >
struct comperator<OperandAT,OperandBT,true >
{
    static void compare(const OperandAT &a,const OperandBT &b)
    {
        CPPUNIT_ASSERT_DOUBLES_EQUAL(a,b,1.e-12);
    }
};

//----------------------------------------------------------------------------
//!
//! \brief compare integers and strings
//! 
//! This template function compares two values which are integers and strings. 
//! 
template<
         typename OperandAT,
         typename OperandBT
        > 
void compare(const OperandAT &a,const OperandBT &b)
{
    static const bool is_float = std::is_floating_point<OperandAT>::value || 
                                 std::is_floating_point<OperandBT>::value;
    comperator<OperandAT,OperandBT,is_float>::compare(a,b);
}


template<
         typename OperandAT,
         typename OperandBT
        >
void compare(OperandAT &&a,OperandBT &&b)
{
    static const bool is_float = std::is_floating_point<OperandAT>::value || 
                                 std::is_floating_point<OperandBT>::value;
    comperator<OperandAT,OperandBT,is_float>::compare(a,b);
}

//---------------------------------------------------------------------------
//!
//! \brief compare complex
//! 
//! Function template comparing two complex numbers
//!
template<typename GeneralT>
void compare(const std::complex<GeneralT> &a,const std::complex<GeneralT> &b)
{
    compare(a.real(),b.real());
    compare(a.imag(),b.imag());
}

//----------------------------------------------------------------------------
//!
//! \brief comparison of value_ref instances
//!
template<typename GeneralT> void compare(const value_ref &a, const GeneralT &b)
{
    type_id_t t_id = type_id_map<GeneralT>::type_id;
    type_id_t r_id = a.type_id();

    if(t_id == r_id) compare(a.as<GeneralT>(),b);
    
}


//----------------------------------------------------------------------------
template<typename GeneralT> void compare(const GeneralT &a,const value_ref &b)
{
    compare(b,a);
}

//----------------------------------------------------------------------------
void compare(const value_ref &a,const value_ref &b);

//----------------------------------------------------------------------------
void compare(const value &a,const value &b);

//----------------------------------------------------------------------------
void compare(const string &a,const string &b);

