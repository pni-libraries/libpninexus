
#include "scalar_attribute_test_complex32.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(scalar_attribute_test_complex32);

//-----------------------------------------------------------------------------
void scalar_attribute_test_complex32::setUp() 
{ 
    file = h5::nxfile::create_file("scalar_attribute_test_complex32.nxs",
                                    true);
    h5::nxgroup root = file.root();
    group = root.create_group("test");
}

//-----------------------------------------------------------------------------
void scalar_attribute_test_complex32::tearDown() 
{ 
    close(group);
    file.close();
}

//-----------------------------------------------------------------------------
void scalar_attribute_test_complex32::test_inquery()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    root = xml::create_from_file("scalar_attribute_complex32.xml");
    child = root.get_child("group.attribute");

    CPPUNIT_ASSERT(xml::attribute::size(child)==1);
    CPPUNIT_ASSERT(xml::attribute::rank(child)==0);
    CPPUNIT_ASSERT(xml::attribute::type_id(child) == type_id_t::COMPLEX32);
}

//-----------------------------------------------------------------------------
void scalar_attribute_test_complex32::test_create_object()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    root = xml::create_from_file("scalar_attribute_complex32.xml");
    child = root.get_child("group.attribute");

    //attach the attribute to the group
    h5::nxattribute attr = xml::attribute::object_from_xml(group,child);

    CPPUNIT_ASSERT(attr.size() == 1);
    CPPUNIT_ASSERT(attr.rank() == 1);
    CPPUNIT_ASSERT(attr.type_id() == type_id_t::COMPLEX32);
}
