/**
 * @file unitTest_isServer_UT.c
 *
 * Description: To perform Unit Testing on isServer .
 */

#include "UT_IPSI_UT.hpp"
#include "ipsi.c"
#include "stub_UT.c"

/**
 * To perform Unit Testing on isServer when connection type is "Server"
 *
 * Expected Behavior: Function should return Success stating the connection type is Server
 */
static void test_isServer_Pass(){

	UT_ASSERT(SUCCESS ==(isServer("Server"))); // Check +ive condition

}

/**
 * To perform Unit Testing on isServer when connection type is not "Server" Type
 *
 * Expected Behavior: Function should return Failure stating the connection type is not Server.
 */
static void test_isServer_Fail(){

	UT_ASSERT(FAILURE == (isServer("ABC"))); // Check -ive condition
}

/**
 * To perform Unit Testing on isServer when connection type is NULL
 *
 * Expected Behavior: Function should return Failure stating the connection type is NULL.
 */
static void test_isServer_NULL(){

	UT_ASSERT(FAILURE == (isServer(NULL)));
}

/** Unit Testing for isServer starts */
int main()
{
	UT_START
	test_isServer_Pass();
	test_isServer_Fail();
	test_isServer_NULL();
}
