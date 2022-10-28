FLAGS = g++ -g -std=c++17 -Wall -Wextra #-Werror
SOURCES = Graph/*.cpp GraphAlgorithms/*.cpp DotFormatHandler/*.cpp DataStructures/Matrix/*.cpp \
			DataStructures/Stack/*.cpp DataStructures/Queue/*.cpp ConsoleEngine/*.cpp

demo:
	$(FLAGS) $(SOURCES) -o app.out
	./app.out

clang_style:
	clang-format -i $(SOURCES)

clean:
	rm -rf app.out app.out.dSYM
