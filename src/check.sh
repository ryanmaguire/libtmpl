#!/bin/bash
ref="window_functions/tmpl_coss_double.c"

# Get the first 18 lines of the reference file
ref_head=$(head -n 18 "$ref")

# Recursively find files and compare
find . -type f ! -path "$ref" | while read -r file; do
    # Get first 18 lines of current file
    file_head=$(head -n 18 "$file")

    # Compare with reference
    if [[ "$file_head" != "$ref_head" ]]; then
        echo "$file"
    fi
done
