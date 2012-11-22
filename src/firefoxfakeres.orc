#include "winuser.h"
#include "odinrsrc.h"


/////////////////////////////////////////////////////////////////////////////
//
// Version (based on NT 4 SP3)
//

1 VERSIONINFO
 FILEVERSION 0x08, 0x00, 0x01, 0x00
 PRODUCTVERSION 0x08, 0x00, 0x01, 0x00
 FILEFLAGSMASK 0x3fL
 FILEFLAGS 0x00
 FILEOS 0x10001L
 FILETYPE 0x1L
 FILESUBTYPE 0x0L
BEGIN
    BLOCK "StringFileInfo"
    BEGIN
        BLOCK "040904E4"
        BEGIN
            VALUE "CompanyName", "Mozilla Corporation\0"
            VALUE "FileDescription", "Firefox\0"
            VALUE "FileVersion", "10.0.0\0"
            VALUE "InternalName", "Firefox\0"
            VALUE "LegalCopyright", "Copyright (C) 1999-2012\0"
            VALUE "LegalTrademarks", "\0"
            VALUE "OriginalFilename", "firefox.exe\0"
            VALUE "ProductName", "Firefox\0"
            VALUE "ProductVersion", "10.0.0\0"
        END
    END
    BLOCK "VarFileInfo"
    BEGIN
	VALUE "Translation", 0x409, 0x04E4
    END
END
