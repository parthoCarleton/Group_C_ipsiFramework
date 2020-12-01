/**
 * @file File Name: controllerApp.hpp (Header file)
 *
 * This software embodies materials and concepts which are entitled for the
 * course:
 * ELG 6179: ADV TOPICS IN SOFTWARE ENGINEER. (Software Development in C) [University of Ottawa]
 * SYSC5709F: Software Development with C [Carleton University]
 *
 * Description: This Application is a Demo Application intended to show the
 * capabilities of IPSI library for Inter-Process communication.
 * This Application (a.k.a Service Requester Application) has the ability to Control the
 * rendering of Video graphics that are rendered by other specialize application
 * capable to render Graphics on Console.
 *
 * @note: Can be used as a reference guide for using IPSI interface.
 *
 */

#ifndef IPSIFRAMEWORK_DEMO_CONTROLLER_INC_CONTROLLERAPP_HPP_
#define IPSIFRAMEWORK_DEMO_CONTROLLER_INC_CONTROLLERAPP_HPP_

#include<iostream>
#include<stdlib.h>
#include<string.h>
#include <climits>
#include <unistd.h>
#define SERVICE_1_ALIVE 9
#define SERVICE_1_DEAD 10
#define IPSI_FAILURE 0
#define IPSI_SUCCESS 1
using namespace std;
extern "C"
{
#include "ipsi.h"
}

#endif /* IPSIFRAMEWORK_DEMO_CONTROLLER_INC_CONTROLLERAPP_HPP_ */
