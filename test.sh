#!/bin/bash
make && valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all ./cub3d ./parsing/map1.cub