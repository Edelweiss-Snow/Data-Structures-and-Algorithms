#!/bin/bash
rm `ll | grep x | tail -4 | awk '{print $9}'`
