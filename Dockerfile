FROM python:3.9-slim

RUN python -m venv /opt/venv
ENV PATH="/opt/venv/bin:$PATH"

COPY python-src/requirements.txt .

RUN python -m pip install --upgrade pip && \
    pip install -r requirements.txt

RUN apt update && apt install -y gcc \
g++ \
make \
cmake \
libzmq3-dev


RUN printf "\nalias ls='ls --color=auto'\n" >> ~/.bashrc
RUN printf "\nalias ll='ls -alF'\n" >> ~/.bashrc

ENV PACKAGE_PATH="/workspace/src/package"