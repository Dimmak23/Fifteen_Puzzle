#1.
Go in the console to the next folder: [Where Qt installed]\Qt\6.3.1\mingw_64\bin

pass to the windeployqt.exe next arguments:
windeployqt.exe --dir [PATH_TO_DEPLOY] --compiler-runtime --release --qmldir [PATH_TO_QML] [TO_DEPLOY_EXE] 

where:
	- [PATH_TO_DEPLOY]: an empty folder where you would like the dependencies to be copied
	- [PATH_TO_QML]: the folder where you have your qml files
	- [TO_DEPLOY_EXE]: path to your executable in format - [PATH]\<name>.exe

====>ISSUE

message from console:
Unable to find the platform plugin.

<----SOLUTION

remove '--release' from command

#2.
Add <name>.exe to the [PATH_TO_DEPLOY]

#3.
Run executable to check.

====>ISSUE

On some machines next error appear, message from console:
libgcc_s_seh-1.dll - missing

<----SOLUTION

add such dll from: [Where Qt installed]\Qt\6.3.1\mingw_64\bin
to the: [PATH_TO_DEPLOY].

#4.
Run executable to check.

====>ISSUE

On some machines next error appear, message from console:
The application was unable to start correctly (0xc000007b).
Click OK to close the application.

<----SOLUTION

Run dependancy walker and find any 32bit DLL's that could be linked
to our 64bit executable.
In our case it is:
libgcc_s_dw2-1.dll
libstdc++-6.dll
libwinpthread-1.dll

Replace them in the [PATH_TO_DEPLOY] with the same named ones from [Where Qt installed]\Qt\6.3.1\mingw_64\bin.

<++++PROGRESS

libgcc_s_dw2-1.dll	DIDN'T REPLACED
libstdc++-6.dll		REPLACED
libwinpthread-1.dll	REPLACED

<0---RESULT

Application is running on all tested machines (Windows 10, 64bit).