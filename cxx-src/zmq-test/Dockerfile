FROM gcc:latest

RUN apt update && apt install -y cmake \
libzmq3-dev

RUN printf "\nalias ls='ls --color=auto'\n" >> ~/.bashrc
RUN printf "\nalias ll='ls -alF'\n" >> ~/.bashrc