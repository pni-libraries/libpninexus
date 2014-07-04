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
// Created on: Jul 4, 2013
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#pragma once

#include <boost/variant.hpp>
#include <pni/core/types.hpp>
#include <pni/core/arrays.hpp>
#include "../nxobject.hpp"
#include "../nxobject_traits.hpp"
#include "get_object.hpp"

namespace pni{
namespace io{
namespace nx{
    
    using namespace pni::core;

    //-------------------------------------------------------------------------
    //!
    //! \ingroup algorithm_code
    //! \brief create an attribute
    //!
    //! Function template creating an attribute for a parent 
    /*!
    \code
    auto parent = ....;
    auto attr = create_attribute<int32>(parent,"test",shape_t{4,4});
    \endcode
    */
    //! If no shape is passed a scalar attribute is created.
    //!
    //! \throws nxattribute_error in case of errors
    //! \tparam T data type for the attribute
    //! \tparam PTYPE parent template
    //! \tparam IMPID implementation ID
    //! \tparam STYPE container type for the shape (default is shape_t)
    //! \param o parent 
    //! \param n attribute name
    //! \param s attribute shape (optional)
    //! \return istance of nxattribute 
    //!
    template<
             typename T,
             template<nximp_code> class PTYPE,
             nximp_code IMPID,
             typename STYPE = shape_t
            > 
    typename nxobject_trait<IMPID>::attribute_type
    create_attribute(const PTYPE<IMPID> &o,const string &n,
                     const STYPE &s=STYPE())
    {
        return o.template attr<T>(n,s);
    }
    
    //-------------------------------------------------------------------------
    //!
    //! \ingroup algorithm_code
    //! \brief create an attribute 
    //!
    //! Create an attribute whose name and parent object is described by a
    //! Nexus path. The parent object referenced by the path must exist in
    //! order for the function to succeed. 
    //! The first argument is the root for the path if it is relative. 
    //! If the path is an absolute one it just acts as a reference from which 
    //! to obtain the root group of the Nexus file.
    /*!
    \code
    nxpath path = path_from_string("/:NXentry/:NXinstrument/:NXdetector/data@test");
    auto root = get_object(...);
    create_attribute<int32>(root,path,shape_t{4,4});
    \endcode
    */
    //! The last argument is the shape of the attribute which is optional. 
    //! If no shape is passed a scalar attribute is created. 
    //! 
    //! An exception is raised if the path does not refere to an attribute.
    //! 
    //! \throws nxattribute_error in the case of errors
    //! \tparam T data type of the field
    //! \tparam PTYPE parent type template
    //! \tparam IMPID implementation ID
    //! \tparam STYPE container type for the shape (default is shape_t)
    //! \param o parent instance
    //! \param path Nexus path to the attribute
    //! \param s shape of the attribute
    //! \return instance of nxattribute
    //!
    template<
             typename T,
             template<nximp_code> class PTYPE,
             nximp_code IMPID,
             typename STYPE = shape_t
            > 
    typename nxobject_trait<IMPID>::attribute_type
    create_attribute(const PTYPE<IMPID> &o,const nxpath &path,
                     const STYPE &s=STYPE())
    {
        nxpath parent_path(path); parent_path.attribute("");

        //check if the path describes an attribute
        if(path.attribute().empty())
            throw nxattribute_error(EXCEPTION_RECORD,
                    "Path does not describe an attribute!");

        //obtain the parent for the target object - this will always be a 
        //grou ptype
        auto parent = get_object(o,parent_path);

        //finally create the attribute
        return create_attribute(parent,path.attribute(),s);
    }

    //------------------------------------------------------------------------
    //!
    //! \ingroup algorithm_code
    //! \brief create attribute 
    //! 
    //! 
    template<
             typename T,
             template<nximp_code> class PTYPE,
             nximp_code IMPID,
             typename ...ARGTS
            >
    typename nxobject_trait<IMPID>::attribute_type
    create_attribute(const PTYPE<IMPID> &o,type_id_t tid,ARGTS ...args)
    {
        if(tid == type_id_t::UINT8)
            return create_attribute<uint8>(o,args...);
        else if(tid == type_id_t::INT8)
            return create_attribute<int8>(o,args...);
        else if(tid == type_id_t::UINT16)
            return create_attribute<uint16>(o,args...);
        else if(tid == type_id_t::INT16)
            return create_attribute<int16>(o,args...);
        else if(tid == type_id_t::UINT32)
            return create_attribute<uint32>(o,args...);
        else if(tid == type_id_t::INT32)
            return create_attribute<int32>(o,args...);
        else if(tid == type_id_t::UINT64)
            return create_attribute<uint64>(o,args...);
        else if(tid == type_id_t::INT64)
            return create_attribute<int64>(o,args...);
        else if(tid == type_id_t::FLOAT32)
            return create_attribute<float32>(o,args...);
        else if(tid == type_id_t::FLOAT64)
            return create_attribute<float64>(o,args...);
        else if(tid == type_id_t::FLOAT128)
            return create_attribute<float128>(o,args...);
        else if(tid == type_id_t::COMPLEX32)
            return create_attribute<complex32>(o,args...);
        else if(tid == type_id_t::COMPLEX64)
            return create_attribute<complex64>(o,args...);
        else if(tid == type_id_t::COMPLEX128)
            return create_attribute<complex128>(o,args...);
        else if(tid == type_id_t::BOOL)
            return create_attribute<bool_t>(o,args...);
        else if(tid == type_id_t::STRING)
            return create_attribute<string>(o,args...);
        else
            throw type_error(EXCEPTION_RECORD,
                    "Unknown type code!");
        
    }
    

