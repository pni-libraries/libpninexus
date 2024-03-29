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
// ===========================================================================
//
// Created on: Sep 26, 2011
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
//

#pragma once
#include <pni/types.hpp>
#include <pni/error.hpp>
#include <pni/windows.hpp>

namespace pni{
namespace tiff{

    //! 
    //! \ingroup image_io_tiff
    //! \brief error during TIFF reading
    //!
    //! This exception is thrown in cases where errors occur during reading 
    //! TIFF files.
    //!
    class PNINEXUS_EXPORT tiff_read_error:public pni::exception
    {
        public:
            //! default constructor
            tiff_read_error():exception("tiff_read_error"){}
            //! constructor

            //! \param i signature of the exception issuer
            //! \param d description of the error
            tiff_read_error(const pni::exception_record &i,
                            const pni::string &d):
                exception("tiff_read_error",i,d)
            {}
            //! destructor
            virtual ~tiff_read_error() throw() {}

            //! output operator
            friend std::ostream &operator<<(std::ostream &o,const
                    tiff_read_error &e);
    };

//end of namespace
}
}

