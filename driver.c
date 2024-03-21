#include <ntddk.h>

// Forward declarations
VOID DpcRoutine(_In_ PKDPC Dpc, _In_opt_ PVOID DeferredContext, _In_opt_ PVOID SystemArgument1, _In_opt_ PVOID SystemArgument2);
VOID DriverUnload(_In_ PDRIVER_OBJECT DriverObject);
VOID DebugPrintRoutine();

KTIMER Timer;
KDPC Dpc;

VOID DebugPrintRoutine()
{
    static ULONG64 exampleDisk = 0;
    static ULONG64 exampleBaseboard = 0;
    static ULONG64 exampleUuid = 0;
    static ULONG64 exampleBootkit = 0;
    static ULONG64 exampleNetwork = 0;
    static ULONG64 examplePci = 0;

    // Print the values and increment for the next run
    DbgPrint("[kernel] disk: %016llX\n", exampleDisk++);
    DbgPrint("[kernel] baseboard: %016llX\n", exampleBaseboard++);
    DbgPrint("[kernel] uuid: %016llX\n", exampleUuid++);
    DbgPrint("[kernel] secure bootkit has been bypassed with entry: %016llX\n", exampleBootkit++);
    DbgPrint("[kernel] network func: %016llX\n", exampleNetwork++);
    DbgPrint("[kernel] pci device(s) has been found and mapped with entry: %016llX\n", examplePci++);
}
VOID DpcRoutine(
    _In_ PKDPC Dpc,
    _In_opt_ PVOID DeferredContext,
    _In_opt_ PVOID SystemArgument1,
    _In_opt_ PVOID SystemArgument2)
{
    UNREFERENCED_PARAMETER(Dpc);
    UNREFERENCED_PARAMETER(DeferredContext);
    UNREFERENCED_PARAMETER(SystemArgument1);
    UNREFERENCED_PARAMETER(SystemArgument2);

    DebugPrintRoutine();

    LARGE_INTEGER interval;
    interval.QuadPart = -10000000; // 1 second interval
    KeSetTimer(&Timer, interval, &Dpc);
}

VOID DriverUnload(_In_ PDRIVER_OBJECT DriverObject)
{
    UNREFERENCED_PARAMETER(DriverObject);

    KeCancelTimer(&Timer);
    KeFlushQueuedDpcs();

    DbgPrint("Driver Unload called\n");
}

NTSTATUS DriverEntry(_In_ PDRIVER_OBJECT DriverObject, _In_ PUNICODE_STRING RegistryPath)
{
    UNREFERENCED_PARAMETER(RegistryPath);

    DriverObject->DriverUnload = DriverUnload;

    KeInitializeTimer(&Timer);

    // Initialize the DPC.
    KeInitializeDpc(&Dpc, DpcRoutine, NULL);

    LARGE_INTEGER dueTime;
    dueTime.QuadPart = -10000000; // 1 second
    KeSetTimer(&Timer, dueTime, &Dpc);

    return STATUS_SUCCESS;
}
