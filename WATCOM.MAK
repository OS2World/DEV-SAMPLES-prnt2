
# MAKE file for WATCOM.MAK     Release 5

# Revised:  1995-03-01

# Copyright ¸ 1987-1995  Prominare Inc.

# MAKE file created by Prominare Builder  Release 5

# Macro definitions

C_SW=-c -ms -4s -s -ox -zp4 -w3 
RC_SW=-r 


Print.Exe: AppDefs.Obj FilePrn.Obj Print.Obj\
        Print.Res PrnAPI.Obj PrnWnd.Obj\
        Support.Obj
 WLink @WATCOM.Lnk
 rc Print.Res Print.Exe

AppDefs.Obj: AppDefs.C
 Wcl386 $(C_SW) -Fo$*.Obj AppDefs.C

FilePrn.Obj: FilePrn.C
 Wcl386 $(C_SW) -Fo$*.Obj FilePrn.C

Print.Obj: Print.C
 Wcl386 $(C_SW) -Fo$*.Obj Print.C

Print.Res: Print.Rc
 Rc $(RC_SW) Print.Rc $*.Res

PrnAPI.Obj: PrnAPI.C
 Wcl386 $(C_SW) -Fo$*.Obj PrnAPI.C

PrnWnd.Obj: PrnWnd.C
 Wcl386 $(C_SW) -Fo$*.Obj PrnWnd.C

Support.Obj: Support.C
 Wcl386 $(C_SW) -Fo$*.Obj Support.C

