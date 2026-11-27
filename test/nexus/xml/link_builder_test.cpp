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
// Created on: Dec 11, 2017
//
#include <boost/test/unit_test.hpp>
#include <boost/test/unit_test.hpp>
#include <pni/nexus/xml/object_builder.hpp>
#include <pni/nexus/xml/node.hpp>
#include <h5cpp/hdf5.hpp>

using namespace hdf5;
using namespace pni;

struct LinkBuilderFixture
{
    file::File nexus_file;
    node::Group root_group;
    nexus::xml::Node xml_node;
    nexus::xml::ObjectBuilder builder;

    LinkBuilderFixture()
    {
      nexus_file = file::create("LinkBuilderTest.nxs",
                                file::AccessFlags::Truncate);
      root_group = nexus_file.root();
    }

    node::Link link(const std::string &group_path, const std::string &name)
    {
      node::Group group = node::get_node(root_group, group_path);
      return group.links[name];
    }

    hdf5::Path target(const std::string &group_path, const std::string &name)
    {
      return link(group_path, name).target().object_path();
    }
};

static const std::string structure =
    "<group name=\"scan_1\" type=\"NXentry\">"
    "<group name=\"instrument\" type=\"NXinstrument\">"
    "<group name=\"pilatus\" type=\"NXdetector\">"
    "<field name=\"data\" type=\"NX_INT32\"/>"
    "</group></group>";

BOOST_AUTO_TEST_SUITE(NexusXMLTest)

BOOST_FIXTURE_TEST_SUITE(LinkBuilder,LinkBuilderFixture)

BOOST_AUTO_TEST_CASE(targets_with_names)
{
  BOOST_CHECK_NO_THROW(xml_node = nexus::xml::Node::from_string(
      structure +
      "<group name=\"data\" type=\"NXdata\">"
      "<link name=\"names\" target=\"/scan_1/instrument/pilatus/data\"/>"
      "<link name=\"names_types\" "
      "target=\"/scan_1:NXentry/instrument:NXinstrument/pilatus/data\"/>"
      "</group></group>"));
  BOOST_CHECK_NO_THROW(builder = nexus::xml::ObjectBuilder(xml_node));
  BOOST_CHECK_NO_THROW(builder.build(root_group));

  BOOST_CHECK(target("scan_1/data", "names") ==
              hdf5::Path("/scan_1/instrument/pilatus/data"));
  BOOST_CHECK(target("scan_1/data", "names_types") ==
              hdf5::Path("/scan_1/instrument/pilatus/data"));
}

BOOST_AUTO_TEST_CASE(targets_with_types)
{
  // groups given by their types as in the NeXus Data Writer
  BOOST_CHECK_NO_THROW(xml_node = nexus::xml::Node::from_string(
      structure +
      "<group name=\"data\" type=\"NXdata\">"
      "<link name=\"types\" target=\"/NXentry/NXinstrument/NXdetector/data\"/>"
      "<link name=\"colon_types\" "
      "target=\"/:NXentry/:NXinstrument/pilatus/data\"/>"
      "</group>"
      "<link name=\"relative\" target=\"NXinstrument/NXdetector/data\"/>"
      "</group>"));
  BOOST_CHECK_NO_THROW(builder = nexus::xml::ObjectBuilder(xml_node));
  BOOST_CHECK_NO_THROW(builder.build(root_group));

  BOOST_CHECK(target("scan_1/data", "types") ==
              hdf5::Path("/scan_1/instrument/pilatus/data"));
  BOOST_CHECK(target("scan_1/data", "colon_types") ==
              hdf5::Path("/scan_1/instrument/pilatus/data"));
  BOOST_CHECK(target("scan_1", "relative") ==
              hdf5::Path("instrument/pilatus/data"));
  BOOST_CHECK(link("scan_1/data", "types").is_resolvable());
}

BOOST_AUTO_TEST_CASE(targets_defined_later)
{
  // targets which do not exist yet keep their names
  BOOST_CHECK_NO_THROW(xml_node = nexus::xml::Node::from_string(
      "<group name=\"scan_1\" type=\"NXentry\">"
      "<group name=\"data\" type=\"NXdata\">"
      "<link name=\"later\" target=\"/scan_1/sample/name\"/>"
      "</group>"
      "<group name=\"sample\" type=\"NXsample\">"
      "<field name=\"name\" type=\"NX_CHAR\">water</field>"
      "</group></group>"));
  BOOST_CHECK_NO_THROW(builder = nexus::xml::ObjectBuilder(xml_node));
  BOOST_CHECK_NO_THROW(builder.build(root_group));

  BOOST_CHECK(target("scan_1/data", "later") ==
              hdf5::Path("/scan_1/sample/name"));
  BOOST_CHECK(link("scan_1/data", "later").is_resolvable());
}

BOOST_AUTO_TEST_CASE(unresolved_types)
{
  BOOST_CHECK_NO_THROW(xml_node = nexus::xml::Node::from_string(
      "<group name=\"scan_1\" type=\"NXentry\">"
      "<link name=\"missing\" target=\"/scan_1/:NXsample/name\"/>"
      "</group>"));
  BOOST_CHECK_NO_THROW(builder = nexus::xml::ObjectBuilder(xml_node));
  BOOST_CHECK_THROW(builder.build(root_group), std::runtime_error);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()
