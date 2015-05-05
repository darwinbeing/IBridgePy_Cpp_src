CC=g++

LIBS_CFLAGS=-lboost_python -lpython2.7

PYTHON_DIR=/usr/local/Cellar/python/2.7.9/Frameworks/Python.framework/Versions/2.7/include/python2.7/

BOOST_DIR=/Users/kvbian/local/boost

IBCPP_SRC=IBridgePy.cpp IBClient.cpp EClientSocketBase.cpp EPosixClientSocket.cpp

TARGET=IBCpp.so

$(TARGET): $(IBCPP_SRC)
	$(CC) -shared -fPIC -DIB_USE_STD_STRING -o $@ $(LIBS_CFLAGS) -I. -I./include -I$(PYTHON_DIR) -L$(BOOST_DIR)/lib -I$(BOOST_DIR)/include $^

clean:
	rm -rf *.o $(TARGET)
