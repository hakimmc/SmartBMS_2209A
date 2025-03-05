@echo off
setlocal EnableDelayedExpansion
set RULE_NAME=OTTOMOTIVE_BMS
set PORT_NUMBER=5166

:: Check Is Rule Exist
netsh advfirewall firewall show rule name="%RULE_NAME%" > nul 2>&1
if not errorlevel 1 (
    echo The rule "%RULE_NAME%" already exists.
    goto :EOF
)

:: If Rule Not Available, Add It
netsh advfirewall firewall add rule name="%RULE_NAME%" dir=in action=allow protocol=TCP localport=%PORT_NUMBER%
echo The rule "%RULE_NAME%" has been added successfully.
endlocal
