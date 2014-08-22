//
// (c) Copyright 2014 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
// Created on: aug 21, 2014
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#pragma once

#include "../nximp_code.hpp"
#include "../nxobject.hpp"

namespace pni{
namespace io{
namespace nx{

    //!
    //! \ingroup algorithm_code
    //! \brief get filename
    //! 
    //! Return the filename an object belongs to. This template works for
    //! instances of
    //! 
    //! \li nxgroup
    //! \li nxfield
    //! \li nxattribute
    //! 
    //! \throws invalid_object_error in case of an invalid object
    //! \throws io_error if filename cannot be retrieved
    //! \throws type_error if the implementation type does not support
    //! filename retrieval
    //! \throws object_error in case of any other error
    //!
    //! \tparam OTYPE object type template
    //! \tparam IMPID implementation ID
    //!
    //! \param o reference to the object
    //! \return name of the object
    //!
    template<
             template<nximp_code> class OTYPE,
             nximp_code IMPID
            >
    string get_filename(const OTYPE<IMPID> &o)
    {
        return o.filename();
    }


    //------------------------------------------------------------------------
    //!
    //! \ingroup algorithm_internal_code
    //! \brief get filename visitor
    //!
    //! Retrieving the name of the file an object belongs too.
    //! 
    //! \tparam GTYPE group type
    //! \tparam FTYPE field type
    //! \tparam ATYPE attribute type
    //! \sa get_filename
    //!
    template<
             typename GTYPE,
             typename FTYPE,
             typename ATYPE
            > 
    class get_filename_visitor : public boost::static_visitor<string>
    {
        public:
            //! result type
            typedef string result_type;
            //! Nexus group type
            typedef GTYPE group_type;
            //! Nexus field type
            typedef FTYPE field_type;
            //! Nexus attribute type
            typedef ATYPE attribute_type; 

            //-----------------------------------------------------------------
            //!
            //! \brief process group instances
            //!
            //! Retrieve the name of the file the group belongs to.
            //!
            //! \throws invalid_object_error in case of an invalid object
            //! \throws io_error if filename cannot be retrieved
            //! \throws type_error if the implementation type does not support
            //! filename retrieval
            //! \throws object_error in case of any other error
            //!
            //! \param g group instance
            //! \return string with the group name
            //!
            result_type operator()(const group_type &g) const
            {
                return get_filename(g);
            }

            //-----------------------------------------------------------------
            //!
            //! \brief process field instances
            //!
            //! Retrieve the name of the file the field belongs to
            //!
            //! \throws invalid_object_error if the field is not valid
            //! \throws io_error if filename retrieval fails
            //! \throws type_error if the implementation type does not 
            //! support filename retrieval
            //! \throws object_error in case of any other error
            //!
            //! \param f field instance
            //! \return name of the field
            //!
            result_type operator()(const field_type &f) const
            {
                return get_filename(f);
            }

            //-----------------------------------------------------------------
            //!
            //! \brief process attribute instances
            //!
            //! Retrieve the name of the file within which the attributes parent
            //! is stord.
            //!
            //! \throws invalid_object_error if the attribute is not valid
            //! \throws io_error if filename retrieval fails
            //! \throws type_error if the implementation type does not support
            //! filename retrieval
            //! \throws object_error in case of any other error
            //!
            //! \param a attribute instance
            //! \return name of the attribute
            //!
            result_type operator()(const attribute_type &a) const
            {
                return get_filename(a);
            }
    };

    //!
    //! \ingroup algorithm_code
    //! \brief get filename 
    //!
    //! Get the name of the file where a particular object is stored.
    //! 
    //! \throws invalid_oject_error if the object is not valid
    //! \throws io_error if filename retrieval fails
    //! \throws type_error if the implementation type does not 
    //! support filename retrieval
    //! \throws object_error in case of any other error
    //!
    //! \tparam GTYPE group type
    //! \tparam FTYPE field type
    //! \tparam ATYPE attribute type
    //!
    //! \param o instance of nxobject
    //! \return name of the object
    //!
    template<
             typename GTYPE,
             typename FTYPE,
             typename ATYPE
            > 
    string get_filename(const nxobject<GTYPE,FTYPE,ATYPE> &o)
    {
        typedef get_filename_visitor<GTYPE,FTYPE,ATYPE> visitor_type;
        return boost::apply_visitor(visitor_type(),o);
    }

//end of namespace
}
}
}
