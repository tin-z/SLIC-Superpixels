#!/usr/bin/env python3
import os, sys, re, subprocess
import time

## Config
K_sizes = [300, 600, 1000]
M_param = 40

times = { x:0 for x in K_sizes }

folder_samples = "images"
samples = [ "{}/{}".format(folder_samples, sample) for sample in os.listdir(folder_samples) if sample.endswith(".jpg") ]
rets = subprocess.getoutput("./build.sh")

## Benchmark
for k in K_sizes :
  cc = 0.

  for sample in samples :
    rets = subprocess.getoutput("./slic {} {} {} foo".format(sample, k, M_param))
    rets = [ float(x.split(":")[1]) for x in rets.split("\n") if x.startswith("Time") ]
    assert len(rets) == 1
    cc += rets[0]

    #break

  cc /= len(samples)
  times[k] = cc
  print("  done K:{} result:{:.2f}".format(k, times[k]))
  
  #break


## Print results
print("\n                       K:300       K:600      K:1000")
print("Result arch:{}      ".format("gpu") + "{:.2f}     {:.2f}      {:.2f}".format(*times.values()))

