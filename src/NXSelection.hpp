/*
 * Declaration of the NXfield template
 *
 * (c) Copyright 2011 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
 *
 * Declaration of the NXfield template
 *
 * Created on: Nov 14, 2012
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */
#pragma once

#include <vector>
#include <pni/core/slice.hpp>

using namespace pni::core;

namespace pni{
namespace io{
namespace nx{

    template<typename FTYPE> class NXSelection
    {
        private:
            std::vector<slice>  _selection;
            FTYPE &_field; //!< reference to the original field

            void apply_selection() const
            {
                _field.apply_selection(_selection);
            }

            void reset_selection() const
            {
                _field.reset_selection();
            }
        public:
            //=================public types====================================
            typedef std::vector<slice> selection_type;
            //=============constructors and destructor=========================
            //! default constructor
            NXSelection(selection_type sel,FTYPE &field):
                _selection(sel),
                _field(field)
            {}

            //-----------------------------------------------------------------
            //! copy constructor
            NXSelection(const NXSelection<FTYPE> &sel):
                _selection(sel._selection),
                _field(sel._field)
            {}

            //-----------------------------------------------------------------
            //! destructor
            ~NXSelection()  
            {
                //need to remove all eventual selections in case that something 
                //goes wrong and the selection gets destroyed
                reset_selection();
            }

            //=================assignment operators============================
            NXSelection<FTYPE> &operator=(const NXSelection<FTYPE> &sel)
            {
                if(this == &sel) return *this;
                _selection = sel._selection;
                _field = sel._field;
                return *this;
            }

            //====================public member functions======================
            //! get size
            size_t size() const
            {   
                this->apply_selection();
                size_t s = this->_field.size();
                //release selection
                this->reset_selection();

                return s;
            }

            //-----------------------------------------------------------------
            //! get shape
            template<typename CTYPE> CTYPE shape() const
            {
                this->apply_selection();
                auto s = this->_field.shape<CTYPE>();
                this->reset_selection();
                return s;
            }

            //-----------------------------------------------------------------
            //! get type id
            type_id_t type_id() const
            {
                return _field.type_id();
            }

            //-----------------------------------------------------------------
            //! get the rank
            size_t rank() const
            {
                this->apply_selection();
                size_t r = this->_field.rank();
                this->reset_selection();
                return r;
            }

            //-----------------------------------------------------------------
            //! read data
            template<typename DTYPE> void read(DTYPE &data) const
            {
                this->apply_selection();
                this->_field.read(data);
                this->reset_selection();
            }

            //-----------------------------------------------------------------
            //! write data
            template<typename DTYPE> void write(const DTYPE &data) const
            {
                this->apply_selection();
                this->_field.write(data);
                this->reset_selection();
            }
    };


//end of namespace
}
}
}
