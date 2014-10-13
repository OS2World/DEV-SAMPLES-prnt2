#pragma	title("Printer Driver  --  Version 2  --  (AppDefs.C)")
#pragma	subtitle("   Application Definitions - Interface Definitions")

#pragma	info(noext)

#define	INCL_WIN		   /* Include OS/2 PM Windows Interface	*/

#include <os2.h>

#include "appdefs.h"
#include "prnsetup.h"

/* This	module contains	global variable	definitions for	the printer	*/
/* driver sample code.							*/

/* Filename:   AppDefs.C						*/

/*  Version:   2							*/
/*  Created:   1991-02-28						*/
/*  Revised:   1994-03-07						*/

/* Routines:   None							*/

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

FONTMETRICS fm;			   /* Font Metrics Info			*/
HAB	    hAB;		   /* Program Anchor Block Handle	*/
HSWITCH	    hSwitch;		   /* Task List	Entry Handle		*/

HPOINTER    hptrWait;		   /* Wait Mouse Pointer Handle		*/
HPOINTER    hptrArrow;		   /* Arrow Mouse Pointer Handle	*/

HMQ  hmqPrnSetup;		   /* Program Message Queue Handle	*/
HWND hwndPrnSetup;		   /* Client Window Handle		*/
HWND hwndPrnSetupFrame;		   /* Frame Window Handle		*/
HWND hmenuPrnSetup;		   /* Menu Handle			*/

HWND hwndHelp;			   /* Help Window Handle		*/
HELPINIT helpinit = {
   sizeof(HELPINIT),		   /* Count of Bytes in	Structure	*/
   0L,				   /* Return Value from	Help Manager	*/
   NULL,			   /* Pointer to Tutorial Name		*/
   (PHELPTABLE)
   MAKELONG(HID_APP, 0xffff),	   /* Resource ID for Help Table	*/
   0,				   /* Handle for Help Table		*/
   0,				   /* Handle for Replacement Menu	*/
   0,				   /* Replacement Accelerator ID	*/
   0,				   /* Replacement Menu ID		*/
   "Print Driver Help",		   /* Help-Window Title			*/
   CMIC_HIDE_PANEL_ID,		   /* Display Help Title Only		*/
   "PrnSetup.Hlp" };		   /* Path to Help Library		*/

PRN    prn;			   /* Printer Control Holder		*/
