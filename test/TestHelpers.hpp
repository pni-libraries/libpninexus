//functions and template functions that should make 
//Test development easier.

#ifndef __TESTHELPERS_HPP__
#define __TESTHELPERS_HPP__

#include <pni/utils/Types.hpp>
using namespace pni::utils;

#include<cppunit/TestFixture.h>
#include<cppunit/extensions/HelperMacros.h>
#include<complex>
#include<string>

template<typename T> void init_values(T &a,T &b)
{
    a = 100;
    b = 0;
}

template<typename T> void init_values(std::complex<T> &a,std::complex<T> &b)
{
    a = std::complex<T>(1.293761,-9.83762);
    b = std::complex<T>(0,0);
}

template<> void init_values(String &a,String &b);

template<typename T> void compare_values(T a,T b)
{
    CPPUNIT_ASSERT(a == b);
}

template<typename T> void compare_values(std::complex<T> a,std::complex<T> b)
{
    compare_values(a.real(),b.real());
    compare_values(a.imag(),b.imag());
}


#endif