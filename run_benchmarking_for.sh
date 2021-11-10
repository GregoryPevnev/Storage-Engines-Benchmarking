#!/bin/bash

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

echo "Benchmarking speed and throughput with a workload of $WORKLOAD document(s)"

./$TARGET config.json $WORKLOAD yes 0