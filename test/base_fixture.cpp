//
// (c) Copyright 2016 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
// along with libpninx.  If not, see <http://www.gnu.org/licenses/>.
// ===========================================================================


#include "base_fixture.hpp"

using namespace pni;

//-----------------------------------------------------------------------------
base_fixture::base_fixture(const string &fname,bool open_existing):
    filename(fname),
    file(),
    root()
{
    if(open_existing)
      file = hdf5::file::open(filename,
			      hdf5::file::AccessFlags::ReadOnly);
    else
      file = nexus::create_file(filename,
				hdf5::file::AccessFlags::Truncate);

    root = file.root();

}

//-----------------------------------------------------------------------------
base_fixture::~base_fixture()
{
    root.close();
    file.close();

}
