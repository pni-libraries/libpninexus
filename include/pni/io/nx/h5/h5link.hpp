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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  ee the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with libpniio.  If not, see <http://www.gnu.org/licenses/>.
 *************************************************************************
 *
 * Definition of the H5Link link manager class.
 *
 * Created on: Feb 10, 2012
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

#pragma once

extern "C"{
#include <hdf5.h>
}

#include <pni/core/types.hpp>
#include <pni/core/exceptions.hpp>

#include "../nxpath.hpp"
#include "../nxpath_utils.hpp"

namespace pni{
namespace io {
namespace nx{
namespace h5{

    using namespace pni::core;
    //avoid namespace collisions with std
    using pni::core::exception;
    using pni::core::string;
    using pni::io::nx::nxpath;

    class H5Group;
   
    /*! 
    \ingroup nxh5_classes

    This class holds only static methods which can be used
    to create internal and external links. 
    */
    class h5link
    {
        private:
            /*!
            \brief convert a Nexus path to an HDF5 path

            This static method converts a Nexus path to an HDF5 path. HDF5
            requires that all group and field names are given. Thus, one cannot
            use just the groups class to identify a group. 
            If the name of a group or field is not given a
            pni::core::value_error is thrown.

            \throws pni::core::value_error if element name is missing
            \param p Nexus path object
            \return HDF5 path as a string
            */
            static string _nx2hdf5path(const nxpath &p);


        public:

            /*! 
            \brief create an external link

            The target path for an external link must be a full Nexus path
            including a filename. If it does not contain a filename nxlink_error
            will be thrown. name determines the name of the link as a child of
            loc. The target path must not contain element without a name (HDF5
            cannot handle such situations) otherwise a value_error exception
            will be thrown.

            \throws pni::io::nx::nxlink_error in case of all errors
            \throws pni::core::value_error for path elements wihtout name
            \param target path of the links target
            \param loc location where the link should be created
            \param name linkname below loc
            */
            static void create_external_link(const nxpath &target,
                                             const H5Group &loc,
                                             const string &name);

            //-----------------------------------------------------------------
            /*!
            \brief create an internal link

            Unlike for external links in the target path can be either absolute
            in the file or relative to loc. name determines the name of the link
            below loc. target_path must not have elements without a name. In
            such a case a value_error will be thrown. In addition the
            target_path Nexus path must not contain a file name.

            \throws pni::core::value_error if the target path contains elements
            without an object name
            \throws pni::io::nx::nxlink_error if linking fails
            \param target path to the links target
            \param loc location for the new link
            \param name name of the object below loc
            */
            static void create_internal_link(const nxpath &target,
                                             const H5Group &loc,
                                             const string &name);
    };
//end of namespace
}
}
}
}