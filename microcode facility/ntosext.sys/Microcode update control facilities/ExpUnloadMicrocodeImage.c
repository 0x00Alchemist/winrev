NTSTATUS __stdcall ExpUnloadMicrocodeImage() {
  NTSTATUS Status; 

  Status = 0;
  if ( ExpMicrocodeImageHandle ) {
	  // __SKVLLZ.: idddddkkk
    Status = (HalPrivateDispatchTable[0x19])(0i64);
    
	if ( Status >= 0 ) {
		// __SKVLLZ.: Unloading image
      Status = MmUnloadSystemImage(ExpMicrocodeImageHandle);
      
	  if ( Status >= 0 )
        ExpMicrocodeImageHandle = 0i64;
    }
  }
  
  return Status;
}