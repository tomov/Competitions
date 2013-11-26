@echo off
:begin
color_gen > in
color_ll < in > out1
MM_C < in > out2
type out1
type out2
fc out1 out2
if ERRORLEVEL == 1 goto end
goto begin
:end

