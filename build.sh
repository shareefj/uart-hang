#!/usr/bin/env bash
set -x
set -e

git submodule update --init --recursive
make -C libopencm3
make -C src clean all

echo "Starting Renode - test will hang within 10 seconds"
renode -e "i @test.resc; s"

