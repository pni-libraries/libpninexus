/*
 * (c) Copyright 2013 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 * This file is part of libpniio.
 *
 * libpniio is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * libpniio is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with libpniio.  If not, see <http://www.gnu.org/licenses/>.
 *************************************************************************
 * Created on: Jun 28, 2013
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */
#pragma once

#include "../nxvariant_traits.hpp"

namespace pni{
namespace io{
namespace nx{

    /*!
    \ingroup variant_code
    \brief check attribute visitor

    This visitor checks if the object stored in a variant type is an attribute
    instance. In this case true will be returne. False otherwise. 
    
    \tparam VTYPE variant type
    */
    template<typename VTYPE> 
    class is_attribute_visitor : public boost::static_visitor<bool>
    {
        public:
            //! first type of VTYPE
            typedef typename nxvariant_member_type<VTYPE,0>::type first_member;
            //! result type (bool)
            typedef bool result_type;
            //! Nexus group type
            DEFINE_NXGROUP(first_member) group_type;
            //! Nexus field type
            DEFINE_NXFIELD(first_member) field_type;
            //! Nexus attribute type
            DEFINE_NXATTRIBUTE(first_member) attribute_type;
          
            //-----------------------------------------------------------------
            /*!
            \brief process group instances

            \param g refernece to group instance
            \return false
            */
            result_type operator()(const group_type &g) const
            {
                return false;
            }

            //-----------------------------------------------------------------
            /*!
            \brief process field instances

            \param f reference to field instance
            \return false
            */
            result_type operator()(const field_type &f) const
            {
                return false;
            }

            //-----------------------------------------------------------------
            /*!
            \brief process attribute instances

            \param a reference to attribute instance
            \return true
            */
            result_type operator()(const attribute_type &a) const
            {
                return true;
            }
    };

    /*!
    \ingroup variant code
    \brief check if attribute

    A wrapper around the is_attribute_visitor template. The function returns
    true if the object stored in VTYPE is an attribute. In all other cases false
    is returned.
    \tparam VTYPE variant type
    \param o reference to instance of VTYPE
    \return true if o is an attribute, false otherwise
    */
    template<typename VTYPE> 
    typename is_attribute_visitor<VTYPE>::result_type is_attribute(const VTYPE &o)
    {
        return boost::apply_visitor(is_attribute_visitor<VTYPE>(),o);
    }

//end of namespace
}
}
}