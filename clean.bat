@echo off
rem Author: Siddhartha Tiwari [201851127@iiitvadodara.ac.in]
rem Date: May 28th 2020
rem Execute this file on windows to clean the residual files created by different programs while execution in this project
rem Add accordingly, to this batch file, the files you want to remove.

cd CPP
Set "condition=0"
IF EXIST *.txt (
    Set condition=1
)
IF EXIST *.log (
    Set condition=1
)
IF EXIST *.exe (
    Set condition=1
)
IF %condition% EQU 1 (
    del *.txt *.log *.exe /f /q
)

cd ..
cd CLIENT
Set "condition=0"
IF EXIST *.txt (
    Set condition=1
)
IF EXIST *.log (
    Set condition=1
)
IF EXIST *.exe (
    Set condition=1
)
IF %condition% EQU 1 (
    del *.txt *.log *.exe /f /q /s
)

cd ..
cd SERVER
Set "condition=0"
IF EXIST *.txt (
    Set condition=1
)
IF EXIST *.log (
    Set condition=1
)
IF EXIST *.exe (
    Set condition=1
)
IF %condition% EQU 1 (
    del *.txt *.log *.exe /f /q
)

cd ..