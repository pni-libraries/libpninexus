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
 *
 * Definition of the NXConfiguration class.
 *
 * Created on: Apr 17, 2012
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

#pragma once

#include<vector>
#include<map>
#include<pni/utils/Types.hpp>

using namespace pni::utils;

namespace pni{
    namespace nx{

        /*! 
        \brief library configuration class

        This class holds the configuration of the library. The class is
        initialized from several configuration files. 

        The global configuration of the library resides on Linux under 
        /etc/pni/pninx/ 
        
        Aside from this every user can have a local configuration under 
        $HOME/.pni/pninx

        The configuration holds information such as the timezone of the 
        machine, the NXDL files for base classes and application definitions. 
        
        The class is implemented as a singleton and available as a global
        variable from all instances. The class provides methods to reread the
        configuration at runtime. This allows, for instance the installation of
        additional NXDL files while a program is running. 
        */
        class NXConfiguration{
            private:
                String __config_dir_root; //!< root directory of the library
                                          //!< configuration
                String __global_nxdl_dir; //!< global NXDL 
                std::vector<String> __base_classes; //!< base classes
                std::vector<String> __app_classes;  //!< application definitions
            public:
                //! default constructor
                NXConfiguration();

                //! destructor
                ~NXConfiguration();

                //! get global configuration directory
                String global_config_dir() const;

                //! get the global NXDL directory
                String global_nxdl_dir() const;

                //! get base classes
                const std::vector<String> &base_classes() const;

                //! get application definitions
                const std::vector<String> &app_classes() const;

                //! reset
                void reset();





        };

//end of namespace
}
}
