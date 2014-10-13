
/* appdefs.h	    Created:	1995-02-09  Revised:   1995-03-08	*/

/* Module Definition Header						*/

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



/************************************************************************/
/************************************************************************/
/*	Structure Definitions						*/
/************************************************************************/
/************************************************************************/


typedef	struct _QUEINFO
   {
   PSZ	       pszName;		   /* Device Name			*/
   PSZ	       pszDriverName;	   /* Driver Name			*/
   PSZ	       pszPrinters;	   /* Printers				*/
   PVOID       pDriverData;	   /* Device Data			*/
   } QUEINFO ;		   /* quei */

typedef	QUEINFO	*PQUEINFO; /* pquei */

typedef	struct _PRN
   {
   HAB		hAB;		   /* Anchor block for list		*/
   CHAR		szQueue[256];	   /* Default Queue			*/
   INT		iQueue;		   /* Selected Printer Index		*/
   INT		cQueues;	   /* Total Queue Count			*/
   PQUEINFO	pquei;		   /* Queue Information			*/
   } PRN ;		   /* prn */

typedef	PRN *PPRN;	   /* pprn */

/* --- Font Selection Structure	Definitions ---------------------------	*/

typedef	struct _FONTSEL		       /* fsel */
   {
   LONG	  lMatch;		       /* Font Match Number		*/
   BOOL	  fFixed;		       /* Fixed	Size Flag		*/
   LONG	  lPointSize;		       /* Font Point Size		*/
   LONG	  lNominalPointSize;	       /* Nominal Font Point Size	*/
   CHAR	  szFacename[32];	       /* Font Face Name		*/
   } FONTSEL ;

typedef	FONTSEL	*PFONTSEL;

typedef	struct _FONTSIZE	       /* fsiz */
   {
   PSZ	  pszSize;		       /* Font Match Number		*/
   LONG	  lPointSize;		       /* Font Point Size		*/
   } FONTSIZE ;

#define	TWIPS_POINT    20L

/* --- Re-entrant Printer Support -------------------------------------	*/

typedef	struct _PRNDATA
   {
   PRN	    prn;		       /* Printer Information		*/
   FONTSEL  fsel;		       /* Font Selection		*/
   LONG	    cPrnFiles;		       /* Files	Count			*/
   BOOL	    fLineNumbers;	       /* Include Line Numbers Flag	*/
   BOOL	    fDateFooter;	       /* Date and Time	Footer Flag	*/
   CHAR	    szTitle[CCHMAXPATH];       /* Print	Title			*/
   CHAR	    aszFiles[1][CCHMAXPATH];   /* Files	Array Start		*/
   } PRNDATA ;		   /* prni */

#define	PRNDATASIZE (sizeof(PRNDATA) - CCHMAXPATH)

typedef	PRNDATA	*PPRNDATA;

#define	TAB 9			   /* Tab Stop Value			*/
#define	LF 10			   /* Line Feed	Value			*/
#define	CR 13			   /* Carriage Return Value		*/
#define	TOF 12			   /* Top of Form Value			*/
#define	EOF_MARK 26		   /* End of File Mark Value		*/
#define	ESCAPE 27		   /* Escape Value			*/
#define	TOP_MARGIN 4		   /* Printout Top Margin Count		*/

/************************************************************************/
/************************************************************************/
/*	Global Variable	Definitions					*/
/************************************************************************/
/************************************************************************/

extern FONTMETRICS fm;		   /* Font Metrics Info			*/
extern HSWITCH	   hSwitch;	   /* Task List	Entry Handle		*/
extern HAB	   hAB;		   /* Program Anchor Block Handle	*/

extern HPOINTER	   hptrWait;	   /* Wait Mouse Pointer Handle		*/
extern HPOINTER	   hptrArrow;	   /* Arrow Mouse Pointer Handle	*/

extern HMQ  hmqPrnSetup;	   /* Program Message Queue Handle	*/
extern HWND hwndPrnSetup;	   /* Client Window Handle		*/
extern HWND hwndPrnSetupFrame;	   /* Frame Window Handle		*/
extern HWND hmenuPrnSetup;	   /* Menu Handle			*/

extern HWND hwndHelp;		   /* Help Window Handle		*/
extern HELPINIT	helpinit;	   /* Help Initialization Table		*/

extern PRN  prn;		   /* Printer Control Holder		*/


/************************************************************************/
/************************************************************************/
/*	Function Prototype Definitions					*/
/************************************************************************/
/************************************************************************/

VOID	InitApp(HWND hwndFrame,	HWND hwndClient, PSZ pszWindowListTitle);
HWND	CreateStdWindow(HWND hwndParent, ULONG flStyle,	ULONG flCreateFlags,
			PSZ pszClientClass, PSZ	pszTitle, ULONG	styleClient,
			HMODULE	hmod, ULONG idResources, PHWND phwndClient,
			LONG x,	LONG y,	LONG cx, LONG cy);
MRESULT	PDSKeyProc(HWND	hWnd, ULONG msg, MPARAM	mp1, MPARAM mp2);
VOID	PDSGetTemplate(HWND hWnd, ULONG	id);

MRESULT	EXPENTRY PrintDriverWndProc(HWND hWnd, ULONG msg, MPARAM mp1, MPARAM mp2);

BOOL	PrnCreatePrinterList(PPRN pprn);
BOOL	PrnDestroyPrinterList(PPRN pprn);
HDC	PrnOpenDC(PPRN pprn, PSZ pszDataType);
BOOL	PrnQueryJobProperties(PPRN pprn, INT iQueue);
PSZ	PrnQueryPrinterName(PPRN pprn);
MRESULT	EXPENTRY PrnSetupDlgProc(HWND hWnd, ULONG msg, MPARAM mp1, MPARAM mp2);
MRESULT	EXPENTRY FilePrintDlgProc(HWND hWnd, ULONG msg,	MPARAM mp1, MPARAM mp2);
BOOL EXPENTRY PDSText3DRegister(HAB hAB);
BOOL EXPENTRY PDSFrame3DRegister(HAB hAB);
BOOL EXPENTRY PDSFontSelRegister(HAB hAB);
BOOL EXPENTRY PDSDirListRegister(HAB hAB);
