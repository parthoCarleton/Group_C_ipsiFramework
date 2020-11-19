/**
 * @file unitTest_ipsiRegisterFunction_UT.c
 *
 * Description: To perform Unit Testing on ipsi_register_function.
 */

#include "UT_IPSI_UT.hpp"
#include "ipsi.c"
#include "stub_UT.c"

/** Dummy Function */
void dummyRegisterFunction(){}

/*
 * To perform unit Testing on ipsi_register_function , when valid function and its unique name was provided.
 *
 *  Expected Behavior : Should return SUCCESS indicating that the callback function and its
 *  associated unique name was registered with IPSILibrary.
 */
static void test_ipsiRegisterFunction_PASS(){

	UT_ASSERT(SUCCESS == ipsi_register_function(dummyRegisterFunction,"PLAY"))
	UT_ASSERT(! (strcmp (method_name_array[0],"PLAY")));
}

/*
 * To perform unit Testing on ipsi_register_function, when valid function and NULL unique name was provided.
 *
 *  Expected Behavior : Should return FAILURE indicating that unique name for service function was not
 *  valid.
 */
static void test_ipsiRegisterFunction_methodNameNULL(){

	UT_ASSERT(FAILURE == ipsi_register_function(dummyRegisterFunction,NULL))

}

/*
 * To perform unit Testing on ipsi_register_function, when NULL function pointer and unique name was provided.
 *
 *  Expected Behavior : Should return FAILURE indicating that function pointer passed was not valid.
 */
static void test_ipsiRegisterFunction_funPtrNULL(){

	UT_ASSERT(FAILURE == ipsi_register_function(NULL,"dummy"));

}

/*
 * To perform unit Testing on ipsi_register_function, when NULL function pointer and NULL name was provided.
 *
 *  Expected Behavior : Should return FAILURE indicating that invalid arguments was provided.
 */
static void test_ipsiRegisterFunction_NULL(){

	UT_ASSERT(FAILURE == ipsi_register_function(NULL,NULL));

}

/** Unit Testing of ipsiRegisterFunction starts */
int main()
{
	UT_START
	test_ipsiRegisterFunction_PASS();
	test_ipsiRegisterFunction_methodNameNULL();
	test_ipsiRegisterFunction_funPtrNULL();
	test_ipsiRegisterFunction_NULL();
	UT_STOP
}
