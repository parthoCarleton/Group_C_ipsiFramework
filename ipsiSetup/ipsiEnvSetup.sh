#!/bin/bash


echo "******************************************************************************************"
echo "----------------Make sure you have STABLE INTERNET CONNECTION--------------"
echo "You are about to set Environment for IPIS framework + Demo Apps + UT framework in your System"
printf "\n"
echo "NOTE: You should have administration privilages to download the packages"
echo "******************************************************************************************"
sleep 1

sudo add-apt-repository "deb http://security.ubuntu.com/ubuntu xenial-security main"
sudo apt-get update
sudo apt-get install -y build-essential cmake  vim libgtk2.0-dev \
                        libavcodec-dev libavformat-dev \
                        libswscale-dev libjpeg-dev libpng-dev libtiff5-dev \
                        libjasper-dev libopencv-dev checkinstall \
                        libjpeg-dev libjasper-dev libavcodec-dev \
                        libavformat-dev libswscale-dev libdc1394-22-dev \
                        libmp3lame-dev libopencore-amrnb-dev \
                        libopencore-amrwb-dev libtheora-dev libvorbis-dev \
                        libxvidcore-dev x264 v4l-utils unzip \
			libdbus-1-dev libdbus-glib-1-dev lcov xterm 
printf "\n"
echo "***************************************************************************"
echo "NOTE: Your machine has now required packages to run Demo + Unit Testing tools"
echo "You are not required to re-Run this option Again"
echo "If any packages failed to install then contact the Developers or try re-Running this option"
printf "\n"
echo "WARNING: If Demo or Unit Testing Framework fails to compile or execute , you might try to re-Run"
echo "this option or contact the Developer"
echo "***************************************************************************"
