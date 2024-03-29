//
// (c) Copyright 2015 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
// Created on: Sep 08, 2015
//      Authors:
//              Eugen Wintersberger <eugen.wintersberger@desy.de>
//              Jan Kotanski <jan.kotanski@desy.de>
//
//

#include <pni/formatters/scalar_format.hpp>
#include <h5cpp/contrib/nexus/ebool.hpp>
#include <boost/format.hpp>

namespace pni{
    using namespace pni;

#define PNINEXUS_SCALAR_FORMAT_FUNCTION(type) \
    string format(type v)\
    {\
        return ""; \
    }

    //=========================================================================
    string format(const uint8 &v)
    {
        boost::format fmt("%|+|");
        fmt % uint16(v);

        return fmt.str();
    }

    //=========================================================================
    string format(const int8 &v)
    {
        boost::format fmt("%|+|");
        fmt % int16(v);
        return fmt.str();
    }

    //=========================================================================
    string format(const uint16 &v)
    {
        boost::format fmt("%|+|");
        fmt % v;
        return fmt.str();
    }

    //=========================================================================
    string format(const int16 &v)
    {
        boost::format fmt("%|+|");
        fmt %v;
        return fmt.str();
    }

    //=========================================================================
    string format(const uint32 &v)
    {
        boost::format fmt("%|+|");
        fmt %v;
        return fmt.str();
    }

    //=========================================================================
    string format(const int32 &v)
    {
        boost::format fmt("%|+|");
        fmt %v;
        return fmt.str();
    }

    string format(const uint64 &v)
    {
        boost::format fmt("%|+|");
        fmt %v;
        return fmt.str();
    }

    string format(const int64 &v)
    {
        boost::format fmt("%|+|");
        fmt %v;
        return fmt.str();
    }

    string format(const float32 &v)
    {
        boost::format fmt("%|+.9e|");
        fmt %v;
        return fmt.str();
    }
    string format(const float64 &v)
    {
        boost::format fmt("%|+.17e|");
        fmt %v;
        return fmt.str();
    }

    string format(const float128 &v)
    {
        boost::format fmt("%|+.17e|");
        fmt %v;
        return fmt.str();
    }

    string format(const complex32 &v)
    {
        boost::format fmt_p("%|+.9e|+I%|.9e|");
        boost::format fmt_m("%|+.9e|-I%|.9e|");

        if(v.imag()<0)
        {
            fmt_m %v.real() %(-1.*v.imag());
            return fmt_m.str();
        }
        else
        {
            fmt_p %v.real() %v.imag();
            return fmt_p.str();
        }

    }
    string format(const complex64 &v)
    {
        boost::format fmt_p("%|+.17e|+I%|.17e|");
        boost::format fmt_m("%|+.17e|-I%|.17e|");

        if(v.imag()<0)
        {
            fmt_m %v.real() %(-1.*v.imag());
            return fmt_m.str();
        }
        else
        {
            fmt_p %v.real() %v.imag();
            return fmt_p.str();
        }
    }

    string format(const complex128 &v)
    {
        boost::format fmt_p("%|+.17e|+I%|.17e|");
        boost::format fmt_m("%|+.17e|-I%|.17e|");

        if(v.imag()<0)
        {
            fmt_m %v.real() %(-1.*v.imag());
            return fmt_m.str();
        }
        else
        {
            fmt_p %v.real() %v.imag();
            return fmt_p.str();
        }
    }

    string format(const bool_t &v)
    {
        if(v)
            return "true";
        else
            return "false";
    }

    string format(const hdf5::datatype::EBool &v)
    {
        if(v)
            return "true";
        else
            return "false";
    }

    //-------------------------------------------------------------------------
    string format(const string &s)
    {
        return s;
    }

    //-------------------------------------------------------------------------
    string format(const value &v)
    {
        switch(v.type_id())
        {
            case type_id_t::UInt8:
                return format(v.as<uint8>());
            case type_id_t::Int8:
                return format(v.as<int8>());
            case type_id_t::Int16:
                return format(v.as<int16>());
            case type_id_t::UInt16:
                return format(v.as<uint16>());
            case type_id_t::UInt32:
                return format(v.as<uint32>());
            case type_id_t::Int32:
                return format(v.as<int32>());
            case type_id_t::UInt64:
                return format(v.as<uint64>());
            case type_id_t::Int64:
                return format(v.as<int64>());
            case type_id_t::Float32:
                return format(v.as<float32>());
            case type_id_t::Float64:
                return format(v.as<float64>());
            case type_id_t::Float128:
                return format(v.as<float128>());
            case type_id_t::Complex32:
                return format(v.as<complex32>());
            case type_id_t::Complex64:
                return format(v.as<complex64>());
            case type_id_t::Complex128:
                return format(v.as<complex128>());
            case type_id_t::Bool:
                return format(v.as<bool_t>());
            case type_id_t::EBool:
                return format(v.as<hdf5::datatype::EBool>());
            case type_id_t::String:
                return format(v.as<string>());
            default:
                return "";
        }
    }

    //-------------------------------------------------------------------------
    string format(const value_ref &)
    {
        return "";
    }

//end of namespace
}
