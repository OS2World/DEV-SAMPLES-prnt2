#pragma title("Printer Driver  --  Version 2  --  (PrnAPI.C)")
#pragma subtitle("   Printer API's - Interface Definitions")

#pragma info(noext)

#define INCL_DEV                   /* Include OS/2 Device Interface     */
#define INCL_DOS                   /* Include OS/2 DOS Kernal           */
#define INCL_GPI                   /* Include OS/2 PM GPI Interface     */
#define INCL_SPL                   /* Include OS/2 PM Spooler Interface */
#define INCL_SPLDOSPRINT
#define INCL_WIN                   /* Include OS/2 PM Windows Interface */

#include <malloc.h>
#include <os2.h>
#include <string.h>

#include "appdefs.h"
#include "prnsetup.h"

/* This file contains the printer support functions that can be used    */
/* to select a printer, manipulate job properties, and open a DC        */
/* for printing.                                                        */

/* Filename:   PrnAPI.C                                                 */

/*  Version:   2                                                        */
/*  Created:   1995-02-09                                               */
/*  Revised:   1995-03-14                                               */

/* Routines:   BOOL PrnCreatePrinterList(PPRN pprn);                    */
/*             BOOL PrnDestroyPrinterList(PPRN pprn);                   */
/*             HDC PrnOpenDC(PPRN pprn, PSZ pszDataType);               */
/*             BOOL PrnQueryJobProperties(PPRN pprn, INT iQueue);       */
/*             PSZ PrnQueryPrinterName(PPRN pprn);                      */
/*             MRESULT EXPENTRY PrnSetupDlgProc(HWND hWnd, ULONG msg,   */
/*                                              MPARAM mp1, MPARAM mp2);*/

/************************************************************************/
/************************************************************************/
/************************************************************************/
/* DISCLAIMER OF WARRANTIES:                                            */
/* -------------------------                                            */
/* The following [enclosed] code is sample code created by IBM          */
/* Corporation and Prominare Inc.  This sample code is not part of any  */
/* standard IBM product and is provided to you solely for the purpose   */
/* of assisting you in the development of your applications.  The code  */
/* is provided "AS IS", without warranty of any kind.  Neither IBM nor  */
/* Prominare shall be liable for any damages arising out of your        */
/* use of the sample code, even if they have been advised of the        */
/* possibility of such damages.                                         */
/************************************************************************/
/************************************************************************/
/************************************************************************/
/*                     D I S C L A I M E R                              */
/* This code is provided on an as is basis with no implied support.     */
/* It should be considered freeware that cannot be rebundled as         */
/* part of a larger "*ware" offering without our consent.               */
/************************************************************************/
/************************************************************************/
/************************************************************************/

/* Copyright ¸ International Business Machines Corp., 1995.             */
/* Copyright ¸ 1995  Prominare Inc.  All Rights Reserved.               */

/* -------------------------------------------------------------------- */

#pragma subtitle("   Printer Control - Create Printer List Function")
#pragma page( )

/* --- PrnCreatePrinterList ---------------------------- [ Public ] --- */
/*                                                                      */
/*     This function is construct a list of printers.                   */
/*                                                                      */
/*     Upon Entry:                                                      */
/*                                                                      */
/*     PPRN pprn; = Printer Control Structure Pointer                   */
/*                                                                      */
/*     Upon Exit:                                                       */
/*                                                                      */
/*     PrnCreatePrinterList =  TRUE : Queue List Retrieved              */
/*                          = FALSE : No Queue List Retrieved           */
/*                                                                      */
/* -------------------------------------------------------------------- */

BOOL PrnCreatePrinterList(PPRN pprn)

