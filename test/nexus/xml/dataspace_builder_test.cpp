//
// (c) Copyright 2017 DESY
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
// Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
// Created on: Dec 13, 2017
//
#include <boost/test/unit_test.hpp>
#include <pni/nexus/xml/dataspace_builder.hpp>
#include <pni/nexus/xml/dimension_node_handler.hpp>

using namespace pni::nexus;
using hdf5::dataspace::Simple;


BOOST_AUTO_TEST_SUITE(DataspaceBuilderTest)

BOOST_AUTO_TEST_CASE(default_constructed)
{
  xml::DataspaceBuilder builder;
  Simple space = builder.build();
  BOOST_CHECK(space.size() == 1);
}

BOOST_AUTO_TEST_CASE(test_case_1)
{
  xml::DataspaceBuilder builder(xml::Node::from_file("dimensions/dim1.xml"));
  Simple space = builder.build();
  BOOST_CHECK(space.size() == 55*100);
  hdf5::Dimensions current = space.current_dimensions();
  BOOST_CHECK(current.size() == 2);
}

BOOST_AUTO_TEST_CASE(test_case_2)
{
  xml::DataspaceBuilder builder(xml::Node::from_file("dimensions/dim2.xml"));
  BOOST_CHECK_THROW(builder.build(),std::runtime_error);
}

BOOST_AUTO_TEST_CASE(test_case_3)
{
  xml::DataspaceBuilder builder(xml::Node::from_file("dimensions/dim3.xml"));
  BOOST_CHECK_THROW(builder.build(),pni::key_error);
}

BOOST_AUTO_TEST_CASE(test_case_4)
{
  xml::DataspaceBuilder builder(xml::Node::from_file("dimensions/dim4.xml"));
  BOOST_CHECK_THROW(builder.build(),pni::key_error);
}

BOOST_AUTO_TEST_CASE(test_case_5)
{
  xml::DataspaceBuilder builder(xml::Node::from_file("dimensions/dim5.xml"));
  BOOST_CHECK_THROW(builder.build(),pni::key_error);
}

BOOST_AUTO_TEST_CASE(test_case_6)
{
  xml::DataspaceBuilder builder(xml::Node::from_file("dimensions/dim6.xml"));
  BOOST_CHECK_THROW(builder.build(),std::runtime_error);
}

BOOST_AUTO_TEST_CASE(extendible_known_dimensions)
{
  // fully defined dimensions are as with build()
  xml::DataspaceBuilder builder(xml::Node::from_file("dimensions/dim1.xml"));
  Simple space = builder.build_extendible();
  BOOST_CHECK(space.current_dimensions() == builder.build().current_dimensions());
  BOOST_CHECK(space.maximum_dimensions() == builder.build().maximum_dimensions());
}

BOOST_AUTO_TEST_CASE(extendible_missing_value)
{
  // the length of the first dimension is missing
  xml::DataspaceBuilder builder(xml::Node::from_file("dimensions/dim5.xml"));
  Simple space = builder.build_extendible();
  BOOST_CHECK(space.current_dimensions() == hdf5::Dimensions({0, 100}));
  BOOST_CHECK(space.maximum_dimensions() ==
              hdf5::Dimensions({H5S_UNLIMITED, 100}));
  BOOST_CHECK(builder.extendible_dimensions() ==
              hdf5::Dimensions({xml::DimensionNodeHandler::unknown_length(),
                                100}));
}

BOOST_AUTO_TEST_CASE(extendible_datasource_value)
{
  // lengths provided by datasources of the NeXus Data Writer
  xml::DataspaceBuilder builder(xml::Node::from_string(
      "<dimensions rank=\"2\">"
      "<dim index=\"1\" value=\"3\"/>"
      "<dim index=\"2\" value=\"$datasources.length\"/>"
      "</dimensions>"));
  Simple space = builder.build_extendible();
  BOOST_CHECK(space.current_dimensions() == hdf5::Dimensions({3, 0}));
  BOOST_CHECK(space.maximum_dimensions() ==
              hdf5::Dimensions({3, H5S_UNLIMITED}));
  // the strict build still raises an exception
  BOOST_CHECK_THROW(builder.build(), std::exception);
}

BOOST_AUTO_TEST_SUITE_END()
