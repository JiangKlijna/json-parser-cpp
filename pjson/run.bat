@echo off
make
set result=%ERRORLEVEL%
if %result% equ 0 (
	main
	del *.o
	del main.exe
)
