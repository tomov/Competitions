@copy nim1.in nim.in
@copy nim1.in nim_jury.txt
:test
nim <nim.in >nim.out
nim_jury <nim.out >nim.in
@if errorlevel==3 goto jurywins
@if errorlevel==2 goto playerwins
@if errorlevel==1 goto wrongmove
@goto test
:wrongmove
@echo Gre6en hod
@goto end
:playerwins
@echo Igra4a pe4eli
@goto end
:jurywins
@echo Jurito pe4eli
@goto end
:end
@pause