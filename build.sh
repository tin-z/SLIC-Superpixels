#!/usr/bin/env bash
g++ test_slic.cpp slic.cpp -o slic `pkg-config --cflags --libs opencv`