{
PPRQINFO3 pQueueInfo;              /* Queue Information                 */
ULONG     cReturned;               /* Returned Queue Count              */
ULONG     cTotal;                  /* Total Count                       */
ULONG     cbNeeded;                /* Buffer Size                       */
ULONG     aulVersion[2];           /* Version Number Holder             */
PCHAR     pch;                     /* Character Pointer                 */
register INT i;                    /* Loop Counter                      */
register UINT n;                   /* Loop Counter                      */

DosQuerySysInfo(QSV_VERSION_MAJOR, QSV_VERSION_REVISION, aulVersion,
                2UL * sizeof(ULONG));

                       /* Determine the amount of memory required for   */
                       /* queue information                             */

SplEnumQueue((PSZ)NULL, 3UL, (PVOID)NULL, 0UL, &cReturned, &cTotal,
             &cbNeeded, NULL);

                       /* Check to see if any printers were detected    */
                       /* and if none were found, return with the no    */
                       /* no queue list retrieved flag                  */
if ( cTotal == 0L )
   {
   pprn->hAB     = 0UL;
   pprn->cQueues = 0;
   return(FALSE);
   }
                       /* Allocate memory for the queue list            */

if ( DosAllocMem((PPVOID)(PVOID)&pQueueInfo, cbNeeded, PAG_READ | PAG_WRITE | PAG_COMMIT) )
   {
   pprn->hAB     = 0UL;
   pprn->cQueues = 0;
   return(FALSE);
   }
                       /* Retrieve the queue list from the system       */

SplEnumQueue((PSZ)NULL, 3UL, (PVOID)pQueueInfo, cbNeeded, &cReturned,
             &cTotal, &cbNeeded, NULL);

pprn->pquei = (PQUEINFO)malloc(sizeof(QUEINFO) * cTotal);

                       /* Scan the queue list looking for the entry     */
                       /* that contains the default queue and when      */
                       /* found, save the queue index entry             */

for ( i = 0; i < cReturned; i++ )
   {
   if ( pQueueInfo[i].pszName )
       {
       pprn->pquei[i].pszName = (PSZ)malloc((n = strlen(pQueueInfo[i].pszName) + 1));
       memcpy(pprn->pquei[i].pszName, pQueueInfo[i].pszName, n);
       }
   else
       pprn->pquei[i].pszName = NULL;

   if ( pQueueInfo[i].pszDriverName )
       {
       pprn->pquei[i].pszDriverName = (PSZ)malloc((n = strlen(pQueueInfo[i].pszDriverName) + 1));
       memcpy(pprn->pquei[i].pszDriverName, pQueueInfo[i].pszDriverName, n);
       }
   else
       pprn->pquei[i].pszDriverName = NULL;

   if ( pQueueInfo[i].pszPrinters )
       {
       pprn->pquei[i].pszPrinters = (PSZ)malloc((n = strlen(pQueueInfo[i].pszPrinters) + 1));
       memcpy(pprn->pquei[i].pszPrinters, pQueueInfo[i].pszPrinters, n);
       }
   else
       pprn->pquei[i].pszPrinters = NULL;

   pprn->pquei[i].pDriverData = (PSZ)malloc((ULONG)pQueueInfo[i].pDriverData->cb);
   memcpy(pprn->pquei[i].pDriverData, pQueueInfo[i].pDriverData, (ULONG)pQueueInfo[i].pDriverData->cb);

                       /* Check for the default queue                   */

   if ( ((aulVersion[0] == 20UL) && (aulVersion[1] >= 10UL)) || (aulVersion[0] > 20UL) )
       if ( pQueueInfo[i].fsType & PRQ3_TYPE_APPDEFAULT )
           pprn->iQueue = i;
   }

if ( (aulVersion[0] == 20UL) && (aulVersion[1] < 10UL) )
   {
                       /* Get the default queue to use                  */

   if ( PrfQueryProfileString(HINI_PROFILE, "PM_SPOOLER", "QUEUE", NULL,
                              pprn->szQueue, 256UL) )
       {
                       /* Truncate the semicolon delimiter in the queue */
                       /* name                                          */

       pch = strchr(pprn->szQueue, ';');
       *pch = 0;
       }
   else
                       /* No default queue name found, use the first    */
                       /* printer from the list                         */

       strcpy(pprn->szQueue, pQueueInfo->pszName);

                       /* Scan the queue list looking for the entry     */
                       /* that contains the default queue and when      */
                       /* found, save the queue index entry             */

   for ( i = 0; i < cReturned; i++ )
       if ( !strcmp(pprn->szQueue, pQueueInfo[i].pszName) )
           {
           pprn->iQueue = i;
           break;
           }
   }
                       /* Save the queue information within the printer */
                       /* information structure and save the number of  */
                       /* queues found within the system as well and    */
                       /* return the queues found flag                  */

pprn->cQueues = (INT)cReturned;

DosFreeMem((PVOID)pQueueInfo);

return(TRUE);
}
#pragma subtitle("   Printer Control - Destroy Printer List Function")
#pragma page( )

