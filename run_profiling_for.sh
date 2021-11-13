#!/bin/bash

PROFILING_METRICS_PATH="./metrics/profiling"

STORAGE_ENGINE="$1"

case $STORAGE_ENGINE in

  mock)
    echo "Mock Storage Engine"
    TARGET="./build/bin/bench_mock"
    ;;

  sqlite3)
    echo "SQLite3"
    TARGET="./build/bin/bench_sqlite3"
    ;;

  forestdb)
    echo "ForestDB"
    TARGET="./build/bin/bench_forestdb"
    ;;

  leveldb)
    echo "LevelDB"
    TARGET="./build/bin/bench_leveldb"
    ;;

  *)
    echo "INVALID STORAGE ENGINE PROVIDED"
    exit 1
    ;;
esac

WORKLOAD="$2"

if [ -z "$WORKLOAD" ]
  then
    echo "INVALID WORKLOAD SUPPLIED"
    exit 1
fi

echo "Profiling disk IO"

mkdir -p "$PROFILING_METRICS_PATH/$STORAGE_ENGINE"

rm -rf "$PROFILING_METRICS_PATH/$STORAGE_ENGINE/$WORKLOAD"

# Waiting for 10s for IO-Snoop to start up
./$TARGET config.json $WORKLOAD no 10 &

iosnoop -p $! > "$PROFILING_METRICS_PATH/$STORAGE_ENGINE/$WORKLOAD"