FROM --platform=arm64 ubuntu:22.10

RUN apt-get update
RUN apt-get install -y clang
RUN apt-get install -y graphviz libcgraph6 libgvc6

RUN mkdir /app
WORKDIR /app

COPY . /app
RUN mkdir /app/tmp
RUN clang++ -std=c++20 -Iincludes/ -o parse-cfg src/main.cpp src/CFG.cpp src/FileUtil.cpp

RUN chmod +x /app/scripts/exec.sh
CMD [ "/app/scripts/exec.sh" ]