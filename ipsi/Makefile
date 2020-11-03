
LIB_NAME = libipsi

LIB_SRC_DIR = src/ipsi.c

LIB_SO_DIR = bin/$(LIB_NAME).so

LIB_OBJ_DIR = obj/$(LIB_NAME).o

IPSI_INCLUDE_DIR = -I/usr/include/dbus-1.0 \
		   -I/usr/lib/x86_64-linux-gnu/dbus-1.0/include \
		   -I/usr/include/glib-2.0 \
		   -Iinc/

DBUG_FLAG = -g

CFLAGS = -c -Wall -Wextra  -fpic

CXX = gcc

$(LIB_NAME).so : $(LIB_NAME).o
	$(CXX) -shared -o $(LIB_SO_DIR) $(LIB_OBJ_DIR)

$(LIB_NAME).o : $(LIB_SRC_DIR)
	$(CXX) $(CFLAGS) $(DBUG_FLAG) $(LIB_SRC_DIR) $(IPSI_INCLUDE_DIR) -o $(LIB_OBJ_DIR)

clean: 
	rm -v bin/* obj/*
