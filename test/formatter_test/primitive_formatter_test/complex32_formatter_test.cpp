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
//  Created on: Feb 11, 2015
//      Authors: Eugen Wintersberger <eugen.wintersberger@desy.de>
//               Jan Kotanski <jan.kotanski@desy.de>
//

#include <boost/test/unit_test.hpp>
#include <pni/types.hpp>
#include <pni/formatters/scalar_format.hpp>

using namespace pni; 
using namespace pni;

BOOST_AUTO_TEST_SUITE(complex32_formatter_test)

    BOOST_AUTO_TEST_CASE(test)
    {
        typedef complex32 input_type;
        string result = format(input_type(1.256987f,3.452907f));
        BOOST_CHECK(result == "+1.256986976e+00+I3.452907085e+00");

        result = format(input_type(1.256987f,-3.452907f));
        BOOST_CHECK(result == "+1.256986976e+00-I3.452907085e+00");

        result = format(input_type(-1.256987f,-3.452907f));
        BOOST_CHECK(result == "-1.256986976e+00-I3.452907085e+00");

        result = format(input_type(-1.256987f,3.452907f));
        BOOST_CHECK(result == "-1.256986976e+00+I3.452907085e+00");

        result = format(input_type(0,3.45f));
        BOOST_CHECK(result == "+0.000000000e+00+I3.450000048e+00");

        result = format(input_type(0,-3.45f));
        BOOST_CHECK(result == "+0.000000000e+00-I3.450000048e+00");
    }

BOOST_AUTO_TEST_SUITE_END()