/* --- PrnDestroyPrinterList --------------------------- [ Public ] --- */
/*                                                                      */
/*     This function is used to destroy a constructed printer list.     */
/*                                                                      */
/*     Upon Entry:                                                      */
/*                                                                      */
/*     PPRN pprn; = Printer Control Structure Pointer                   */
/*                                                                      */
/*     Upon Exit:                                                       */
/*                                                                      */
/*     PrnDestroyPrinterList =  TRUE : List Destroyed                   */
/*                           = FALSE : Error                            */
/*                                                                      */
/* -------------------------------------------------------------------- */

BOOL PrnDestroyPrinterList(PPRN pprn)

{
register INT i;                    /* Loop Counter                      */

                       /* Check to make sure that memory was allocated  */
                       /* for the list and if the case, release it      */
if ( pprn->hAB )
   {
   for ( i = 0; i < pprn->cQueues; i++ )
       {
       if ( pprn->pquei[i].pszName )
           free(pprn->pquei[i].pszName);

       if ( pprn->pquei[i].pszDriverName )
           free(pprn->pquei[i].pszDriverName);

       if ( pprn->pquei[i].pszPrinters )
           free(pprn->pquei[i].pszPrinters);

       free(pprn->pquei[i].pDriverData);
       }

   pprn->hAB = 0;
   pprn->cQueues = 0;
   return(TRUE);
   }
                       /* No memory allocated for the list, return      */
                       /* error flag                                    */
return(FALSE);
}
#pragma subtitle("   Printer Control - Printer DC Open Function")
#pragma page( )

/* --- PrnOpenDC --------------------------------------- [ Public ] --- */
/*                                                                      */
/*     This function is used to open a device context on a specified    */
/*     printer.                                                         */
/*                                                                      */
/*     Upon Entry:                                                      */
/*                                                                      */
/*     PPRN pprn;        = Printer Control Structure Pointer            */
/*     PSZ  pszDataType; = Data Type (PM_Q_STD or PM_Q_RAW)             */
/*                                                                      */
/*     Upon Exit:                                                       */
/*                                                                      */
/*     PrnOpenDC = Printer Device Context                               */
/*                                                                      */
/* -------------------------------------------------------------------- */

HDC PrnOpenDC(PPRN pprn, PSZ pszDataType)

{
CHAR         achDriverName[256];   /* Driver Name                       */
DEVOPENSTRUC dop;                  /* Device Open Structure             */
register INT i;                    /* Loop Counter                      */

if ( !pprn->cQueues )
   return((HDC)NULL);
                       /* Initialize the driver data structure          */

memset(&dop, 0, sizeof(DEVOPENSTRUC));

                       /* Set the logical address                       */

dop.pszLogAddress = pprn->pquei[pprn->iQueue].pszName;

                       /* Set the driver name (ie. PSCRIPT)             */

if ( (i = (INT)strcspn(pprn->pquei[pprn->iQueue].pszDriverName, ".")) != 0 )
   {
   dop.pszDriverName = memcpy(achDriverName, pprn->pquei[pprn->iQueue].pszDriverName, (UINT)i);
   achDriverName[i] = 0;
   }
else
   dop.pszDriverName = strcpy(achDriverName, pprn->pquei[pprn->iQueue].pszDriverName);

dop.pdriv  = (PVOID)pprn->pquei[pprn->iQueue].pDriverData;

                       /* Set data type (ie. PM_Q_STD or PM_Q_RAW)      */

dop.pszDataType = pszDataType;

/* Other data values include:                                           */
/*                                                                      */
/*  dop.pszComment    = "comments"; // Comment for OD_Q                 */
/*  dop.pszQueueProcName   = NULL;  // queue processor;                 */
/*                                  //  NULL => use default             */
/*  dop.pszQueueProcParams = NULL;  // parms for queue processor        */
/*  dop.pszSpoolerParams   = NULL;  // spooler parms (use NULL!)        */
/*  dop.pszNetworkParams   = NULL;  // network parms (use NULL!)        */

return(DevOpenDC(pprn->hAB, OD_QUEUED, "*", 9L, (PDEVOPENDATA)(PVOID)&dop, (HDC)0L));
}
#pragma subtitle("   Printer Control - Job Properies Query Function")
#pragma page( )

