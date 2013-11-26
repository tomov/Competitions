@echo off
:begin
dgen
1325Dirt < sgsdf.txt > out1
dijk-heap-bin < sgsdf.txt > out2
type out1
fc out1 out2
if ERRORLEVEL == 1 goto end
goto begin
:end