//#include <cppunit/TestRunner.h>
//#include <cppunit/TestResult.h>
#include <cppunit/extensions/HelperMacros.h>
#include <iostream>
#include <OPLabel.h>
#include <TestOPLabel.h>

CPPUNIT_TEST_SUITE_REGISTRATION (TestOPLabel) ;

void TestOPLabel::TestToy(void) {
	// It should pass
	CPPUNIT_ASSERT(1 == 1) ;	
	// It should fail
	CPPUNIT_ASSERT(1 == 2) ;
}

class TestOPLabel: public CppUnit::TestCase {
/*
public :
	OPLabelTest(std::string name) : CppUnit::TestCase(name) {}

	void runTest() {
		// It should pass
		CPPUNIT_ASSERT(1 == 1) ;	
		// It should fail
		CPPUNIT_ASSERT(1 == 2) ;
	}
*/

}


int main(){
/*	CppUnit::TestCaller<OPLabelTest> test("toyTest at this time",&OPLabelTest::runTest()) ;
	CppUnit::TestResult result ;
	result.run(&result) ;*/
	std::cout << "Test" << std::endl ;
}

