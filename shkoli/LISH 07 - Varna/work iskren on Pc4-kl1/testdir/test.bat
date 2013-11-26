@echo off
time < tt
%1.exe < %1.%2.in > %1.%2.m
time < tt
fc %1.%2.m %1.%2.sol

