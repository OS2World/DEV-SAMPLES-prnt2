#pragma	title("Printer Driver  --  Version 2  --  (PrnWnd.C)")
#pragma	subtitle("   Application Window - Interface Definitions")

#pragma	info(noext)

#define	INCL_WIN		   /* Include OS/2 PM Windows Interface	*/

#include <os2.h>

#include "appdefs.h"
#include "prnsetup.h"

/* This	module contains	application window procedure.			*/

/* Filename:   PrnWnd.C							*/

/*  Version:   2							*/
/*  Created:   1995-03-07						*/
/*  Revised:   1995-03-08						*/

/* Routines:   MRESULT EXPENTRY	PrintDriverWndProc(HWND	hWnd,		*/
/*						   ULONG msg,		*/
/*						   MPARAM mp1,		*/
/*						   MPARAM mp2);		*/

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

#pragma	subtitle("   Client Window - Client Window Procedure")
#pragma	page( )

/* --- PrintDriverWndProc ------------------------------ [ Public ] ---	*/
/*									*/
/*     This function is	used to	process	the messages sent to the	*/
/*     applications client window.					*/
/*									*/
/*     Upon Entry:							*/
/*									*/
/*     HWND   hWnd; = Window Handle					*/
/*     ULONG  msg;  = PM Message					*/
/*     MPARAM mp1;  = Message Parameter	1				*/
/*     MPARAM mp2;  = Message Parameter	2				*/
/*									*/
/*     Upon Exit:							*/
/*									*/
/*     PrintDriverWndProc = Message Handling Result			*/
/*									*/
/* --------------------------------------------------------------------	*/

MRESULT	EXPENTRY PrintDriverWndProc(HWND hWnd, ULONG msg, MPARAM mp1, MPARAM mp2)

{
RECTL rcl;			    /* Window Rectangle			*/
HPS   hPS;			    /* Presentation Space Handle	*/


switch ( msg )
   {
			/* Window being	created, perform window		*/
			/* initialization				*/
   case	WM_CREATE :

       hptrWait	 = WinQuerySysPointer(HWND_DESKTOP, SPTR_WAIT,	FALSE);
       hptrArrow = WinQuerySysPointer(HWND_DESKTOP, SPTR_ARROW,	FALSE);

			/************************************************/
			/* PDSGetTemplate is used to allow controls in	*/
			/* windows.  Do	not remove this	function if you	*/
			/* intend to include controls within the window.*/
			/************************************************/

	PDSGetTemplate(hWnd, WIN_PRINTDRIVER);
	break;
			/* Process key press from keyboard		*/
   case	WM_CHAR	:
			/************************************************/
			/* PDSKeyProc is used to allow controls	in	*/
			/* windows.  Do	not remove this	function if you	*/
			/* intend to include controls within the window.*/
			/************************************************/

	return(PDSKeyProc(hWnd,	msg, mp1, mp2));
			/* Process control selections			*/
			/* Process menu	and button selections		*/
   case	WM_COMMAND :
	switch ( SHORT1FROMMP(mp1) )
	    {
	   case	IDM_PRINT :
	       WinDlgBox(HWND_DESKTOP, hwndPrnSetupFrame, (PFNWP)FilePrintDlgProc,
			 (HMODULE)NULL,	DLG_FILEPRN, NULL);
	       break;
	    case IDM_PRINTERSETUP :
		WinDlgBox(HWND_DESKTOP,	hwndPrnSetupFrame, (PFNWP)PrnSetupDlgProc,
			  (HMODULE)NULL, DLG_PRNSETUP, (PVOID)&prn);
		break;
	    }
	break;
			/* Erase window	background			*/

   case	WM_ERASEBACKGROUND :
	WinQueryWindowRect(hWnd, &rcl);
	WinFillRect((HPS)LONGFROMMP(mp1), &rcl,	SYSCLR_WINDOW);
	break;
			/* Paint client	window				*/
   case	WM_PAINT :
	hPS = WinBeginPaint(hWnd, (HPS)NULL, &rcl);
	WinFillRect(hPS, &rcl, SYSCLR_WINDOW);
	WinEndPaint(hPS);
	break;
			/* Window being	destroyed, perform clean-up	*/
			/* operations					*/
   case	WM_DESTROY :
	break;

			/* Default message processing			*/
   default :
       return(WinDefWindowProc(hWnd, msg, mp1, mp2));
   }
return(0L);
}
