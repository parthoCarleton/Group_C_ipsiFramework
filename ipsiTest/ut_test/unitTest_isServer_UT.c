/**
 * @file unitTest_isServer_UT.c
 *
 * Description: To perform Unit Testing on is_server .
 */

#include "UT_IPSI_UT.hpp"
#include "ipsi.c"
#include "stub_UT.c"

/**
 * To perform Unit Testing on is_server when connection type is "Server"
 *
 * Expected Behavior: Function should return Success stating the connection type is Server
 */
static void test_isServer_Pass(){

	UT_ASSERT(SUCCESS ==(is_server("Server"))); // Check +ive condition

}

/**
 * To perform Unit Testing on is_server when connection type is not "Server" Type
 *
 * Expected Behavior: Function should return Failure stating the connection type is not Server.
 */
static void test_isServer_Fail(){

	UT_ASSERT(FAILURE == (is_server("ABC"))); // Check -ive condition
}

/**
 * To perform Unit Testing on is_server when connection type is NULL
 *
 * Expected Behavior: Function should return Failure stating the connection type is NULL.
 */
static void test_isServer_NULL(){

	UT_ASSERT(FAILURE == (is_server(NULL)));
}

/** Unit Testing for is_server starts */
int main()
{
	UT_START
	test_isServer_Pass();
	test_isServer_Fail();
	test_isServer_NULL();
	UT_STOP
}
