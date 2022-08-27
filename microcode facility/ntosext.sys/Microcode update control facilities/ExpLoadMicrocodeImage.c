NTSTATUS __stdcall ExpLoadMicrocodeImage() {
  int MicrocodeImageFileName; 
  int Status; 
  _DWORD *ExportedRoutineByName; 
  struct _UNICODE_STRING DestinationString; 
  struct _UNICODE_STRING BaseName; 
  PVOID ImageHandle; 
  PVOID ImageBaseAddress; 

  ImageBaseAddress = 0i64;
  ImageHandle = 0i64;
  DestinationString = 0i64;
  BaseName = 0i64;
  
  RtlInitUnicodeString(&DestinationString, 0i64);
  if ( ExpMicrocodeImageHandle ) {
    MicrocodeImageFileName = 0xC0000022;
    goto LABEL_14;
  }
  
  RtlInitUnicodeString(&DestinationString, 0i64);
  
  // __SKVLLZ.: Getting .dll image of microcode updater
  MicrocodeImageFileName = ExpGetMicrocodeImageFileName(&DestinationString);
  if ( MicrocodeImageFileName >= 0 ) {
    RtlInitUnicodeString(&BaseName, L"mcupdate.dll");
    
	// __SKVLLZ.: here we go
	Status = MmLoadSystemImage(&DestinationString, 0i64, &BaseName, 0i64, &ImageHandle, &ImageBaseAddress);
    MicrocodeImageFileName = Status;
    if ( Status < 0 ) {
      if ( Status == 0xC0000034 )
        MicrocodeImageFileName = 0;

LABEL_13:
      if ( MicrocodeImageFileName >= 0 )
        goto LABEL_16;

      goto LABEL_14;
    }
    
	/* __SKVLLZ.: If we loaded updater successfully we gonna search specific exported routine named "MciImageInfo",
	  both Intel and AMD has it */
	ExportedRoutineByName = RtlFindExportedRoutineByName(ImageBaseAddress, "McImageInfo");
    if ( !ExportedRoutineByName || *ExportedRoutineByName != 1 || ExportedRoutineByName[1] != 56 ) {
      MicrocodeImageFileName = 0xC0000059;
      goto LABEL_13;
    }
	
	// __SKVLLZ.: shitposting on HalLocateHiberRanges runtime function
    MicrocodeImageFileName = (HalPrivateDispatchTable[0x18])(ImageHandle);
    if ( MicrocodeImageFileName >= 0 ) {
      ExpMicrocodeImageHandle = ImageHandle;
	  
	  // __SKVLLZ.: Cannot say what is it really. Maybe some unknown shit?
      (HalPrivateDispatchTable[0x1A])();
	  
      goto LABEL_13;
    }
  }
  
LABEL_14:
  if ( ImageHandle )
    MmUnloadSystemImage(ImageHandle);

LABEL_16:
  if ( DestinationString.Buffer )
    ExFreePoolWithTag(DestinationString.Buffer, 0x646F4375u);

  return MicrocodeImageFileName;
}