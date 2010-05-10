//
// Example of security using a relative callback
// and a relative patch, strings embedded in the
// data blob, expired/locked serial numbers and
// a RSA-encrypted password string

// Uncomment the following line while testing
// #define test
#define INCL_BASE

#include <stdio.h>
#include <string.h>
// #include <dos.h>
#include <os2.h>

#include "Securit2.h"
#include "ecomstation.inc"

int main(void)
{
   CHAR s[80];
   LONG temp;
   ULONG  ulBootDrv;
   CHAR pszRegName[] = "D:\\OS2\\ECSREG11.INI";

#if defined(DEBUG)
   KeyAllowDebugger();
#endif

   KeySetup(TRUE, FALSE, TRUE, 0x010101, &SIBlob, SIBlobLen);

   DosQuerySysInfo(QSV_BOOT_DRIVE, QSV_BOOT_DRIVE, &ulBootDrv, sizeof(ulBootDrv));

   pszRegName[0] = (char)(ulBootDrv + 'A' - 1);

   if (KeySetNamePswIni(pszRegName, "eComStationRegistration"))
   {
       printf("Name and Password retrieved and set\n");
   } else
   {
       printf("Problems with INI\n");
       return 0;
   }

   if (KeyCheck(TRUE))
   {
       CHAR Buffer[80] = {0};
       LONG Len;

       Len = KeyGetRegisteredName(&Buffer[0], sizeof(Buffer));

       printf("Registered to: [%s]\n", Buffer);
   }
   else
   {
      // Check why KeyCheck failed
      switch (KeyGetSerialNumberStatus())
      {
         case snExpired:
             sprintf(s, "Serial number expired"); break;

      case snLocked:
          sprintf(s, "Key is locked"); break;

         default :
          sprintf(s, "Unregistered"); break;
      }
      printf("%s\n", s);
   }

   return 0;
}

