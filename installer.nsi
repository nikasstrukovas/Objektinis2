
Outfile "Setup.exe"
InstallDir $PROGRAMFILES\VU\Nikas-Strukovas
RequestExecutionLevel admin

Section
    SetOutPath $INSTDIR
    File /r "C:\Users\Nikas\Documents\Objektinis installeris"
SectionEnd
