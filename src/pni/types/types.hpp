//
// (c) Copyright 2011 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
// Created on: May 16, 2011
// Authors:
//         Eugen Wintersberger <eugen.wintersberger@desy.de>
//         Jan Kotanski <jan.kotanski@desy.de>
//
//
#pragma once

#include <complex>
#include <string>
#include <cstdint>
#include <vector>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/joint_view.hpp>
#include <h5cpp/contrib/nexus/ebool.hpp>

#ifdef _MSC_VER
#include <basetsd.h>
typedef SSIZE_T ssize_t;
#endif

#include <pni/types/binary.hpp>
#include <pni/types/bool.hpp>
#include <pni/types/none.hpp>

namespace pni{

    /*! \addtogroup type_classes
      @{
     */

    //---------------------integer types---------------------------------------
    typedef int8_t   int8;   //!< 8Bit signed integer type
    typedef uint8_t  uint8;  //!< 8Bit unsigned integer type
    typedef int16_t  int16;  //!< 16Bit signed integer type
    typedef uint16_t uint16; //!< 16Bit unsigned integer type
    typedef int32_t  int32;  //!< 32Bit signed integer type
    typedef uint32_t uint32; //!< 32Bit unsigned integer type
    typedef int64_t  int64;  //!< 64Bit signed integer type
    typedef uint64_t uint64; //!< 64Bit unsigned integer type

    //-------------------floating point types----------------------------------
    typedef double      float64;   //!< 64Bit IEEE floating point type
    typedef float       float32;   //!< 32Bit IEEE floating point type
    typedef long double float128;  //!< 128Bit IEEE floating point type

    //-----------------------complex types--------------------------------------
    //! 32Bit complex floating point type
    typedef std::complex<float32>  complex32; 
    //! 64Bit complex floating point type 
    typedef std::complex<float64>  complex64; 
    //! 128Bit complex floating point type
    typedef std::complex<float128> complex128; 

    //-----------------------utility types-------------------------------------
    typedef std::string     string; //!< String type
    typedef binary_t<uint8> binary; //!< data type for binary data
    /*! @} */

    //-------------------------------------------------------------------------
    // define some mpl containers with types 

    //!
    //! \ingroup type_classes
    //! \brief integer types vector
    //!
    //! An MPL vector with all integer types supported by libpninexus
    //!
    typedef boost::mpl::vector<uint8,int8,
                               uint16,int16,
                               uint32,int32,
                               uint64,int64> integer_types;

    //------------------------------------------------------------------------
    //!
    //! \ingroup type_classes
    //! \brief floating point types vector
    //!
    //! An MPL vector with all floating point types supported by libpninexus
    //!
    typedef boost::mpl::vector<float32,
                               float64,
                               float128> float_types;

    //------------------------------------------------------------------------
    //!
    //! \ingroup type_classes
    //! \brief complex types vector
    //!
    //! An MPL vector with all complex number types supported by libpninexus.
    //!
    typedef boost::mpl::vector<complex32,
                               complex64,
                               complex128> complex_types;

    //------------------------------------------------------------------------
    //!
    //! \ingroup type_classes
    //! \brief non numeric types vector
    //!
    //! An MPL vector with all numeric types supported by libpninexus.
    //!
    typedef boost::mpl::joint_view<
        boost::mpl::joint_view<integer_types,float_types>::type,
        complex_types
        > numeric_types;

    //------------------------------------------------------------------------
    //!
    //! \ingroup type_classes
    //! \brief non numeric types
    //!
    //! A boos MPL vector with non numeric types
    //!
    typedef boost::mpl::vector<none,bool_t,hdf5::datatype::EBool,binary,string> non_numeric_types;

    //------------------------------------------------------------------------
    //!
    //! \ingroup type_classes
    //! \brief all primitive types
    //! 
    //! This MPL vector contains all primitive types. These types are in some
    //! sense considered as POD types.
    //!
    typedef boost::mpl::joint_view<numeric_types,non_numeric_types> 
        primitive_types;

    //------------------------------------------------------------------------
    //! 
    //! \ingroup type_classes
    //! \brief type codes for PNI data types
    //! 
    //! Typed enumeration with type IDs. 
    //!
    enum class type_id_t {None,       //!< no data type
                          Int8,       //!< signed 8Bit integer
                          UInt8,      //!< unsigned 8Bit integer
                          Int16,      //!< signed 16Bit integer
                          UInt16,     //!< unsigned 16Bit integer
                          Int32,      //!< signed 32Bit integer
                          UInt32,     //!< unsigned 32Bit integer
                          Int64,      //!< signed 64Bit integer
                          UInt64,     //!< unsigned 64Bit integer
                          Float32,    //!< 32Bit IEEE floating point
                          Float64,    //!< 64Bit IEEE floating point
                          Float128,   //!< 128Bit IEEE floating point
                          Complex32,  //!< 32Bit IEEE floating point complex
                          Complex64,  //!< 64Bit IEEE floating point complex
                          Complex128, //!< 128Bit IEEE floating point complex
                          String,     //!< String type
                          Binary,     //!< binary data
                          Bool,        //!< integer boolean data
                          EBool        //!< enum boolean data
                      };

