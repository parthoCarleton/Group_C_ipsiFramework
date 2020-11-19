/**
 * @file unitTest_ipsiMethodCall_UT.c
 *
 * Description: To perform Unit Testing on ipsi_method_call.
 */

#include "UT_IPSI_UT.hpp"
#include "ipsi.c"
#include "stub_UT.c"

/**
 * To perform unit testing on ipsi_method_call when valid Server application name and
 * service request nameis passed.
 *
 * Expected Behavior: the function return SUCCESS as it was able to place request on
 * dbus session bus, dbus_connection_send was able to send the request on dbus channel
 */
static void test_ipsiMethodCall_PASS(){

	ipsi_state = IPSI_GOOD_STATE; // ipsiConnection was executed successful
	UT_ASSERT(SUCCESS == ipsi_method_call("Dummy","Play"));
}

/**
 * To perform unit testing on ipsi_method_call when valid Server application name and
 * service request name is passed but dbus_connection_send was unable to send the request.
 *
 * Expected Behavior: the function return Failure as it was not able to place request on
 * dbus session bus and dbus_connection_send fails to send request.
 */
static void test_ipsiMethodCall_SENDFAIL(){
	ipsi_state = IPSI_GOOD_STATE; // ipsiConnection was executed successful
	conditionCASE = DBUS_CONNECTION_SEND_FAIL;
	UT_ASSERT(FAILURE == ipsi_method_call("Dummy","Play"));
}

/**
 * To perform unit testing on ipsi_method_call when NULL was passed as Server application.
 *
 * Expected Behavior: the function return Failure as it failed to create valid connection name
 * in order to send request on dbus channel.
 */
static void test_ipsiMethodCall_appName_NULL(){

	ipsi_state = IPSI_GOOD_STATE; // ipsiConnection was executed successful
	UT_ASSERT(FAILURE == ipsi_method_call(NULL,"Play"));
}

/*
 * To perform unit Testing on ipsi_method_call when ipsiConnectionType has set BAD state flag
 */
static void test_ipsiMethodCall_ipsiCOnectionType_Fail(){
	ipsi_state = IPSI_BAD_STATE; // ipsiConnection was executed successful
	UT_ASSERT(FAILURE == ipsi_method_call("Server","Play"));
}

/** Unit Testing on ipsi_method_call Start Here */
int main()
{
	UT_START
	test_ipsiMethodCall_PASS();
	test_ipsiMethodCall_SENDFAIL();
	test_ipsiMethodCall_appName_NULL();
	test_ipsiMethodCall_ipsiCOnectionType_Fail();
	UT_STOP

}
