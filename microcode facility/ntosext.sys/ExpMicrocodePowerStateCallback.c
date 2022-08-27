void __fastcall ExpMicrocodePowerStateCallback(PVOID CallbackContext, PVOID Argument1, PVOID Argument2) {
  if ( Argument1 == 3 ) {
    if ( Argument2 ) {
      if ( Argument2 == 1 ) {
        ExpReleaseMicrocodeUpdateLock(CallbackContext); // __SKVLLZ.: Releasing CallbackContext block
        (HalPrivateDispatchTable[0x1A])();
      }
    } else {
      ExpAcquireMicrocodeUpdateLock();
    }
  }
}