FROM ubuntu:20.04

RUN apt-get update -y
RUN apt-get install -y software-properties-common
RUN apt-add-repository -y ppa:lttng/stable-2.13
RUN apt-get update -y
RUN apt-get install -y cmake build-essential liblttng-ust-dev lttng-tools

RUN mkdir /msquic
WORKDIR /msquic

ENTRYPOINT []
