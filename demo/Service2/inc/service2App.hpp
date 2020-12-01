/**
 * @file File Name: service2App.hpp
 *
 * This software embodies materials and concepts which are entitled for the
 * course:
 * ELG 6179: ADV TOPICS IN SOFTWARE ENGINEER. (Software Development in C) [University of Ottawa]
 * SYSC5709F: Software Development with C [Carleton University]
 *
 * Description: This Application is a Demo Application intended to show the
 * capabilities of IPSI library for Inter-Process communication.
 * This Application (a.k.a) Service Provider application has the ability to render
 * Video graphics that are controlled by Service Requester Application.
 *
 * @note: Can be used as a reference guide for using IPSI interface.
 *
*/

#ifndef IPSIFRAMEWORK_DEMO_SERVICE2_INC_SERVICE2APP_HPP_
#define IPSIFRAMEWORK_DEMO_SERVICE2_INC_SERVICE2APP_HPP_

#define RUNNING_THREAD 14
#define START_THREAD 15
#define IPSI_FAILURE 0
#define IPSI_SUCCESS 1
#define START_VIDEO 7
#define RESUME_VIDEO 9
#define PAUSE_VIDEO 10
#define STOP_VIDEO 11
#include <iostream>
#include <opencv2/opencv.hpp>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
extern "C"
{
#include "../../../ipsi/inc/ipsi.h"
}
using namespace cv;
using namespace std;

#endif /* IPSIFRAMEWORK_DEMO_SERVICE2_INC_SERVICE2APP_HPP_ */
