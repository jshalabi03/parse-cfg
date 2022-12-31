# Parse CFG
## About
* Generates control-flow graph from C++ source file
* Emits x86 Intel ASM with `clang 15.0.0`
* Docker image fetches required dependencies and ensures standardized output
* Uses Graphviz to generate PNG visualization of control-flow graph

___

![](https://media.giphy.com/media/Tb2J3IGtk6WSqtwdJi/giphy.gif)

___

## Usage

> The following instructions may be executed via running the `script.sh` shell script:
>
> `$ sh script.sh <path-to-input>`
>
> The output will be generated in the `output/` directory

___

Build `Docker` image

```
$ docker build -t clang_image .
```

Create container

```
$ CONTAINER_ID=$(docker create clang_image:latest)
```

Copy input file to container

```
$ docker cp <path-to-input> $CONTAINER_ID:/app/tmp/index.cpp
```

Start container to generate output

```
$ docker start $CONTAINER_ID
```

Copy output files from container to local machine

```
$ docker cp $CONTAINER_ID:/app/tmp/cfg.dot <path-to-output-dir>
$ docker cp $CONTAINER_ID:/app/tmp/cfg.png <path-to-output-dir>
```

Delete container

```
$ docker rm $CONTAINER_ID
```
