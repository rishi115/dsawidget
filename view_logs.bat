@echo off
echo ========================================
echo DSA Widget Debug Logs
echo ========================================
echo.
echo Clearing old logs...
adb logcat -c
echo.
echo Starting log viewer...
echo Press Ctrl+C to stop
echo.
echo ========================================
echo.
adb logcat -s DSAWidget:D flutter:I
