/*************************************************
  SecureIt for OS/2 v2.0
  IBM VAC++ interface definition
  (C) 1997 Allan Mertner
*************************************************/

#include <os2.h>

#ifdef __cplusplus
  extern "C" {
#endif

/* Constants returned by KeyQuerySerialNumberStatus API */

#define snUndefined 0
#define snValid     1
#define snLocked    2
#define snExpired   3

/* SecureIt v2 API definitions */

VOID EXPENTRY KeySetNamePsw(PCHAR Name, PCHAR Psw);
  /* Specify name and password as entered by user, C style */

BOOL EXPENTRY KeySetNamePswIni(PCHAR FileName, PCHAR AppName);
  /* Read Name and Password from INI file */

BOOL EXPENTRY KeyWriteNamePswToIni(PCHAR FileName, PCHAR AppName);
  /* Write a good Name and Password to INI file */

ULONG EXPENTRY KeyGetRegisteredName(PCHAR Buffer, ULONG BufLen);
  /* Returns the registered name in Buffer of length BufLen */


VOID EXPENTRY KeySetVersion(ULONG Version);
  /* Set version number (obsolete) */

VOID EXPENTRY KeySetup(BOOL UseSerialNo, BOOL UseHighAscii, BOOL UseRSAPassword,
     ULONG Version, PVOID ExtraData, ULONG ExtraLen);
  /* 2.0: Setup up SecureIt version code, Serial Number, Blob data */

VOID EXPENTRY KeySetCallOffsets(ULONG High, PLONG Offsets);
  /* 2.0: Define offsets for all CallBack fields in password */

VOID EXPENTRY KeySetPatchOffsets(ULONG High, PLONG Offsets);
  /* 2.0: Define offsets for all CodePatch fields in password */


BOOL EXPENTRY KeyCheck(BOOL Automatic);
  /* Check if name/password combination is valid; if Automatic */
  /* is True, performs all Patches and Calls automatically */

BOOL EXPENTRY KeyDispatch(ULONG Number);
  /* Manually call function specified in Number (1-4) */

BOOL EXPENTRY KeyCodePatch(ULONG Number);
  /* Manually patch code specified in Number (1-4) */

ULONG EXPENTRY KeyQueryUserValue(ULONG Number);
  /* Retrieve user value specified in Number (1-4) */


ULONG EXPENTRY KeyGetSerialNumber();
  /* 2.0: Return the current serial number; -1 if error or undefined */

BYTE EXPENTRY KeyGetSerialNumberStatus();
  /* 2.0: Return the serial number status */

BOOL EXPENTRY KeyGetSerialNumberExpiry(PULONG Year, PULONG Month, PULONG Day);
  /* 2.0: Return the date of expiry for the current serial number; FALSE if no expiry */


ULONG EXPENTRY KeyGetUserString(ULONG Index, PCHAR Buffer, ULONG BufLen);
  /* 2.0: Return decoded string Index from data blob */

ULONG EXPENTRY KeyGetFileChecksum(PCHAR FileName, LONG CheckLen);
  /* 2.0: Calculate 32-bit CRC of file */

ULONG EXPENTRY KeyGetCRC32(PCHAR Data, ULONG Len);
  /* 2.0: Calculate 32-bit CRC of block of data */

BOOL EXPENTRY KeyManualPatch(ULONG Address, ULONG Size, VOID * Data);
  /* Manually patch code at Address with Data^, for Size bytes */

BOOL EXPENTRY KeyManualDispatch(ULONG Address);
  /* Manually call the code at Address */

VOID EXPENTRY KeyManualJump(ULONG Address);
  /* Transfer control, Jump, to Address */

VOID EXPENTRY KeyOverwriteCode(ULONG From, ULONG WithData);
  /* Overwrite code from address From with data Withdata, until return address */

VOID EXPENTRY KeyScrambleStr(PCHAR S, ULONG Seed);
  /* Scramble C style string */

VOID EXPENTRY KeyAllowDebugger();
  /* Allow the SecureIt code to be debugged */

#ifdef __cplusplus
  }
#endif

