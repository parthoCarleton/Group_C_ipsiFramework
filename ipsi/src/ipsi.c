/**
 * @file File Name: ipsi.c
 *
 * This software embodies materials and concepts which are entitled for the
 * course:
 * ELG 6179: ADV TOPICS IN SOFTWARE ENGINEER. (Software Development in C) [University of Ottawa]
 * SYSC5709F: Software Development with C [Carleton University]
 *
 * Description: This is the core of IPSI-Framework library
 * that allows multiple applications to connect and perform a service request.
 * This framework abstracts the complex low-level system’s communication protocol
 * by revealing a simplified service interface that can be used by the
 * applications to invoke service requests to other applications.
 *
 * External API by IPSI-Framework:
 * int ipsiConnectionType(char *appName,char *connectionName);
 * int ipsiRegisterFunction(void (*funPtr)(), char *methodName);
 * int ipsiMethodCall(char *appName,char* methodName);
 * int ipsiListen();
 * void ipsiClose();
 *
 * Designed and Developed by:
 * Partho Ghosal -
 * Ashwini Upasani -
 * Deepti -
 * Rajdeep Virdi -
 */

#define SUCCESS 1					/** IPSI library indicating Success to perform certain task */
#define FAILURE 0					/** IPSI library indicating Failure to perform certain task */
#define NUMBER_OF_METHOD 100		/** Max number of services that can be registered with IPSI */
#define MAX_STRING_SIZE 10000		/** Max Size of character to be used for representing application or Service Name */
#define START_IPSI_LISTEN 0			/** Start listening to Service Request */
#define STOP_IPSI_LISTEN 1			/** Stop listening to any Service Request */
#define IPSI_CLEAN_UP_CLEAR 2		/** Do not close Dbus connection with IPSI */
#define IPSI_CLEAN_UP_SET 3			/** Needs to close Dbus connection */
#define IPSI_NONE 4   				/** No Application has been registered with IPSI */
#define IPSI_SERVER 5 				/** To identify the application registered with IPSI is a "Server" */
#define IPSI_CALLER 6 				/** To identify the application registered with IPSI is a "Caller" */

#ifdef IPSI_NOLOG					/** Deactivate IPSI library Logging */
#define IPSI_LOG(...)
#else
#define IPSI_LOG(...) printf(__VA_ARGS__) /** Activate IPSI library Logging */
#endif

#include "ipsi.hpp"

/* Global Variable Declaration */
/*********************************/

/** Dbus structured message */
DBusMessage* msg;
/** Dbus Connection Name */
DBusConnection* conn;
/** Dbus Object representing an exception */
DBusError err;

/** IPSI common return VALUE **/
int ret = FAILURE ;

/** IPSI tracks the content of data in the methodNameArry and funPtrArry */
int indexCounter=0;

/** IPSI flag to stop DBUS connection */
int cleanupFlag= IPSI_CLEAN_UP_CLEAR;

/** IPSI flag to identify that the application has started to listen service request. */
int ipsiListenFlag = START_IPSI_LISTEN;

/** Static interface path in Dbus object. */
static char iface[100] = "test.method.Type";

/** Store Built Connection name as per Dbus specification */
static char connectionName [100]= {};

/** Track the unique Name of the registered callback function */
char methodNameArry[NUMBER_OF_METHOD][MAX_STRING_SIZE];

/** Track the registered callback function */
void (*funPtrArry[NUMBER_OF_METHOD]) ();

/** IPSI flag to identify application role throughout its life cycle. */
static int applicationRole= IPSI_NONE;
/*********************************/

/**
 * This is an utility function, used to check if the application
 * requesting is a "Server" or not
 *
 * @param[in] connectionType : should be "Server"
 *
 * @return SUCCESS: The application is "Server" Type
 * @return FAILURE: The application is not a "Server" Type
 */
static int isServer(char *connectionType){

	return FAILURE;
}

/**
 * This is an utility function, used to check if the application
 * requesting is a "Caller" or not.
 *
 * @param[in] connectionType : should be "Caller"
 *
 * @return SUCCESS: The application is "Caller" Type
 * @return FAILURE: The application is not a "Caller" Type
 */
static int isCaller(char *connectionType){

	return FAILURE;
}

/**
 * \brief This is an External API used to register callback functions for the services offered by the Service Provider.
 *
 * Service Provider should register its callback functions with a unique name. This unique service name can be used
 * by the Service requester to invoke service request by using ipsiMethodCall().
 *
 * @param[in] funPtr():  callback function that offers services
 *
 * @param[in] methodName: Unique name of the callback function that Service Provider
 * application should provide to identify its services request
 *
 * @return SUCCESS: The function call was able to register the function with IPSI library
 * @return FAILURE: The function call was unable to register the function with IPSI library
 **/
