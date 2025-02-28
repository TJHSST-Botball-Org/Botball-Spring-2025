#!/bin/bash

# Source directory where modules are located
MODULES_DIR="./module"

# Destination directory for copying files
DEST_DIR="./include"

# Ensure the destination directory exists
mkdir -p "$DEST_DIR"

# Loop through each subdirectory in the modules directory
for MODULE_DIR in "$MODULES_DIR"/*; do
    # Check if it's a directory
    if [ -d "$MODULE_DIR/public/kipr" ]; then
        echo "Processing: $MODULE_DIR/public/kipr"

        # Copy all contents of the kipr directory to the destination
        cp -r "$MODULE_DIR/public/kipr"/* "$DEST_DIR/kipr"
    else
        echo "No kipr folder found in $MODULE_DIR/public"
    fi
done

echo "Copy operation completed. Files are in $DEST_DIR."
