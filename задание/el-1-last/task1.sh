#!/bin/bash

echo "Кол-во списков в директории lists:"
find lists/ -type f -name '*.src' | wc -l
echo "Кол-во уникальных имен программ в списках:"
cat $(find lists/ -type f -name '*.src') | grep ".src$" -v | sort | uniq | wc -l