int ipsiRegisterFunction(void (*funPtr)(), char *methodName){
	if( NULL == methodName || NULL == funPtr){
		IPSI_LOG ("[IPSI] Invalid arguments, FAILED to update DataBase");
		return FAILURE;
	}
	strcpy(methodNameArry[indexCounter],methodName);
	funPtrArry[indexCounter] = funPtr;
	indexCounter++;
	return SUCCESS;

}


/**
 * This is an utility function, used to build Connection name for
 * low-level communication protocol [Dbus].
 *
 * @param[in] appName : Application unique name.
 *
 * @return SUCCESS: Connection name was built as per DBUS specification .
 * @return FAILURE: not able to build the connection name as per DBUS specification.
 */
static int buildConnectionName(char *appName)
{
	char appNameURL [100] = "test.method.";
	if(NULL == appName){
		IPSI_LOG("[IPSI] Empty appName");
		return FAILURE;
	}
	int len= strlen(appName);
	strncat(appNameURL, appName, len);
	strcpy(connectionName,appNameURL);
	IPSI_LOG("[IPSI] ConnectionName:%s\n",connectionName);
	return SUCCESS;
}

/**
 * This is an utility function, that helps in binding
 * connection name with connectionType that severs as an input to
 * low-level communication protocol [Dbus].
 *
 * @param[in] appName:  Unique Name of the application
 *
 * @param[in] connectionType: Specify the role of the application as either "Caller" or "Server"
 *
 * @return SUCCESS: Binding connection name with connection type was successful as per DBUS specification .
 * @return FAILURE: Cannot be able to bind connection name with connection type as per DBUS specification
 */
static int initConnectionName(char *appName,char *connectionType){

	return FAILURE;
}

/**
 * \brief This is an External API used by the application to register with IPSI library and specify its
 * role as "Caller"/"Server" along with a unique name
 *
 * Service requester Application should register itself as "Caller" and with a unique name, this will allow the
 * application to invoke service request to desired service provider.
 * Service provider Application should register itself as "Server" and with a unique name, this will allow the application
 * to server any service request and allow service requester application to invoke services with the unique name.
 *
 * @param[in] appName:  Unique Name of the application
 *
 * @param[in] connectionType: Specify the role of the application either "Caller" or "Server"
 *
 * @return SUCCESS: The application successfully registered itself with IPSI library
 * @return FAILURE: The application was unable to register with IPSI library , an appropriate error message will be shown on console
 **/
int ipsiConnectionType(char *appName, char *connectionType){

	if(!(initConnectionName(appName,connectionType))){
		IPSI_LOG("[IPSI] Invalid Connection Type, Exiting...\n");
		return FAILURE;
	}

	conn = dbus_bus_get(DBUS_BUS_SESSION, &err);
	if (dbus_error_is_set(&err)) {
		IPSI_LOG("[IPSI] Connection Error (%s)\n", err.message);
		dbus_error_free(&err);
		return FAILURE;
	}
	if (NULL == conn) {
		IPSI_LOG("[IPSI] Connection Null\n");
		return FAILURE;
	}

	ret = dbus_bus_request_name(conn, connectionName, DBUS_NAME_FLAG_REPLACE_EXISTING , &err);
	if (dbus_error_is_set(&err)) {
		IPSI_LOG("[IPSI] Name Error (%s)\n", err.message);
		dbus_error_free(&err);
		return FAILURE;
	}

	if (DBUS_REQUEST_NAME_REPLY_PRIMARY_OWNER != ret) {
		IPSI_LOG("[IPSI] Not Primary Owner (%d)\n", ret);
		return FAILURE;
	}

	return SUCCESS;

}

/**
 * This is an utility function, that helps to obtain Dbus object URL.
 *
 * \note should be used after buildConnectionName() only.
 *
 * @param[in] appNameURL: Dbus bus name that the application want to invoke the request
 * @param[out] buffChar:  Will contain a string that mention the Dbus object path name
 */
