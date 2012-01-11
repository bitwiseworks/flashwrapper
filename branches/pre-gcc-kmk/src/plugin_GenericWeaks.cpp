/* $Id: plugin_GenericWeaks.cpp,v 1.4 2003/09/17 17:41:56 bird Exp $
 *
 * Stubs for weak symbol resolution.
 *
 * InnoTek Systemberatung GmbH confidential
 *
 * Copyright (c) 2003 InnoTek Systemberatung GmbH
 * Author: knut st. osmundsen <bird@anduin.net>
 *
 * All Rights Reserved
 *
 */



#ifdef __IBMCPP__
/*
 * This weak resolving ASSUMES that the caller cleans the stack!
 * (i.e. anything but __stdcall calling convention will work very nicely.)
 */
extern "C" unsigned npGenericNPWeakStub(void);
extern "C" void * NPJNICreateDownWrapperWeakStub(void);
extern "C" unsigned upCreateWrapperWeakStub(void **pv1, void *pv2, int rc);
extern "C" const char * getIIDCIDNameWeakStub(void *pv1);

unsigned npGenericNPWeakStub(void)
{
    return 0x80004001; /** NS_ERROR_NOT_IMPLEMENTED */
}

void * NPJNICreateDownWrapperWeakStub(void)
{
    return 0;
}

unsigned upCreateWrapperWeakStub(void **pv1, void *pv2, int rc)
{
    if (rc)
        return rc;
    return 0x80004001; /** NS_ERROR_NOT_IMPLEMENTED */
}

const char * getIIDCIDNameWeakStub(void *pv1)
{
    return "<unknown/weak>";
}

#endif

