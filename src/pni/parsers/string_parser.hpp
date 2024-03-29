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
// Created on: Jun 8, 2017
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#pragma once

#include <pni/parsers/parser.hpp>

namespace pni{

    //!
    //! \ingroup parser_classes
    //! \brief parsing strings
    //!
    //! This specialization of the parser template parses strings form user
    //! input. Virtually this class does nothing it just passes the string
    //! provided by the user right through.
    //! 
    template<>
    class PNINEXUS_EXPORT parser<pni::string>
    {
        public:
            using result_type = pni::string;

            result_type operator()(const pni::string &data) const;
    };
}
