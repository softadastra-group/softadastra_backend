#!/bin/bash

echo "🧪 Running tests..."

# Executable paths
INTEGRATION="./build/bin/adastra_tests"
UNIT="./build/bin/adastra_unittests"

# Integration tests
if [ -f "$INTEGRATION" ]; then
    echo "➡️ Running integration tests:"
    $INTEGRATION
else
    echo "❌ File not found: $INTEGRATION"
fi

# Unit tests
if [ -f "$UNIT" ]; then
    echo "➡️ Running unit tests:"
    $UNIT
else
    echo "❌ File not found: $UNIT"
fi
