CXX = g++
CXXFLAGS = -std=c++11 -Wall
TARGET = analisador
SRC = analisador.cpp

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

clean:
	rm -f $(TARGET)

run: all
	./$(TARGET)