#!/bin/bash

echo "Mini Tester for Mini Assignment 5"
echo ""

#################################
echo "**Testing to see if report.c is compileable**"
echo "gcc -o report report.c"
gcc -o report report.c
echo "exit code: "$?
echo ""

#################################
echo "**Testing number of arguments**"
echo "./report data.csv"
./report data.csv
echo "exit code: "$?
echo ""

#################################
echo "**Testing to see if data file is readable**"
echo "./report nosuchdata.csv \"Jane Doe\" rpt.txt"
./report nosuchdata.csv "Jane Doe" rpt.txt
echo "exit code: "$?
echo ""

#################################
echo "**Testing to see if user is present in csv file**"
echo "./report data.csv \"Jane Doe\" rpt.txt"
./report data.csv "Jane Doe" rpt.txt
echo "exit code: "$?
echo ""

#################################
echo "**Testing to see if output file can be created**"
echo "./report data.csv \"Markus Bender\" rpt.txt"
./report data.csv "Markus Bender" rpt.txt
echo "exit code: "$?
echo ""

#################################
echo "**Testing Outputs - (Test 1) - no collaborators**"
echo "./report data.csv \"Markus Bender\" rpt.txt"
./report data.csv "Markus Bender" rpt.txt
echo "exit code: "$?
echo "-> cat rpt.txt"
cat rpt.txt
echo ""

#################################
echo "**Testing Outputs - (Test 2) - collaborators found**"
echo "./report data.csv \"Adaline Murphy\" rpt.txt"
./report data.csv "Adaline Murphy" rpt.txt
echo "exit code: "$?
echo "-> cat rpt.txt"
cat rpt.txt
echo ""

echo "Testing complete."
exit 0;
