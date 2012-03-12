/* Include files */
#define  INCL_DOSMODULEMGR
#define  INCL_DOSMISC
#define  INCL_DOSPROCESS
#define  INCL_DOSERRORS
#define  INCL_DOSSEMAPHORES

#define ORIGINAL_VAC_FUNCTIONS

#include <os2wrap.h>    //Odin32 OS/2 api wrappers
ULONG APIENTRY DosGetResource(HMODULE a, ULONG b, ULONG c, PPVOID d);

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <odin.h>
#include <win32api.h>
//#include <win32type.h>
#include <odinapi.h>
//#include <winconst.h>
#include <odinlx.h>
//#include <dbglog.h>
#include <initdll.h>
#include <time.h>

#include "npapi.h"

//#include <custombuild.h>
#include "plugin_RCDefines.h"

static HMODULE hFL32Win = 0;
static HMODULE g_hInstance = 0;
static char g_originalFileName[255] = {0};

BOOL WIN32API FlashPreCustomize();

//******************************************************************************
//******************************************************************************
#if 0
CUSTOMBUILD_COMMON CustomBuild = 
{
    &AcrobatPreCustomize,
    &InitCustomization,
    &EndCustomization,
    &IsPEStubLoader,

    //custom build name
    "AR32WIN.DLL",

    //Registry base
    NULL,  //use standard shared custom build base
  
    //Exception log disable environment variable
    "AR32_DISABLE_EXCEPTLOG",
    //Exception log path environment variable
    "AR32_PATH_EXCEPTLOG",

    //Windows version
    WINVERSION_NT40,

    //Allow Odin.ini usage
    FALSE,

    //SMP support
    FALSE,

    //Enable Drag and Drop
    FALSE,

    //Enable Odin system menu items
    FALSE,
    
    //Window look and feel
    OS2_APPEARANCE,

    //Convert color cursors to mono
    TRUE,

    //font mappings
    {
      { "MS Sans Serif",  "WarpSans" },
      { "MS Shell Dlg",   "WarpSans" },
      { "MS Shell Dlg 2", "WarpSans" },
      {  NULL, NULL } //last entry!!
    },
    // FT2LIB integration
    FALSE,

    // WINMM: DirectAudio support
    FALSE,

    // WIMM: Wave audio support
    TRUE,

    //list of remainder of registered dlls (order is important due to dependencies!!)
    //(NTDLL, KERNEL32, USER32 and GDI32 are always registered)
    //NOTE: MSVCRT is included in the Acrobat distribution
    {
      {  "ADVAPI32.DLL", NULL,  NULL },
      {  "VERSION.DLL",  NULL,   NULL },
      {  "WSOCK32.DLL",  NULL,   NULL },
      {  "WINMM.DLL",    NULL,     NULL },
      {  "OLE32.DLL",    NULL,     NULL },
      {  "COMCTL32.DLL", NULL,  NULL },
      {  "SHELL32.DLL",  NULL,   NULL },
      {  "COMDLG32.DLL", NULL,  NULL },
      {  "WINSPOOL.DRV", NULL,  NULL },
      {  "DDRAW.DLL",    NULL,     NULL },
      {  "OLEAUT32.DLL", NULL,  NULL },
      {  "OLEPRO32.DLL", NULL,  NULL },
      {  "OLEDLG.DLL",   NULL,    NULL },
      {  "LZ32.DLL",     NULL,      NULL },
      {  "MSVFW32.DLL",  NULL,   NULL },
      {  "MPR.DLL",      NULL,       NULL },
      {  "IMM32.DLL",    NULL,     NULL },
      {  "SHLWAPI.DLL",  NULL,   NULL },
      {  "SHFOLDER.DLL", NULL,  NULL },
      {  "RICHED32.DLL", NULL,  NULL },
      {  "WININET.DLL",  NULL,   NULL },
      {  "URLMON.DLL",  NULL,   NULL },
#ifdef USE_MSVCRT
      {  "MSVCRT.DLL",   NULL,    NULL },
#endif
      {  NULL, 0, NULL } //last entry!!
    }
};

