#!/bin/bash

# Specifying storage engines to be used for benchmarking
STORAGE_ENGINES=( "sqlite3" )

# Sizes of test workloads to be used for running the benchmarking on
# WORKLOAD_SIZES=( 100 1000 10000 100000 )
WORKLOAD_SIZES=( 5000 )

# Path for outputting the benchmarking metrics (Speed and Throughput)
BENCHMARKING_METRICS_PATH="./metrics/benchmarking"

# Preparing a corresponding directory for the output

mkdir -p $BENCHMARKING_METRICS_PATH

# Running the benchmarking and outputting to a file (With additional cleanup of previous benchmarks)

echo "Benchmarking speed and throughput"

for se in "${STORAGE_ENGINES[@]}"
do
  echo -e "\nStorage Engine:"
  echo "$se" | awk '{print toupper($0)}'

  mkdir -p "$BENCHMARKING_METRICS_PATH/$se"

  for ws in "${WORKLOAD_SIZES[@]}"
  do
    echo "Workload Size: $ws"

    rm -rf "$BENCHMARKING_METRICS_PATH/$se/$ws"

    "./build/bin/bench_$se" config.json $ws yes 0 > "$BENCHMARKING_METRICS_PATH/$se/$ws"

    echo
  done

  echo -e "---------------------------------------------------------"
done

echo "Finished benchmarking all storage engines"
