/**
 * @file File Name: ipsi.c
 *
 * This software embodies materials and concepts which are entitled for the
 * course:
 * ELG 6179: ADV TOPICS IN SOFTWARE ENGINEER. (Software Development in C) [University of Ottawa]
 * SYSC5709F: Software Development with C [Carleton University]
 *
 * Description: This is the core of IPSI-Framework library
 * that allows multiple applications to connect and perform service requests.
 * This framework abstracts the complex low-level system’s communication protocol
 * by revealing a simplified service interface that can be used by the
 * applications to invoke service requests to other applications.
 *
 * External API by IPSI-Framework:
 * int ipsi_connection_type(char *app_name,char *connection_name);
 * int ipsi_register_function(void (*fun_ptr)(), char *method_name);
 * int ipsi_method_call(char *app_name,char* method_name);
 * int ipsi_listen();
 * void ipsi_close();
 *
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
#define IPSI_GOOD_STATE	796			/** To state that IPSI library has no flaws in its operation */
#define IPSI_BAD_STATE	795			/** To state that IPSI library has encountered flaws in its operation */

#ifdef IPSI_NOLOG					/** Deactivate IPSI library Logging */
#define IPSI_LOG(...)
#else
#define IPSI_LOG(...) printf(__VA_ARGS__) /** Activate IPSI library Logging */
#endif

#include "ipsi.hpp"

/* Global Variable Declaration */
/*********************************/

/** Dbus structured message */
DBusMessage *msg;
/** Dbus Connection Name */
DBusConnection *conn;
/** Dbus Object representing an exception */
DBusError err;

/** IPSI Internal State **/
int ipsi_state = IPSI_BAD_STATE;

/** IPSI common return VALUE **/
int ret = FAILURE;

/** IPSI tracks the content of data in the method_name_array and fun_ptr_array */
int index_counter = 0;

/** IPSI flag to stop DBUS connection */
int cleanup_flag = IPSI_CLEAN_UP_CLEAR;

/** IPSI flag to identify that the application has started to listen service request. */
int ipsi_listen_flag = START_IPSI_LISTEN;

/** Static interface path in Dbus object. */
static char iface[100] = "test.method.Type";

/** Store Built Connection name as per Dbus specification */
static char connection_name[100] = { };

/** Track the unique Name of the registered callback function */
char method_name_array[NUMBER_OF_METHOD][MAX_STRING_SIZE];

/** Track the registered callback function */
void (*fun_ptr_array[NUMBER_OF_METHOD]) ();

/** IPSI flag to identify application role throughout its life cycle. */
static int application_role = IPSI_NONE;
/*********************************/

/**
 * This is an utility function, use to check if the application
 * requesting is a "Server" or not
 *
 * @param[in] connection_type : should be "Server"
 *
 * @return SUCCESS: The application is "Server" Type
 * @return FAILURE: The application is not a "Server" Type
 */
static int is_server (char *connection_type){

	if (NULL == connection_type)
		return FAILURE;
	char server_type[10] = "Server";
	if (!(strcmp (connection_type, server_type)))
	{
		IPSI_LOG ("[IPSI] Connection Type is Server\n");
		return SUCCESS;
	}
	return FAILURE;
}

/**
 * This is an utility function, use to check if the application
 * requesting is a "Caller" or not.
 *
 * @param[in] connection_type : should be "Caller"
 *
 * @return SUCCESS: The application is "Caller" Type
 * @return FAILURE: The application is not a "Caller" Type
 */
static int is_caller (char *connection_type){

	if (NULL == connection_type)
		return FAILURE;

	char caller_type[10] = "Caller";
	if (!(strcmp (connection_type, caller_type)))
	{
		IPSI_LOG ("[IPSI] Connection Type is Caller\n");
		return SUCCESS;
	}
	return FAILURE;
}

/**
 * \brief This is an External API use to register callback functions for the services offered by the Service Provider.
 *
 * Service Provider should register its callback functions with a unique name. This unique service name can be used
 * by the Service requester to invoke service request by using ipsi_method_call().
 *
 * @param[in] fun_ptr():  callback function that offers services
 *
 * @param[in] method_name: Unique name of the callback function that Service Provider
 * application should provide to identify its services request
 *
 * @return SUCCESS: The function call was able to register the function with IPSI library
 * @return FAILURE: The function call was unable to register the function with IPSI library
 **/
int ipsi_register_function (void (*fun_ptr) (), char *method_name){

	if (NULL == method_name || NULL == fun_ptr)
	{
		IPSI_LOG ("[IPSI] Invalid arguments, FAILED to update DataBase");
		return FAILURE;
	}
	strcpy (method_name_array[index_counter], method_name);
	fun_ptr_array[index_counter] = fun_ptr;
	index_counter++;
	return SUCCESS;
}