//******************************************************************************
// AcrobatPreCustomize
//
// Called after kernel32, user32 and gdi32 are initialized
//******************************************************************************
BOOL WIN32API FlashPreCustomize()
{
     HKEY hKey;

     //Check for custom build audio setting key. (BEFORE WINMM INIT!)
     //If not present, then enable wave audio by default.
     if(RegOpenKeyA(HKEY_LOCAL_MACHINE, CUSTOM_BUILD_OPTIONS_KEY, &hKey) == 0)
     {
         DWORD dwSize, dwType;
         DWORD dwFlag;

         dwSize = sizeof(dwFlag);
         LONG rc = RegQueryValueExA(hKey, DISABLE_AUDIO_KEY,
                                    NULL, &dwType,
                                    (LPBYTE)&dwFlag,
                                    &dwSize);
         if(rc == 0 && dwType == REG_DWORD && dwFlag == 1) {
             //Disable wave audio
             CustomBuild.fWaveAudio = FALSE;
         }

         dwSize = sizeof(dwFlag);
         rc = RegQueryValueExA(hKey, ENABLE_AR_FT2LIB_INTEGRATION,
                               NULL, &dwType,
                               (LPBYTE)&dwFlag,
                               &dwSize);
         if(rc == 0 && dwType == REG_DWORD && dwFlag == 1) {
             //Enable FT2LIB integration
             CustomBuild.fFreeType = TRUE;
         }

         dwSize = sizeof(dwFlag);
         rc = RegQueryValueExA(hKey, ENABLE_POSTSCRIPT_PASSTHROUGH,
                               NULL, &dwType,
                               (LPBYTE)&dwFlag,
                               &dwSize);
         if(rc == 0 && dwType == REG_DWORD && dwFlag == 0) {
             //Disable Postscript passthrough printing
             ODIN_SetPostscriptPassthrough(FALSE);
         }
     }
     else
     {
         //Disable wave audio by default
         CustomBuild.fWaveAudio = FALSE;
     }

     //check if installer is running
     PPIB ppib;
     PTIB ptib;

     if(DosGetInfoBlocks(&ptib, &ppib) == NO_ERROR) {
         char *lpszParam = ppib->pib_pchcmd + strlen(ppib->pib_pchcmd) + 1;
         if(strstr(lpszParam, "_INS5576._MP")) {
             fInstaller = TRUE;
         }
     }

     return TRUE;
}


