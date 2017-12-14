//
// (c) Copyright 2014 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
//  Created on: Jul 16, 2014
//      Author: Eugen Wintersberger
//

#include <pni/io/nx/h5/file_imp.hpp>
#include <pni/io/nx/h5/group_imp.hpp>
#include <pni/io/nx/h5/attribute_imp.hpp>
#include <pni/io/nx/h5/h5dataspace.hpp>
#include <pni/io/nx/h5/h5datatype.hpp>
#include <pni/io/nx/h5/attribute_utils.hpp>

#include <pni/io/nx/h5/h5_error_stack.hpp>

#include <boost/regex.hpp>

#include <sstream>

namespace pni{
namespace io{
namespace nx{
namespace h5{
    
    using namespace pni::core;

    //=================private functions=======================================
    bool is_family_filename(const string &fname)
    {
        boost::regex r("%[[:digit:]]*[idu]");
        
        boost::smatch matches;
        return boost::regex_search(fname,matches,r);        
    }


    //=========Implementation fo constructors an destructors===================
    //implementation of the default constructor
    file_imp::file_imp() noexcept
        :_object()
    {}

    //-------------------------------------------------------------------------
    file_imp::file_imp(object_imp &&o) 
        :_object(std::move(o))
    {
        if(get_hdf5_type(_object)!=h5object_type::FILE)
            throw type_error(EXCEPTION_RECORD,
                    "Object is not a file object!");
    }

    //=================Implementation of file specific methods=================
    void file_imp::close()
    {
        //check for open objects in the file
        if(_object.is_valid()) flush();
#ifdef DEBUG
        std::cerr<<"Open files:      "<< 
        H5Fget_obj_count(_object.id(),H5F_OBJ_FILE)<<std::endl;
        std::cerr<<"Open data sets:  "<<
        H5Fget_obj_count(_object.id(),H5F_OBJ_DATASET)<<std::endl;
        std::cerr<<"Open groups:     "<<
        H5Fget_obj_count(_object.id(),H5F_OBJ_GROUP)<<std::endl;
        std::cerr<<"Open data type:  "<<
        H5Fget_obj_count(_object.id(),H5F_OBJ_DATATYPE)<<std::endl;
        std::cerr<<"Open attributes: "<<
        H5Fget_obj_count(_object.id(),H5F_OBJ_ATTR)<<std::endl;
#endif
        _object.close();
    }
    
    //-------------------------------------------------------------------------
    file_imp file_imp::open(const string &path,bool ro)
    {
        //check if the file is a valid HDF5 file
        if(!H5Fis_hdf5(path.c_str()))
            throw file_error(EXCEPTION_RECORD, 
                  "File ["+path+"] is not an HDF5 file!\n\n"+
                  get_h5_error_string());

        object_imp acc_plist(H5Pcreate(H5P_FILE_ACCESS));

        //need to determine the file driver used to create the file: 
        //A possible solution would be to check the file name (could reuse the 
        //testing code from above).
        if(is_family_filename(path))
            H5Pset_fapl_family(acc_plist.id(),H5F_FAMILY_DEFAULT,H5P_DEFAULT);

        //open the file in the appropriate mode
        if(ro)
            return file_imp(object_imp(H5Fopen(path.c_str(),
                                               H5F_ACC_RDONLY,
                                               acc_plist.id())));
        else
            return file_imp(object_imp(H5Fopen(path.c_str(),
                                               H5F_ACC_RDWR,
                                               acc_plist.id())));
    }


    //-------------------------------------------------------------------------
    file_imp file_imp::create(const string &n,bool overwrite,ssize_t ssize)
    {
        //create property lists for file creation an access
        object_imp create_plist(H5Pcreate(H5P_FILE_CREATE));

        object_imp acc_plist(H5Pcreate(H5P_FILE_ACCESS));

        if(ssize > 0)
            //enable splitting
            H5Pset_fapl_family(acc_plist.id(),ssize*1024*1024,H5P_DEFAULT);

        object_imp file;
        if(overwrite)
            file = object_imp(H5Fcreate(n.c_str(),
                                        H5F_ACC_TRUNC,
                                        create_plist.id(),
                                        acc_plist.id()));
        else
            file = object_imp(H5Fcreate(n.c_str(),
                                        H5F_ACC_EXCL,
                                        create_plist.id(),
                                        acc_plist.id()));

        //in the end we need to set the HDF5 version to the correct
        //value
        unsigned major,minor,rel;
        H5get_libversion(&major,&minor,&rel);
        std::ostringstream vstring;
        vstring<<major<<"."<<minor<<"."<<rel;
   
        attribute_imp a(create_attribute(file,
                                         "HDF5_version",
                                         get_type(type_id_t::STRING),
                                         h5dataspace(),
                                         true));
        string version(vstring.str());
        a.write(type_id_t::STRING,&version);

        return file_imp(std::move(file));
    }

    //-------------------------------------------------------------------------
    void file_imp::flush() const
    {
        if(_object.is_valid()) 
            if(H5Fflush(_object.id(),H5F_SCOPE_LOCAL)<0)
                throw io_error(EXCEPTION_RECORD,"Flush to file failed!");
    }
   
    //------------------------------------------------------------------------
    bool file_imp::is_valid() const
    {
        return _object.is_valid();
    }

    //-------------------------------------------------------------------------
    bool file_imp::is_readonly() const
    {
        if(!is_valid())
            throw invalid_object_error(EXCEPTION_RECORD,
                    "Cannot retrieve file intent from invalid file object!");

        unsigned int stat;
        if(H5Fget_intent(_object.id(),&stat)<0)
            throw file_error(EXCEPTION_RECORD,"Cannot retrieve file intent!");

        if(stat==H5F_ACC_RDWR) return false;
        return true;
    }
    
    //------------------------------------------------------------------------
    group_imp file_imp::root() const
    {
        if(!is_valid())
            throw invalid_object_error(EXCEPTION_RECORD,
                    "Cannot obtain root group from invalid file object!");

        return group_imp(object_imp(H5Oopen(_object.id(),"/",H5P_DEFAULT)));
    }

//end of namespace
}
}
}
}