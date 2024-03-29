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
// Created on: Dec 8, 2017
//
#include <h5cpp/hdf5.hpp>
#include <pni/nexus/xml/group_builder.hpp>
#include <pni/nexus/xml/object_builder.hpp>
#include <pni/nexus/xml/node.hpp>
#include <pni/exceptions.hpp>
#include <pni/error.hpp>

namespace pni {
namespace nexus {
namespace xml {

hdf5::node::Group group_from_node(const hdf5::node::Group &parent,
                                  const Node &group_node)
{
    using namespace pni;

    //typedef GroupT group_type;
    //typedef typename GroupT::value_type object_type;

    //fetch the name for the group
    std::string name = group_node.name();

    if((name.empty() || name == "/")  && parent.link().path().is_root())
        return parent;

    if(name.empty())
    {
      throw value_error(PNINEXUS_EXCEPTION_RECORD,
              "XML group does not provide a name!");
    }

    try{
      const hdf5::node::Group & parent_group = dynamic_cast<const hdf5::node::Group &>(parent);
      if(parent_group.nodes.exists(name)){
	std::stringstream ss;
	ss << "The '" << name << "' group at '" << parent.link().path() << "' already exists";
	throw std::runtime_error(ss.str());
      }
    }
    catch(const std::bad_cast&){
	std::stringstream ss;
	ss << "The '" << parent.link().path() << "' node is not of the Group type";
	throw std::runtime_error(ss.str());
    }
    //create the group
    hdf5::node::Group group(parent,name);

    //if the tag has a type attribute add its value as an NX_class
    //attribute
    const auto & attributes = group_node.get_child("<xmlattr>");

    for(const boost::property_tree::ptree::value_type &v: attributes){
      auto name =  v.first.data();
      if(strcmp(name, "type") == 0)
	name = "NX_class";
      else if(strcmp(name, "name") == 0)
	continue;
      group.attributes.create(name, hdf5::datatype::create<std::string>(),
			      hdf5::dataspace::Scalar()).write(v.second.data());
    }
    return group;
}

GroupBuilder::GroupBuilder(const Node &xml_node):
    ObjectBuilder(xml_node)
{}

void GroupBuilder::build(const hdf5::node::Node &parent) const
{
  using hdf5::node::Group;

  Group parent_group = parent;
  Group new_group = group_from_node(parent,node());

  ObjectBuilder builder(node());
  builder.build(new_group);
}

} // namespace xml
} // namespace nexus
} // namespace pni
