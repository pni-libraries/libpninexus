/*
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
 * Definition of the NXDeflateFilter class.
 *
 * Created on: Feb 16, 2012
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */
#pragma once

#include "nxfilter.hpp"

namespace pni{
namespace io {
namespace nx{
    //need this here to avoid name collisions with tango headers.
    using pni::core::array;
    using pni::core::string;
    using pni::core::exception;

    /*! 
    \ingroup nexus_utilities
    \brief Nexus deflate filter

    This class provides an implementation of the simple deflate filter as it is
    implemented in zlib. 
    */
    template<typename Imp> class nxdeflate_filter:public nxfilter<Imp>
    {
        public:
            //====================constructors and destructor==================
            //! default constructor
            explicit nxdeflate_filter():nxfilter<Imp>() { }

            //-----------------------------------------------------------------
            //! copy constructor
            nxdeflate_filter(const nxdeflate_filter<Imp> &f)
                :nxfilter<Imp>(f)
            { }

            //-----------------------------------------------------------------
            //! move constructor
            nxdeflate_filter(nxdeflate_filter<Imp> &&f)
                :nxfilter<Imp>(std::move(f))
            { }

            //-----------------------------------------------------------------
            //! standard constructor
            nxdeflate_filter(uint32 r,bool s)
                :nxfilter<Imp>(Imp(r,s))
            { }

            //-----------------------------------------------------------------
            //! destructor
            ~nxdeflate_filter() { }

            //====================assignment operators=========================
            //! copy assignment operator
            nxdeflate_filter<Imp> &
                operator=(const nxdeflate_filter<Imp> &f)
            {
                if(this != &f) nxfilter<Imp>::operator=(f);
                return *this;
            }

            //-----------------------------------------------------------------
            //! move assignment operator
            nxdeflate_filter<Imp> &operator=(nxdeflate_filter<Imp> &&f)
            {
                if(this != &f) nxfilter<Imp>::operator=(std::move(f));
                return *this;
            }

            //==============filter attribute access methods====================
            //! set compression rate
            void compression_rate(uint32 r)
            {
                this->imp().compression_rate(r);
            }

            //-----------------------------------------------------------------
            //! get compression rate
            uint32 compression_rate() const
            {
                return this->imp().compression_rate();
            }

            //-----------------------------------------------------------------
            //! set shuffle 
            void shuffle(bool s)
            {
                this->imp().shuffle(s);
            }

            //-----------------------------------------------------------------
            //! get shuffle flag
            bool shuffle() const
            {
                return this->imp().shuffle();
            }

    };

//end of namespace
}
}
}
