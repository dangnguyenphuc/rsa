DEBUG_MAIN_FILE = "debug/main"
MAIN_FILE = "src/main.cpp"
DEBUG_TEST_FILE = "debug/test"
TEST_FILE = "src/testing.cpp"

main: src/main.cpp headers/main.h
	chmod 755 cipher/*
	g++ -g -O2 -std=c++11 -pthread -march=native $(MAIN_FILE) -o $(DEBUG_MAIN_FILE) -lntl -lgmp -lm
	./$(DEBUG_MAIN_FILE)
test: src/testing.cpp
	g++ -g -O2 -std=c++11 -pthread -march=native $(TEST_FILE) -o $(DEBUG_TEST_FILE) -lntl -lgmp -lm
	./$(DEBUG_TEST_FILE)
clean:
	rm -rf debug/*