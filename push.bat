@echo off

set isPush="true"

call:check '%1' "git add ?"
call:check '%2' "git commit -m ?"
if %isPush%=="true" (
	call:push %1 %2 %3 %4
)

goto :eof

:check
	if %~1=='' (
		echo %~2
		set isPush=""
	)
goto :eof

:push
	git add "%~1"
	git commit -m "%~2"
	git push
	if not "%~3"=="" if not "%~4"=="" (
		rem ouput git username
		%~3
		rem ouput git password
		%~4
	)
goto :eof
