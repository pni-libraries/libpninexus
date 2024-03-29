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
// Created on: Dec 14, 2017
//

#include "builder_fixture.hpp"
#include <h5cpp/core/filesystem.hpp>

BuilderFixture::BuilderFixture(const fs::path &nexus_file,
                               const fs::path &xml_file)
{
  using namespace pni;
  using pni::type_id_t;
  file = hdf5::file::create(nexus_file,
                            hdf5::file::AccessFlags::Truncate);
  root_group = file.root();

  nexus::xml::Node n = nexus::xml::Node::from_file(xml_file);
  nexus::xml::ObjectBuilder builder(n);
  builder.build(root_group);


}

BuilderFixture::~BuilderFixture()
{}
