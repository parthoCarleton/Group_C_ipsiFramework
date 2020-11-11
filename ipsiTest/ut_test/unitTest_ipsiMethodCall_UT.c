/**
 * @file unitTest_ipsiMethodCall_UT.c
 *
 * Description: To perform Unit Testing on ipsiMethodCall.
 */

#include "UT_IPSI_UT.hpp"
#include "ipsi.c"
#include "stub_UT.c"

/**
 * To perform unit testing on ipsiMethodCall when valid Server application name and
 * service request nameis passed.
 *
 * Expected Behavior: the function return SUCCESS as it was able to place request on
 * dbus session bus, dbus_connection_send was able to send the request on dbus channel
 */
static void test_ipsiMethoCall_PASS(){

	UT_ASSERT(SUCCESS == ipsiMethodCall("Dummy","Play"));
}

/**
 * To perform unit testing on ipsiMethodCall when valid Server application name and
 * service request name is passed but dbus_connection_send was unable to send the request.
 *
 * Expected Behavior: the function return Failure as it was not able to place request on
 * dbus session bus and dbus_connection_send fails to send request.
 */
static void test_ipsiMethoCall_SENDFAIL(){
	conditionCASE = DBUS_CONNECTION_SEND_FAIL;
	UT_ASSERT(FAILURE == ipsiMethodCall("Dummy","Play"));
}

/**
 * To perform unit testing on ipsiMethodCall when NULL was passed as Server application.
 *
 * Expected Behavior: the function return Failure as it failed to create valid connection name
 * in order to send request on dbus channel.
 */
static void test_ipsiMethoCall_appName_NULL(){

	UT_ASSERT(FAILURE == ipsiMethodCall(NULL,"Play"));
}

/** Unit Testing on ipsiMethodCall Start Here */
int main()
{
	UT_START
	test_ipsiMethoCall_PASS();
	test_ipsiMethoCall_SENDFAIL();
	test_ipsiMethoCall_appName_NULL();
	UT_STOP

}
