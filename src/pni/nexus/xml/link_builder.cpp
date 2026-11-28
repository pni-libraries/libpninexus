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

#include <pni/nexus/xml/link_builder.hpp>
#include <pni/nexus/path/path.hpp>
#include <pni/nexus/predicates.hpp>
#include <pni/nexus/path/utils.hpp>
#include <h5cpp/core/filesystem.hpp>
#include <list>
#include <sstream>
#include <stdexcept>

namespace pni {
namespace nexus {
namespace xml {

namespace {

//!
//! \brief NeXus class of a target path element given by its type
//!
//! Elements are given by types, e.g. ':NXentry', or by names with the NX
//! prefix which are not names of child objects, e.g. 'NXentry', as in the
//! NeXus Data Writer.
//!
std::string element_class(const hdf5::node::Group &group,
                          const pni::nexus::Path::Element &element)
{
  const std::string &name = element.first;
  const std::string &type = element.second;
  if(name.empty())
    return type;
  if(type.empty() && name.size() > 2 && name.compare(0, 2, "NX") == 0 &&
     !group.links.exists(name))
    return name;
  return std::string();
}

//!
//! \brief converts a link target to an HDF5 path
//!
//! Elements given by types are replaced by the names of the first child
//! groups of these types. Elements which cannot be resolved, e.g. objects
//! defined later in the XML, keep their names.
//!
hdf5::Path resolve_target(const hdf5::node::Group &link_parent,
                          const pni::nexus::Path &target)
{
  std::list<std::string> names;
  bool absolute = false;
  bool valid = true;
  hdf5::node::Group current = link_parent;

  auto iter = target.begin();
  if(iter != target.end() && iter->first == "/")
  {
    absolute = true;
    current = link_parent.link().file().root();
    ++iter;
  }

  for(; iter != target.end(); ++iter)
  {
    std::string name = iter->first;
    if(name == "." || name == "..")
    {
      names.push_back(name);
      valid = false;
      continue;
    }

    if(valid)
    {
      std::string nxclass = element_class(current, *iter);
      if(!nxclass.empty())
      {
        pni::nexus::IsBaseClass is_class(nxclass);
        for(auto node: current.nodes)
          if(is_class(node))
          {
            name = node.link().path().name();
            break;
          }
      }
    }

    if(name.empty())
    {
      std::stringstream ss;
      ss << "Cannot resolve the element ':" << iter->second
         << "' of the link target [" << target << "]!";
      throw std::runtime_error(ss.str());
    }
    names.push_back(name);

    if(valid && current.nodes.exists(name) &&
       hdf5::node::is_group(current.nodes[name]))
      current = hdf5::node::Group(current.nodes[name]);
    else
      valid = false;
  }

  hdf5::Path path(names.cbegin(), names.cend());
  path.absolute(absolute);
  return path;
}

} // anonymous namespace

LinkBuilder::LinkBuilder(const Node &node):
    ObjectBuilder(node)
{}

void LinkBuilder::build(const hdf5::node::Node &parent) const
{
  
  if (!(node().has_attribute("target")))
    return;

  hdf5::node::Group link_parent(parent);
  std::string link_name = node().attribute("name").str_data();
  pni::nexus::Path link_target(pni::nexus::Path::from_string(node().attribute("target").str_data()));

  if(link_target.has_filename())
  {
    //create an external link
    fs::path file_path = link_target.filename();
    hdf5::Path target_path(link_target);

    hdf5::node::link(file_path,target_path,link_parent,link_name);

  }
  else
  {
    //create a soft link, groups can be given by their types
    hdf5::Path target_path = resolve_target(link_parent, link_target);
    hdf5::node::link(target_path,link_parent,link_name);
  }

}


} // namespace xml
} // namespace nexus
} // namespace pni
