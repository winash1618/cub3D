#!/bin/bash
make && valgrind --leak-check=full --show-leak-kinds=all ./cub3d ./parsing/map1.cub