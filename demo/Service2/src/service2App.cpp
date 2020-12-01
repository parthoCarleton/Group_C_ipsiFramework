/**
 * @file File Name: service2App.cpp
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

#include "service2App.hpp"

volatile int play_state = START_VIDEO;
static int thread_state = START_THREAD ;
int ret_thread =0;
pthread_t threads[3];
pthread_mutex_t ipsi_processing_lock;

/**
 * Video Rendering on Screen.
 */
void * video_render(void *){

	cout<<"[Service 2] Starting Video Rendering Services Please Wait...."<<endl;
	sleep(2);
	// Create a VideoCapture object and open the input file
	VideoCapture cap("media/test.mp4"); // Play static video in media folder

	if(!cap.isOpened()){
		cout << "[Service 2] Error opening video stream or file" << endl;
		return 0;
	}
	cout<<"[Service 2] Video Rendering Services !STARTED!"<<endl;
	while(START_VIDEO == play_state || RESUME_VIDEO == play_state){

		Mat frame;
		// Capture frame-by-frame
		cap >> frame;

		// If the frame is empty, break immediately
		if (frame.empty()){
			cap.set(CAP_PROP_POS_FRAMES, 0);
			continue;
		}

		namedWindow( "Display window", WINDOW_NORMAL);// Create a window for display.
		resizeWindow("Display window", 500,300);
		// Display the resulting frame
		imshow( "Display window", frame );

		waitKey(25);

		if( PAUSE_VIDEO == play_state)
		{
			cout<<"[Service 2] Video is now Paused"<<endl;
			while(PAUSE_VIDEO == play_state);
			if(RESUME_VIDEO == play_state){
				cout<<"[Service 2] Video playback is now Resumed"<<endl;
			}
		}
		if(STOP_VIDEO == play_state){
			// When everything done, release the video capture object
			cap.release();
			// Closes all the frames
			destroyAllWindows();
			cout<<"[Service 2] Exiting Video Rendering Services.."<<endl;
			sleep(2);
			cout<<"[Service 2] Video Rendering !STOPED!.."<<endl;
			pthread_exit(&ret_thread);
		}
	}
	return 0;
}

/**
 * Service Requester Application has requested to
 * play video on screen if the video was not playing on screen.
 */
void video_play()
{
	std::cout << "----------------------------------------------" << std::endl;
	if(START_THREAD == thread_state){ // Singleton thread
		cout<<"[Service 2] Request to Render Video on Screen"<<endl;
		play_state = START_VIDEO;
		pthread_create(&threads[0],NULL,video_render,NULL);
		thread_state =RUNNING_THREAD;
	}
	else{
		cout<<"[Service 2] The video is already rendering on Screen "<<endl;
	}
	std::cout << "----------------------------------------------" << std::endl;
	return;
}

/**
 * Service Requester Application has requested to
 * pause video playback if it was playing on screen.
 */
void video_pause()
{
	std::cout << "----------------------------------------------" << std::endl;
	if(RUNNING_THREAD ==  thread_state && (RESUME_VIDEO == play_state || START_VIDEO == play_state) ){
		cout<<"[Service 2] Request to Pause Video Rendering"<<endl;
		play_state = PAUSE_VIDEO; //Pause Video
	}
	else if ((RUNNING_THREAD ==  thread_state) && !(RESUME_VIDEO == play_state || START_VIDEO == play_state)) {
		cout<<"[Service 2] Video is already Paused on Screen "<<endl;
	}
	else{
		cout<<"[Service 2] No videos are rendering on Screen "<<endl;
	}
	std::cout << "----------------------------------------------" << std::endl;
	return;
}

/**
 * Service Requester Application has requested to
 * resume video playback if it was paused on screen.
 */
void video_resume()
{
	std::cout << "----------------------------------------------" << std::endl;
	if(RUNNING_THREAD ==  thread_state && PAUSE_VIDEO == play_state){
		cout<<"[Service 2] Request to Resume Video Rendering"<<endl;
		play_state = RESUME_VIDEO; // resume Video
	}
	else if ((RUNNING_THREAD ==  thread_state) && (PAUSE_VIDEO != play_state) ){
		cout<<"[Service 2] Video playback is already in running state  "<<endl;
	}
	else{
		cout<<"[Service 2] No videos are rendering on Screen "<<endl;
	}
	std::cout << "----------------------------------------------" << std::endl;
	return;
}

/**
 * Service Requester Application has requested to
 * Terminate this application and its services.
 */
void service_2_Exit()
{
	std::cout << "----------------------------------------------" << std::endl;
	cout<<"[Service 2] !CAUTION! Requested to KILL Myself! "<<endl;
	/** Do not attempt to invoke ipsi_close() in this function as
	 * it is still under ipsi_listen() context, it is advisable to
	 * set condition flag and safely return from the function
	 */
	pthread_mutex_unlock(&ipsi_processing_lock);
	std::cout << "----------------------------------------------" << std::endl;
	return;

}

