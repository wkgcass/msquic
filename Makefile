.DEFAULT_GOAL := build

IS_WIN = 0
ifneq (,$(findstring MINGW,$(OS)))
	IS_WIN = 1
else ifneq (,$(findstring Windows,$(OS)))
	IS_WIN = 1
endif

.PHONY: clean
clean:
	rm -rf ./build
	rm -rf ./artifacts

.PHONY: build
build:
ifeq (1,$(IS_WIN))
	pwsh ./scripts/build.ps1 -Tls openssl -Config Release -DisableTools -DisableTest -DisablePerf -DisableLogs
else
	mkdir -p build/
	cd build/ && cmake -G 'Unix Makefiles' ..
	cd build/ && cmake --build .
endif
