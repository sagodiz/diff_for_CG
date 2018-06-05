@ECHO OFF
SETLOCAL

:: script global variables
SET file=%1

FOR %%i IN ("%file%") DO (
SET filename=%%~ni
)

echo %file%

 python convert-graph-formats.py  -i graphml -o json %file% %filename%.json

EXIT /B 0