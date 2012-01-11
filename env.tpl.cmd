@echo off

rem
rem Initialize GCC environment. By default, it is assumed that GCC
rem can be found in PATH.
rem
rem call gcc446.cmd
rem 
rem Some GCC environment scripts may incorrectly set BUILD_PLATFORM
rem to a value confusing recent kBuilds so that it needs to be reset.
rem
rem set BUILD_PLATFORM=

rem
rem Cause kBuild to print all executed commands.
rem 
rem set KBUILD_VERBOSE=2

