@echo off
:begin
egen > in
expr < in > out1
exb < in > out2
type out1
type out2
fc out1 out2
if ERRORLEVEL == 1 goto end
goto begin
:end