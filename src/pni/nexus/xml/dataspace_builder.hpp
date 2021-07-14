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
#include <h5cpp/hdf5.hpp>
#include <pni/windows.hpp>

namespace pni {
namespace nexus {
namespace xml {

class PNINEXUS_EXPORT DataspaceBuilder
{
  private:
    Node node_;
  public:
    DataspaceBuilder() = default;
    DataspaceBuilder(const DataspaceBuilder &) = default;

    DataspaceBuilder(const Node &node);

    hdf5::dataspace::Simple build() const;
};


} // namespace xml
} // namespace nexus
} // namespace pni
