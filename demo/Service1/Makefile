
APP_EXE = Service1

APP_SRC_DIR = src/service1App.cpp

APP_EXE_DIR = bin/$(APP_EXE)

OPENCV_INCLUDE_DIR = -I/usr/include/opencv4 \
		     -I/usr/include

OPENCV_LIBRARY_PATH = -L/usr/local/lib

IPSI_LIBRARY_NAME = -lipsi

IPSI_INCLUDE_DIR = -I/usr/include/dbus-1.0 \
		   -I/usr/lib/x86_64-linux-gnu/dbus-1.0/include \
		   -I/usr/include/glib-2.0 \
		   -Iinc/ \
		   -I../../ipsi/inc

IPSI_LIBRARY_DIR = -L../../ipsi/bin

IPSI_LIBRARY = $(IPSI_LIBRARY_NAME) -ldbus-1 -ldbus-glib-1

OPENCV_LIBRARY = -lopencv_videoio \
		 -lopencv_core \
		 -lopencv_video \
		 -lopencv_stitching \
		 -lopencv_highgui \
		 -lopencv_ml \
		 -lopencv_video \
		 -lopencv_objdetect \
		 -lopencv_calib3d \
		 -lopencv_imgcodecs\
		 -lopencv_features2d \
		 -lopencv_flann \
		 -lopencv_photo \
		 -lopencv_imgproc \
		 -lopencv_core

THREAD_LIB = -lpthread 

DBUG_FLAG = -g

CFLAGS = -Wall -Wextra

CXX = g++

Service : $(APP_SRC_DIR)
	$(CXX) $(CFLAGS) $(DBUG_FLAG) $(APP_SRC_DIR) $(OPENCV_INCLUDE_DIR) $(IPSI_INCLUDE_DIR) $(IPSI_LIBRARY_DIR) $(IPSI_LIBRARY) $(OPENCV_LIBRARY) $(THREAD_LIB) -o $(APP_EXE_DIR)

clean: 
	rm -v bin/*
