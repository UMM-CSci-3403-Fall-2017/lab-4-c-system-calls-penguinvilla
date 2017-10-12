#!/bin/bash

num_dirs=$(find -L $1 -type d | wc -l)
num_files=$(find -L $1 -type f | wc -l)

echo "There were $num_dirs directories."
echo "There were $num_files regular files."
