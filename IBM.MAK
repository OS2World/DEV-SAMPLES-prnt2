
# MAKE file for PrnSetup.MAK     Release 5

# Revised:  1995-03-01

# Copyright ¸ 1987-1995  Prominare Inc.

# MAKE file created by Prominare Builder  Release 5

# Macro definitions

C_SW=-G4 -O+ -Rn -W3 -C 
RC_SW=-r 


Print.Exe: AppDefs.Obj FilePrn.Obj Print.Obj\
        Print.Res PrnAPI.Obj PrnWnd.Obj\
        Support.Obj
 Link386 /ALIGN:4 /BASE:0x00010000 /EXEPACK @IBM.Lnk;
 rc Print.Res Print.Exe

AppDefs.Obj: AppDefs.C
 ICC $(C_SW) -Fo$*.Obj AppDefs.C

FilePrn.Obj: FilePrn.C
 ICC $(C_SW) -Fo$*.Obj FilePrn.C

Print.Obj: Print.C
 ICC $(C_SW) -Fo$*.Obj Print.C

Print.Res: Print.Rc
 Rc $(RC_SW) Print.Rc $*.Res

PrnAPI.Obj: PrnAPI.C
 ICC $(C_SW) -Fo$*.Obj PrnAPI.C

PrnWnd.Obj: PrnWnd.C
 ICC $(C_SW) -Fo$*.Obj PrnWnd.C

Support.Obj: Support.C
 ICC $(C_SW) -Fo$*.Obj Support.C

