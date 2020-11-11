/**
 * @file UT_IPSI_UT.c
 *
 * Description: Header file for unit testing.
 */

#ifndef TEST_UT_IPSI_UT_HPP_
#define TEST_UT_IPSI_UT_HPP_
#include <stdlib.h>
#include <stdio.h>
#define UT_SUCCESS 1
#define UT_FAILURE 0
#define IPSI_NOLOG 1

void printLog(const char *,int,const char *,int);
#define UT_START printf("\n*********************************************************\n"); \
				 printf("**[START] Unit Testing** - [%s]\n",__FILE__); \
				 printf("\n*********************************************************\n");

#define UT_STOP printf("\n*********************************************************\n"); \
				 printf("**[STOP] Unit Testing** - [%s]\n",__FILE__); \
				 printf("\n*********************************************************\n"); \
				 exit(0);

#define UT_ASSERT(cond) if(cond){ printLog\
					(__FILE__, __LINE__, __func__ ,UT_SUCCESS);} \
						else { printLog\
							(__FILE__, __LINE__, __func__ ,UT_FAILURE);}

void printLog(const char *fileName,int lineNumber,const char *funcName,int flag){

	if(UT_SUCCESS == flag)
		printf ("[PASSED] [%s]\n",funcName);
	else{
		printf ("[FAILED] [%s] at lineNo: %d\n",funcName,lineNumber);
		abort();
	}
}

#endif /* TEST_UT_IPSI_UT_HPP_ */
