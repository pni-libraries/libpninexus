/*
 * NXGroupTest.cpp
 *
 *  Created on: Aug 4, 2011
 *      Author: eugen
 */

#include "NXGroupTest.hpp"

#include<cppunit/extensions/HelperMacros.h>

#include "NX.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(NXGroupTest);

void NXGroupTest::setUp(){
	_fname = "test.group.h5";
	Index i;
	_f.close();
	_f.setFileName(_fname);
	_f.setOverwrite(true);
	CPPUNIT_ASSERT_NO_THROW(_f.create());


	_write_str_attr = "hello world";
	_write_scalar_attr = 100;
	_shape = Shape();
	_shape.rank(2);
	_shape.dim(0,3);
	_shape.dim(1,3);

	_write_array_attr = Int16Array();
	i.rank(_shape.rank());
	_write_array_attr.shape(_shape);
	_write_array_attr.allocate();
	i[0] = 0; i[1] = 0; _write_array_attr(i) = 1;
	i[0] = 0; i[1] = 1; _write_array_attr(i) = 2;
	i[0] = 0; i[1] = 2; _write_array_attr(i) = 3;
	i[0] = 1; i[1] = 0; _write_array_attr(i) = 4;
	i[0] = 1; i[1] = 1; _write_array_attr(i) = 5;
	i[0] = 1; i[1] = 2; _write_array_attr(i) = 6;
	i[0] = 2; i[1] = 0; _write_array_attr(i) = 7;
	i[0] = 2; i[1] = 1; _write_array_attr(i) = 8;
	i[0] = 2; i[1] = 2; _write_array_attr(i) = 9;

	_write_cmplx_scalar = Complex64(1,-2);

	_read_array_attr = Int16Array();

}

void NXGroupTest::tearDown(){
	//close the file
	std::cerr<<"0000000000000000000 CLOSING FILE 00000000000000000000000!"<<std::endl;
	_f.close();
}

void NXGroupTest::testCreation(){
	NXGroup g;

	g = _f.createGroup("/hello/world");
	g.close();
	g = _f.createGroup("/directory_1");


	//test copy constructor
	NXGroup g1(g);
	CPPUNIT_ASSERT(g1.isOpen());
	CPPUNIT_ASSERT(g.isOpen());
	CPPUNIT_ASSERT(g1.getName() == g.getName());

	//test move constructor
	NXGroup g2 = std::move(g1);
	CPPUNIT_ASSERT(!g1.isOpen());
	CPPUNIT_ASSERT(g2.isOpen());

}

void NXGroupTest::testOpen(){
	NXGroup g1,g2;

	g1 = _f.createGroup("/directory1/data");

	g2 = _f.open("/directory1");
	NXGroup g = g2.open("data");
	NXGroup g3;
	g3 = g2.open("data");

	NXGroup g4 = _f.open("/directory1/data");

	CPPUNIT_ASSERT_THROW(_f.open("directory2"),pni::nx::NXGroupError);
	CPPUNIT_ASSERT_NO_THROW(_f.open("directory1/data"));

	g1.close();
	g2.close();

}

void NXGroupTest::testAttributes(){
	NXGroup g;

	g = _f.createGroup("/Hello/world1");

	//write attribute data
	g.setAttribute("StringAttribute",_write_str_attr);
	g.setAttribute("FloatScalarAttribute",_write_scalar_attr);
	g.setAttribute("IndexOfRefraction",_write_cmplx_scalar);
	g.setAttribute("ArrayAttribute",_write_array_attr);


	//read data
	g.getAttribute("StringAttribute",_read_str_attr);
	g.getAttribute("FloatScalarAttribute",_read_scalar_attr);
	g.getAttribute("ArrayAttribute",_read_array_attr);
	g.getAttribute("IndexOfRefraction",_read_cmplx_scalar);

	//check if values are the same
	CPPUNIT_ASSERT(_write_str_attr == _read_str_attr);
	CPPUNIT_ASSERT(_read_scalar_attr == _read_scalar_attr);
	CPPUNIT_ASSERT(_read_array_attr == _write_array_attr);
	CPPUNIT_ASSERT(_write_cmplx_scalar == _read_cmplx_scalar);
}