    //! 
    //! \ingroup type_classes
    //! \brief output operator for type_id_t
    //! 
    //! Adds a string representation of a TypeID to the output stream.
    //! 
    //! \param o reference to output stream
    //! \param tid reference to the TypID 
    //! \return reference to output stream
    //!
    PNINEXUS_EXPORT std::ostream &operator<<(std::ostream &o,const type_id_t &tid);


    //!
    //! \ingroup type_classes
    //! \brief type class definitions
    //!
    //! classes of data types provided by the PNI utility library
    enum class type_class_t {None,       //!< unspecified type
                             Integer,    //!< integer type
                             Float,      //!< floating point type
                             Binary,     //!< binary data type
                             Bool,       //!< boolean data type
                             Complex,    //!< complex data type
                             String      //!< class for string types
                            };




//if the compiler does not provide comparison operators for typed enumerations
//we have to do this by ourselves
#ifdef ENUMBUG
    //!
    //! \ingroup type_classes_internal
    //! \brief < operator for type_id_t
    //!
    //! gcc 4.4 does not implement the < operator for scoped enums. In such 
    //! cases this overloaded version is used. This operator will only be used 
    //! if the code is compiled with \c -DENUMBUG.
    //! 
    bool operator<(type_id_t a,type_id_t b);

    //-------------------------------------------------------------------------
    //!
    //! \ingroup type_classes_internal
    //! \brief > operator for type_id_t
    //!
    //! gcc 4.4 does not implement the > operator for scoped enums. In such 
    //! cases this overloaded version is used. This operator will only be used 
    //! if the code is compiled with \c -DENUMBUG.
    //! 
    bool operator>(type_id_t a,type_id_t b);
    
    //-------------------------------------------------------------------------
    //!
    //! \ingroup type_classes_internal
    //! \brief <= operator for type_id_t
    //!
    //! gcc 4.4 does not implement the <= operator for scoped enums. In such 
    //! cases this overloaded version is used. This operator will only be used 
    //! if the code is compiled with \c -DENUMBUG.
    //! 
    bool operator<=(type_id_t a,type_id_t b);
    
    //-------------------------------------------------------------------------
    //!
    //! \ingroup type_classes_internal
    //! \brief >= operator for type_id_t
    //!
    //! gcc 4.4 does not implement the >= operator for scoped enums. In such 
    //! cases this overloaded version is used. This operator will only be used 
    //! if the code is compiled with \c -DENUMBUG.
    //! 
    bool operator>=(type_id_t a,type_id_t b);

    //-------------------------------------------------------------------------
    //!
    //! \ingroup type_classes_internal
    //! \brief < operator for type_class_t
    //!
    //! gcc 4.4 does not implement the < operator for scoped enums. In such 
    //! cases this overloaded version is used. This operator will only be used 
    //! if the code is compiled with \c -DENUMBUG.
    //! 
    bool operator<(type_class_t a,type_class_t b);
    
    //-------------------------------------------------------------------------
    //!
    //! \ingroup type_classes_internal
    //! \brief > operator for type_class_t
    //!
    //! gcc 4.4 does not implement the > operator for scoped enums. In such 
    //! cases this overloaded version is used. This operator will only be used 
    //! if the code is compiled with \c -DENUMBUG.
    //! 
    bool operator>(type_class_t a,type_class_t b);
    
    //-------------------------------------------------------------------------
    //!
    //! \ingroup type_classes_internal
    //! \brief <= operator for type_class_t
    //!
    //! gcc 4.4 does not implement the <= operator for scoped enums. In such 
    //! cases this overloaded version is used. This operator will only be used 
    //! if the code is compiled with \c -DENUMBUG.
    //! 
    bool operator<=(type_class_t a,type_class_t b);
    
    //-------------------------------------------------------------------------
    //!
    //! \ingroup type_classes_internal
    //! \brief >= operator for type_class_t
    //!
    //! gcc 4.4 does not implement the >= operator for scoped enums. In such 
    //! cases this overloaded version is used. This operator will only be used 
    //! if the code is compiled with \c -DENUMBUG.
    //! 
    bool operator>=(type_class_t a,type_class_t b);
#endif
    
    //! standard type for array shapes
    typedef std::vector<size_t> shape_t;
    //! another alias for the standard shape type
    typedef std::vector<size_t> shape_type;

//end of namespace
}
