/**
 * @file unitTest_ipsiListen_UT.c
 *
 * Description: To perform Unit Testing on ipsi_listen and ipsi_close.
 */

#include "UT_IPSI_UT.hpp"
#include "ipsi.c"
#include "stub_UT.c"
#define DUMMY_FUNCTION_CALLED 100
#define DUMMY_FUNCTION_NOT_CALLED 101

static int call_flag = DUMMY_FUNCTION_NOT_CALLED;

/**
 * Dummy functions
 */
void dummyFunction (){

	ipsi_listen_flag = STOP_IPSI_LISTEN;
	call_flag = DUMMY_FUNCTION_CALLED;
}

/**
 * To perform unit testing on ipsi_listen when dbus_connection_pop_msg send valid Dbus message to invoke
 * dummyFunction by ipisListen function
 * dumyFunction simulate role of closing dbus connection so that ipsi_listen should stop listening for other request after
 * this call.
 * @note The above scenario  will be a multiThreaded scenario
 *
 * Expected Behavior: Should return SUCCESS and callFlag should set to DUMMY_FUNCTION_CALLED
 */
static void test_ipsiListen_PASS(){

	ipsi_state = IPSI_GOOD_STATE;
	ipsi_register_function (dummyFunction,"dummy");
	UT_ASSERT(SUCCESS == ipsi_listen());
	UT_ASSERT(DUMMY_FUNCTION_CALLED == call_flag);

	ipsi_listen_flag = START_IPSI_LISTEN; // Reset
	call_flag = DUMMY_FUNCTION_NOT_CALLED;
}

/**
 * To perform unit testing on ipsi_listen when dbus_connection_pop_msg sends Null Message
 *
 * @note: as ipsi_listen is a blocking function it was necessary to create internal fault in the
 * program to cover the line of the code, hence this is an unexpected case to occur.
 *
 * ipsi_listen continue to listen for valid message from dbus until any internal fault stops ipsiListen to exit
 * and return.
 */
static void test_ipsiListen_NoMSG(){

	ipsi_state = IPSI_GOOD_STATE;
	conditionCASE = DBUS_LISTEN_NOMSG_FAULT;
	ipsi_register_function (dummyFunction,"dummy");
	UT_ASSERT(FAILURE == ipsi_listen());

}

/**
 * To perform unit testing on ipsi_close if Server calls.
 *
 * @note: ipsi_close should be called by Server application Only to stop listening for any service request
 *
 */
static void test_ipsiListen_ipsiClose(){

	application_role = IPSI_SERVER;
	cleanup_flag = IPSI_CLEAN_UP_SET;
	ipsi_close();
	UT_ASSERT(ipsi_listen_flag == STOP_IPSI_LISTEN);
}

/**
 * To perform unit testing on ipsi_close if called by other application.
 *
 * @note: ipsi_close should be called by Server application Only to stop listening for any service request
 *
 */
static void test_ipsiListen_ipsiClose_differntApplication(){

	application_role = IPSI_CALLER;
	cleanup_flag = IPSI_CLEAN_UP_SET;
	ipsi_close();
	UT_ASSERT(ipsi_listen_flag == STOP_IPSI_LISTEN);
}

/**
 * To perform unit testing on ipsi_listen , when ipsiConnectionType has set BAD state flag
 */
static void test_ipsiListen_ipsiConnectionType_fail(){
	ipsi_state = IPSI_BAD_STATE;
	UT_ASSERT(FAILURE == ipsi_listen());
}


/** Unit Testing on ipsi_listen and ipsi_close Start Here */
int main()
{
	UT_START
	test_ipsiListen_PASS();
	test_ipsiListen_NoMSG();
	test_ipsiListen_ipsiClose();
	test_ipsiListen_ipsiClose_differntApplication();
	test_ipsiListen_ipsiConnectionType_fail();
	UT_STOP

}
