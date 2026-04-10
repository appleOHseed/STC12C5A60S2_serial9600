@echo off
PATH = C:\Windows\System32;D:\cygwin64;D:\Program Files\SDCC\bin;%PATH%
REM set src=test8051 REM set src=stc15wINterupt REM set src=LEDBlink
REM set src=LEDcounter REM set src=UARTSerial REM set src=SentHello
REM set src=stc15wBLINK	REM set src=15W408LED   REM set src=15W408LED
REM set src=STC12C5A60S2 REM set src=Seri12C5A60S2
set src=stc12Sent
@echo on
sdcc %src%.c
@echo off
if %ERRORLEVEL% equ 0 (GOTO END)
timeout 999
REM timeout /T 999

:END
echo.
echo エラーは有りません。
@echo off
set bk=back
if exist %src%.asm (move %src%.asm %bk% > NUL)
if exist %src%.lk  (move %src%.lk  %bk% > NUL)
if exist %src%.lst (move %src%.lst %bk% > NUL)
if exist %src%.map (move %src%.map %bk% > NUL)
if exist %src%.mem (move %src%.mem %bk% > NUL)
if exist %src%.rel (move %src%.rel %bk% > NUL)
if exist %src%.sym (move %src%.sym %bk% > NUL)
if exist %src%.hex (move %src%.hex %bk% > NUL)
if exist %src%.ihx (ren %src%.ihx %src%.hex > NUL)
timeout 3
REM timeout /T 3