static int convertReqToDbusURLFormat(char *appNameURL,char *buffChar){


	char src[7] = "Object";
	buffChar[0] = '/';
	int iBuffCharCount=1;
	int jAppName =0;
	while(appNameURL[jAppName]!='\0')
	{
		buffChar[iBuffCharCount] = appNameURL[jAppName];
		if('.'==appNameURL[jAppName])
		{
			buffChar[iBuffCharCount]='/';
		}
		if(12 == jAppName)
		{
			buffChar[iBuffCharCount]='\0';
			break;
		}
		jAppName++;
		iBuffCharCount++;
	}
	strncat(buffChar, src, 7);
	return SUCCESS;
}

/**
 * \brief This is an External API That will allow Service Requester to place service
 * request.
 *
 * Service Requester should specify the name of the Service provider and the
 * name of the Service that is provided by the Service provider application.
 *
 * @param[in] appName: Name of the Service Provider Application which
 * is providing Services that Service Requester Application is interested in.
 *
 * @param[in] methodName: Name of the Service that Service Provider
 * application is providing to its requester application
 *
 * @return  SUCCESS: The function call was able to place request
 * @return  FAILURE: The function call was not able to place the request.
 **/
int ipsiMethodCall(char *appName,char* methodName)
{
	char appNameURL [100] = {};
	char buffChar [100] = {};
	if (FAILURE == buildConnectionName(appName)){
		IPSI_LOG ("[IPSI] Invalid Service Provider Name \n");
		return FAILURE;
	}
	strcpy(appNameURL,connectionName);
	convertReqToDbusURLFormat(appNameURL,buffChar);

	IPSI_LOG("[IPSI] TEST Modify:%s\n",buffChar);
	msg = dbus_message_new_method_call(appNameURL, // target for the method call
			buffChar, // object to call on
			"test.method.Type", // interface to call on
			methodName);

	IPSI_LOG("[IPSI] appNameURL:%s objURL:%s methodName:%s \n",appNameURL,buffChar,methodName);
	if (!dbus_connection_send (conn, msg, NULL)) { // -1 is default timeout
		IPSI_LOG("[IPSI] Out Of Memory!\n");
		return FAILURE;
	}
	return SUCCESS;
}

/**
 * \brief This is an External API that will allow Service Provider to listen for service request
 *
 * Service Provider will listen for service request that is requested by the Service Requester Application.
 * If the service request is valid it will invoke the service that has been registered with the
 * IPSI library with ipsiRegisterFunction() by the Service provider application.
 *
 *\note This function will block the current thread on which it was called until service invocation was performed
 * and then it will resume to block the current thread for listening any other service request.
 *
 * \note To stop listening for any service request , call ipsiClose() API this will free the current thread on which
 * ipsiListen was operating and should exit with SUCCESS.
 *
 * @return  SUCCESS: It was able to exit Successfully
 * @return  FAILURE: It was not able to exit Successfully as it was not able to able to exit from system's IPC properly
 **/
int ipsiListen(){

	IPSI_LOG("[IPSI] Listening for method calls\n");
	while (!ipsiListenFlag) {
		// non blocking read of the next available message
		dbus_connection_read_write(conn, 0);
		msg = dbus_connection_pop_message(conn);

		// loop again if we haven't got a message
		if (NULL == msg) {
			continue;
		}

		for(int i =0 ; i<indexCounter ; i++)
		{
			if (dbus_message_is_method_call(msg, iface,methodNameArry[i] ))
			{
				IPSI_LOG("[IPSI]Listen methodName:%s\n",methodNameArry[i]);
				funPtrArry[i]();
				break;
			}
		}
		// free the message*/
		dbus_message_unref(msg);
	}

	if (STOP_IPSI_LISTEN == ipsiListenFlag){

		cleanupFlag = IPSI_CLEAN_UP_SET;
		IPSI_LOG("[IPSI]Listen was STOPPED as per request from ipsiClose()\n");
	}
	else
	{
		IPSI_LOG("[IPSI]Listen was STOPPED due to internal Fault\n");
		return FAILURE;
	}

	return SUCCESS;
}

/**
 * This is an External API that will allow Service Provider application to stop listening to service request.
 **/
void ipsiClose(){

	if(IPSI_SERVER == applicationRole){
		IPSI_LOG ("[IPSI] ****Shutting Down***\n");
		ipsiListenFlag = STOP_IPSI_LISTEN;
		while (IPSI_CLEAN_UP_SET != cleanupFlag);
		//dbus_connection_close(conn); //TODO , do not attempt to close shared connection. it is safe to exit in Dbus.
		IPSI_LOG ("[IPSI] ****!EXITED!***\n");
	}
	else
		IPSI_LOG ("[IPSI] You are not a Server, Invalid Request\n");

}

