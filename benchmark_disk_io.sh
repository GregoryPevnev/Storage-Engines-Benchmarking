#!/bin/bash

STORAGE_ENGINE="$1"

case $STORAGE_ENGINE in

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

  # TODO: Remove
  mock)
    echo "Mock Storage Engine"
    TARGET="./build/bin/bench_mock"
    ;;

  *)
    echo "INVALID STORAGE ENGINE PROVIDED"
    exit 1
    ;;
esac

echo "Benchmarking disk IO"

rm -rf ./disk_info

# Note: Waiting for 3s for IO-Snoop to start up
sleep 3 && ./$TARGET benchmark_config.json && echo "DONE (Can close)" &

iosnoop -p $! > ./disk_info

