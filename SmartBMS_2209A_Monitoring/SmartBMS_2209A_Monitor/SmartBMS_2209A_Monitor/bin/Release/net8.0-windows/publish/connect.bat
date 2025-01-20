@echo off
setlocal
set script_dir=%~dp0
set xml_file=wifi.xml
set profile_name=Ottomotive_BMS
netsh wlan add profile filename="%script_dir%%xml_file%"
netsh wlan connect name="%profile_name%"
for /f "tokens=2 delims=:" %%i in ('netsh wlan show interfaces ^| findstr /r /c:"SSID" ^| findstr /v /c:"BSSID"') do (
    set "SSID=%%i"
)
set SSID=%SSID:~1%
echo %SSID%
:end