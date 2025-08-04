#!/bin/bash

# Define the binary path
BINARY="./build/bin/softadastra_main"

# Check if the binary exists
if [ -f "$BINARY" ]; then
    echo "🚀 Launching adastra_main..."
    $BINARY
else
    echo "❌ Binary not found: $BINARY"
    echo "👉 Please compile first using ./build_prod.sh or ./build_dev.sh"
fi