/**
 * This is an utility function, use to build Connection name for
 * low-level communication protocol.[Dbus]
 *
 * @param[in] app_name : Application unique name.
 *
 * @return SUCCESS: Connection name was built as per DBUS specification .
 * @return FAILURE: Unable to build the connection name as per DBUS specification.
 */
static int build_connection_name (char *app_name){

	char app_name_URL[100] = "test.method.";
	if (NULL == app_name)
	{
		IPSI_LOG ("[IPSI] Empty app_name");
		return FAILURE;
	}
	int len = strlen (app_name);
	strncat (app_name_URL, app_name, len);
	strcpy (connection_name, app_name_URL);
	IPSI_LOG ("[IPSI] connection_name:%s\n", connection_name);
	return SUCCESS;
}

/**
 * This is an utility function, that helps in binding
 * connection name with connection_type that severs as an input to
 * low-level communication protocol.[Dbus]
 *
 * @param[in] app_name:  Unique Name of the application
 *
 * @param[in] connection_type: Specify the role of the application either "Caller" or "Server"
 *
 * @return SUCCESS: Binding connection name with connection type was successful as per DBUS specification .
 * @return FAILURE: Unable to bind connection name with connection type as per DBUS specification
 */
static int init_connection_name (char *app_name, char *connection_type){

	if (is_server (connection_type))
	{
		if (SUCCESS == build_connection_name (app_name))
		{
			application_role = IPSI_SERVER;
			return SUCCESS;
		}
		else
			return FAILURE;
	}
	else if (is_caller (connection_type))
	{
		if (SUCCESS == build_connection_name (app_name))
		{
			application_role = IPSI_CALLER;
			return SUCCESS;
		}
		else
			return FAILURE;
	}
	return FAILURE;
}

/**
 * \brief This is an External API use by the application to register with IPSI library and specify its
 * role as "Caller"/"Server" along with a unique name
 *
 * Service requester Application should register itself as "Caller" and with a unique name, this will allow the
 * application to invoke service request to desired service provider.
 * Service provider Application should register itself as "Server" and with a unique name, this will allow the application
 * to server any service request and allow service requester application to invoke services with the unique name.
 *
 * @param[in] app_name:  Unique Name of the application
 *
 * @param[in] connection_type: Specify the role of the application either "Caller" or "Server"
 *
 * @return SUCCESS: The application as successfully registered itself with IPSI library
 * @return FAILURE: The application was unable to register with IPSI library , an appropriate error message will be shown on console
 **/
int ipsi_connection_type (char *app_name, char *connection_type){

	if (!(init_connection_name (app_name, connection_type)))
	{
		IPSI_LOG ("[IPSI] Invalid Connection Type, Exiting...\n");
		return FAILURE;
	}
	
	conn = dbus_bus_get (DBUS_BUS_SESSION, &err);
	if (dbus_error_is_set (&err))
	{
		IPSI_LOG ("[IPSI] Connection Error (%s)\n", err.message);
		dbus_error_free (&err);
		ipsi_state = IPSI_BAD_STATE;
		return FAILURE;
	}
	if (NULL == conn)
	{
		IPSI_LOG ("[IPSI] Connection Null\n");
		ipsi_state = IPSI_BAD_STATE;
		return FAILURE;
	}

	ret =
			dbus_bus_request_name (conn, connection_name,
					DBUS_NAME_FLAG_REPLACE_EXISTING, &err);
	if (dbus_error_is_set (&err))
	{
		IPSI_LOG ("[IPSI] Name Error (%s)\n", err.message);
		dbus_error_free (&err);
		ipsi_state = IPSI_BAD_STATE;
		return FAILURE;
	}
	if (DBUS_REQUEST_NAME_REPLY_PRIMARY_OWNER != ret)
	{
		IPSI_LOG ("[IPSI] Not Primary Owner (%d)\n", ret);
		ipsi_state = IPSI_BAD_STATE;
		return FAILURE;
	}
	ipsi_state = IPSI_GOOD_STATE;
	return SUCCESS;

}

/**
 * This is an utility function, that helps to obtain Dbus object URL.
 *
 * \note should be used after build_connection_name() only.
 *
 * @param[in] app_name_URL: Dbus bus name that the application want to invoke the request
 * @param[out] buffer_char:  Will contain a string that mention the Dbus object path name
 */
static int convert_request_to_dbus_URL_format (char *app_name_URL, char *buffer_char){

	char src[7] = "Object";
	buffer_char[0] = '/';
	int ibuffer_charCount = 1;
	int japp_name = 0;
	while (app_name_URL[japp_name] != '\0')
	{
		buffer_char[ibuffer_charCount] = app_name_URL[japp_name];
		if ('.' == app_name_URL[japp_name])
		{
			buffer_char[ibuffer_charCount] = '/';
		}
		if (12 == japp_name)
		{
			buffer_char[ibuffer_charCount] = '\0';
			break;
		}
		japp_name++;
		ibuffer_charCount++;
	}
	strncat (buffer_char, src, 7);
	return SUCCESS;
}