/* --- PrnQueryJobProperties --------------------------- [ Public ] --- */
/*                                                                      */
/*     This function is used to get printer job properties.  It is      */
/*     valid for a printer to require no job properties.  In this       */
/*     case, *pcb == 0.                                                 */
/*                                                                      */
/*     Upon Entry:                                                      */
/*                                                                      */
/*     PPRN pprn;   = Printer Control Structure Pointer                 */
/*     INT  iQueue; = Selected Queue Index                              */
/*                                                                      */
/*     Upon Exit:                                                       */
/*                                                                      */
/*     PrnQueryJobProperties =  TRUE : Properties Retrieved             */
/*                           = FALSE : Buffer to Small                  */
/*                                                                      */
/* -------------------------------------------------------------------- */

BOOL PrnQueryJobProperties(PPRN pprn, INT iQueue)

{
CHAR      achDeviceName[256];      /* Device Name                       */
CHAR      achDriverName[256];      /* Driver Name                       */
PCHAR     pch;                     /* Character Pointer                 */
register INT i;                    /* Index                             */

if ( !pprn->cQueues )
   return(FALSE);
                       /* Find the driver/device delimiter and parse    */
                       /* out the driver name and the device name       */

if ( (i = (INT)strcspn(pprn->pquei[iQueue].pszDriverName, ".")) != 0 )
   {
   memcpy(achDriverName, pprn->pquei[iQueue].pszDriverName, (UINT)i);
   achDriverName[i] = 0;
                       /* Set the device name                           */

   strcpy(achDeviceName, &pprn->pquei[iQueue].pszDriverName[i + 1]);
   }
else
   {
   strcpy(achDriverName, pprn->pquei[iQueue].pszDriverName);
   achDeviceName[0] = 0;
   }
                       /* Get terminate properly the printer name       */

if ( (pch = strchr(pprn->pquei[iQueue].pszPrinters, ',')) != NULL )
   *pch = 0;

return((BOOL)(DevPostDeviceModes(pprn->hAB, (PVOID)pprn->pquei[iQueue].pDriverData, achDriverName,
                                 achDeviceName, pprn->pquei[iQueue].pszPrinters,
                                 DPDM_POSTJOBPROP) == DEV_OK));
}
#pragma subtitle("   Printer Control - Printer Information Query Function")
#pragma page( )

/* --- PdsPrintQueryPrinterName ------------------------ [ Public ] --- */
/*                                                                      */
/*     This function is used to get information on a printer.           */
/*                                                                      */
/*     Upon Entry:                                                      */
/*                                                                      */
/*     PPRN pprn; = Printer Control Structure Pointer                   */
/*                                                                      */
/*     Upon Exit:                                                       */
/*                                                                      */
/*     PrnQueryPrinterName = Address of Printer Name                    */
/*                                                                      */
/* -------------------------------------------------------------------- */

PSZ PrnQueryPrinterName(PPRN pprn)

{

if ( !pprn->cQueues )
   return((PSZ)NULL);
                       /* Return the address of the printer name        */

return(pprn->pquei[pprn->iQueue].pszName);
}
#pragma subtitle("   Printer Control - Printer Setup Dialogue Procedure")
#pragma page( )

/* --- PrnSetupDlgProc --------------------------------- [ Public ] --- */
/*                                                                      */
/*     This function is used to process the Printer Setup dialogue      */
/*     procedure.                                                       */
/*                                                                      */
/*     Upon Entry:                                                      */
/*                                                                      */
/*     HWND   hWnd; = Dialogue Window Handle                            */
/*     ULONG  msg;  = PM Message                                        */
/*     MPARAM mp1;  = Message Parameter 1                               */
/*     MPARAM mp2;  = Message Parameter 2                               */
/*                                                                      */
/*     Upon Exit:                                                       */
/*                                                                      */
/*     PrnSetupDlgProc = Message Handling Result                        */
/*                                                                      */
/* -------------------------------------------------------------------- */