void NXGroupTest::testAttributeExceptions(){
	NXGroup g;

	g = _f.createGroup("/hello/world");

	//write attribute data
	g.setAttribute("StringAttribute",_write_str_attr);
	g.setAttribute("FloatScalarAttribute",_write_scalar_attr);
	g.setAttribute("IndexOfRefraction",_write_cmplx_scalar);
	g.setAttribute("ArrayAttribute",_write_array_attr);

	//trying to overwrite attributes
	CPPUNIT_ASSERT_NO_THROW(g.setAttribute("StringAttribute",_write_str_attr));
	CPPUNIT_ASSERT_NO_THROW(g.setAttribute("FloatScalarAttribute",_write_scalar_attr));
	CPPUNIT_ASSERT_NO_THROW(g.setAttribute("IndexOfRefraction",_write_cmplx_scalar));
	CPPUNIT_ASSERT_NO_THROW(g.setAttribute("ArrayAttribute",_write_array_attr));

	//trying to read attributes that do not exist
	CPPUNIT_ASSERT_THROW(g.getAttribute("StringAttribute_not",_read_str_attr),H5AttributeError);
	CPPUNIT_ASSERT_THROW(g.getAttribute("FloatScalarAttribute_not",_read_scalar_attr),H5AttributeError);
	CPPUNIT_ASSERT_THROW(g.getAttribute("ArrayAttribute_not",_read_array_attr),H5AttributeError);
	CPPUNIT_ASSERT_THROW(g.getAttribute("IndexOfRefraction_not",_read_cmplx_scalar),H5AttributeError);

	g.close();
}

void NXGroupTest::testInternalLinks(){
	NXGroup g1,g2;
	NXField f,fr;

	//create a group and some data
	CPPUNIT_ASSERT_NO_THROW(g1 = _f.createGroup("/group1"));
	CPPUNIT_ASSERT_NO_THROW(g2 = _f.createGroup("/group2/detector/data"));

	CPPUNIT_ASSERT(g1.getPath() == "/group1");
	CPPUNIT_ASSERT(g1.getBase() == "/");
	CPPUNIT_ASSERT(g1.getName() == "group1");

	CPPUNIT_ASSERT(g2.getPath() == "/group2/detector/data");
	CPPUNIT_ASSERT(g2.getBase() == "/group2/detector/");
	CPPUNIT_ASSERT(g2.getName() == "data");

	CPPUNIT_ASSERT_NO_THROW(g2.createLink(g1));
	CPPUNIT_ASSERT_NO_THROW(g2.createLink(g1,"detdata"));

	//link now g1 into g2
	CPPUNIT_ASSERT_NO_THROW(g1.createLink("/group2/detector/g1_link"));

	g1 = _f.open("/group2/detector/data");
	g1.createLink("/mydata");

}

void NXGroupTest::testExistence(){
	NXGroup g1,g2;
	NXField f;

	g1 = _f.createGroup("/scan_1/instrument");
	g1 = _f.createGroup("/scan_2/instrument/detector");

	g1 = _f.open("scan_1");
	CPPUNIT_ASSERT(g1.exists("instrument"));
	CPPUNIT_ASSERT(g1.exists("/scan_2"));
	CPPUNIT_ASSERT(!g1.exists("/instrument"));
	g2 = _f.open("scan_2");
	CPPUNIT_ASSERT(g2.exists("instrument/detector/"));
	CPPUNIT_ASSERT(!g2.exists("/instrument/detector/data"));

	CPPUNIT_ASSERT(_f.exists("scan_1"));
	CPPUNIT_ASSERT(_f.exists("/scan_1/instrument"));
	CPPUNIT_ASSERT(_f.exists("scan_2/instrument/detector"));
}

void NXGroupTest::testRemove(){
	NXGroup g1;
	NXField f;
}

void NXGroupTest::testAssignment(){
	NXGroup g1,g2;

	CPPUNIT_ASSERT_NO_THROW(g1 = _f.createGroup("test1"));
	CPPUNIT_ASSERT_NO_THROW(g2 = g1);
	CPPUNIT_ASSERT(g1.isOpen());
	CPPUNIT_ASSERT(g2.isOpen());

	NXGroup g3;
	CPPUNIT_ASSERT_NO_THROW(g3 = std::move(g2));
	CPPUNIT_ASSERT(g3.isOpen());
	CPPUNIT_ASSERT(!g2.isOpen());
}