/**
 * \brief This is an External API That will allow Service Requester to place service
 * request.
 *
 * Service Requester should specify the name of the Service provider and the
 * name of the Service that is provided by the Service provider application.
 *
 * @param[in] app_name: Name of the Service Provider Application which
 * is providing Services that Service Requester Application is interested in.
 *
 * @param[in] method_name: Name of the Service that Service Provider
 * application is providing to its requester application
 *
 * @return  SUCCESS: The function call was able to place request
 * @return  FAILURE: The function call was not able to place the request.
 **/
int ipsi_method_call (char *app_name, char *method_name){
	char app_name_URL[100] = { };
	char buffer_char[100] = { };

	if (IPSI_BAD_STATE == ipsi_state)
	{
		IPSI_LOG
		("[IPSI] ipsi_method_call() failed because ipsi_connection_type() was not successful executed \n");
		return FAILURE;
	}

	if (FAILURE == build_connection_name (app_name))
	{
		IPSI_LOG ("[IPSI] Invalid Service Provider Name \n");
		return FAILURE;
	}
	strcpy (app_name_URL, connection_name);
	convert_request_to_dbus_URL_format (app_name_URL, buffer_char);

	IPSI_LOG ("[IPSI] TEST Modify:%s\n", buffer_char);
	msg = dbus_message_new_method_call (app_name_URL,	// target for the method call
			buffer_char,	// object to call on
			"test.method.Type",	// interface to call on
			method_name);

	IPSI_LOG ("[IPSI] app_name_URL:%s objURL:%s method_name:%s \n",
			app_name_URL, buffer_char, method_name);
	if (!dbus_connection_send (conn, msg, NULL))
	{				// -1 is default timeout
		IPSI_LOG ("[IPSI] Out Of Memory!\n");
		return FAILURE;
	}
	return SUCCESS;
}

/**
 * \brief This is an External API that will allow Service Provider to listen for service request
 *
 * Service Provider will listen for service requests that are requested by the Service Requester Application.
 * If the service request is valid it will invoke the service that has been registered with the
 * IPSI library with ipsi_register_function() by the Service provider application.
 *
 *\note This function will block the current thread on which it was called until service invocation was performed
 * and then it will resume to block the current thread for listening any other service request.
 *
 * \note To stop listening for any service request , call ipsi_close() API this will free the current thread on which
 * ipsi_listen was operating and should exit with SUCCESS.
 *
 * @return  SUCCESS: It was able to exit Successfully
 * @return  FAILURE: It was not able to exit Successfully as it was not able to able to exit from system's IPC properly
 **/
int ipsi_listen (){
	if (IPSI_BAD_STATE == ipsi_state)
	{
		IPSI_LOG
		("[IPSI] ipsi_listen() failed because ipsi_connection_type() was not successful executed \n");
		return FAILURE;
	}

	IPSI_LOG ("[IPSI] Listening for method calls\n");
	while (!ipsi_listen_flag)
	{
		// non blocking read of the next available message
		dbus_connection_read_write (conn, 0);
		msg = dbus_connection_pop_message (conn);

		// loop again if we haven't got a message
		if (NULL == msg)
		{
			continue;
		}

		for (int i = 0; i < index_counter; i++)
		{
			if (dbus_message_is_method_call (msg, iface, method_name_array[i]))
			{
				IPSI_LOG ("[IPSI]Listen method_name:%s\n",
						method_name_array[i]);
				fun_ptr_array[i] ();
				break;
			}
		}
		// free the message*/
		dbus_message_unref (msg);
	}

	if (STOP_IPSI_LISTEN == ipsi_listen_flag)
	{

		cleanup_flag = IPSI_CLEAN_UP_SET;
		IPSI_LOG
		("[IPSI]Listen was STOPPED as per request from ipsi_close()\n");
	}
	else
	{
		IPSI_LOG ("[IPSI]Listen was STOPPED due to internal Fault\n");
		return FAILURE;
	}

	return SUCCESS;
}

/**
 * This is an External API that will allow Service Provider application to stop listening to service request.
 **/
void ipsi_close (){

	if (IPSI_SERVER == application_role)
	{
		IPSI_LOG ("[IPSI] ****Shutting Down***\n");
		ipsi_listen_flag = STOP_IPSI_LISTEN;
		while (IPSI_CLEAN_UP_SET != cleanup_flag);
		//dbus_connection_close(conn); //TODO , do not attempt to close shared connection. it is safe to exit in Dbus.
		IPSI_LOG ("[IPSI] ****!EXITED!***\n");
	}
	else
		IPSI_LOG ("[IPSI] You are not a Server, Invalid Request\n");

}
