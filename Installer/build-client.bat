@echo off
FOR /F "tokens=* USEBACKQ" %%F IN (`git rev-list --count HEAD`) DO (
SET REVISION=%%F
)

cd nsis
makensis.exe /DVERSION=1.0.0.DEV /DREVISION=%REVISION% ../installer-client.nsi
cd ..
