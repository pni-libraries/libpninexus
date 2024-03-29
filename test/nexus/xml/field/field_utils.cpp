//
// (c) Copyright 2015 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
// ===========================================================================
//
//  Created on: Sep 04, 2015
//  Authors:
//          Eugen Wintersberger <eugen.wintersberger@desy.de>
//          Jan Kotanski <jan.kotanski@desy.de>
//

#include "field_utils.hpp"
#include <pni/nexus/xml/field_node.hpp>
#include <h5cpp/contirub/nexus/ebool.hpp>


namespace xml_test{
namespace field_test{

    size_t size(const pni::nexus::xml::Node &node)
    {
        return pni::nexus::xml::FieldNode::size(node);
    }

    size_t rank(const pni::nexus::xml::Node &node)
    {
        return pni::nexus::xml::FieldNode::rank(node);
    }

    pni::type_id_t type_id(const pni::nexus::xml::Node &node)
    {
        return pni::nexus::xml::FieldNode::type_id(node);
    }

#define PNINEXUS_DEF_DATA_FROM_XML(type) \
    void data_from_xml(const pni::nexus::xml::Node &node, \
                       type &value) \
    { \
        using namespace pni::nexus::xml; \
        value = FieldNode::data_from_xml<type>(node); \
    }

    PNINEXUS_DEF_DATA_FROM_XML(pni::uint8)
    PNINEXUS_DEF_DATA_FROM_XML(pni::int8)
    PNINEXUS_DEF_DATA_FROM_XML(pni::uint16)
    PNINEXUS_DEF_DATA_FROM_XML(pni::int16)
    PNINEXUS_DEF_DATA_FROM_XML(pni::uint32)
    PNINEXUS_DEF_DATA_FROM_XML(pni::int32)
    PNINEXUS_DEF_DATA_FROM_XML(pni::uint64)
    PNINEXUS_DEF_DATA_FROM_XML(pni::int64)

    PNINEXUS_DEF_DATA_FROM_XML(pni::float32)
    PNINEXUS_DEF_DATA_FROM_XML(pni::float64)
#ifndef _MSC_VER
    PNINEXUS_DEF_DATA_FROM_XML(pni::float128)
#endif
    
    PNINEXUS_DEF_DATA_FROM_XML(pni::complex32)
    PNINEXUS_DEF_DATA_FROM_XML(pni::complex64)
#ifndef _MSC_VER
    PNINEXUS_DEF_DATA_FROM_XML(pni::complex128)
#endif

    PNINEXUS_DEF_DATA_FROM_XML(pni::string)
    PNINEXUS_DEF_DATA_FROM_XML(pni::bool_t)
    PNINEXUS_DEF_DATA_FROM_XML(hdf5::datatype:EBool)
    
    PNINEXUS_DEF_DATA_FROM_XML(uint8_vector)
    PNINEXUS_DEF_DATA_FROM_XML(int8_vector)
    PNINEXUS_DEF_DATA_FROM_XML(uint16_vector)
    PNINEXUS_DEF_DATA_FROM_XML(int16_vector)
    PNINEXUS_DEF_DATA_FROM_XML(uint32_vector)
    PNINEXUS_DEF_DATA_FROM_XML(int32_vector)
    PNINEXUS_DEF_DATA_FROM_XML(uint64_vector)
    PNINEXUS_DEF_DATA_FROM_XML(int64_vector)

    PNINEXUS_DEF_DATA_FROM_XML(float32_vector)
    PNINEXUS_DEF_DATA_FROM_XML(float64_vector)
#ifndef _MSC_VER
    PNINEXUS_DEF_DATA_FROM_XML(float128_vector)
#endif
    
    PNINEXUS_DEF_DATA_FROM_XML(complex32_vector)
    PNINEXUS_DEF_DATA_FROM_XML(complex64_vector)
#ifndef _MSC_VER
    PNINEXUS_DEF_DATA_FROM_XML(complex128_vector)
#endif

    PNINEXUS_DEF_DATA_FROM_XML(string_vector)
    PNINEXUS_DEF_DATA_FROM_XML(bool_t_vector)
    PNINEXUS_DEF_DATA_FROM_XML(ebool_vector)

#define PNINEXUS_DEF_DATA_TO_XML(type) \
    void data_to_xml(const type &value,pni::nexus::xml::Node &node) \
    { \
        using namespace pni::nexus::xml; \
        FieldNode::data_to_xml(node,value); \
    }
    
    PNINEXUS_DEF_DATA_TO_XML(pni::uint8)
    PNINEXUS_DEF_DATA_TO_XML(pni::int8)
    PNINEXUS_DEF_DATA_TO_XML(pni::uint16)
    PNINEXUS_DEF_DATA_TO_XML(pni::int16)
    PNINEXUS_DEF_DATA_TO_XML(pni::uint32)
    PNINEXUS_DEF_DATA_TO_XML(pni::int32)
    PNINEXUS_DEF_DATA_TO_XML(pni::uint64)
    PNINEXUS_DEF_DATA_TO_XML(pni::int64)

    PNINEXUS_DEF_DATA_TO_XML(pni::float32)
    PNINEXUS_DEF_DATA_TO_XML(pni::float64)
#ifndef _MSC_VER
    PNINEXUS_DEF_DATA_TO_XML(pni::float128)
#endif
    
    PNINEXUS_DEF_DATA_TO_XML(pni::complex32)
    PNINEXUS_DEF_DATA_TO_XML(pni::complex64)
#ifndef _MSC_VER
    PNINEXUS_DEF_DATA_TO_XML(pni::complex128)
#endif

    PNINEXUS_DEF_DATA_TO_XML(pni::string)
    PNINEXUS_DEF_DATA_TO_XML(pni::bool_t)
    PNINEXUS_DEF_DATA_TO_XML(hdf5::datatype::EBool)
    
    PNINEXUS_DEF_DATA_TO_XML(uint8_vector)
    PNINEXUS_DEF_DATA_TO_XML(int8_vector)
    PNINEXUS_DEF_DATA_TO_XML(uint16_vector)
    PNINEXUS_DEF_DATA_TO_XML(int16_vector)
    PNINEXUS_DEF_DATA_TO_XML(uint32_vector)
    PNINEXUS_DEF_DATA_TO_XML(int32_vector)
    PNINEXUS_DEF_DATA_TO_XML(uint64_vector)
    PNINEXUS_DEF_DATA_TO_XML(int64_vector)

    PNINEXUS_DEF_DATA_TO_XML(float32_vector)
    PNINEXUS_DEF_DATA_TO_XML(float64_vector)
#ifndef _MSC_VER
    PNINEXUS_DEF_DATA_TO_XML(float128_vector)
#endif
    
    PNINEXUS_DEF_DATA_TO_XML(complex32_vector)
    PNINEXUS_DEF_DATA_TO_XML(complex64_vector)
#ifndef _MSC_VER
    PNINEXUS_DEF_DATA_TO_XML(complex128_vector)
#endif

    PNINEXUS_DEF_DATA_TO_XML(string_vector)
    PNINEXUS_DEF_DATA_TO_XML(bool_t_vector)
    PNINEXUS_DEF_DATA_TO_XML(ebool_vector)

    pni::nexus::xml::Node
    object_to_xml(const hdf5::node::Node &object)
    {
        using namespace pni::nexus::xml;
        return FieldNode::object_to_xml(object);
    }

    hdf5::node::Node
    object_from_xml(const hdf5::node::Node &parent,
                    const pni::nexus::xml::Node &node)
    {
        using namespace pni::nexus::xml;
        return FieldNode::object_from_xml(parent,node);
    }
}
}
