# Makefile 
CXX = g++
CXXFLAGS = -O3 -fopenmp -march=native -ffast-math

TARGET = correlate_prog
OBJS = main.o correlate.o

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET)

main.o: main.cpp correlate.h
	$(CXX) $(CXXFLAGS) -c main.cpp

correlate.o: correlate.cpp correlate.h
	$(CXX) $(CXXFLAGS) -c correlate.cpp

clean:
	rm -f $(OBJS) $(TARGET)

*Analysis Steps*
Compile: Run make in your terminal.
Sequential Test: Run perf stat ./correlate_prog 1000 1000 1.
Parallel Test: Run perf stat ./correlate_prog 1000 1000 4 
