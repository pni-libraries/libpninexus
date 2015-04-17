//
// (c) Copyright 2013 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
// Created on: Jul 15, 2013
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//


#include <pni/io/nx/xml/data_node.hpp>
#include <boost/algorithm/string.hpp>

namespace pni{
namespace io{
namespace nx{
namespace xml{

    string data_node::read(const node &n) 
    {
        string data = n.data();
        boost::algorithm::trim(data);
        return data;
    }

    //-------------------------------------------------------------------------
    void data_node::write(node &n,const string &data) 
    {
        n.put_value(data);
    }

//end of namespace
}
}
}
}