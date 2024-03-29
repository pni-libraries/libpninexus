//
// (c) Copyright 2013 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
//  Created on: Oct 28, 2013
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
#include <pni/arrays.hpp>

#include "array_types.hpp"
#include "../data_generator.hpp"
#include "../compiler_version.hpp"

using namespace pni;

template<typename TestArrayT> struct test_mdarray_fixture
{
    typedef TestArrayT array_type;
    typedef typename array_type::value_type value_type;
    typedef typename array_type::storage_type storage_type;
    typedef typename array_type::map_type map_type;

    typedef random_generator<value_type> generator_type;

    generator_type generator;
    shape_t shape;

    test_mdarray_fixture():
        generator(),
        shape(shape_t{2,3,5})
    {}
};

BOOST_AUTO_TEST_SUITE(test_mdarray)

    typedef boost::mpl::joint_view<all_dynamic_arrays,
#if GCC_VERSION > 40800
                                    boost::mpl::joint_view<
                                    all_fixed_dim_arrays<3>,
                                    all_static_arrays<2,3,5>
                                    >
#else
                                    all_fixed_dim_arrays<3>
#endif
                                    > array_types;
        
    template<typename ContainerT,typename...IndicesT>
    static void create_index(ContainerT &index,IndicesT ...indexes)
    {
        index = ContainerT{indexes...};
    }

    template<typename ElementT,size_t TDimN,typename ...IndicesT>
    static void create_index(std::array<ElementT,TDimN> &c,IndicesT ...indexes)
    {
        c = std::array<ElementT,TDimN>{{indexes...}};
    }

    template<
             typename IndexT,
             typename ArrayT
            >
    void test_multiindex_access_with_container()
    {
        typedef test_mdarray_fixture<ArrayT> fixture_type;
        typedef typename fixture_type::value_type value_type;

        fixture_type fixture;

        auto a = ArrayT::create(fixture.shape);
        IndexT index;
            
        for(size_t i=0;i<fixture.shape[0];i++)
            for(size_t j=0;j<fixture.shape[1];j++)
                for(size_t k=0;k<fixture.shape[2];k++)
                {
                    value_type v = fixture.generator();
                    create_index(index,i,j,k);
                    a(index) = v;
                    BOOST_CHECK_EQUAL(a(index),v);
                }

    }

    //========================================================================
    // Create a mdarray instance from a view
    BOOST_AUTO_TEST_CASE_TEMPLATE(test_view_construction,TestArrayT,array_types)
    {
        typedef test_mdarray_fixture<TestArrayT> fixture_type; 
        typedef typename fixture_type::value_type value_type;
        typedef dynamic_array<value_type> darray_type;

        fixture_type fixture; 

        auto a = darray_type::create(shape_t{100,20,30});
        std::generate(a.begin(),a.end(),fixture.generator);

        auto view = a(slice(0,2),slice(0,3),slice(0,5));
        TestArrayT target(view);
        auto view_shape = view.template shape<shape_t>();
        auto target_shape = target.template shape<shape_t>();
    
        BOOST_CHECK_EQUAL_COLLECTIONS(view_shape.begin(),view_shape.end(),
                                      target_shape.begin(),target_shape.end());
        BOOST_CHECK_EQUAL(view.size(),target.size());
        BOOST_CHECK_EQUAL(view.rank(),target.rank());
        BOOST_CHECK_EQUAL_COLLECTIONS(view.begin(),view.end(),
                                      target.begin(),target.end());
    }

    //========================================================================
    BOOST_AUTO_TEST_CASE(test_is_view_index)
    {
        BOOST_CHECK((is_view_index<size_t,size_t,size_t>::value==false));
        BOOST_CHECK((is_view_index<slice,size_t,size_t>::value==true));
        BOOST_CHECK((is_view_index<size_t,slice,size_t>::value==true));
        BOOST_CHECK((is_view_index<size_t,size_t,slice>::value==true));
    }
    
    //========================================================================
    BOOST_AUTO_TEST_CASE_TEMPLATE(test_inquery,TestArrayT,array_types)
    {
        typedef test_mdarray_fixture<TestArrayT> fixture_type;
        typedef typename fixture_type::value_type value_type;

        fixture_type fixture;
        auto a = TestArrayT::create(fixture.shape);
        BOOST_CHECK_EQUAL(a.size(),30u);
        BOOST_CHECK_EQUAL(a.rank(),3u);
        BOOST_CHECK(TestArrayT::type_id == type_id_map<value_type>::type_id);
    }

    //========================================================================
    BOOST_AUTO_TEST_CASE_TEMPLATE(test_linear_access_operator,TestArrayT,array_types)
    {
        typedef test_mdarray_fixture<TestArrayT> fixture_type;
        typedef typename fixture_type::value_type value_type;

        fixture_type fixture;

        auto a = TestArrayT::create(fixture.shape);
        const TestArrayT &ca = a;
        for(size_t index=0;index<a.size();++index)
        {
            value_type v = fixture.generator();
            a[index] = v;
            BOOST_CHECK_EQUAL(a[index],v);
            BOOST_CHECK_EQUAL(ca[index],v);
        }
    }

    //========================================================================
    BOOST_AUTO_TEST_CASE_TEMPLATE(test_linear_access_pointer,TestArrayT,array_types)
    {
        typedef test_mdarray_fixture<TestArrayT> fixture_type;
        
        fixture_type fixture; 

        auto a = TestArrayT::create(fixture.shape);
        std::generate(a.begin(),a.end(),fixture.generator);
        auto ptr = a.data();

        for(size_t index=0;index<a.size();++index)
            BOOST_CHECK_EQUAL(a[index],*(ptr++));
    }

    //========================================================================
    BOOST_AUTO_TEST_CASE_TEMPLATE(test_linear_access_at,TestArrayT,array_types)
    {
        typedef test_mdarray_fixture<TestArrayT> fixture_type;
        typedef typename fixture_type::value_type value_type;

        fixture_type fixture;

        auto a = TestArrayT::create(fixture.shape);
        const TestArrayT &ca = a;
        for(size_t index=0;index<a.size();++index)
        {
            value_type v = fixture.generator();
            a.at(index) = v;
            BOOST_CHECK_EQUAL(a.at(index),v);
            BOOST_CHECK_EQUAL(ca.at(index),v);
        }

        BOOST_CHECK_THROW(a.at(a.size()),index_error);
    }
    
    //========================================================================
    BOOST_AUTO_TEST_CASE_TEMPLATE(test_linear_access_iter,TestArrayT,array_types)
    {
        typedef test_mdarray_fixture<TestArrayT> fixture_type;
        typedef typename fixture_type::value_type value_type;

        fixture_type fixture;

        auto a = TestArrayT::create(fixture.shape);

        typename TestArrayT::iterator iter = a.begin();
        typename TestArrayT::const_iterator citer = a.begin();

        for(;iter!=a.end();++iter,++citer)
        {
            value_type v = fixture.generator();
            *iter = v;
            BOOST_CHECK_EQUAL(*iter,v);
            BOOST_CHECK_EQUAL(*citer,v);
        }
    }

    //========================================================================
    BOOST_AUTO_TEST_CASE_TEMPLATE(test_linear_access_riter,TestArrayT,array_types)
    {
        typedef test_mdarray_fixture<TestArrayT> fixture_type;
        typedef typename fixture_type::value_type value_type;

        fixture_type fixture;

        auto a = TestArrayT::create(fixture.shape);

        typename TestArrayT::reverse_iterator iter = a.rbegin();
        typename TestArrayT::const_reverse_iterator citer = a.rbegin();

        for(;iter!=a.rend();++iter,++citer)
        {
            value_type v = fixture.generator();
            *iter = v;
            BOOST_CHECK_EQUAL(*iter,v);
            BOOST_CHECK_EQUAL(*citer,v);
        }
    }

    //========================================================================
    BOOST_AUTO_TEST_CASE_TEMPLATE(test_multiindex_access,TestArrayT,array_types)
    {
        typedef test_mdarray_fixture<TestArrayT> fixture_type;
        typedef typename fixture_type::value_type value_type;

        fixture_type fixture;

        auto a = TestArrayT::create(fixture.shape);
            
        for(size_t i=0;i<fixture.shape[0];i++)
            for(size_t j=0;j<fixture.shape[1];j++)
                for(size_t k=0;k<fixture.shape[2];k++)
                {
                    value_type v = fixture.generator();
                    a(i,j,k) = v;
                    BOOST_CHECK_EQUAL(a(i,j,k),v);
                }
    }

    //========================================================================
    BOOST_AUTO_TEST_CASE_TEMPLATE(test_muldiindex_access_container,TestArrayT,array_types)
    {

        test_multiindex_access_with_container<std::vector<size_t>,TestArrayT>();
        test_multiindex_access_with_container<std::array<size_t,3>,TestArrayT>();
        test_multiindex_access_with_container<std::list<size_t>,TestArrayT>();

        test_multiindex_access_with_container<std::vector<uint64>,TestArrayT>();
        test_multiindex_access_with_container<std::array<uint64,3>,TestArrayT>();
        test_multiindex_access_with_container<std::list<uint64>,TestArrayT>();
    }

BOOST_AUTO_TEST_SUITE_END()




