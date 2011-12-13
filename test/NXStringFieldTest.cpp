/*
 * NXStringFieldTest.cpp
 *
 *  Created on: Dec 5, 2011
 *      Author: Eugen Wintersberger
 */

#include "NXStringFieldTest.hpp"

#include<cppunit/extensions/HelperMacros.h>

#include "NX.hpp"
#include "NXExceptions.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(NXStringFieldTest);

//------------------------------------------------------------------------------
void NXStringFieldTest::setUp(){
	file.setFileName("NXStringFieldTest.h5");
	file.setOverwrite(true);
	file.setReadOnly(false);
	file.create();

	strdata.push_back(String("Hello"));
	strdata.push_back(String("this is a test"));
	strdata.push_back(String("a stupid text"));
}

//------------------------------------------------------------------------------
void NXStringFieldTest::tearDown(){
	file.close();
	strdata.clear();
}

//------------------------------------------------------------------------------
void NXStringFieldTest::testCreation(){
	std::cout<<"NXStringFieldTest::testCreation()-----------------------------";
	std::cout<<std::endl;

	NXStringField field;  //default constructor

	//standard construction
	NXStringField f2 = file.createStringField("text");
	CPPUNIT_ASSERT(f2.isOpen());

	//copy construction
	NXStringField f3(f2);
	CPPUNIT_ASSERT(f2.isOpen());
	CPPUNIT_ASSERT(f3.isOpen());

	//move construction
	NXStringField f4 = std::move(f2);
	CPPUNIT_ASSERT(f4.isOpen());
	CPPUNIT_ASSERT(!f2.isOpen());
}

//------------------------------------------------------------------------------
void NXStringFieldTest::testOpen(){
	std::cout<<"NXStringFieldTest::testOpen()---------------------------------";
	std::cout<<std::endl;

	file.createStringField("text1");
	file.createStringField("text2");

	NXStringField f1 = file.open("text1");
	f1 = file.open("text2");

	file.createNumericField("data",TypeID::UINT32,"cps","numeric test data");
	CPPUNIT_ASSERT_THROW(f1 = std::move(file.open("data")),pni::nx::NXFieldError);
}

//------------------------------------------------------------------------------
void NXStringFieldTest::testAssignment(){
	std::cout<<"NXStringFieldTest::testAssignment()---------------------------";
	std::cout<<std::endl;

	NXStringField f;
	CPPUNIT_ASSERT_NO_THROW(f = file.createStringField("text1"));
	CPPUNIT_ASSERT(f.isOpen());

	NXStringField f2;
	CPPUNIT_ASSERT_NO_THROW(f2 = f);
	CPPUNIT_ASSERT(f2.isOpen());
	CPPUNIT_ASSERT(f.isOpen());

	NXStringField f3;
	CPPUNIT_ASSERT_NO_THROW(f3 = std::move(f));
	CPPUNIT_ASSERT(f3.isOpen());
	CPPUNIT_ASSERT(!f.isOpen());
}

//------------------------------------------------------------------------------
void NXStringFieldTest::testAppend(){
	std::cout<<"NXStringFieldTest::testAppend()-------------------------------";
	std::cout<<std::endl;

	NXStringField field = file.createStringField("text");
#ifdef OLD_CXX
    for(auto iter=strdata.begin();iter!=strdata.end();iter++){
        String s = *iter;
#else
	for(String &s: strdata ){
#endif
		CPPUNIT_ASSERT_NO_THROW(field.append(s));
	}


}


//------------------------------------------------------------------------------
void NXStringFieldTest::testGetIndividual(){
	std::cout<<"NXStringFieldTest::testGetIndividual()------------------------";
	std::cout<<std::endl;

	testAppend();
	NXStringField field = file.open("text");

	for(UInt64 i=0;i<strdata.size();i++){
		String s = field.get(i);
	}
}

//------------------------------------------------------------------------------
void NXStringFieldTest::testGetAll(){
	std::cout<<"NXStringFieldTest::testGetAll()-------------------------------";
	std::cout<<std::endl;
	NXStringField write = file.createStringField("text");

	char sep = '\n';
	String total;
#ifdef OLD_CXX
    for(auto iter=strdata.begin();iter!=strdata.end();iter++){
        String s = *iter;
#else
	for(String &s: strdata){
#endif
		total += s+sep;
		write.append(s);
	}
	//remove trailing "\n"
	total = String(total,0,total.size()-1);


	NXStringField read = file.open("text");
	String text;
	text = read.get(sep);
	CPPUNIT_ASSERT(total == text);

}

//------------------------------------------------------------------------------
void NXStringFieldTest::testSet(){
	std::cout<<"NXStringFieldTest::testSet()----------------------------------";
	std::cout<<std::endl;

	NXStringField field = file.createStringField("text");

	//write data
	CPPUNIT_ASSERT_NO_THROW(field.set(2,strdata[2]));
	CPPUNIT_ASSERT_NO_THROW(field.set(1,strdata[1]));
	CPPUNIT_ASSERT_NO_THROW(field.set(0,strdata[0]));

	//read back data
	CPPUNIT_ASSERT(field.get(0ul) == strdata[0]);
	CPPUNIT_ASSERT(field.get(1ul) == strdata[1]);
	CPPUNIT_ASSERT(field.get(2ul) == strdata[2]);


}

//------------------------------------------------------------------------------
void NXStringFieldTest::testStreamRead(){
	std::cout<<"NXStringFieldTest::testStreamRead()---------------------------";
	std::cout<<std::endl;

	NXStringField field = file.createStringField("text");
	field<<strdata[0];
	field<<strdata[1];
	field<<strdata[2];

	//read back
	//read back data
	CPPUNIT_ASSERT(field.get(0ul) == strdata[0]);
	CPPUNIT_ASSERT(field.get(1ul) == strdata[1]);
	CPPUNIT_ASSERT(field.get(2ul) == strdata[2]);


}

//------------------------------------------------------------------------------
void NXStringFieldTest::testStreamWrite(){
	std::cout<<"NXStringFieldTest::testStreamWrite()--------------------------";
	std::cout<<std::endl;

	NXStringField field = file.createStringField("text");

	//write data
	CPPUNIT_ASSERT_NO_THROW(field.set(2,strdata[2]));
	CPPUNIT_ASSERT_NO_THROW(field.set(1,strdata[1]));
	CPPUNIT_ASSERT_NO_THROW(field.set(0,strdata[0]));

	String s;
	field>>s; CPPUNIT_ASSERT(s==strdata[0]);
	field>>s; CPPUNIT_ASSERT(s==strdata[1]);
	field>>s; CPPUNIT_ASSERT(s==strdata[2]);

}
