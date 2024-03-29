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
#pragma once

#include <pni/nexus/xml/node.hpp>
#include <pni/nexus/xml/dataspace_builder.hpp>
#include <h5cpp/hdf5.hpp>

namespace pni {
namespace nexus {
namespace xml {

using FilterParameters = std::tuple<unsigned int,   // filter_id
				    std::string,    // name
				    std::string,    // cd_values, int separated by comma
    				    std::string>;  // availability: mandatory, optional
  
using IndexFilterParametersMap = std::map<unsigned int,   // index,
					  FilterParameters>;

  
class DatasetCreationListBuilder
{
  private:
    Node node_;
    DataspaceBuilder dataspace_builder_;

    void set_compression(hdf5::property::DatasetCreationList &dcpl) const;
    void set_chunking(hdf5::property::DatasetCreationList &dcpl) const;
    static FilterParameters parameters_from_node(const Node &node);
    void get_cd_values(const std::string text,
		       std::vector<unsigned int> & cd_values) const;
  public:
    DatasetCreationListBuilder() = default;
    DatasetCreationListBuilder(const DatasetCreationListBuilder &) = default;
    DatasetCreationListBuilder(const Node &node);

    hdf5::property::DatasetCreationList build() const;
};


} // namespace xml
} // namespace nexus
} // namespace pni
