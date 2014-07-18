//
// (c) Copyright 2012 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
// Created on: Feb 10, 2012
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

#include <pni/io/nx/nxpath.hpp>
#include <pni/io/nx/nxlink_type.hpp>
#include <boost/current_function.hpp>
#include "h5link_test.hpp"
#include <pni/io/nx/algorithms.hpp>


CPPUNIT_TEST_SUITE_REGISTRATION(h5link_test);

//-----------------------------------------------------------------------------
void h5link_test::setUp()
{
    _file1 = h5::file_imp::create("h5link_test1.h5",true,0);
    _file2 = h5::file_imp::create("h5link_test2.h5",true,0);
}

//------------------------------------------------------------------------------
void h5link_test::tearDown()
{
    _file1.close();
    _file2.close();
}

void h5link_test::test_internal()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;

    h5::group_imp root_group(_file1.root());
    h5::group_imp g(root_group,"test");
    //the original group should be a hard link
    CPPUNIT_ASSERT(h5::h5link::link_type(root_group,"test") == nxlink_type::HARD);

    //straight forward - the link name is just a single name
    nxpath target = nxpath::from_string("/test");
    CPPUNIT_ASSERT_NO_THROW(h5::h5link::create_internal_link(target,root_group,"link_1"));
    CPPUNIT_ASSERT(root_group.has_child("link_1"));
    h5::group_imp lg(root_group.at("link_1"));
    //this should be now a soft link
    CPPUNIT_ASSERT(h5::h5link::link_type(root_group,"link_1")==nxlink_type::SOFT);

    //check for exceptions
    target = nxpath::from_string("test.nx://test/data");
    CPPUNIT_ASSERT_THROW(h5::h5link::create_internal_link(target,root_group,"link_2"),
                         pni::io::nx::nxlink_error);

    target = nxpath::from_string("/:NXentry/data");
    CPPUNIT_ASSERT_THROW(h5::h5link::create_internal_link(target,root_group,"link_3"),
                         pni::core::value_error);
}

//------------------------------------------------------------------------------
void h5link_test::test_external()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;

    h5::group_imp root_group(_file1.root());
    h5::group_imp g(root_group,"test");
    CPPUNIT_ASSERT(h5::h5link::link_type(root_group,"test") == nxlink_type::HARD);

    root_group = h5::group_imp(_file2.root());
    nxpath target = nxpath::from_string("h5link_test1.h5://test");
    //create a link to the group data in the first file
    CPPUNIT_ASSERT_NO_THROW(h5::h5link::create_external_link(target,root_group,"external"));
    CPPUNIT_ASSERT(h5::h5link::link_type(root_group,"external") 
            == nxlink_type::EXTERNAL);
    CPPUNIT_ASSERT(root_group.has_child("external"));

    //echeck exceptions
    target = nxpath::from_string("/test/data");
    CPPUNIT_ASSERT_THROW(h5::h5link::create_external_link(target,root_group,"ext2"),
            pni::io::nx::nxlink_error);


    target = nxpath::from_string("h5link_test1.h5://:NXentry/data");
    CPPUNIT_ASSERT_THROW(h5::h5link::create_external_link(target,root_group,"external"),
            pni::core::value_error);
}

//-----------------------------------------------------------------------------
void h5link_test::test_link_type()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    h5::group_imp root_group = _file1.root();
    
    //exception if child does not exist
    CPPUNIT_ASSERT_THROW(h5::h5link::link_type(root_group,"test"),key_error);
    
}