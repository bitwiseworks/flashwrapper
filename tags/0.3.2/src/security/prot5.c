//
// Example of security using a relative callback
// and a relative patch, strings embedded in the
// data blob, expired/locked serial numbers and
// a RSA-encrypted password string

// Uncomment the following line while testing
// #define test

// Level 1: Simply call to check if the user registered
// Level 2: Registers a call back function
// Level 3: Registers a call back function and code patching function
// Level 4: Level 3 plus self wiping code in memory

// #define __SECURITY_LEVEL_1__
// #define __SECURITY_LEVEL_2__
// #define __SECURITY_LEVEL_3__
#define __SECURITY_LEVEL_4__

#include <stdio.h>
#include <string.h>
// #include <dos.h>
#include <os2.h>

#include "Securit2.h"

int RegisteredFunction(void);
int UnRegisteredFunction(void);

PFN Registered=(PFN)UnRegisteredFunction;

#if defined(__SECURITY_LEVEL_3__) | defined(__SECURITY_LEVEL_4__)
BOOL FixedLocation(char *Buffer);
#endif

int IsRegistered(VOID);

#if defined(__SECURITY_LEVEL_2__)
// Call back function.   When you call eCSKeyCheck, this routine will be invoked.
// For security level 2, it simply sets the registered function pointer
int IsRegistered(VOID)
{
   if (KeyCheck(FALSE)) Registered = RegisteredFunction;
   return 0;
}
#endif

#if defined(__SECURITY_LEVEL_3__) | defined(__SECURITY_LEVEL_4__)
BOOL FixedLocation(char *Buffer)
{
   // Now verify the checksum against the user value
   // This is what the code should really do - after being patched in memory
   // Registered = (eCSKeyQueryUserValue(1) == eCSKeyGetFileChecksum(Buffer, 0));

   // This is the - wrong - code we generate to be patched
   //  This is the code a hecker will see but it's not the actual code that would be executed
   return (KeyQueryUserValue(3) == KeyGetFileChecksum(Buffer, 0));
}

// Call back function.   When you call eCSKeyCheck, this routine will be invoked.
int IsRegistered(VOID)
{
   CHAR Buffer[255];

   eCSLoadCheckSum(Buffer, sizeof(Buffer));

   if (FixedLocation(Buffer)) Registered=(PFN)RegisteredFunction;
   /* Security Level 4 overwrites both the FixedLocation & IsRegistered code */
#if defined(__SECURITY_LEVEL_4__)
   {
      LONG temp = (LONG)&FixedLocation+11;
      LONG i;
      LONG Data = 0xffff;
      for (i=0; i<15; i++) {
         KeyManualPatch(temp, 2, &Data);
         temp += 2;
      } /* endfor */
      for (temp=(LONG)IsRegistered+0x0e,i=0; i<10; i++) {
         KeyManualPatch(temp, 2, &Data);
         temp += 2;
      } /* endfor */
   }
#endif
   return 0;
}
#endif

int UnRegisteredFunction(VOID)
{
   CHAR Buffer[80];
   CHAR s[80];

   // Get the registered user name
   KeyGetRegisteredName(Buffer, sizeof(Buffer));

   // "Program registered to ..."
   printf("\n%s%s\n", TXTProgramRegisteredTo(s), Buffer);

   // "Serial Number ..."
   printf("%s%8.8x\n", TXTSerialNumber(s), KeyGetSerialNumber());

   // Notify user that key will expire next month
#if defined(__WATCOMC__)
   {
      struct dosdate_t date;

      _dos_getdate( &date );
      date.month++;
      if (date.month==13) {
         date.month=1;
         date.year++;
      } /* endif */
      printf("%s %2d-%2d-%2d", TXTLicenseWillExpireOn(s), date.month, date.day, date.year);
   }
#endif

   return 0;
}

int RegisteredFunction(VOID)
{
   CHAR Buffer[80];
   CHAR s[80];
   ULONG Year, Month, Day;

   // Get the registered user name
   KeyGetRegisteredName(Buffer, sizeof(Buffer));

   // "Program registered to ..."
   printf("\n%s%s\n", TXTProgramRegisteredTo(s), Buffer);

   // "Serial Number ..."
   printf("%s%8.8x\n", TXTSerialNumber(s), KeyGetSerialNumber());

   // Try to get the serial number expiry date
   if (KeyGetSerialNumberExpiry(&Year, &Month, &Day))
   {
      // Notify user that key will expire
      printf("%s %2d-%2d-%2d", TXTLicenseWillExpireOn(s), Day, Month, Year);
   }

   // Write the "This function is only available..." strings
   printf("\n%s\n", TXTRegisteredUsersOnly(s));
   printf("%s\n", TXTYouMustBeOneOfThose(s));

   return 0;
}

int main()
{
   CHAR s[80];
   LONG temp;

#if defined(test)
   KeyAllowDebugger();
#endif

#if !defined(__SECURITY_LEVEL_1__)
   // Set up relative address for the CallBack and CodePatch functions
   temp = (LONG)&IsRegistered;

   // Pass 1 address only
   KeySetCallOffsets(0, &temp);
#endif

#if defined(__SECURITY_LEVEL_3__) | defined(__SECURITY_LEVEL_4__)
   temp = (LONG)&FixedLocation;
   {
   LONG Data = 0x016A;   /* 0x48E8016A; */
   KeyManualPatch(temp+0x0011, 2, &Data);
   }
#endif

#if defined(__SECURITY_LEVEL_4__)
/*
   temp = (LONG)&FixedLocation;
   eCSKeySetPatchOffsets(0, &temp);
*/
#endif

   // Verify that SecureIt is functional!
   if (!eCSVerifySecurityIntegrity(s)) {
      CHAR Buffer[255];
      LONG lCheckSum;

      eCSLoadCheckSum(Buffer, sizeof(Buffer));
      lCheckSum=KeyGetFileChecksum(Buffer, 0);

      /* Don't really print it out.   Write it out (encrypted) to a log file so you know why the program doesn't work */
      /* Scramble C style string */
      KeyScrambleStr(s, lCheckSum);
      printf("%s\n",s);   /* In real life, instead of print, write it to a log file */
   }
#if defined(__SECURITY_LEVEL_1__)
   else Registered = RegisteredFunction;
#endif

   if (KeyCheck(TRUE))
   {
      // Call the main program.   This can either become a registered, or unregisterd version.
      (*Registered)();
   }
   else
   {
      // Check why KeyCheck failed
      switch (KeyGetSerialNumberStatus())
      {
         case eCSExpired :
            TXTSerialNumberExpired(s); break;

         case eCSLocked :
            TXTKeyIsLocked(s); break;

         default :
            TXTProgramIsUnregistered(s); break;
      }
      printf("%s\n", s);
   }

   return 0;
}

