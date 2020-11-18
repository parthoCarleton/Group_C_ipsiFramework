/**
 * @file unitTest_ipsiListen_UT.c
 *
 * Description: To perform Unit Testing on ipsiListen and ipsiClose.
 */

#include "UT_IPSI_UT.hpp"
#include "ipsi.c"
#include "stub_UT.c"
#define DUMMY_FUNCTION_CALLED 100
#define DUMMY_FUNCTION_NOT_CALLED 101

static int callFALG = DUMMY_FUNCTION_NOT_CALLED;

/**
 * Dummy functions
 */
void dummyFunction (){

	ipsiListenFlag = STOP_IPSI_LISTEN;
	callFALG = DUMMY_FUNCTION_CALLED;
}

/**
 * To perform unit testing on ipsiListen when dbus_connection_pop_msg send valid Dbus message to invoke
 * dummyFunction by ipisListen function
 * dumyFunction simulate role of closing dbus connection so that ipsiListen should stop listening for other request after
 * this call.
 * @note The above scenario  will be a multiThreaded scenario
 *
 * Expected Behavior: Should return SUCCESS and callFlag should set to DUMMY_FUNCTION_CALLED
 */
static void test_ipsiListen_PASS(){

	ipsiState = IPSI_GOOD_STATE;
	ipsiRegisterFunction (dummyFunction,"dummy");
	UT_ASSERT(SUCCESS == ipsiListen());
	UT_ASSERT(DUMMY_FUNCTION_CALLED == callFALG);

	ipsiListenFlag = START_IPSI_LISTEN; // Reset
	callFALG = DUMMY_FUNCTION_NOT_CALLED;
}

/**
 * To perform unit testing on ipsiListen when dbus_connection_pop_msg sends Null Message
 *
 * @note: as ipsiListen is a blocking function it was necessary to create internal fault in the
 * program to cover the line of the code, hence this is an unexpected case to occur.
 *
 * ipsiListen continue to listen for valid message from dbus until any internal fault stops ipsiListen to exit
 * and return.
 */
static void test_ipsiListen_NoMSG(){

	ipsiState = IPSI_GOOD_STATE;
	conditionCASE = DBUS_LISTEN_NOMSG_FAULT;
	ipsiRegisterFunction (dummyFunction,"dummy");
	UT_ASSERT(FAILURE == ipsiListen());

}

/**
 * To perform unit testing on ipsiClose if Server calls.
 *
 * @note: ipsiClose should be called by Server application Only to stop listening for any service request
 *
 */
static void test_ipsiListen_ipsiClose(){

	applicationRole = IPSI_SERVER;
	cleanupFlag = IPSI_CLEAN_UP_SET;
	ipsiClose();
	UT_ASSERT(ipsiListenFlag == STOP_IPSI_LISTEN);
}

/**
 * To perform unit testing on ipsiClose if called by other application.
 *
 * @note: ipsiClose should be called by Server application Only to stop listening for any service request
 *
 */
static void test_ipsiListen_ipsiClose_differntApplication(){

	applicationRole = IPSI_CALLER;
	cleanupFlag = IPSI_CLEAN_UP_SET;
	ipsiClose();
	UT_ASSERT(ipsiListenFlag == STOP_IPSI_LISTEN);
}

/**
 * To perform unit testing on ipsiListen , when ipsiConnectionType has set BAD state flag
 */
static void test_ipsiListen_ipsiConnectionType_fail(){
	ipsiState = IPSI_BAD_STATE;
	UT_ASSERT(FAILURE == ipsiListen());
}


/** Unit Testing on ipsiListen and ipsiClose Start Here */
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
