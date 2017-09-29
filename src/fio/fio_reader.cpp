//
// (c) Copyright 2011 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
// Created on: Apr 30, 2012
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
///

#include <sstream>
#include <string>
#include <pni/io/fio/fio_reader.hpp>
#include <boost/regex.hpp>
#include <boost/algorithm/string/trim.hpp>

static const boost::regex parameter_section_re("^[[:space:]]*%p[[:space:]]*");
static const boost::regex data_section_re("^[[:space:]]*%d[[:space:]]*");
static const boost::regex key_value_re("^\\s*(?<KEY>[^=]+)\\s*=\\s*(?<VALUE>[^=]+)\\s*");
static const boost::regex col_descriptor_re("^\\s*Col\\s+(?<INDEX>\\d+)\\s+(?<NAME>\\w+)\\s+(?<TYPE>\\w+)");
static const boost::regex data_record_re("^(?:\\s+[+-\\.0-9eE]+)+\\s*");
//boost::regex dcol("[+-]?\\d+\\.?\\d*e?[+-]?\\d*");

namespace pni{
namespace io{

    //======================private member functions===========================
    void fio_reader::_parse_file(std::ifstream &stream)
    {
        pni::core::string line_buffer;
        boost::smatch match;

        //
        // we use a two step approach here:
        // -> in the first parser run we look for the offsets of the
        //    different sections in the file
        // -> in the second run we parse the sections
        while(!stream.eof())
        {
            //read a character
            std::getline(stream,line_buffer);
            if(boost::regex_match(line_buffer,match,parameter_section_re))
            {
            	_param_offset = stream.tellg();
            }
            else if(boost::regex_match(line_buffer,match,data_section_re))
            {
            	_data_offset = stream.tellg();
            	break; //terminate the loop - the data section is the last one
            }
        }

        stream.seekg(_param_offset,std::ios::beg);
        _parse_parameters(stream);
        stream.seekg(_data_offset,std::ios::beg);
        _parse_data(stream);

        //reset EOF bit
        stream.clear();
    }

    //-------------------------------------------------------------------------
    void fio_reader::_parse_parameters(std::ifstream &stream)
    {
        pni::core::string param_name,param_value,line_buffer;
        boost::smatch match;
        //clear the parameter map
        _param_map.clear();

        //read the parameter section
        while(!stream.eof())
        {
        	//read a single character form the file
            std::getline(stream,line_buffer);
            
            if(boost::regex_match(line_buffer,match,key_value_re))
            {
            	pni::core::string key = match.str("KEY");
            	pni::core::string value = match.str("VALUE");
            	boost::trim(key);
            	boost::trim(value);

            	_param_map.insert({key,value});
            }
            else
            {
            	return;	//if we encounter a non-key-value line we are done
            }
        }
    }

    //-------------------------------------------------------------------------
    void fio_reader::_parse_data(std::ifstream &stream)
    {
        //boost::regex dcol("[+-]?\\d*.?\\d*[e]?[+-]?\\d*");
        //boost::regex is_dcol("^\\s+[+-]?\\d+\\.?\\d*e?[+-]?\\d*.*");
        boost::smatch match;

        pni::core::string linebuffer;
        std::streampos data_offset_tmp = 0;
        size_t nr = 0; //number of records

        pni::core::string line_buffer;

        while(!stream.eof())
        {
            std::getline(stream,line_buffer);
            
            if(boost::regex_match(line_buffer,match,col_descriptor_re))
            {
            	pni::core::string cname = match.str("NAME"),
            			          ctype = match.str("TYPE");
            	boost::trim(cname);
            	boost::trim(ctype);

            	_append_column(column_info(cname,_typestr2id(ctype),std::vector<size_t>()));
            }
            else if(boost::regex_match(line_buffer,match,data_record_re))
            {
//                if(!_data_offset) _data_offset = data_offset_tmp;
//                         _read_data_line(linebuffer);
            	nr++;
            }
        }
       
        //set the number of records in the file
        _nrecords(nr);
        //must be called here to clear EOF error bit
        //must be called before next call to seekg
        stream.clear();
    }

    //-------------------------------------------------------------------------
    void fio_reader::_get_parameter_data(std::ifstream &stream,
                                         pni::core::string &value)
        const
    {
        char buffer;
        value.clear();

        while(!stream.eof())
        {
            stream.get(buffer);
            if(buffer == '\n') break;
            value.push_back(buffer);
        }
    }

    //=================implementation of static private methods================
    pni::core::type_id_t fio_reader::_typestr2id(const pni::core::string &tstr)
    {
        if(tstr == "FLOAT") 
            return pni::core::type_id_t::FLOAT32;
        else if(tstr == "DOUBLE")
            return pni::core::type_id_t::FLOAT64;
        else
            return pni::core::type_id_t::NONE;
    }



    //-------------------------------------------------------------------------
    std::vector<pni::core::string> fio_reader::_read_data_line(const pni::core::string &line)
    {
        boost::regex dcol("[+-]?\\d+\\.?\\d*e?[+-]?\\d*");
        std::vector<pni::core::string> record;

        boost::match_results<pni::core::string::const_iterator> imatch;
        pni::core::string::const_iterator start = line.begin();
        pni::core::string::const_iterator end   = line.end();
        while(boost::regex_search(start,end,imatch,dcol,boost::match_default))
        {
            record.push_back(imatch.str());
            start = imatch[0].second;
        }

        return record;
    }

    //=======================constructors and destructor======================= 
    //default constructor implementation
    fio_reader::fio_reader():
    	spreadsheet_reader(),
		_param_map(),
		_param_offset(0),
		_data_offset(0),
		_columns()
    {}

    //-------------------------------------------------------------------------
    //standard constructor implementation
    fio_reader::fio_reader(const pni::core::string &n):
        spreadsheet_reader(n),
        _param_map(),
        _data_offset(0),
		_param_offset(0),
		_columns()
    {
        _parse_file(_get_stream()); 
    }

    //-------------------------------------------------------------------------
    //! destructor
    fio_reader::~fio_reader()
    {}

    //=============public memeber methods======================================
    //implementation of nparameters
    size_t fio_reader::nparameters() const
    {
        return _param_map.size();
    }
    
    //-------------------------------------------------------------------------
    //implementation of parameter names
    std::vector<pni::core::string> fio_reader::parameter_names() const
    {
        std::vector<pni::core::string> pnames;
        std::transform(_param_map.begin(),_param_map.end(),
        		std::back_inserter(pnames),
				[](const parameter_map_type::value_type &pair){return pair.first;});

        return pnames;
    }



//end of namespace
}
}
