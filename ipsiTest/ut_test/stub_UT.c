/**
 * @file stub_UT.c
 *
 * Description: Dbus stub function used for Unit Testing
 */

#ifndef STUB_ND
#define STUB_ND

#include <dbus/dbus.h>
#define DBUS_GET_CASE1 10
#define DBUS_GET_CASE2 11
#define DBUS_GET_CASE3 12
#define DBUS_REQUESTNAME_CASE1 13
#define DBUS_REQUESTNAME_CASE2 14
#define DBUS_REQUESTNAME_CASE3 15
#define DBUS_CONNECTION_SEND_FAIL 16
#define DBUS_LISTEN_NOMSG_FAULT 17

volatile int conditionCASE = DBUS_GET_CASE1;

struct DBusConnection{};
struct DBusMessage {};
struct DBusConnection dummyConn;
struct DBusMessage dummyMSG;

dbus_bool_t dbus_error_is_set (const DBusError *error) {

	return error->name != NULL;
}

void 	dbus_error_free (DBusError *error) {
}

int dbus_bus_request_name (DBusConnection *connection, const char *name, unsigned int flags, DBusError *error){

	if (DBUS_REQUESTNAME_CASE2 == conditionCASE){
		error->name = "FAIL";
		return DBUS_REQUEST_NAME_REPLY_PRIMARY_OWNER;
	}
	else if (DBUS_REQUESTNAME_CASE3 == conditionCASE){
		error->name = NULL;
		return DBUS_REQUEST_NAME_REPLY_ALREADY_OWNER;
	}
	else
		error->name = NULL;
	return DBUS_REQUEST_NAME_REPLY_PRIMARY_OWNER;
}

DBusConnection * 	dbus_bus_get (DBusBusType type, DBusError *error) {

	if (DBUS_GET_CASE2 == conditionCASE)
	{
		error->name = "fail";
		return &dummyConn;
	}
	else if(DBUS_GET_CASE3 == conditionCASE)
	{
		error->name = NULL;
		return NULL;
	}
	else //case 1
		error->name = NULL;
	return &dummyConn;


}

DBusMessage*
dbus_message_new_method_call (const char *destination,
		const char *path,
		const char *iface,
		const char *method) {}
dbus_bool_t 	dbus_connection_send (DBusConnection *connection, DBusMessage *message, dbus_uint32_t *serial){

	if (DBUS_CONNECTION_SEND_FAIL == conditionCASE)
		return FALSE;
	return TRUE;

}
dbus_bool_t 	dbus_connection_read_write (DBusConnection *connection, int timeout_milliseconds){}
DBusMessage * 	dbus_connection_pop_message (DBusConnection *connection){

	if (DBUS_LISTEN_NOMSG_FAULT == conditionCASE){
		ipsi_listen_flag = DBUS_LISTEN_NOMSG_FAULT;
		return NULL;
	}

	return &dummyMSG;
}
dbus_bool_t 	dbus_message_is_method_call (DBusMessage *message, const char *iface, const char *method){

	return TRUE;
}
void dbus_message_unref	(	DBusMessage * 	message	)	{}
void dbus_connection_close (DBusConnection * connection){};
#endif
