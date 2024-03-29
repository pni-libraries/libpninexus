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
// Created on: Dec 18, 2017
//

#include <sstream>
#include <pni/nexus/path/path_object.hpp>

namespace pni {
namespace nexus {

PathObject::PathObject():
    type_(Type::None),
    attribute_(),
    group_(),
    dataset_()
{}

PathObject::PathObject(const hdf5::attribute::Attribute &attribute):
    type_(Type::Attribute),
    attribute_(attribute),
    group_(),
    dataset_()
{}

PathObject::PathObject(const hdf5::node::Link &link):
    type_(Type::None),
    attribute_(),
    group_(),
    dataset_(),
    link_()
{
  if(!link.is_resolvable())
  {
    type_ = Type::Link;
    link_ = link;
  }
  else
  {
    hdf5::node::Node node = *link;
    if(node.type() == hdf5::node::Type::Group)
    {
      group_ = node;
      type_ = Type::Group;
    }
    else if(node.type() == hdf5::node::Type::Dataset)
    {
      type_ = Type::Dataset;
      dataset_ = node;
    }
  }
}

PathObject::PathObject(const hdf5::node::Node &node):
    type_(Type::None),
    attribute_(),
    group_(),
    dataset_()
{
  switch(node.type())
  {
    case hdf5::node::Type::Dataset:
      dataset_ = node;
      type_ = Type::Dataset;
      break;
    case hdf5::node::Type::Group:
      group_ = node;
      type_ = Type::Group;
      break;
    default:
      std::stringstream ss;
      ss<<"HDF5 node ["<<node.link().path()<<"] is neither a dataset nor a group"
        <<" and thus cannot be converted to an instance of PathObject!";
      throw std::runtime_error(ss.str());
  }
}

PathObject::Type PathObject::type() const noexcept
{
  return type_;
}

PathObject::operator hdf5::attribute::Attribute() const
{
  if(type() != Type::Attribute)
  {
    std::stringstream ss;
    ss<<"PathObject stores an instance of "<<type()<<" and cannot be "
      <<"converted to an attribute!";
    throw std::runtime_error(ss.str());
  }
  return attribute_;
}

PathObject::operator hdf5::node::Group() const
{
  if(type() != Type::Group)
  {
    std::stringstream ss;
    ss<<"PathObject stores an instance of "<<type()<<" and cannot be "
      <<"converted to a group!";
    throw std::runtime_error(ss.str());
  }
  return group_;
}

PathObject::operator hdf5::node::Dataset() const
{
  if(type() != Type::Dataset)
  {
    std::stringstream ss;
    ss<<"PathObject stores an instance of "<<type()<<" and cannot be "
      <<"converted to a dataset!";
    throw std::runtime_error(ss.str());
  }
  return dataset_;
}

PathObject::operator hdf5::node::Node() const
{
  if(type()==Type::Dataset)
    return dataset_;
  else if(type() == Type::Group)
    return group_;
  else
  {
    std::stringstream ss;
    ss<<"PathObject stores an instance of "<<type()<<" and cannot be "
        <<"converted to a dataset!";
    throw std::runtime_error(ss.str());
  }
}

PathObject::operator hdf5::node::Link() const
{
  if(type() != Type::Link)
  {
    std::stringstream ss;
    ss<<"PathObject stores an instance of "<<type()<<" and cannot be "
      <<"converted to a link!";
    throw std::runtime_error(ss.str());
  }
  return link_;
}

#ifdef _MSC_VER

bool attributes_are_equal(const hdf5::attribute::Attribute &a,
                          const hdf5::attribute::Attribute &b)
{

    //
    // for attributes we have to check if they are attached to the 
    // same parent node and if they have equal names.
    //
    return (*a.parent_link() == *b.parent_link()) && 
           (a.name() == b.name());
}
bool operator==(const PathObject &a,const PathObject &b)
{
    using hdf5::node::Dataset;
    using hdf5::node::Group;
    using hdf5::node::Link;
    using hdf5::attribute::Attribute;

    if(a.type()!=b.type())
        return false;

    switch(a.type())
    {
        case PathObject::Type::Dataset:
            return static_cast<Dataset>(a)==static_cast<Dataset>(b);
        case PathObject::Type::Group:
            return static_cast<Group>(a)==static_cast<Group>(b);
        case PathObject::Type::Link:
            return static_cast<Link>(a) == static_cast<Link>(b);
        case PathObject::Type::Attribute:
            return attributes_are_equal(static_cast<Attribute>(a),
                                        static_cast<Attribute>(b));
        case PathObject::Type::None:
            return true;
    }
    return false;
}

bool operator<(const PathObject &a,const PathObject &b)
{
    using hdf5::node::Dataset;
    using hdf5::node::Group;
    using hdf5::attribute::Attribute;

    return true;
}
#endif



PathObjectList::operator NodeList() const
{
  NodeList list;
  std::copy(begin(),end(),std::back_inserter(list));
  return list;
}


PathObjectList::operator AttributeList() const
{
  AttributeList list;
  std::copy(begin(),end(),std::back_inserter(list));
  return list;
}

PathObjectList::operator GroupList() const
{
  GroupList list;
  std::copy(begin(),end(),std::back_inserter(list));
  return list;
}

PathObjectList::operator DatasetList() const
{
  DatasetList list;
  std::copy(begin(),end(),std::back_inserter(list));
  return list;
}

std::ostream &operator<<(std::ostream &stream,const PathObject::Type &type)
{
  switch(type)
  {
    case PathObject::Type::None: return stream<<"NONE";
    case PathObject::Type::Attribute: return stream<<"ATTRIBUTE";
    case PathObject::Type::Dataset: return stream<<"DATASET";
    case PathObject::Type::Group: return stream<<"GROUP";
    default:
      return stream;
  }
}




bool is_dataset(const PathObject &object) noexcept
{
  return object.type() == PathObject::Type::Dataset;
}

bool is_attribute(const PathObject &object) noexcept
{
  return object.type() == PathObject::Type::Attribute;
}

bool is_group(const PathObject &object) noexcept
{
  return object.type() == PathObject::Type::Group;
}

bool is_link(const PathObject &object) noexcept
{
  return object.type() == PathObject::Type::Link;
}

} // namespace nexus
} // namespace pni
