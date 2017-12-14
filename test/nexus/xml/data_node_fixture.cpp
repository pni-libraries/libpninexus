//
// (c) Copyright 2016 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
//  Created on: Jan 14, 2016
//      Author: Eugen Wintersberger
//

#include "data_node_fixture.hpp"

using namespace pni::core;
using namespace pni::io::nexus;

//----------------------------------------------------------------------------
DataNodeFixture::DataNodeFixture(const std::string &scalar_data,
                                 const std::string &array_data):
    scalar(xml::Node::from_string(scalar_data)),
    array(xml::Node::from_string(array_data))
{}

//----------------------------------------------------------------------------
DataNodeFixture::~DataNodeFixture()
{ }