BOOL WIN32API LoadOdinEnvironment(void)
{
     ULONG  hModule = 0/*hCustomDll*/;
     ULONG  ulFlag = 0; //dll load
     int    i;
     APIRET rc;
     char   szSystemDir[CCHMAXPATH];
     char   szWindowsDir[CCHMAXPATH];
     char  *szRegistryBase;

//     lpCustomBuild[nrCustomBuilds] = CustomBuild;

     // We only allow certain critical operations during the first custom build load
     if(nrCustomBuilds == 0)
     {
         //Set Windows and System directories based on the path of the custom build dll
         if(DosQueryModuleName(hModule, CCHMAXPATH, szSystemDir) != 0) return FALSE;

         char *endofpath = strrchr(szSystemDir, '\\');
         *(endofpath+1) = 0;
         strcpy(szWindowsDir, szSystemDir);
         //In our shared custom build the system32 and windows directory
         //are identical
         InitDirectoriesCustom(szSystemDir, szWindowsDir);

         //don't allow Odin to save odin.ini
         if(!CustomBuild->fOdinIni) {
             DisableOdinIni();
         }

         //Setup registry
         char *szRegistryPath = szSystemDir;

         if(CustomBuild->szRegistryBase) {
              szRegistryBase = CustomBuild->szRegistryBase;
         }
         else szRegistryBase = INNOWIN_REGISTRY_BASE;

         strcpy(szRegistryPath, szRegistryBase);
         strcat(szRegistryPath, INNOWIN_REG_CURRENTUSER);
         if(RegCreateKeyA(HKEY_CURRENT_USER, szRegistryPath, &hKeyCurrentUser)!=ERROR_SUCCESS_W)
             return FALSE;

         strcpy(szRegistryPath, szRegistryBase);
         strcat(szRegistryPath, INNOWIN_REG_LOCAL_MACHINE);
         if(RegCreateKeyA(HKEY_LOCAL_MACHINE, szRegistryPath, &hKeyLocalMachine)!=ERROR_SUCCESS_W) {
             return FALSE;
         }

         //HKEY_CLASSES_ROOT is an alias for HKEY_LOCAL_MACHINE\Software\Classes
         //(or the other way around, but we can't emulate that)
         if(RegCreateKeyA(hKeyLocalMachine,"Software\\Classes",&hKeyClassesRoot)!=ERROR_SUCCESS_W) {
             return FALSE;
         }

         strcpy(szRegistryPath, szRegistryBase);
         strcat(szRegistryPath, INNOWIN_REG_USERS);
         if(RegCreateKeyA(HKEY_USERS, szRegistryPath, &hKeyUsers)!=ERROR_SUCCESS_W) {
             return FALSE;
         }

         SetRegistryRootKey(HKEY_CLASSES_ROOT, hKeyClassesRoot);
         SetRegistryRootKey(HKEY_CURRENT_USER, hKeyCurrentUser);
         SetRegistryRootKey(HKEY_LOCAL_MACHINE, hKeyLocalMachine);
         SetRegistryRootKey(HKEY_USERS, hKeyUsers);

         //NTDLL	
         SetCustomBuildName("NTDLL.DLL", NULL);
         if(RegisterLxDll(hModule, NULL, (PVOID)NULL) == 0) {
             DebugInt3();
             return FALSE;
         }

         //Change Windows version
         OdinSetVersion(CustomBuild->dwWindowsVersion);

         //Override shared semaphore name used to synchronize memory map list
         //access (to avoid name clash with Odin)
         SetCustomMMapSemName(INNOWIN_MMAPSEM_NAME);

         //check for exception log overrides (env. variables)
         if(getenv((CustomBuild->szEnvExceptLogDisable) ? CustomBuild->szEnvExceptLogDisable : INNOWIN_EXCEPTLOG_DISABLE)) {
             dprintf(("Disabling exception log"));
             SetExceptionLogging(FALSE);
         }
         char *lpszExceptLog = getenv((CustomBuild->szEnvExceptLogPath) ? CustomBuild->szEnvExceptLogPath : INNOWIN_EXCEPTLOG_PATH);
         if(lpszExceptLog) {
             dprintf(("Set exception log path to %s", lpszExceptLog));
             SetCustomExceptionLog(lpszExceptLog);
         }

         //Initialize WGSS first
         rc = WGSS_DLL_InitTerm(hModule, ulFlag);
         if(rc == 0) {
            DebugInt3();
            return FALSE;
         }

         //Kernel32
         SetCustomBuildName("KERNEL32.DLL", &nt_kernel32_header);
         rc = inittermKernel32(hModule, ulFlag);
         if(rc == 0) {
            DebugInt3();
            return FALSE;
         }

         //If there are multiple CPU's in the system and SMP is disabled, then
         //force all threads to run on CPU 0
         if(!CustomBuild->fSMP && cCPUs > 1)
         {
             SetProcessAffinityMask(GetCurrentProcess(), 1);
         }

         //call precustomize function (if present)
         if(CustomBuild->pfnPreCustomize)
         {
             if(CustomBuild->pfnPreCustomize() == FALSE) {
                 DebugInt3();
                 return FALSE;
             }
         }

         //User32
         if(!CustomBuild->fOdinSysMenuItems) {
             DisableOdinSysMenuItems(); //must be called before loading user32
         }
         //Override shared semaphore name used to synchronize global window handle
         //array access (to avoid name clash with Odin)
         SetCustomWndHandleSemName(INNOWIN_WINSEM_NAME);

         //Set custom names for std windows
         SetCustomStdClassName(INNOWINCLASSNAME);

         //Disable drag 'n drop if required
         DisableDragDrop(CustomBuild->fDragDrop);

         //Must do this before USER32 init!
         SetFreeTypeIntegration(CustomBuild->fFreeType);

         SetCustomBuildName("USER32.DLL", &nt_user32_header);
         rc = inittermUser32(hModule, ulFlag);
         if(rc == 0) {
            DebugInt3();
            return FALSE;
         }

         SetWindowAppearance(CustomBuild->dwWindowAppearance);

         // Force color to mono cursor conversion (necessary due to lack of hardware color
         // cursor support in crappy OS/2 display drivers)
         if(CustomBuild->fMonoCursor) {
             CustForceMonoCursor();
         }

         //Gdi32
         SetCustomBuildName("GDI32.DLL", &nt_gdi32_header);
         rc = inittermGdi32(hModule, ulFlag);
         if(rc == 0) {
            DebugInt3();
            return FALSE;
         }

         for(i=0;CustomBuild->fontMapping[i].szWindowsFont != NULL;i++)
         {
             PROFILE_SetOdinIniString(ODINFONTSECTION, CustomBuild->fontMapping[i].szWindowsFont, CustomBuild->fontMapping[i].szPMFont);
         }
     }
     dprintf(("LoadCustomEnvironment %d", nrCustomBuilds));

     // Check all requested dlls
     for(i=0;CustomBuild->registeredDll[i].szName != NULL;i++)
     {
         for(int j=0;j<MAX_CUSTOM_DLLS;j++)
         {
             if(!strcmp(CustomBuild->registeredDll[i].szName, CustomDll[j].szName))
             {
                 break;
             }
         }
         if(j == MAX_CUSTOM_DLLS) {
             DebugInt3();
             return FALSE;
         }
     }

     if(nrCustomBuilds == 0)
     {
         //WINMM pre-init checking
         if(!CustomBuild->fDirectAudio) {
             DisableDirectAudio();
         }
         if(!CustomBuild->fWaveAudio) {
             DisableWaveAudio();
         }

         for(i=0;i<MAX_CUSTOM_DLLS;i++)
         {
             SetCustomBuildName(CustomDll[i].szName, CustomDll[i].pfh);

             if(CustomDll[i].pfnInitterm) {
                  rc = CustomDll[i].pfnInitterm(hModule, ulFlag);
             }
             else rc = RegisterLxDll(hModule, NULL, (PVOID)NULL);
             if(rc == 0) {
                 DebugInt3();
                 return FALSE;
             }
         }
         //remember number of dlls for unload
         nrRegisteredDlls = i;

         //Register dummy dlls
         for(i=0;i<MAX_CUSTOM_SYSTEM_DLLS;i++)
         {
             int j;

             for(j=0;j<nrRegisteredDlls;j++)
             {
                 if(!strcmp(CustomDll[j].szName, SystemDll[i].szName))
                 {
                     break;
                 }
             }
             if(j == nrRegisteredDlls)
             {
                 SetCustomBuildName(SystemDll[i].szName, NULL);
                 if(RegisterLxDll(hModule, NULL, (PVOID)NULL) == 0)
                 {
                     DebugInt3();
                     return FALSE;
                 }
             }
         }
         SetCustomBuildName(NULL, NULL);
     }


     //Register dummy dll
     SetCustomBuildName(CustomBuild->szCustomBuildDllName, NULL);
     if(RegisterLxDll(hModule, 0, NULL) == 0)
     {
         DebugInt3();
         return FALSE;
     }

     if(CustomBuild->pfnPostCustomize)
     {
         if(CustomBuild->pfnPostCustomize() == FALSE)
         {
             DebugInt3();
             return FALSE;
         }
     }

     nrCustomBuilds++;

     //DosLoadModule the dll to make sure it stays put. (plugin issue)
     HMODULE hmod;
     if (DosLoadModule(NULL, 0, CustomBuild->szCustomBuildDllName, &hmod)) {
//         DebugInt3();
     }

     return TRUE;
}
//******************************************************************************
//******************************************************************************
BOOL WIN32API UnloadCustomEnvironment(BOOL fExitList)
{
    if(fExitList)
    {
        for(int i=0;i<MAX_CUSTOMBUILDS;i++)
        {
            if(lpCustomBuild[i] && lpCustomBuild[i]->pfnEndCustomize)
            {
                lpCustomBuild[i]->pfnEndCustomize();
            }
        }
    }

    nrCustomBuilds--;
#if 0
    if(nrCustomBuilds == 0) {
         //Unregister all valid dlls in reversed order
         for(i=nrRegisteredDlls-1;i>=0;i--)
         {
             rc = CustomDll[i].pfnInitterm(hModule, ulFlag);
         }

         inittermGdi32(hModule, ulFlag);
         inittermUser32(hModule, ulFlag);
         inittermKernel32(hModule, ulFlag);
         WGSS_DLL_InitTerm(hModule, ulFlag);
    }
#endif
     return TRUE;
}

