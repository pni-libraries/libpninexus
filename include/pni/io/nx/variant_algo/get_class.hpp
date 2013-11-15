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
 * Created on: Jul 1, 2013
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */
#pragma once

#include "../nxvariant_traits.hpp"

namespace pni{
namespace io{
namespace nx{

    /*!
    \ingroup variant_code
    \brief get class visitor

    Retrieves the Nexus class of a group stored in variant type. 
    \tparam VTYPE variant type
    \sa get_class
    */
    template<typename VTYPE> 
    class get_class_visitor : public boost::static_visitor<string>
    {
        public:
            //! result type
            typedef string result_type;
            //! Nexus group type
            typedef typename nxvariant_group_type<VTYPE>::type group_type;
            //! Nexus field type
            typedef typename nxvariant_field_type<VTYPE>::type field_type;
            //! Nexus attribute type
            typedef typename nxvariant_attribute_type<VTYPE>::type attribute_type;

            /*!
            \brief process gruops 

            Retrieve the content of the NX_class attribute of a Nexus group 
            and return it as a string. If the group has no type (the NX_class
            attribute does not exist) an exception will be thrown.
            \throws nxgroup_error if NX_class attribute does not exist
            \param g group instance
            \return Nexus class as string
            */
            result_type operator()(const group_type &g) const
            {
                result_type buffer;
                if(g.has_attr("NX_class"))
                    g.attr("NX_class").read(buffer);
                else
                    throw nxgroup_error(EXCEPTION_RECORD,
                            "Group "+g.path()+" has no class attribute!");

                return buffer;
            }

            //-----------------------------------------------------------------
            /*!
            \brief process fields

            Fields have no Nexus class. Thus an exception will be thrown when
            this visitor is applied to a field.
            \throw nxfield_error 
            \param f instance of a field
            \return empty string
            */
            result_type operator()(const field_type &f) const
            {
                throw nxfield_error(EXCEPTION_RECORD,
                        "Fields do not have a class!");
                return result_type();
            }

            //-----------------------------------------------------------------
            /*!
            \brief process attributes

            Attributes have no Nexus class. Thus an exception will be thrown. 
            \throw nxattribute_error 
            \param a attribute instance
            \return empty string
            */
            result_type operator()(const attribute_type &a) const
            {
                throw nxattribute_error(EXCEPTION_RECORD,
                        "Attributes do not have a class!");
                return result_type();
            }
    };

    /*!
    \ingroup variant_code
    \brief get class wrapper

    Wrapper function for the get_class_visitor template. If the object stored in
    the variant type is a group its Nexus class will be retrieved. If the group
    does not have the NX_classs attribute an exception will be thrown. 
    Exceptions are thrown also in cases where the object stored in the variant
    are fields or attributes.

    \throws nxgroup_error if the group has no NX_class attribute
    \throws nxfield_error if applied to a field
    \throws nxattribute_error if applied to an attribute
    \tparam VTYPE variant type
    \param o instance of VTYPE
    \return Nexus class as a tring
    */
    template<typename VTYPE> 
    typename get_class_visitor<VTYPE>::result_type get_class(const VTYPE &o)
    {
        return boost::apply_visitor(get_class_visitor<VTYPE>(),o);
    }

//end of namespace
}
}
}