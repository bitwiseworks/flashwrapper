//
// (c) 2004 Yuri Dario <mc6530@mclink.it>
//

/* Include files */
#define  INCL_DOSMODULEMGR
#define  INCL_DOSMISC
#define  INCL_DOSPROCESS
#define  INCL_DOSSEMAPHORES
#include <os2wrap.h>    //Odin32 OS/2 api wrappers
#include <time.h>
#include <win32type.h>
#include <odinlx.h>
#include <winconst.h>

#include <emx/startup.h>

#include "npapi.h"

// local
#include "NpWrap.h"

#if 0
extern int CRT_init(void);
extern void CRT_term(void);
void _ctordtorInit( void );
void _ctordtorTerm( void );
#endif

static void _System cleanup(ULONG ulReason);

BOOL WINAPI LibMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID fImpLoad)
{
   switch (fdwReason)
   {
   case DLL_PROCESS_ATTACH:
      TIMEBOMB_INIT1();
      return TRUE;
   case DLL_THREAD_ATTACH:
   case DLL_THREAD_DETACH:
   case DLL_PROCESS_DETACH:
      return TRUE;
   }
   return FALSE;
}

/****************************************************************************/
/* _DLL_InitTerm is the function that gets called by the operating system   */
/* loader when it loads and frees this DLL for each process that accesses   */
/* this DLL.  However, it only gets called the first time the DLL is loaded */
/* and the last time it is freed for a particular process.  The system      */
/* linkage convention MUST be used because the operating system loader is   */
/* calling this function.                                                   */
/****************************************************************************/
unsigned long _System _DLL_InitTerm(unsigned long hModule, unsigned long
                                   ulFlag)
{
   APIRET rc;

   /*-------------------------------------------------------------------------*/
   /* If ulFlag is zero then the DLL is being loaded so initialization should */
   /* be performed.  If ulFlag is 1 then the DLL is being freed so            */
   /* termination should be performed.                                        */
   /*-------------------------------------------------------------------------*/

   switch (ulFlag) {
      case 0 :

         _CRT_init();
         __ctordtorInit();

         //CheckVersionFromHMOD(PE2LX_VERSION, hModule); /*PLF Wed  98-03-18 05:28:48*/

         /*******************************************************************/
         /* A DosExitList routine must be used to clean up if runtime calls */
         /* are required and the runtime is dynamically linked.             */
         /*******************************************************************/

         if(RegisterLxDll( (HINSTANCE)hModule, LibMain, //DllMain,
			   (PVOID)NULL, //&_Resource_PEResTab,
			   0, 0, 0) == FALSE)
      		return 0UL;

         // save handle
         g_hInstance = hModule;
         // get resources
         rc = DosGetResource( hModule, (ULONG) RT_RCDATA, NP_INFO_OriginalFilename, (PVOID*) &g_originalFileName);
         debug(( "g_originalFileName %d,%d\n", RT_RCDATA, NP_INFO_OriginalFilename));
         debug(( "g_originalFileName %s\n", g_originalFileName));

         // add exit list handler
#if 0
         rc = DosExitList(0x0000F000|EXLST_ADD, cleanup);
         if(rc)
            return 0UL;
#endif

         break;

      case 1 :

         UnregisterLxDll( (HINSTANCE)hModule);
         __ctordtorTerm();
         _CRT_term();
         break;

      default  :
         return 0UL;
   }

   /***********************************************************/
   /* A non-zero value must be returned to indicate success.  */
   /***********************************************************/
   return 1UL;
}

#if 0
static void _System cleanup(ULONG ulReason)
{
   _ctordtorTerm();
   CRT_term();
   DosExitList(EXLST_EXIT, cleanup);
   return ;
}
#endif
