/**
 * @file unitTest_ipsiConnectionType_UT.c
 *
 * Description: To perform Unit Testing on ipsiConnectionType.
 */

#include "UT_IPSI_UT.hpp"
#include "ipsi.c"
#include "stub_UT.c"


/**
 * To perform Unit test on ipsiConnectionType that accept Unique name and
 * connection type as "Caller"
 *
 * Expected Behavior : should return SUCCESS stating that the application
 * has been registered successfully with IPSI library as Caller
 */
static void test_ipcConnectionType_CALLER() {
	UT_ASSERT (SUCCESS == ipsiConnectionType("demo","Caller"));
	UT_ASSERT (IPSI_CALLER == applicationRole);

}

/**
 * To perform Unit test on ipsiConnectionType that accept Unique name and
 * connection type as "Server"
 *
 * Expected Behavior : should return SUCCESS stating that the application
 * has been registered successfully with IPSI library as Server
 */
static void test_ipcConnectionType_SERVER() {
	UT_ASSERT (SUCCESS == ipsiConnectionType("demo","Server"));
	UT_ASSERT (IPSI_SERVER == applicationRole);

}

/**
 * To perform Unit test on ipsiConnectionType while passing Unique name as NULL
 * and connection type as "Server"
 *
 * Expected Behavior : should return Failure
 */
static void test_ipcConnectionType_emptyAPPname_Server (){
	UT_ASSERT (FAILURE == ipsiConnectionType(NULL,"Server"));
}

/**
 * To perform Unit test on ipsiConnectionType while passing Unique name  as NULL
 * and connection type as "Caller"
 *
 * Expected Behavior : should return Failure
 */
static void test_ipcConnectionType_emptyAPPname_Caller (){
	UT_ASSERT (FAILURE == ipsiConnectionType(NULL,"Caller"));
}

/**
 * To perform Unit test on ipsiConnectionType when dbus_bus_request_name return
 * Successful by setting an exception which makes dbus_error_is_set to return true.
 *
 * Expected Behavior : should return Failure, indicating Dbus connection error
 */
static void test_ipcConnectionType_DBUS_GET_CASE2() {
	conditionCASE = DBUS_GET_CASE2;
	UT_ASSERT (FAILURE == ipsiConnectionType("demo","Caller"));
}

/**
 * To perform Unit test on ipsiConnectionType when dbus_bus_request_name failed to create
 * DBusConnection and return NULL but no exception was thrown.
 *
 * Expected Behavior : should return Failure, indicating Dbus bus connection cannot be established.
 */
static void test_ipcConnectionType_DBUS_GET_CASE3() {
	conditionCASE = DBUS_GET_CASE3;
	UT_ASSERT (FAILURE == ipsiConnectionType("demo","Caller"));
}

/**
 * To perform Unit test on ipsiConnectionType when dbus_bus_request_name return
 * Successful by setting an exception which makes dbus_error_is_set to return true.
 *
 * Expected Behavior : should return Failure, indicating Dbus NAME error.
 */
static void test_ipcConnectionType_DBUS_REQUESTNAME_CASE2() {
	conditionCASE = DBUS_REQUESTNAME_CASE2;
	UT_ASSERT (FAILURE == ipsiConnectionType("demo","Caller"));
}

/**
 * To perform Unit test on ipsiConnectionType when dbus_bus_request_name return by stating that
 * the connection name that was requested is not a Primary owner of the dbus communication bus.Also
 * no exception was set by dbus_bus_request_name
 *
 * Expected Behavior : should return Failure, indicating requested connection name is not a primary owner.
 */
static void test_ipcConnectionType_DBUS_REQUESTNAME_CASE3() {
	conditionCASE = DBUS_REQUESTNAME_CASE3;
	UT_ASSERT (FAILURE == ipsiConnectionType("demo","Caller"));
}

/**
 * To perform Unit test on ipsiConnectionType when it has been passed with wrong connection type.
 *
 * Expected Behavior : should return Failure, indicating connection type is wrong.
 */
static void test_ipcConnectionType_connectionTypeNotValid() {

	UT_ASSERT (FAILURE == ipsiConnectionType("demo","ABS"));
}

/** Unit Testing on ipsiConnectionType Start Here */
int main()
{
	UT_START
	test_ipcConnectionType_CALLER();
	test_ipcConnectionType_SERVER();
	test_ipcConnectionType_emptyAPPname_Server();
	test_ipcConnectionType_emptyAPPname_Caller();
	test_ipcConnectionType_DBUS_GET_CASE2();
	test_ipcConnectionType_DBUS_GET_CASE3();
	test_ipcConnectionType_DBUS_REQUESTNAME_CASE2();
	test_ipcConnectionType_DBUS_REQUESTNAME_CASE3();
	test_ipcConnectionType_connectionTypeNotValid();
	UT_STOP
}
