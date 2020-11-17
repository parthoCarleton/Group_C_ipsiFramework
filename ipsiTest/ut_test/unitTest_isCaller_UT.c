/**
 * @file unitTest_isCaller_UT.c
 *
 * Description: To perform Unit Testing on isCaller .
 */

#include "UT_IPSI_UT.hpp"
#include "ipsi.c"
#include "stub_UT.c"

/**
 * To perform unit testing on isCaller when the connection type is "Caller"
 *
 * Expected Behavior:  function should return Success indicating that
 * the connection type was "Caller"
 */
static void test_isCaller_Pass(){

	UT_ASSERT(SUCCESS == (isCaller("Caller"))); // Check +ive condition

}

/**
 * To perform unit testing on isCaller when the connection type as not "Caller" type
 *
 * Expected Behavior:  function should return FALIURE indicating that
 * the connection type was not "Caller"
 */
static void test_isCaller_Fail(){

	UT_ASSERT(FAILURE == (isCaller("abc"))); // Check -ive condition

}

/**
 * To perform unit testing on isCaller when the connection type is NULL
 *
 * Expected Behavior: function should return FALIURE indicating that
 * the connection type was not valid and NULL.
 */
static void test_isCaller_NULL(){

	UT_ASSERT(FAILURE == (isCaller(NULL)));
}

/** Unit Testing for isCaller Starts */
int main()
{
	UT_START
	test_isCaller_Pass();
	test_isCaller_Fail();
	test_isCaller_NULL();
	UT_STOP
}
