#ifndef TESTOPLABEL_H
#define TESTOPLABEL_H

#include<cppunit/TestFixture.h>
#include<cppunit/extensions/HelperMacros.h>

void TestToy(void) ;

class TestOPLabel : public CppUnit::TestFixture {
	CPPUNIT_TEST_SUITE(OPLabel) ;
	CPPUNIT_TEST(TestToy) ;
	CPPUNIT_TEST_SUITE_END() ;

	public :
		void setUp(void) {} 		// Not used
		void tearDown(void) {}		// Not used

}


#endif /*TESTOPLABEL_H*/
