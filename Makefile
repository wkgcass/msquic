.DEFAULT_GOAL := build

.PHONY: clean
clean:
	rm -rf ./build

.PHONY: build
build:
	mkdir -p build/
	cd build/ && cmake -G 'Unix Makefiles' ..
	cd build/ && cmake --build .