#endif

static void _System cleanup(ULONG ulReason);

BOOL WINAPI LibMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID fImpLoad)
{
   switch (fdwReason)
   {
   case DLL_PROCESS_ATTACH:
      /* TIMEBOMB_INIT1(); */
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

   /*-------------------------------------------------------------------------*/
   /* If ulFlag is zero then the DLL is being loaded so initialization should */
   /* be performed.  If ulFlag is 1 then the DLL is being freed so            */
   /* termination should be performed.                                        */
   /*-------------------------------------------------------------------------*/
   APIRET rc;

   hFL32Win = hModule;

   switch (ulFlag) {
      case 0 :
      {
         _CRT_init();
         __ctordtorInit(0);

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
         rc = DosGetResource(hModule, (ULONG) RT_RCDATA, NP_INFO_OriginalFilename, (PVOID*) &g_originalFileName);
//         debug(( "g_originalFileName %d,%d\n", RT_RCDATA, NP_INFO_OriginalFilename));
//         debug(( "g_originalFileName %s\n", g_originalFileName));

         // add exit list handler
#if 0
         rc = DosExitList(0x0000F000|EXLST_ADD, cleanup);
         if(rc)
            return 0UL;
#endif
         break;
      }

      case 1 :
      {
         UnregisterLxDll( (HINSTANCE)hModule);
         __ctordtorTerm(0);
         _CRT_term();
         break;
      }

      default  :
         return 0UL;
   }

   /***********************************************************/
   /* A non-zero value must be returned to indicate success.  */
   /***********************************************************/
   return 1UL;
}
//******************************************************************************
//******************************************************************************
BOOL OSLibQueryModulePath(LPSTR lpszFullPath, INT cbFullPath)
{
    PTIB   ptib;
    PPIB   ppib;

    if(DosGetInfoBlocks(&ptib, &ppib) != NO_ERROR) {
        return FALSE;
    }
 
    if(DosQueryModuleName(ppib->pib_hmte, cbFullPath, lpszFullPath) != NO_ERROR) 
    {
        return FALSE;
    }
    return TRUE;
}
//******************************************************************************
//******************************************************************************
BOOL OSLibQueryFL32WinPath(LPSTR lpszFullPath, INT cbFullPath)
{
    if(DosQueryModuleName(hFL32Win, cbFullPath, lpszFullPath) != NO_ERROR)
    {
        return FALSE;
    }
    return TRUE;
}
//******************************************************************************
//******************************************************************************
