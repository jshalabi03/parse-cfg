#!/bin/bash

INPUT_FILE=$1

docker build -t clang_image .

CONTAINER_ID=$(docker create clang_image:latest)
docker cp $INPUT_FILE $CONTAINER_ID:/app/tmp/index.cpp

docker start $CONTAINER_ID

docker cp $CONTAINER_ID:/app/tmp/cfg.dot ./output
docker cp $CONTAINER_ID:/app/tmp/cfg.png ./output

docker rm $CONTAINER_ID