MRESULT EXPENTRY PrnSetupDlgProc(HWND hWnd, ULONG msg, MPARAM mp1, MPARAM mp2)

{
CHAR szPrinter[CCHMAXPATH];        /* Printer Name Holder               */
PPRN pprn;                         /* Printer List Pointer              */
register INT i, n;                 /* Loop Counters                     */

switch ( msg )
   {
   case WM_INITDLG :
                       /* Save the pointer to user style information    */
                       /* within the dialog's reserved memory           */

       WinSetWindowPtr(hWnd, QWL_USER, (PVOID)(pprn = (PPRN)mp2));

                       /* Go through the queue list and add each of the */
                       /* queue entries to the list box from which the  */
                       /* user can select a printer to use and/or       */
                       /* configure                                     */

       for ( i = 0; i < pprn->cQueues; i++ )
           {
                       /* Insert item and store index                   */

           WinSendDlgItemMsg(hWnd, LB_PRINTERS, LM_SETITEMHANDLE,
                             MPFROMSHORT(n = (INT)LONGFROMMR(WinSendDlgItemMsg(hWnd, LB_PRINTERS, LM_INSERTITEM,
                                                                               MPFROMSHORT(LIT_SORTASCENDING),
                                                                               MPFROMP(strcat(strcat(strcpy(szPrinter,
                                                                                       pprn->pquei[i].pszName), ": "),
                                                                                       pprn->pquei[i].pszDriverName))))),
                             MPFROMP(i));

                       /* If the default printer, save the name to set  */
                       /* selection                                     */

           if ( i == pprn->iQueue )
               WinSendDlgItemMsg(hWnd, LB_PRINTERS, LM_SELECTITEM, MPFROMSHORT(n),
                                 MPFROMSHORT(TRUE));
           }
       break;
                       /* Process list box selections                   */
   case WM_CONTROL :
       switch ( SHORT2FROMMP(mp1) )
           {
                       /* Printer entry selected                        */

           case LN_SELECT :
               WinEnableWindow(WinWindowFromID(hWnd, DID_SETUP), TRUE);
               WinEnableWindow(WinWindowFromID(hWnd, DID_OK),    TRUE);
               break;
           }
       break;

   case WM_COMMAND :
       switch ( SHORT1FROMMP(mp1) )
           {
           case DID_OK :
                       /* Get selection from the list box               */

               pprn = (PPRN)WinQueryWindowPtr(hWnd, QWL_USER);

                       /* Get printer handle                            */

               pprn->iQueue = (INT)LONGFROMMR(WinSendDlgItemMsg(hWnd, LB_PRINTERS, LM_QUERYITEMHANDLE,
                                                                MPFROMLONG(WinSendDlgItemMsg(hWnd, LB_PRINTERS,
                                                                                             LM_QUERYSELECTION,
                                                                                             0L, 0L)),
                                                                0L));
               WinDismissDlg(hWnd, TRUE);
               break;

           case DID_SETUP :

                       /* Get printer handle                            */

               PrnQueryJobProperties((PPRN)WinQueryWindowPtr(hWnd, QWL_USER),
                                     (INT)LONGFROMMR(WinSendDlgItemMsg(hWnd,
                                                                       LB_PRINTERS,
                                                                       LM_QUERYITEMHANDLE,
                                                                       MPFROMLONG(WinSendDlgItemMsg(hWnd,
                                                                                                    LB_PRINTERS,
                                                                                                    LM_QUERYSELECTION,
                                                                                                    0L, 0L)),
                                                                       0L)));
               break;

           case DID_CANCEL :
               WinDismissDlg(hWnd, FALSE);
               break;
           }
       break;
                       /* Close received, exit dialog                   */
   case WM_CLOSE :
       WinDismissDlg(hWnd, FALSE);
       break;

   default :
       return(WinDefDlgProc(hWnd, msg, mp1, mp2));
   }
                       /* Pass through unhandled messages               */
return(0L);
}
