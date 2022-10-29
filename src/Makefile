FLAGS = g++ -g -std=c++17 -Wall -Wextra #-Werror
SOURCES = Graph/*.cpp GraphAlgorithms/*.cpp DataStructures/Matrix/*.cpp \
			DataStructures/Stack/*.cpp DataStructures/Queue/*.cpp ConsoleEngine/*.cpp

demo:
	$(FLAGS) $(SOURCES) -o app.out
	./app.out

test:
	$(FLAGS) Tests/*.cpp Graph/*.cpp GraphAlgorithms/*.cpp DataStructures/Matrix/*.cpp \
			DataStructures/Stack/*.cpp DataStructures/Queue/*.cpp -lgtest

clang_style:
	clang-format -i $(SOURCES)

clean:
	rm -rf app.out app.out.dSYM
