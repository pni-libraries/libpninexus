#pragma once
#include<vector>
#include<pni/core/types.hpp>

using namespace pni::core;

//-----------------------------------------------------------------------------
/*!
\brief create scalar test data

Template function creates a scalar test value. This function is used to test
scalar data IO. Specialized functions are available for Bool and String types.
\tparam T data type requested
\return data value
*/
template<typename T> T create_scalar_data()
{
    return T(1);
}

template<> string create_scalar_data<string>();
template<> bool create_scalar_data<bool>();

//-----------------------------------------------------------------------------
/*!
\brief create array test data

Creates array test data. The data is stored in a std::vector container. 
Data can be used for array data IO. Spezialied functions are available for Bool
and String types.
\tparam T requested data type
\param n number of elements to create
\return container with data values
*/
template<typename T> std::vector<T> create_array_data(size_t n)
{
    std::vector<T> v(n);

    std::fill(v.begin(),v.end(),T(1));
    return v;
}

template<> std::vector<string> create_array_data(size_t n);
template<> std::vector<bool> create_array_data(size_t n);

