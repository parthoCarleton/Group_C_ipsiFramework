/**
 * @file unitTest_ipsiRegisterFunction_UT.c
 *
 * Description: To perform Unit Testing on ipsiRegisterFunction.
 */

#include "UT_IPSI_UT.hpp"
#include "ipsi.c"
#include "stub_UT.c"

/** Dummy Function */
void dummyRegisterFunction(){}

/*
 * To perform unit Testing on ipsiRegisterfunction , when valid function and its unique name was provided.
 *
 *  Expected Behavior : Should return SUCCESS indicating that the callback function and its
 *  associated unique name was registered with IPSILibrary.
 */
static void test_ipsiRegisterFunction_PASS(){

	UT_ASSERT(SUCCESS == ipsiRegisterFunction(dummyRegisterFunction,"PLAY"))
	UT_ASSERT(! (strcmp (methodNameArry[0],"PLAY")));
}

/*
 * To perform unit Testing on ipsiRegisterfunction, when valid function and NULL unique name was provided.
 *
 *  Expected Behavior : Should return FAILURE indicating that unique name for service function was not
 *  valid.
 */
static void test_ipsiRegisterFunction_methodNameNULL(){

	UT_ASSERT(FAILURE == ipsiRegisterFunction(dummyRegisterFunction,NULL))

}

/*
 * To perform unit Testing on ipsiRegisterfunction, when NULL function pointer and unique name was provided.
 *
 *  Expected Behavior : Should return FAILURE indicating that function pointer passed was not valid.
 */
static void test_ipsiRegisterFunction_funPtrNULL(){

	UT_ASSERT(FAILURE == ipsiRegisterFunction(NULL,"dummy"));

}

/*
 * To perform unit Testing on ipsiRegisterfunction, when NULL function pointer and NULL name was provided.
 *
 *  Expected Behavior : Should return FAILURE indicating that invalid arguments was provided.
 */
static void test_ipsiRegisterFunction_NULL(){

	UT_ASSERT(FAILURE == ipsiRegisterFunction(NULL,NULL));

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
