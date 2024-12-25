@echo off
setlocal

REM XML dosyasının bulunduğu dizini al
set script_dir=%~dp0

REM XML dosyasının adı
set xml_file=wifi.xml

REM Profil adı
set profile_name=Ottomotive

REM XML dosyasını kullanarak profili ekle
netsh wlan add profile filename="%script_dir%%xml_file%"

REM Wi-Fi ağına bağlan
netsh wlan connect name="%profile_name%"

REM Bağlı olunan Wi-Fi ağının adını almak için netsh komutunu çalıştır
for /f "tokens=2 delims=:" %%i in ('netsh wlan show interfaces ^| findstr /r /c:"SSID" ^| findstr /v /c:"BSSID"') do (
    set "SSID=%%i"
)

REM SSID'nin başındaki ve sonundaki boşlukları temizle
set SSID=%SSID:~1%

REM Bağlı olunan Wi-Fi ağını yazdır
echo %SSID%

:end