
# MAKE file for Borland.MAK     Release 5

# Revised:  1995-03-01

# Copyright ¸ 1987-1995  Prominare Inc.

# MAKE file created by Prominare Builder  Release 5

# Macro definitions

C_SW=-Ox -v- -w -c 
RC_SW=-r 


Print.Exe: AppDefs.Obj FilePrn.Obj Print.Obj\
        Print.Res PrnAPI.Obj PrnWnd.Obj\
        Support.Obj
 TLink @Borland.Lnk
 rc Print.Res PrnSetup.Exe

AppDefs.Obj: AppDefs.C
 BCC $(C_SW) -Fo$*.Obj AppDefs.C

FilePrn.Obj: FilePrn.C
 BCC $(C_SW) -Fo$*.Obj FilePrn.C

Print.Obj: Print.C
 BCC $(C_SW) -Fo$*.Obj Print.C

Print.Res: Print.Rc
 Rc $(RC_SW) Print.Rc $*.Res

PrnAPI.Obj: PrnAPI.C
 BCC $(C_SW) -Fo$*.Obj PrnAPI.C

PrnWnd.Obj: PrnWnd.C
 BCC $(C_SW) -Fo$*.Obj PrnWnd.C

Support.Obj: Support.C
 $(CC) $(C_SW)-Fo$*.Obj Support.C

