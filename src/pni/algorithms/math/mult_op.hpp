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
// ============================================================================
//
// Created on: Jul 25,2012
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#pragma once

#include <pni/algorithms/math/op_traits.hpp>
#include <pni/utilities/container_iterator.hpp>

namespace pni{

    
    template<typename ArrayT>  class array_view;

    //!
    //! \ingroup mdim_array_internal_classes
    //! \brief Multiplication expression template
    //! 
    //! \tparam Operand1T left hand operand type
    //! \tparam Operand2T right hand operand type
    //! 
    template<
             typename Operand1T,
             typename Operand2T
            > 
    class mult_op
    {
        private:
            //! left operand
            typename op_trait<Operand1T>::ref_type _op1;
            //! right operand
            typename op_trait<Operand2T>::ref_type _op2;
        public:
            //--------------------public types---------------------------------
            //! value type of the multiplication
            typedef typename Operand1T::value_type value_type;
            //! type of the operation class
            typedef mult_op<Operand1T,Operand2T> array_type;
            //! storage type
            typedef void storage_type;
            //! non-const iterator type - this is only to satsify the interaface
            typedef container_iterator<array_type> iterator; 
            //! const iterator type
            typedef container_iterator<const array_type> const_iterator;
            //! reverse iterator type
            typedef container_iterator<array_type> reverse_iterator;
            //! const reverse iterator type
            typedef container_iterator<const array_type> const_reverse_iterator;
            //! view type
            typedef array_view<array_type> view_type;

            //! index map type
            typedef typename array_trait<Operand1T,Operand2T>::map_type map_type;
            //! inplace arithmetic type
            typedef typename array_trait<Operand1T,Operand2T>::inplace_arithmetic
                inplace_arithmetic;

            //===================constructors==================================
            //! 
            //! \brief constructor
            //!
            //! Set up the operator class.
            //! \param o1 left operand
            //! \param o2 right operand
            //!
            mult_op(const Operand1T &o1,const Operand2T &o2):
                _op1(o1),
                _op2(o2)
            {}

            //====================public methods===============================
            //! 
            //! \brief get value at index i
            //!
            //! Return the value of _op1[i]*_op2[i];
            //! \param i index for which to reqest data
            //! \return result of operation
            //!
            value_type operator[](size_t i) const
            {
                return this->_op1[i]*this->_op2[i];
            }

            //-----------------------------------------------------------------
            //!
            //! \brief get value at index i
            //!
            //! Return the result of the operation at index i.
            //! 
            //! \throws index_error if i exceeds size
            //! \param i index for which to perform the operation
            //! \return result of the operation
            //! 
            value_type at(size_t i) const 
            {
                if(i>=size()) 
                    throw index_error(PNINEXUS_EXCEPTION_RECORD,"index exceeds size!");

                return (*this)[i];
            }

            //-----------------------------------------------------------------
            //! 
            //! \brief return size of the operator
            //!
            //! This is the maximum size of the two operands.
            //! \return size of the operation
            //!
            size_t size() const
            {
                return _op1.size() > _op2.size() ? _op1.size() : _op2.size();
            }


            //=====================iterators===================================
            //! 
            //! \brief get iterator on first element
            //! 
            const_iterator begin() const
            {
                return const_iterator(this,0);
            }

            //-----------------------------------------------------------------
            //! 
            //! \brief get iterator on last+1 element
            //! 
            const_iterator end() const
            {
                return const_iterator(this,this->size());
            }
    };
//end of namespace
}
