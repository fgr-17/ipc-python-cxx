FROM python:3.9-slim

RUN python -m venv /opt/venv
ENV PATH="/opt/venv/bin:$PATH"

COPY requirements.txt .

RUN python -m pip install --no-cache-dir --upgrade pip && \
    pip install -r  requirements.txt --no-cache-dir

RUN apt update && apt install -y gcc \
g++ \
make \
cmake \
git

RUN printf "\nalias ls='ls --color=auto'\n" >> ~/.bashrc
RUN printf "\nalias ll='ls -alF'\n" >> ~/.bashrc

ENV PACKAGE_PATH="/workspace/src/package"

RUN pip install git+https://github.com/osvenskan/posix_ipc.git --no-cache-dir