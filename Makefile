all: send receiver

send: RCSwitch.o send.o
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $+ -o $@.out -lwiringPi

receiver: RCSwitch.o receiver.o
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $+ -o $@.out -lwiringPi

clean:
	$(RM) *.o *.out
