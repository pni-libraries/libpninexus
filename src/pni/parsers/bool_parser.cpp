//
// (c) Copyright 2017 DESY
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
// Created on: Jun 7, 2017
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
//

#include <pni/parsers/bool_parser.hpp>

namespace pni{

    parser<pni::bool_t>::parser():
        _true_regex("^T(rue|RUE)|true|1$"),
        _false_regex("^F(alse|ALSE)|false|0$")
    {}


    parser<pni::bool_t>::parser(const pni::string &true_regex,
                                      const pni::string &false_regex):
        _true_regex(true_regex),
        _false_regex(false_regex)
    {}

    parser<pni::bool_t>::result_type
    parser<pni::bool_t>::operator()(const pni::string &input) const
    {
        using namespace pni;

        if(boost::regex_match(input,_true_regex))
            return true;
        else if(boost::regex_match(input,_false_regex))
            return false;
        else
        {
            std::stringstream ss;
            ss<<"Input ["<<input<<"] cannot be converted to a boolean value!";
            throw parser_error(EXCEPTION_RECORD,ss.str());
        }
    }

}
