/**
 * @file File Name: controllerApp.cpp
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

#include "controllerApp.hpp"

int main()
{
	string control;
	char state = 'N';
	int in_option;

	cout<<"********************************************"<<endl;
	cout<<"! Welcome to CONTROLLER Application !"<<endl<<endl;
	cout<<"********************************************"<<endl;
	cout<<"--DISCLAIMER : "<<endl;
	cout<<"This is a Demo Application intended to show the capabilities of IPSI communication"<<endl;
	cout<<"********************************************"<<endl;
	cout<<"This Application has the ability to Control the rendering of Video graphics that are rendered by other specialize application capable to render Graphics on Console."<<endl;
	cout<<"********************************************"<<endl<<endl;

	cout<< "[Controller] Starting Application ....."<<endl;
	sleep(3);
	cout<<"[Controller] Attempting to register with IPSI library"<<endl;
	sleep(2);
	if(IPSI_SUCCESS == ipsi_connection_type ((char*)"caller",(char*)"Caller")){
		cout<<"[Controller] [PASSED] Application was successfully Registered"<<endl;
	}
	else{
		cout<<"[Controller] [FAILED] Error! check IPSI Log , try restarting your system!"<<endl;
		exit(0);
	}
	cout<<"[Controller] Registration with IPSI library completed"<<endl;
	cout<<"********************************************"<<endl;
	sleep(1);

	while(state == 'N' || 'n' == state)
	{
		std::cout<<endl<<"*** Make sure Service Provider Applications are Running else request will be dropped ***"<<endl<<endl;
		std::cout << "++++++++++++++++++Controller_Application+++++++++++++++++++++" << std::endl;
		std::cout << "++++++Control Video Graphics on Service 1 Application++++++++"<<endl;
		std::cout << "0. Request Service 1 APP to Play Video " <<endl;
		std::cout << "1. Request Service 1 APP to Pause Video " <<endl;
		std::cout << "2. Request Service 1 APP to Resume Video " <<endl;
		std::cout << "3. Request Service 1 APP to Stop Video " <<endl;
		std::cout << "4. Request Service 1 APP to Terminate " <<endl;
		std::cout << "++++++Control Video Graphics on Service 2 Application++++++++"<<endl;
		std::cout << "5. Request Service 2 APP to Play Video " <<endl;
		std::cout << "6. Request Service 2 APP to Pause Video " <<endl;
		std::cout << "7. Request Service 2 APP to Resume Video " <<endl;
		std::cout << "8. Request Service 2 APP to Stop Video " <<endl;
		std::cout << "9. Request Service 2 APP to Terminate " <<endl;
		std::cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl;
		std::cout << "**To EXIT from this option enter any NUMBER apart from the above option**" <<endl<<endl;
		std::cout << "Enter the option \r" << std::endl;

		std::cin >> in_option;
		if(cin.fail()){
			cout<< "!Input was not an Integer please TRY AGAIN!"<<endl;
			cin.clear();
			cin.ignore(INT_MAX,'\n');
			continue;
		}

		switch(in_option){

		case 0:
			std::cout << "----------------------------------------------" << std::endl;
			std::cout<< "[Controller] Requesting Service 1 to Play Video \n" <<endl;
			if(IPSI_SUCCESS == ipsi_method_call((char*)"server",(char*)"Play")){
				cout<<"[Controller] [PASSED] Request was placed successfully"<<endl;
			}
			else{
				cout<<"[Controller] [FAILED] ipsi_method_call() failed see IPSI log"<<endl;
			}
			std::cout << "----------------------------------------------" << std::endl;
			break;

		case 1 :
			std::cout << "----------------------------------------------" << std::endl;
			std::cout<< "[Controller] Requesting Service 1 to Pause Video \n" <<endl;
			if(IPSI_SUCCESS == ipsi_method_call((char*)"server",(char*)"Pause")){
				cout<<"[Controller] [PASSED] Request was placed successfully"<<endl;
			}
			else{
				cout<<"[Controller] [FAILED] ipsi_method_call() failed see IPSI log"<<endl;
			}
			std::cout << "----------------------------------------------" << std::endl;
			break;

		case 2 :
			std::cout << "----------------------------------------------" << std::endl;
			std::cout<< "[Controller] Requesting Service 1 to Resume Video \n" <<endl;
			if(IPSI_SUCCESS == ipsi_method_call((char*)"server",(char*)"Resume")){
				cout<<"[Controller] [PASSED] Request was placed successfully"<<endl;
			}
			else{
				cout<<"[Controller] [FAILED] ipsi_method_call() failed see IPSI log"<<endl;
			}
			std::cout << "----------------------------------------------" << std::endl;
			break;

		case 3 :
			std::cout << "----------------------------------------------" << std::endl;
			std::cout<< "[Controller] Requesting Service 1 to Stop Video \n" <<endl;
			if(IPSI_SUCCESS ==  ipsi_method_call((char*)"server",(char*)"Stop")){
				cout<<"[Controller] [PASSED] Request was placed successfully"<<endl;
			}
			else{
				cout<<"[Controller] [FAILED] ipsi_method_call() failed see IPSI log"<<endl;
			}
			std::cout << "----------------------------------------------" << std::endl;
			break;

		case 4 :
			std::cout << "----------------------------------------------" << std::endl;
			std::cout<< "[Controller] Requesting Service 1 to Terminate \n" <<endl;
			if(IPSI_SUCCESS == ipsi_method_call((char*)"server",(char*)"Exit")){
				cout<<"[Controller] [PASSED] Request was placed successfully"<<endl;
			}
			else{
				cout<<"[Controller] [FAILED] ipsi_method_call() failed see IPSI log"<<endl;
			}
			std::cout<< "[Controller] Warning ! You may need to Re-Start Service 1 App else all future requests will be dropped!" <<endl;
			std::cout << "----------------------------------------------" << std::endl;
			break;

		case 5 :
			std::cout << "----------------------------------------------" << std::endl;
			std::cout<< "[Controller] Requesting Service 2 to Play Video \n" <<endl;
			if(IPSI_SUCCESS == ipsi_method_call((char*)"server2",(char*)"Play")){
				cout<<"[Controller] [PASSED] Request was placed successfully"<<endl;
			}
			else{
				cout<<"[Controller] [FAILED] ipsi_method_call() failed see IPSI log"<<endl;
			}
			std::cout << "----------------------------------------------" << std::endl;
			break;

		case 6 :
			std::cout << "----------------------------------------------" << std::endl;
			std::cout<< "[Controller] Requesting Service 2 to Pause Video \n" <<endl;
			if(IPSI_SUCCESS == ipsi_method_call((char*)"server2",(char*)"Pause")){
				cout<<"[Controller] [PASSED] Request was placed successfully"<<endl;
			}
			else{
				cout<<"[Controller] [FAILED] ipsi_method_call() failed see IPSI log"<<endl;
			}
			std::cout << "----------------------------------------------" << std::endl;
			break;

		case 7 :
			std::cout << "----------------------------------------------" << std::endl;
			std::cout<< "[Controller] Requesting Service 2 to Resume Video \n" <<endl;
			if(IPSI_SUCCESS == ipsi_method_call((char*)"server2",(char*)"Resume")){
				cout<<"[Controller] [PASSED] Request was placed successfully"<<endl;
			}
			else{
				cout<<"[Controller] [FAILED] ipsi_method_call() failed see IPSI log"<<endl;
			}
			std::cout << "----------------------------------------------" << std::endl;
			break;

		case 8 :
			std::cout << "----------------------------------------------" << std::endl;
			std::cout<< "[Controller] Requesting Service 2 to Stop Video \n" <<endl;
			if(IPSI_SUCCESS == ipsi_method_call((char*)"server2",(char*)"Stop")){
				cout<<"[Controller] [PASSED] Request was placed successfully"<<endl;
			}
			else{
				cout<<"[Controller] [FAILED] ipsi_method_call() failed see IPSI log"<<endl;
			}
			std::cout << "----------------------------------------------" << std::endl;
			break;

		case 9 :
			std::cout << "----------------------------------------------" << std::endl;
			std::cout<< "[Controller] Requesting Service 2 to Terminate \n" <<endl;
			if(IPSI_SUCCESS == ipsi_method_call((char*)"server2",(char*)"Exit")){
				cout<<"[Controller] [PASSED] Request was placed successfully"<<endl;
			}
			else{
				cout<<"[Controller] [FAILED] ipsi_method_call() failed see IPSI log"<<endl;
			}
			std::cout<< "[Controller] Warning ! You may need to Re-Start Service 1 App else all future requests will be dropped!" <<endl;
			std::cout << "----------------------------------------------" << std::endl;
			break;

		default:
			std::cout<< "[Controller] !Unknown Option! \n" <<endl;
			std::cout<< "[Controller] Want to Exit (Y/N)?\n";
			cin >> state;
		}
	}
	std::cout<< "[Controller] Shutting Down...... \n";
	ipsi_method_call((char*)"server",(char*)"Exit"); // Shutdown Service 1
	ipsi_method_call((char*)"server2",(char*)"Exit"); // Shutdown Service 2
	sleep(3);
	std::cout<< "[Controller] *!Exited!* \n";
	sleep(2);
}

