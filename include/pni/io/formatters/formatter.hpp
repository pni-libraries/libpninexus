//
// (c) Copyright 2015 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
// Created on: Feb 11, 2015
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
//
#pragma once

#include <vector>
#include <iterator>
#include <pni/core/types.hpp>
#include <pni/core/type_erasures.hpp>
#include <boost/spirit/include/karma.hpp>

#include "get_generator.hpp"

namespace pni{
namespace io{

    using namespace pni;
    using namespace boost::spirit;

    //!
    //! \ingroup formatter_classes
    //! \brief scalar formatter
    //! 
    //! This is the default implementation of a formatter. It is intended to 
    //! be used with scalar and complex primitive types. 
    //! 
    //! \tparam T primitive type
    template<typename T> 
    class formatter
    {
        private: 
            //! output iterator type
            typedef std::back_insert_iterator<core::string> iterator_type;
            //! generator type
            typedef typename get_generator<iterator_type,T>::type generator_type; 
            
            //! generator instance
            generator_type generator;
    
        public:

            //!
            //! \brief generate output
            //! 
            //! Take the input value and convert it to its string 
            //! representation.
            //! 
            //! \param value a value of type T
            //! \return string representation of value
            //! 
            core::string operator()(const T &v) const
            {
                core::string buffer;
                iterator_type inserter(buffer);

                karma::generate(inserter,generator,v);

                return buffer;
            }            
    };
    
    //-------------------------------------------------------------------------
    //!
    //! \ingroup formatter_classes
    //! \brief formatter for strings
    //! 
    //! A specialization of the formatter template for scalar values for 
    //! strings. In fact this formatter does nothing else than passing 
    //! the string through to output. 
    //!
    template<> class formatter<core::string>
    {
        public:
            core::string operator()(const core::string &v) const
            {
                return v;
            }
    };

    //-------------------------------------------------------------------------
    //!
    //! \ingroup formatter_classes
    //! \brief formatter for bool
    //! 
    //! A specialization of the formatter template for scalar boolean values.
    //!
    template<> class formatter<bool>
    {
        public:
            core::string operator()(const bool &v) const
            {
                if(v) return "true";
                
                return "false";
            }
    };
    
    //-------------------------------------------------------------------------
    //!
    //! \ingroup formatter_classes
    //! \brief formatter for value_ref type erasure
    //! 
    //! A specialization of the formatter template for scalar values for the 
    //! value_ref type erasure.
    //!
    template<> class formatter<core::value_ref>
    {
        public:
            core::string operator()(const core::value_ref &v) const
            {
                return formatter<core::value>()(core::to_value(v));
            }
    };

 

    //------------------------------------------------------------------------
    //!
    //! \ingroup formatter_classes
    //! \brief vector formatter
    //!
    //! Specialization of the default formatter for vectors.  The elements of
    //! the vector must be of a primitive type.
    //!
    //! \tparam T element type of the vector
    //!
    template<typename T> 
    class formatter<std::vector<T>>
    {
        private:
            //! output iterator type
            typedef std::back_insert_iterator<core::string> iterator_type;
            //! generator type
            typedef typename get_generator<iterator_type,T>::type generator_type; 
            //! generator instance
            generator_type generator;

        public:

            //! 
            //! \brief generate output
            //! 
            //! Take the input vector and return its string representation. 
            //!
            //! \param v input vector
            //! \return string representation of the input vector
            //! 
            core::string operator()(const std::vector<T> &v) const
            {
                core::string buffer;
                iterator_type inserter(buffer);

                karma::generate(inserter,generator % ' ',v);

                return buffer;
            }
    };
    
    //-------------------------------------------------------------------------
    template<> 
    class formatter<std::vector<core::string>>
    {
        private:
            //! output iterator type
            typedef std::back_insert_iterator<core::string> iterator_type;
            //! generator type
            //typedef typename get_generator<iterator_type,T>::type generator_type; 
            //! generator instance
            //generator_type generator;

        public:

            //! 
            //! \brief generate output
            //! 
            //! Take the input vector and return its string representation. 
            //!
            //! \param v input vector
            //! \return string representation of the input vector
            //! 
            core::string operator()(const std::vector<core::string> &v) const
            {
                core::string buffer;
                iterator_type inserter(buffer);

                karma::generate(inserter,karma::string % '\n',v);

                return buffer;
            }
    };
    
    //-------------------------------------------------------------------------
    /*
    template<>
    class formatter<core::array>
    {
        private:
            formatter<core::value> value_formatter;
            
            char _start;  //start symbol for the sequence
            char _stop;   //stop symbol for the sequence
            char _sep;    //element seperator
            
        public:
            formatter():
                _sep(' ')
            {}
            
            //-----------------------------------------------------------------
            formatter(char sep):
                _sep(sep)
            {}
            
            //-----------------------------------------------------------------
            formatter(char start,char stop,char sep):
                _start(start),
                _stop(stop),
                _sep(sep)
            {}
            
            //-----------------------------------------------------------------
            core::string operator()(const core::array &v) const
            {
                core::string result;
                
                auto iter     = v.begin();
                auto end_iter = v.end();
                
                //return an empty string if the array has no content
                if(iter==end_iter) return result;
                
                result += value_formatter(*iter);
                
                for(++iter;iter!=end_iter;++iter)
                    result += _sep + value_formatter(*iter);
                
                return result;
            }
            
    };*/

//end of namespace
}
}
