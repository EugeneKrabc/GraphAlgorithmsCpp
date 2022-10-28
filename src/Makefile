FLAGS = g++ -g -std=c++17 -Wall -Wextra -Werror
SOURCES = Graph/*.cpp GraphAlgorithms/*.cpp DotFormatHandler/*.cpp DataStructures/Matrix/*.cpp \
			DataStructures/Stack/*.cpp DataStructures/Queue/*.cpp ConsoleEngine/*.cpp

demo:
	$(FLAGS) $(SOURCES) -o app.out
	./app.out

clean:
	rm app.out