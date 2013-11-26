@echo off
echo. | time
trade.exe < login > log
echo. | time
fc log logout
