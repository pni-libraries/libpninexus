//
// (c) Copyright 2014 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
//
// ===========================================================================
//
// Created on: Mar 17, 2014
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

//-----------------------------------------------------------------------------
// basic array inquery 
//-----------------------------------------------------------------------------
#include <vector>
#include <pni/types.hpp>
#include <pni/arrays.hpp>

using namespace pni;

//some usefull type definitions
typedef dynamic_array<float64> darray_type;

template<typename ArrayT>
void show_info(const ArrayT &a)
{
    std::cout<<"Data type: "<<type_id(a)<<std::endl;
    std::cout<<"Rank     : "<<a.rank()<<std::endl;
    std::cout<<"Shape    : (";
    auto s = a.template shape<shape_t>();
    for(auto n: s) std::cout<<" "<<n<<" ";
    std::cout<<")"<<std::endl;
    std::cout<<"Size     : "<<a.size()<<std::endl;
}

int main(int ,char **)
{
    auto a1 = darray_type::create(shape_t{1024,2048});

    show_info(a1);

    return 0;
}

