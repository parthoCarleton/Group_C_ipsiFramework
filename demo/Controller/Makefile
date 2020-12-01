
APP_EXE = Controller

APP_SRC_DIR = src/controllerApp.cpp

APP_EXE_DIR = bin/$(APP_EXE)

IPSI_LIBRARY_NAME = -lipsi

IPSI_INCLUDE_DIR = -I/usr/include/dbus-1.0 \
		   -I/usr/lib/x86_64-linux-gnu/dbus-1.0/include \
		   -I/usr/include/glib-2.0 \
		   -Iinc/ \
		   -I../../ipsi/inc/

IPSI_LIBRARY_DIR = -L../../ipsi/bin/

IPSI_LIBRARY = $(IPSI_LIBRARY_NAME) -ldbus-1 -ldbus-glib-1

DBUG_FLAG = -g

CFLAGS = -Wall -Wextra

CXX = g++

Controller : $(APP_SRC_DIR) 
	$(CXX) $(CFLAGS) $(DBUG_FLAG) $(APP_SRC_DIR) $(IPSI_INCLUDE_DIR) $(IPSI_LIBRARY_DIR) $(IPSI_LIBRARY) -o $(APP_EXE_DIR)

clean: 
	rm -v bin/*
