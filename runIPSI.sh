#!bash

echo "***************************************************************"
echo "Welcome to Inter-Process Service Interface [IPSI] Greeting Page"
printf "\n"
echo "* IPSI-Framework library allows multiple applications "
echo "* to communicate by performing service requests.This framework abstracts "
echo "* the complex low-level system’s communication protocol by revealing "
echo "* a simplified service interface that can be used by the applications"
echo "* to invoke service requests to other applications."
printf "\n"
echo "***************************************************************"
echo "***************************************************************"
echo " You can choose from the following option:"
echo " 0. Build ipsi Shared library"
echo " 1. Demonstate capabilites of IPSI framework"
echo " 2. Run Unit Test on IPSI framework"
echo " 3. Setup IPSI Framework envrionment in Your machine"
echo " Press any other Key to Exit from this Page "
echo "***************************************************************"
read option

case $option in

	0)
		echo "*You have Selected*"
		echo " 0. Build ipsi Shared library"
		sleep 1
		printf "\n"
		echo "NOTE: You should have ran option 3 atleast once in your system"
		echo "If all packages where installed , you can ignore this by Pressing any key"
		echo "otherwise, press y/Y to setup your machine"
		read ack
		if  [ "$ack" = "Y" ] || [ "$ack" = "y" ]
		then
			echo "** Setting up Environment for IPSI Framework **"
			cd ipsiSetup
			sh ipsiEnvSetup.sh
			cd ../
		fi
		cd ipsi
		make
		cd ../
		printf "\n"
		echo "***************************************************************"
		echo "IPSI shared library - ipsi.so can be found in ipsi/bin"
	        echo "IPSI shared library - ipsi.h can be found in ipsi/inc"	
		echo "***************************************************************"
		;;

	1)
		echo "*You have Selected*"
		echo " 1. Demonstate capabilites of IPSI framework"
		echo " NOTE: You should have minimum resolution of 1280x1024 resolution for Demo apps to run comfortably"	
		sleep 1
		printf "\n"
		echo "NOTE: You should have ran option 3 atleast once in your system"
		echo "If all packages where installed , you can ignore this by Pressing any key"
		echo "otherwise, press y/Y to setup your machine"
		read ack
		if  [ "$ack" = "Y" ] || [ "$ack" = "y" ]
		then
			echo "** Setting up Environment for IPSI Framework **"
			cd ipsiSetup
			sh ipsiEnvSetup.sh
			cd ../
		fi
		cd demo
		sh runDemo.sh
		cd ../
		;;
	2) 
		echo "*You have Selected*"
		echo " 2. Run Unit Test on IPSI framework"
		sleep 1
		printf "\n"
		echo "NOTE: You should have ran option 3 atleast once in your system"
		echo "If all packages where installed , you can ignore this by Pressing any key"
		echo "otherwise, press y/Y to setup your machine"
		read ack
		if  [ "$ack" = "Y" ] || [ "$ack" = "y" ]
		then
			echo "** Setting up Environment for IPSI Framework **"
			cd ipsiSetup
			sh ipsiEnvSetup.sh
			cd ../
		fi
		cd ipsiTest
		sh runUT.sh
		cd ../
		;;
	3)
		echo "*You have Selcted*"
		echo " 3. Setup IPSI envrionment in Your PC"
		sleep 1
		cd ipsiSetup
		sh ipsiEnvSetup.sh
		cd ../
		;;

	*)
		echo "You have entered unknow option"
		echo "Goodbye ,We will now Exit!! "
esac
