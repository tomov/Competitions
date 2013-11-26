@echo off
:begin
grgen > in
g < in > out1
groupb < in > out2
type out1
type out2
fc out1 out2
if ERRORLEVEL == 1 goto end
goto begin
:end