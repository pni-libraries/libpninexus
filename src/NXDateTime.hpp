/*
 * (c) Copyright 2011 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 * This file is part of libpninx.
 *
 * libpninx is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * libpninx is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with libpninx.  If not, see <http://www.gnu.org/licenses/>.
 *************************************************************************
 * NXDateTime.hpp
 *
 *  Created on: Nov 17, 2011
 *      Author: Eugen Wintersberger
 */

#pragma once

#include<ctime>
#include<boost/date_time/posix_time/posix_time.hpp>
#include<boost/date_time/local_time_adjustor.hpp>
#include<boost/date_time/c_local_time_adjustor.hpp>
#include <pni/utils/Types.hpp>

using namespace pni::utils;
using namespace boost::posix_time;
using namespace boost::gregorian;

namespace pni {
namespace nx {

    /*! \ingroup util_classes
    \brief date time factory

    NXDateTime provides static methods to create date-time strings which are
    compliant to the Nexus standard. It is highly important for this class to
    work properly that the time zone setup is correct.  Time-zone information
    can come either directly from the host machine the program is running on or
    can be configured manually if this setup is not correct. 
    */
    class NXDateTime {
        private:
            //! get date time from ptime 
            static String __get_date_time_str(const ptime &t);
            //! get delta to UTC as a string
            static String __get_utc_delta();
        public:
            //-----------------------------------------------------------------
            /*! date-time now

            Returns a string with a Nexus compliant date-time string for now.
            \return Nexus date-time string
            */
            static String get_date_time_str();

            //-----------------------------------------------------------------
            /*! date-time at t

            Converts a given time in time_t format to a Nexus date-time string.
            \param t time as time_t
            \return Nexus date-time string
            */
            static String get_date_time_str(const time_t &t);
    };

//end of namepsace
} 
} 