    //-------------------------------------------------------------------------
    //!
    //! \ingroup algorithm_internal_code
    //! \brief create attribute visitor
    //!
    //! This visitor creates an attribute below the group stored in the 
    //! variant type.  If the stored object is not a group an exception will 
    //! be thrown. 
    //! \tparam VTYPE variant type
    //! \tparam T data type of the attribute
    //! \tparam STYPE container type for the shape
    //! \sa create_attribute
    //!
    template<
             typename GTYPE,
             typename FTYPE,
             typename ATYPE,
             typename T,
             typename STYPE
            > 
    class create_attribute_visitor : public boost::static_visitor<ATYPE>
    {
        private:
            string _name;  //!< the name of the field
            STYPE _shape;  //!< shape of field
        public:
            //! result type
            typedef ATYPE result_type;
            //! Nexus group type
            typedef GTYPE group_type;
            //! Nexus field type
            typedef FTYPE field_type;
            //! Nexus attribute type
            typedef ATYPE attribute_type;

            //-----------------------------------------------------------------
            //!
            //! \brief constructor
            //!
            //! \param n name of the attribute
            //! \param s shape of the attribute
            //!
            create_attribute_visitor(const string &n,const STYPE &s):
                _name(n),
                _shape(s)
            {}

            //-----------------------------------------------------------------
            //!
            //! \brief process group instances
            //!
            //! Create a new attribute of name _name attached to group g.ant.
            //! \throws nxattribute_error in case of errors
            //! \param g parent group instance for the attribute
            //! \return new group stored as object_types
            //!
            result_type operator()(const group_type &g) const
            {
                return create_attribute<T>(g,_name,_shape);
            }

            //-----------------------------------------------------------------
            //!
            //! \brief process field instances
            //!
            //! Create a new attribute of name _name attached to field f.
            //! \throws nxattribute_error in case of errors
            //! \param f field instance
            //! \return empty result type
            //!
            result_type operator()(const field_type &f) const
            {
                return create_attribute<T>(f,_name,_shape);
            }

            //-----------------------------------------------------------------
            //!
            //! \brief process attribute instances
            //!
            //! An attribute cannot create an  attribute - an exception will be
            //! thrown.
            //! \throws nxattribute_error 
            //! \param a attribute instance
            //! \return an empty result type
            //!
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
            result_type operator()(const attribute_type &a) const
            {
                throw nxattribute_error(EXCEPTION_RECORD,
                        "Cannot create a group below an attribute!");
                return result_type();
            }
#pragma GCC diagnostic pop
    };

    //-------------------------------------------------------------------------
    //!
    //! \ingroup algorithm_code
    //! \brief create_attribute wrapper
    //!
    //! This wrapper function for the create_attribute_visitor creates a new
    //! attribute below attached to an object stored in the varian type.  The 
    //! object must be a field or a group type.
    /*!
    \code
    object_types g = get_object(...);
    create_attribute<int32>(g,"test",shape_t{4,4});
    \endcode
    */
    //!
    //! \throws nxattribute_error in case of errors
    //! \tparam T data type of the field
    //! \tparam VTYPE variant type
    //! \tparam STYPE container type for the shape (default is shape_t)
    //! \param o instance of VTYPE with the parent group
    //! \param n name of the new attribute
    //! \param s shape of the attribute
    //! \return object_types with the newly created attribute
    //!
    template<
             typename T,
             typename GTYPE,
             typename FTYPE,
             typename ATYPE,
             typename ...TYPES,
             typename STYPE = shape_t
            > 

    ATYPE create_attribute(const nxobject<GTYPE,FTYPE,ATYPE> &o,
                           const string &n,const STYPE &s=STYPE())
    {
        typedef create_attribute_visitor<GTYPE,FTYPE,ATYPE,T,STYPE> visitor_t;
        return boost::apply_visitor(visitor_t(n,s),o);
    }
    
    
    //-------------------------------------------------------------------------
    //!
    //! \ingroup algorithm_code
    //! \brief create_attribute wrapper
    //!
    //! Wrapper function for the create_attribute_visitor template. The 
    //! function creates a new attribute described  by a path relative to the 
    //! object passed as the first argument of the function. This object must 
    //! be either a gruop or a field.
    /*!
    \code
    nxpath path = path_from_string("/:NXentry/:NXinstrument/:NXdetector/data@test");
    object_types root = get_object(...);
    create_attribute<int32>(root,path,shape_t{4,4});
    \endcode
    */
    //! \throws nxattribute_error in the case of errors
    //! \tparam T data type of the field
    //! \tparam VTYPE variant type
    //! \tparam STYPE container type for the shape (default is shape_t)
    //! \param o instance of VTYPE with the parent group
    //! \param path Nexus path to the attribute
    //! \param s shape of the attribute
    //! \return object_types with the newly created attribute
    //!
    template<
             typename T,
             typename GTYPE,
             typename FTYPE,
             typename ATYPE,
             typename ...TYPES,
             typename STYPE = shape_t
            > 
    ATYPE create_attribute(const nxobject<GTYPE,FTYPE,ATYPE> &o,
                           const nxpath &path,const STYPE &s=STYPE())
    {
        typedef create_attribute_visitor<GTYPE,FTYPE,ATYPE,T,STYPE> visitor_t;
        nxpath group_path,target_path;

        //check if the path describes an attribute
        if(path.attribute().empty())
            throw nxattribute_error(EXCEPTION_RECORD,
                    "Path does not describe an attribute!");

        split_last(path,group_path,target_path);

        auto parent = get_object(o,group_path);
        auto target = get_child(parent,target_path.begin()->first,
                           target_path.begin()->second);

        return boost::apply_visitor(visitor_t(target_path.attribute(),s),target);
    }
    

//end of namespace
}
}
}
