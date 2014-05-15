@echo off
cl /W4 /Ox /MD /wd4100 /nologo for_each_process.cc for_each_process.def "/IC:\Program Files (x86)\Windows Kits\8.1\Debuggers\inc" /link /dll "C:\Program Files (x86)\Windows Kits\8.1\Debuggers\lib\x86\engextcpp.lib" /out:for_each_process.dll
