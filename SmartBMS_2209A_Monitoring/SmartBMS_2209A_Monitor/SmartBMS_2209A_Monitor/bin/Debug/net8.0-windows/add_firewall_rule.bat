@echo off
setlocal EnableDelayedExpansion
set RULE_NAME=BMS_TCP_Connection
set PORT_NUMBER=5156
netsh advfirewall firewall show rule name="%RULE_NAME%" > nul
if not errorlevel 1 (
    netsh advfirewall firewall delete rule name="%RULE_NAME%"
)
netsh advfirewall firewall add rule name="%RULE_NAME%" dir=in action=allow protocol=TCP localport=%PORT_NUMBER%
endlocal