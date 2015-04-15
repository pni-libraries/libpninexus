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
//
// Created on: Nov 28, 2014
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#pragma once

#include <pni/core/types.hpp>

#include "node.hpp"
#include "node_data.hpp"
#include "../../parsers.hpp"
#include "../../formatters.hpp"

namespace pni{
namespace io{
namespace nx{
namespace xml{

    using namespace pni::core;

    //!
    //! \ingroup xml_classes
    //! \brief general IO objects
    //!
    //! This class provides functions common for field and attribute nodes. 
    //!
    struct io_object
    {
        //--------------------------------------------------------------------
        //!
        //! \brief return object size
        //! 
        //! Returns the number of elements a field or attribute can store. 
        //! If the node contains a dimensions tag the number of elements is 
        //! computed from the shape described by the dimensions tag. If no
        //! dimensions tag is provided the node is assumed to describe a scalar
        //! object with a size of 1.
        //!
        //! \throws parser_error in case of an error
        //! \param io_node XML node with IO object metadata
        //! \return number of elements stored in the object
        //! 
        static size_t size(const node &io_node);

        //--------------------------------------------------------------------
        //!
        //! \brief return object rank
        //! 
        //! This function returns the number of dimensions an IO object has. 
        //! For nodes with an dimensions child this number is provided by the 
        //! rank attribute of the dimensions tag. For scalar objects the rank
        //! is 0.
        //!
        //! \throws parser_error in case of an error
        //! \param io_node XML node with IO object metadata
        //! \return number of dimensions
        //! 
        static size_t rank(const node &io_node);

        //--------------------------------------------------------------------
        //!
        //! \brief return object name
        //!
        //! Returns the name of the object which is determined by the name 
        //! attribute of the node.
        //! 
        //! \throws parser_error in case of an error
        //! \param io_node XML node with object metadata
        //! \return name of the object
        //! 
        static string name(const node &io_node);
        
        //--------------------------------------------------------------------
        //!
        //! \brief return object shape
        //! 
        //! \throws parser_error in case of an error
        //! \param io_node XML node with object metadata
        //! \return shape information
        //! 
        static shape_t shape(const node &io_node);
        
        //--------------------------------------------------------------------
        //!
        //! \brief get type id
        //! 
        //! Retrieves the type id of the field described by the XML node.
        //! 
        //! \throws parser_error if attribute cannot be read
        //! \throws type_error if type cannot be translated 
        //! 
        //! \param io_node the node with field information
        //! \return type id of the field
        //!
        static type_id_t type_id(const node &io_node);
        
        //--------------------------------------------------------------------
        //!
        //! \brief get data from XML
        //! 
        //! Reads the data stored with the XML field node. It is important 
        //! to understand that an XML node itself can only store simple 
        //! one dimensional containers. It does not provide enough 
        //! information to construct a multidimensional array.
        //!
        //! \throws type_error if the fields data type is not supported
        //! \throws parser_error in case of errors during parsing data text
        //!
        //! \param io_node the XML node with the data
        //! \return instance of array with the data
        //! 
        template<typename T>
        static T data_from_xml(const node &io_node)
        {
            typedef string::const_iterator iterator_type;
            pni::io::parser<iterator_type,T> p;

            return p(node_data::read(io_node));
        }

        //--------------------------------------------------------------------
        //!
        //! \brief write data to XML
        //! 
        //! Write data from value to the XML io_node. 
        //! 
        //! \tparam T type to write
        //! \param value instance of T from which to read data
        //! \param io_node the XML node to which to write the data
        //!
        template<typename T>
        static void data_to_xml(const T &value,node &io_node)
        {
            typedef formatter<T> formatter_type; 
            formatter_type f;
            io_node.put_value(f(value));
        }

    };

//end of namespace
}
}
}
}

