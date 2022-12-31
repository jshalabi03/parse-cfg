#!/bin/bash

/app/parse-cfg -f tmp/index.cpp -o tmp/cfg.dot
dot -Tpng tmp/cfg.dot -o tmp/cfg.png