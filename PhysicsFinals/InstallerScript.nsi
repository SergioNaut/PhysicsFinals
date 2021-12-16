OutFile "Finals_installer.exe"

Installdir $DESKTOP\FinalsSergioGolbert

Section

CreateDirectory $INSTDIR\Assets
CreateDirectory $INSTDIR\Project

#This should grab all files from MyDeploymentFolder
CopyFiles $EXEDIR\MyDeploymentFolder\Assets\*.* $INSTDIR\Assets
CopyFiles $EXEDIR\MyDeploymentFolder\ProjectDeployFolder\*.* $INSTDIR\Project

WriteUninstaller "$INSTDIR\Finals_uninstaller.exe"

SectionEnd

#Uninstaller section
Section "Uninstall"

RMDIR /r $INSTDIR

SectionEnd