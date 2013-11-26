@echo off
del input
del login
del logout
del log
copy test%1 input
Vesu checker.exe trade.exe
echo.
