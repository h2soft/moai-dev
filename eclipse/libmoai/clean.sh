#!/bin/bash
rm -rf libs
rm -rf obj

cd ../libcrypto
./clean.sh

echo Build cleaned.