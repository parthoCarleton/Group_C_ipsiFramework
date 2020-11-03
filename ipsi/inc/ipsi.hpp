
/**
 * @file File Name: ipsi.h
 *
 * This software embodies materials and concepts which are entitled for the
 * course:
 * ELG 6179: ADV TOPICS IN SOFTWARE ENGINEER. (Software Development in C) [University of Ottawa]
 * SYSC5709F: Software Development with C [Carleton University]
 *
 * Description: This is the core of IPSI-Framework library (Header File)
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
 * Design and Developed by:
 * Partho Ghosal -
 * Ashwini Upasani -
 * Deepti -
 * Rajdeep -
 */

#ifndef IPSI_HPP_
#define IPSI_HPP_
#include <stdio.h>
#include <dbus/dbus.h>
#include <stdbool.h>
#include <string.h>

/**
 * @brief This is an External API use by the application to register with IPSI library and specify its
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
 * @return SUCCESS: The application as successfully registered itself with IPSI library
 * @return FAILURE: The application was unable to register with IPSI library , an appropriate error message will be shown on console
 **/
int ipsiConnectionType(char *appName,char *connectionName);

/**
 * @brief This is an External API use to register callback functions for the services offered by the Service Provider.
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
int ipsiRegisterFunction(void (*funPtr)(), char *methodName);

/**
 * @brief This is an External API That will allow Service Requester to place service
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
int ipsiMethodCall(char *appName,char* methodName);

/**
 * @brief This is an External API that will allow Service Provider to listen for service request
 *
 * Service Provider will listen for service request that are requested by the Service Requester Application.
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
int ipsiListen();

/**
 * This is an External API that will allow Service Provider application to stop listening to service request.
 **/
void ipsiClose();

#endif /* IPSI_HPP_ */
