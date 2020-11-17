TEST_ISCALLER = unitTest_isCaller_UT.c
#TEST_ISSERVER =	unitTest_isServer_UT.c
#TEST_CONNECTIONTYPE = unitTest_ipsiConnectionType_UT.c
TEST_METHODCALL = unitTest_ipsiMethodCall_UT.c
TEST_REGISTERFUNCTION = unitTest_ipsiRegisterFunction_UT.c
TEST_LISTEN = unitTest_ipsiListen_UT.c

TEST_INCLUDE = -I../../ipsi/src \
				-I../../ipsi/inc \
				-I/usr/include/dbus-1.0 \
				-I/usr/lib/x86_64-linux-gnu/dbus-1.0/include

CXX= gcc
COVERAGE= -fprofile-arcs -ftest-coverage

TEST_ALL:
	$(CXX) $(COVERAGE) $(TEST_INCLUDE) $(TEST_ISCALLER) -o bin/isCaller.ut
#	$(CXX) $(COVERAGE) $(TEST_INCLUDE) $(TEST_ISSERVER) -o bin/isServer.ut
#	$(CXX) $(COVERAGE) $(TEST_INCLUDE) $(TEST_CONNECTIONTYPE) -o bin/ConnectionType.ut
	$(CXX) $(COVERAGE) $(TEST_INCLUDE) $(TEST_METHODCALL) -o bin/MethodCall.ut
	$(CXX) $(COVERAGE) $(TEST_INCLUDE) $(TEST_REGISTERFUNCTION) -o bin/RegisterFunction.ut
	$(CXX) $(COVERAGE) $(TEST_INCLUDE) $(TEST_LISTEN) -o bin/Listen.ut
