#!/usr/bin/env bash
echo -ne "/usr/local/lib" > /etc/ld.so.conf.d/opencv.conf
ldconfig -v
