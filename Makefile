test:
	g++-4.6 -std=c++0x -o juli2ir \
		main.cpp \
		interpreter.cpp \
		iremocon_client.cpp \
		julius_client.cpp \
		-lboost_regex -lboost_system -lboost_thread -lpthread

