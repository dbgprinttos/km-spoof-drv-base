/*++

Module Name:

    public.h

Abstract:

    This module contains the common declarations shared by driver
    and user applications.

Environment:

    user and kernel

--*/

//
// Define an Interface Guid so that app can find the device and talk to it.
//

DEFINE_GUID (GUID_DEVINTERFACE_joonydriver,
    0x4e9513e4,0xfad9,0x484d,0x97,0xf8,0xa7,0x29,0xef,0x57,0x69,0x1f);
// {4e9513e4-fad9-484d-97f8-a729ef57691f}
