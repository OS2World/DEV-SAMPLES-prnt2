#pragma	title("Printer Driver  --  Version 2  --  (Print.C)")
#pragma	subtitle("   main Entry Poiint - Interface Definitions")

#pragma	info(noext, nopar)

#define	INCL_DOS		   /* Include OS/2 DOS Kernal		*/
#define	INCL_WIN		   /* Include OS/2 PM Windows Interface	*/

#include <os2.h>

#include "appdefs.h"
#include "prnsetup.h"

/* This	module contains	main function for the Print Driver application.	*/

/* The executable is created using the following options:		*/
/*									*/
/* Option	       Value						*/
/* ------	       -----						*/
/* Op Sys	       OS/2 PM Executable				*/
/* Optimization	       Maximize						*/
/* Compile Type	       Subsystem					*/
/* CPU		       80486						*/
/* Warning Level       3						*/
/*									*/
/* Equivalent command line invocation:					*/
/*									*/
/*  Icc	-C -G4 -O+ -Rn -W3 Print.C		  IBM C	Set++		*/
/*  BCC	-Ox -v-	-w -c Print.C			  Borland C++ for OS/2	*/
/*  Wcl386 -c -ms -4s -s -ox -zp4 -w3 Print.C	  WATCOM C/C++		*/

/* Filename:   Print.C							*/

/*  Version:   1							*/
/*  Created:   1995-03-07						*/
/*  Revised:   1995-03-07						*/

/* Routines:   int main( );						*/

/************************************************************************/
/************************************************************************/
/************************************************************************/
/* DISCLAIMER OF WARRANTIES:						*/
/* -------------------------						*/
/* The following [enclosed] code is sample code	created	by IBM		*/
/* Corporation and Prominare Inc.  This	sample code is not part	of any	*/
/* standard IBM	product	and is provided	to you solely for the purpose	*/
/* of assisting	you in the development of your applications.  The code	*/
/* is provided "AS IS",	without	warranty of any	kind.  Neither IBM nor	*/
/* Prominare shall be liable for any damages arising out of your	*/
/* use of the sample code, even	if they	have been advised of the	*/
/* possibility of such damages.						*/
/************************************************************************/
/************************************************************************/
/************************************************************************/
/*		       D I S C L A I M E R				*/
/* This	code is	provided on an as is basis with	no implied support.	*/
/* It should be	considered freeware that cannot	be rebundled as		*/
/* part	of a larger "*ware" offering without our consent.		*/
/************************************************************************/
/************************************************************************/
/************************************************************************/

/* Copyright ¸ International Business Machines Corp., 1995.		*/
/* Copyright ¸ 1995  Prominare Inc.  All Rights	Reserved.		*/

/* --------------------------------------------------------------------	*/

PSZ pszPrnSetupClassName = (PSZ)"PrnSetup";


INT main(INT argc, CHAR	*argv[ ])

{
QMSG  qmsg;			   /* PM Message Queue Holder		*/

		       /* Initialize the program for PM	and create the	*/
		       /* message queue					*/

hmqPrnSetup = WinCreateMsgQueue(hAB = WinInitialize(0UL), 0L);

		       /* Register the window class			*/

if ( !WinRegisterClass(hAB, pszPrnSetupClassName, (PFNWP)PrintDriverWndProc,
		       CS_SYNCPAINT | CS_SIZEREDRAW, 0UL) )
   return(0);
		       /* Create the main program window		*/

if ( !(hwndPrnSetupFrame = CreateStdWindow(HWND_DESKTOP, WS_VISIBLE,
					   FCF_NOBYTEALIGN | FCF_TASKLIST |
					   FCF_TITLEBAR	| FCF_ICON |
					   FCF_SYSMENU | FCF_MENU | FCF_MINMAX |
					   FCF_SIZEBORDER,
					   pszPrnSetupClassName, (PSZ)"Print Font Example", 0L,
					   (HMODULE)NULL, WIN_PRINTDRIVER, &hwndPrnSetup, 16, 147, 203,	97)) )
   return(0);


InitApp(hwndPrnSetupFrame, hwndPrnSetup, "Print Font Example");

		       /* Create Help instance and associate it	with	*/
		       /* the programs frame window			*/

if ( (hwndHelp = WinCreateHelpInstance(hAB, &helpinit))	!= (HWND)NULL )
   WinAssociateHelpInstance(hwndHelp, hwndPrnSetupFrame);

		       /* Get default printer to use			*/

if ( PrnCreatePrinterList(&prn)	)
   prn.hAB = hAB;
		       /* Get and dispatch the message to program	*/
		       /* windows					*/

while (	WinGetMsg(hAB, &qmsg, (HWND)NULL, 0UL, 0UL) )
   WinDispatchMsg(hAB, &qmsg);

		       /* Destroy the printer list			*/
if ( prn.hAB !=	0UL )
   PrnDestroyPrinterList(&prn);

		       /* Destroy the Help instance associated with the	*/
		       /* the programs frame window			*/

if ( hwndHelp )
   {
   WinAssociateHelpInstance((HWND)NULL,	hwndPrnSetupFrame);
   WinDestroyHelpInstance(hwndHelp);
   }

		       /* Have received	a WM_QUIT, start the program	*/
		       /* shutdown by destroying the program windows	*/
		       /* and destroying the message queue		*/

WinDestroyWindow(hwndPrnSetupFrame);

WinDestroyMsgQueue(hmqPrnSetup);

		       /* Notify PM that main program thread not needed	*/
		       /* any longer					*/
WinTerminate(hAB);
		       /* Exit back to OS/2 cleanly			*/
return(0);
}
