.DEFAULT_GOAL := clean

.PHONY: clean
clean:
	@echo "nothing to be done"

.PHONY: compile-docker
compile-docker:
	docker rmi -f vproxyio/msquic-compile:latest
	docker build -t vproxyio/msquic-compile:latest ./docker/compile
