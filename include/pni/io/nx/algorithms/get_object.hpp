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
// Created on: Jul 2, 2013
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#pragma once

#include <pni/core/types.hpp>

#include "../nxpath.hpp"
#include "../nxobject_traits.hpp"
#include "get_parent.hpp"
#include "get_root.hpp"
#include "get_attribute.hpp"
#include "get_child.hpp"

#ifdef NOFOREACH
#include <boost/foreach.hpp>
#endif

namespace pni{
namespace io{
namespace nx{

    //!
    //! \ingroup algorithm_code
    //! \brief retrieve an object from path
    //! 
    //! Retrieve an object whose position is determined by a nexus path.
    //! The path can be either relative or absolute.  In the former case 
    //! the path is relative to the parent object. In the latter on the parent
    //! object is only used to retrieve the root group and then continue from 
    //! there.
    //! 
    //! \throws key_error if one of the path element does not lead to a child
    //! \tparam OTYPE parent object type
    //! \tparam IMPID implementation ID of the parent tyep
    //! \param o reference to the parent
    //! \param path reference to the path
    //! \return the requested object as nxobject instance
    //! 
    template<typename OTYPE> 
    auto get_object(const OTYPE &o,const nxpath &path)
    ->decltype(get_parent(o))
    {
        decltype(get_parent(o)) target = o;

        //traverse over the path
        for(auto element: path)
        {
            if(element.first =="/")
                target = get_root(target);
            else if (element.first == ".")
                continue;
            else if (element.first == "..")
                target = get_parent(target);
            else
                target = get_child(target,element.first,element.second);
        }

        //if an attribute was requested 
        if(!path.attribute().empty())
            target = get_attribute(target,path.attribute());
        
        return target;
    }


//end of namespace
}
}
}