/**
 * Service Requester Application has requested to Stop the Video playback on screen.
 */
void video_stop()
{
	std::cout << "----------------------------------------------" << std::endl;
	if(RUNNING_THREAD ==  thread_state){
		cout<<"[Service 2] Request to Stop Video Rendering"<<endl;
		play_state = STOP_VIDEO;
		thread_state = START_THREAD;
	}
	else{
		cout<<"[Service 2] No videos are rendering on Screen "<<endl;
	}
	std::cout << "----------------------------------------------" << std::endl;
	return;
}

/**
 * CleanUp Service 2 Applications and Terminate itself.
 */
void* service_2_Cleanup(void *){


	pthread_mutex_lock(&ipsi_processing_lock);
	std::cout << "----------------------------------------------" << std::endl;
	cout <<"[Service 2] !CAUTION! Shutting Down...."<<endl;
	video_stop();

	cout <<"[Service 2] !If you want me back , you need to Restart me!"<<endl;
	/** Attempt to do all clean up activity for Application
	 * as well request IPSI to close and ShutDown
	 */
	cout <<"[Service 2] Shutting Down IPSI Please Wait ....."<<endl;
	sleep (3);
	ipsi_close();
	sleep (2);
	cout <<"[Service 2] !Exited! ....."<<endl;
	std::cout << "----------------------------------------------" << std::endl;
	pthread_mutex_unlock(&ipsi_processing_lock);
	pthread_exit(&ret_thread);
	return 0;

}

/** Start Service 2 Applications with its Services */
int main()
{

	cout<<"********************************************"<<endl;
	cout<<"! Welcome to Service 2 Application !"<<endl<<endl;
	cout<<"********************************************"<<endl;
	cout<<"--DISCLAIMER : "<<endl;
	cout<<"This is a Demo Application intended to show the capabilities of IPSI communication"<<endl;
	cout<<"********************************************"<<endl;
	cout<<"This Application has the ability to render Video graphics that are controlled by Service Requester Application"<<endl;
	cout<<"********************************************"<<endl;

	// Service 2 cleanUp Activity Thread, It is called when
	// Service Requester wants to terminate this APP.
	pthread_mutex_lock(&ipsi_processing_lock);
	pthread_create(&threads[1],NULL,service_2_Cleanup,NULL);

	//Register your services with ipsiFramework
	if ( IPSI_SUCCESS == ipsi_register_function(video_play,(char*)"Play")){
		cout << "[Service 2] [PASSED] Registered the function video_play() with IPSI lib"<<endl;
	}
	else{
		cout << "[Service 2] [FAILED] Check IPSI Log!, failed to register function video_play() with IPSI lib"<<endl;
	}

	if ( IPSI_SUCCESS == ipsi_register_function(video_pause,(char*)"Pause")){
		cout << "[Service 2] [PASSED] Registered the function video_pause() with IPSI lib"<<endl;
	}
	else{
		cout << "[Service 2] [FAILED] Check IPSI Log!, failed to register function video_pause() with IPSI lib"<<endl;
	}

	if ( IPSI_SUCCESS == ipsi_register_function(video_resume,(char*)"Resume")){
		cout << "[Service 2] [PASSED] Registered the function video_resume() with IPSI lib"<<endl;
	}
	else{
		cout << "[Service 2] [FAILED] Check IPSI Log!, failed to register function video_resume() with IPSI lib"<<endl;
	}

	if ( IPSI_SUCCESS == ipsi_register_function(service_2_Exit,(char*)"Exit")){
		cout << "[Service 2] [PASSED] Registered the function service_2_Exit() with IPSI lib"<<endl;
	}
	else{
		cout << "[Service 2] [FAILED] Check IPSI Log!, failed to register function service_2_Exit() with IPSI lib"<<endl;
	}

	if ( IPSI_SUCCESS == ipsi_register_function(video_stop,(char*)"Stop")){
		cout << "[Service 2] [PASSED] Registered the function video_stop() with IPSI lib"<<endl;
	}
	else{
		cout << "[Service 2] [FAILED] Check IPSI Log!, failed to register function video_stop() with IPSI lib"<<endl;
	}

	//Register the Application as Service Provider.
	if ( IPSI_SUCCESS == ipsi_connection_type ((char*)"server2",(char*)"Server")){
		cout<<"[Service 2] [PASSED] Application was successfully Registered"<<endl;
	}
	else{
		cout<<"[Service 2] [FAILED] Error! check IPSI Log , try restarting your system!"<<endl;
		exit(0);
	}

	//Listen for service Request
	if ( IPSI_SUCCESS == ipsi_listen()){
		cout<<"[Service 2] [PASSED] IPSI successfully exited"<<endl;
	}
	else{
		cout<<"[Service 2] [FAILED] Failed to stop IPSI , check IPSI LOG"<<endl;
	}

	pthread_join(threads[1],NULL);
	return 0;
}

