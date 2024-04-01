CMAKE_DEFINES = 

FILES_TO_COVER = 3DViewer_v2_tests.cc

all: build 

install: configure build

configure:
	cmake -B ../build -S . $(CMAKE_DEFINES)

build: configure
	cd ../build && cmake --build . --target 3DViewer_2-0


run: build
	./../build/3DViewer_2-0.app/Contents/MacOS/3DViewer_2-0

uninstall:
	rm -rf ../build

test: configure
	cd ../build && cmake --build . --target tests
	cp tests/cube.obj ../build
	cp tests/pyramid.obj ../build
	cd ../build && ./tests

dvi:
	open ./html/annotated.html

dist:
	cd ..; tar -cvf archive.tar src

gcov_report: add_lcov_definition configure test
	mkdir -p gcov
	cp $(shell find ../build -type f -name "*.gcda") gcov
	cp $(shell find ../build -type f -name "*.gcno") gcov
	geninfo $(addprefix gcov/, $(addsuffix .gcda, $(FILES_TO_COVER))) -o gcov/data.info --gcov-tool /usr/bin/gcov --ignore-errors inconsistent --exclude v1 --exclude containers
	genhtml gcov/data.info -o report --ignore-errors inconsistent
	open report/index.html

add_lcov_definition:
		$(eval CMAKE_DEFINES += -DCMAKE_CXX_FLAGS="-fprofile-arcs -ftest-coverage -fno-elide-constructors")
		$(eval CMAKE_DEFINES += -DCMAKE_EXE_LINKER_FLAGS="-fprofile-arcs")

style:
	cp ../materials/linters/.clang-format ./
	clang-format -n -style=file $(shell find . -not -path "./build/*" -type f -name "*.cc")
	clang-format -n -style=file $(shell find . -not -path "./build/*" -type f -name "*.h")
	rm -rf .clang-format

clean:
	rm -rf ../.cache
	rm -rf .cache
	cd .. && rm -rf build-*
	cd ../build/ && make clean
	rm -f ../archive.tar
	rm -rf gcov
