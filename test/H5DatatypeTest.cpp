#include "H5DatatypeTest.hpp"


CPPUNIT_TEST_SUITE_REGISTRATION(H5DatatypeTest);


void H5DatatypeTest::setUp(){
}

void H5DatatypeTest::tearDown(){
}

void H5DatatypeTest::test_creation(){
    std::cout<<"void NXDatatypeTest::test_creation()-------------------------";
    std::cout<<std::endl;
    H5Datatype t1;

    //per default no type is created
    CPPUNIT_ASSERT(!t1.is_valid());

    H5Datatype t2(TypeID::UINT8);
    CPPUNIT_ASSERT(t2.is_valid());

    //create a datatype using a type and the factory method
    H5Datatype t3 = H5Datatype::create<Float32>();
    
    
    //copy constructor
    H5Datatype t4 = t2;
    CPPUNIT_ASSERT(t4.is_valid());
    CPPUNIT_ASSERT(t2.is_valid());
    CPPUNIT_ASSERT(t2.type_id() == t4.type_id());

    //move constructor
    H5Datatype t5 = std::move(t2);
    CPPUNIT_ASSERT(t5.is_valid());
    CPPUNIT_ASSERT(!t2.is_valid());
    CPPUNIT_ASSERT(t5.type_id() == TypeID::UINT8);
    

}

void H5DatatypeTest::test_assignment(){
    std::cout<<"void H5Datatype::test_assignment()---------------------------";
    std::cout<<std::endl;

    H5Datatype t1(TypeID::FLOAT32);
    CPPUNIT_ASSERT(t1.is_valid());
    H5Datatype t2;
    CPPUNIT_ASSERT(!t2.is_valid());

    //testing copy assignment
    t2 = t1;
    CPPUNIT_ASSERT(t2.is_valid());
    CPPUNIT_ASSERT(t1.is_valid());
    CPPUNIT_ASSERT(t1.type_id() == t2.type_id());

    
    H5Datatype t3;
    CPPUNIT_ASSERT(!t3.is_valid());
    
    t3 = std::move(t2);
    CPPUNIT_ASSERT(t3.is_valid());
    CPPUNIT_ASSERT(!t2.is_valid());
    CPPUNIT_ASSERT(t3.type_id() == t1.type_id());

}

void H5DatatypeTest::test_inquery(){
    H5Datatype type;

    type = H5Datatype(TypeID::UINT8);
    CPPUNIT_ASSERT(type.type_id() == TypeID::UINT8);
    type = H5Datatype(TypeID::INT8);
    CPPUNIT_ASSERT(type.type_id() == TypeID::INT8);
    
    type = H5Datatype(TypeID::INT16);
    CPPUNIT_ASSERT(type.type_id() == TypeID::INT16);
    type = H5Datatype(TypeID::UINT16);
    CPPUNIT_ASSERT(type.type_id() == TypeID::UINT16);
    
    type = H5Datatype(TypeID::INT32);
    CPPUNIT_ASSERT(type.type_id() == TypeID::INT32);
    type = H5Datatype(TypeID::UINT32);
    CPPUNIT_ASSERT(type.type_id() == TypeID::UINT32);
    
    type = H5Datatype(TypeID::INT64);
    CPPUNIT_ASSERT(type.type_id() == TypeID::INT64);
    type = H5Datatype(TypeID::UINT64);
    CPPUNIT_ASSERT(type.type_id() == TypeID::UINT64);
    
    type = H5Datatype(TypeID::FLOAT32);
    CPPUNIT_ASSERT(type.type_id() == TypeID::FLOAT32);
    
    type = H5Datatype(TypeID::FLOAT64);
    CPPUNIT_ASSERT(type.type_id() == TypeID::FLOAT64);
    
    type = H5Datatype(TypeID::FLOAT128);
    CPPUNIT_ASSERT(type.type_id() == TypeID::FLOAT128);
    
    type = H5Datatype(TypeID::COMPLEX32);
    CPPUNIT_ASSERT(type.type_id() == TypeID::COMPLEX32);
    
    type = H5Datatype(TypeID::COMPLEX64);
    CPPUNIT_ASSERT(type.type_id() == TypeID::COMPLEX64);
    
    type = H5Datatype(TypeID::COMPLEX128);
    CPPUNIT_ASSERT(type.type_id() == TypeID::COMPLEX128);

    type = H5Datatype(TypeID::STRING);
    CPPUNIT_ASSERT(type.type_id() == TypeID::STRING);

    type = H5Datatype(TypeID::BINARY);
    CPPUNIT_ASSERT(type.type_id() == TypeID::BINARY);

}

void H5DatatypeTest::test_comparison(){
    std::cout<<"void H5DatatypeTest::test_comparison()------------------------";
    std::cout<<std::endl;
    H5Datatype t1(TypeID::FLOAT32);
    H5Datatype t2(TypeID::INT32);

    CPPUNIT_ASSERT(t1 != t2);
    CPPUNIT_ASSERT(!(t1 == t2));

    t2 = H5Datatype(TypeID::FLOAT32);
    CPPUNIT_ASSERT(!(t1 != t2));
    CPPUNIT_ASSERT(t1 == t2);
}