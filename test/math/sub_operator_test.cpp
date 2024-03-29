//
// (c) Copyright 2012 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
//  Created on: Jul 25, 2012
//      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#ifdef __GNUG__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#endif
#include <boost/test/unit_test.hpp>
#ifdef __GNUG__
#pragma GCC diagnostic pop
#endif

#include <pni/algorithms/math/div_op.hpp>
#include "array_types.hpp"
#include "fixture.hpp"
#include "number_ranges.hpp"

using namespace pni;

BOOST_AUTO_TEST_SUITE(sub_operator_test)

    BOOST_AUTO_TEST_CASE_TEMPLATE(construction_test,TestArrayT,all_array_types)
    {
        typedef fixture<TestArrayT> fixture_type; 
        typedef sub_op<TestArrayT,TestArrayT> aa_sub_op;
        typedef sub_op<typename fixture_type::scalar_type,TestArrayT> sa_sub_op;
        typedef sub_op<TestArrayT,typename fixture_type::scalar_type> as_sub_op;

        fixture_type f((add_ranges<typename fixture_type::value_type>()));

        aa_sub_op o1(f.lhs,f.rhs);
        BOOST_CHECK_EQUAL(o1.size(),f.lhs.size());
        BOOST_CHECK_EQUAL(o1.size(),f.rhs.size());

        sa_sub_op o2(f.lhs_s,f.rhs);
        BOOST_CHECK_EQUAL(o2.size(),f.rhs.size());

        as_sub_op o3(f.lhs,f.rhs_s);
        BOOST_CHECK_EQUAL(o3.size(),f.lhs.size());
    }

    //========================================================================
    BOOST_AUTO_TEST_CASE_TEMPLATE(access_test,TestArrayT,all_array_types)
    {
        typedef fixture<TestArrayT> fixture_type; 
        typedef typename fixture_type::value_type value_type;
        typedef typename fixture_type::scalar_type scalar_type;

        fixture_type f((add_ranges<value_type>()));

        sub_op<TestArrayT,TestArrayT> o1(f.lhs,f.rhs);
        for(size_t index=0;index<o1.size();++index)
            BOOST_CHECK_EQUAL(o1[index],
                              value_type(f.lhs[index]-f.rhs[index]));

        sub_op<TestArrayT,scalar_type> o2(f.lhs,f.rhs_s);
        for(size_t index=0;index<o2.size();++index)
            BOOST_CHECK_EQUAL(o2[index], 
                              value_type(f.lhs[index]-f.rhs_s[index]));

        sub_op<scalar_type,TestArrayT> o3(f.lhs_s,f.rhs);
        for(size_t index=0;index<o3.size();++index)
            BOOST_CHECK_EQUAL(o3[index], 
                              value_type(f.lhs_s[index]-f.rhs[index]));
    }

    //========================================================================
    BOOST_AUTO_TEST_CASE_TEMPLATE(iterator_test,TestArrayT,all_array_types)
    {
        typedef fixture<TestArrayT> fixture_type; 
        typedef typename fixture_type::value_type value_type;
        typedef typename fixture_type::scalar_type scalar_type;

        fixture_type f((add_ranges<value_type>()));

        size_t index=0;
        sub_op<TestArrayT,TestArrayT> o1(f.lhs,f.rhs);
        for(auto v: o1)
        {
            BOOST_CHECK_EQUAL(v,value_type(f.lhs[index]-f.rhs[index]));
            index++;
        }

        
        sub_op<scalar_type,TestArrayT> o2(f.lhs_s,f.rhs);
        index=0;
        for(auto v: o2)
        {
            BOOST_CHECK_EQUAL(v,value_type(f.lhs_s[index]-f.rhs[index]));
            index++;
        }

        sub_op<TestArrayT,scalar_type> o3(f.lhs,f.rhs_s);
        index=0;
        for(auto v: o3)
        {
            BOOST_CHECK_EQUAL(v,value_type(f.lhs[index]-f.rhs_s[index]));
            index++;
        }
    }

    //========================================================================
    BOOST_AUTO_TEST_CASE_TEMPLATE(operator_test,TestArrayT,all_array_types)
    {
        typedef fixture<TestArrayT> fixture_type; 
        typedef typename fixture_type::value_type value_type;

        fixture_type f((add_ranges<value_type>()));
        auto result = TestArrayT::create(f.shape);

        result = f.lhs-f.rhs;
        BOOST_CHECK_EQUAL(result.size(),f.lhs.size());
        for(size_t index=0;index<result.size();++index)
            BOOST_CHECK_EQUAL(result[index],
                              value_type(f.lhs[index]-f.rhs[index]));

        result = f.lhs_scalar-f.rhs;
        BOOST_CHECK_EQUAL(result.size(),f.rhs.size());
        for(size_t index=0;index<result.size();++index)
            BOOST_CHECK_EQUAL(result[index],
                              value_type(f.lhs_scalar-f.rhs[index]));

        result = f.lhs - f.rhs_scalar;
        BOOST_CHECK_EQUAL(result.size(),f.lhs.size());
        for(size_t index=0;index<result.size();++index)
            BOOST_CHECK_EQUAL(result[index],
                              value_type(f.lhs[index]-f.rhs_scalar));
        
    }

    //========================================================================
    BOOST_AUTO_TEST_CASE_TEMPLATE(operator_on_view_test,TestArrayT,all_array_types)
    {
        typedef fixture<TestArrayT> fixture_type; 
        typedef typename fixture_type::value_type value_type;
        typedef dynamic_array<value_type> result_type;

        fixture_type f((add_ranges<value_type>()));

        auto vrhs = f.rhs(0,slice(0,3),slice(0,4));
        auto vlhs = f.lhs(0,slice(0,3),slice(0,4));

        result_type result(vlhs - vrhs);
        for(size_t index=0;index<result.size();index++)
            BOOST_CHECK_EQUAL(result[index],
                              value_type(vlhs[index]-vrhs[index]));

        result = vlhs - f.rhs_scalar;
        for(size_t index=0;index<result.size();index++)
            BOOST_CHECK_EQUAL(result[index],
                              value_type(vlhs[index]-f.rhs_scalar));

        result = f.lhs_scalar - vrhs;
        for(size_t index=0;index<result.size();index++)
            BOOST_CHECK_EQUAL(result[index],
                              value_type(f.lhs_scalar-vrhs[index]));

    }

BOOST_AUTO_TEST_SUITE_END()



