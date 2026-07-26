#!/bin/bash

# Exit on error
set -e

if [ -z "$1" ]; then
  echo "Usage: ./run_analysis.sh <path_to_dataset.csv>"
  exit 1
fi

DATASET=$1

echo "=================================================="
echo "          POLYDATA ENGINE RUNNING               "
echo "=================================================="

# Step 1: Compile and Run C++ Profiler
echo "Building C++ Ingestion Module..."
g++ -O3 src/data_ingest.cpp -o src/data_ingest
./src/data_ingest "$DATASET"

# Step 2: Run Python EDA & Plotting
python3 src/analysis_engine.py "$DATASET"

# Step 3: Run R Statistical Engine
Rscript src/stats_engine.R "$DATASET"

echo "=================================================="
echo "  ANALYSIS COMPLETE! Check the 'output/' folder.  "
echo "=================================================="
