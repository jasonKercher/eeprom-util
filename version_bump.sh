#!/bin/bash

if [ -z "$1" ]; then
    find . \( -name '*.cpp' -o -name '*.h' -o -name '*.ino' \) -exec head -1 {} +
    exit 0
fi

version="$1"

while read -r src_file; do
    grep -v '^/\*\* VERSION.* \*\*/$' "$src_file" > "${src_file}.stripped"
    echo "/** VERSION $version **/" > "${src_file}.header"
    cat "${src_file}.header" "${src_file}.stripped" > "$src_file"
    rm "${src_file}.header" "${src_file}.stripped"
done < <(find . \( -name '*.cpp' -o -name '*.h' -o -name '*.ino' \))
