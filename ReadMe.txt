note this is only a base driver to print text to dbgview kernel

this base initializes the timer and the DPC object. The timer is set to trigger every second, 
at which point the DPC is called, and the DebugPrintRoutine will be executed to print the incremented values.

this code isnt optimized, this runs functions until functions so please be aware of the cpu usage