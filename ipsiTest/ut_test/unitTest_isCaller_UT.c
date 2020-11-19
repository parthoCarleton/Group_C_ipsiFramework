/**
 * @file unitTest_isCaller_UT.c
 *
 * Description: To perform Unit Testing on is_caller .
 */

#include "UT_IPSI_UT.hpp"
#include "ipsi.c"
#include "stub_UT.c"

/**
 * To perform unit testing on is_caller when the connection type is "Caller"
 *
 * Expected Behavior:  function should return Success indicating that
 * the connection type was "Caller"
 */
static void test_isCaller_Pass(){

	UT_ASSERT(SUCCESS == (is_caller("Caller"))); // Check +ive condition

}

/**
 * To perform unit testing on is_caller when the connection type as not "Caller" type
 *
 * Expected Behavior:  function should return FALIURE indicating that
 * the connection type was not "Caller"
 */
static void test_isCaller_Fail(){

	UT_ASSERT(FAILURE == (is_caller("abc"))); // Check -ive condition

}

/**
 * To perform unit testing on is_caller when the connection type is NULL
 *
 * Expected Behavior: function should return FALIURE indicating that
 * the connection type was not valid and NULL.
 */
static void test_isCaller_NULL(){

	UT_ASSERT(FAILURE == (is_caller(NULL)));
}

/** Unit Testing for is_caller Starts */
int main()
{
	UT_START
	test_isCaller_Pass();
	test_isCaller_Fail();
	test_isCaller_NULL();
	UT_STOP
}
