__int64 __fastcall UefiEsrtOpenFirmwareResourcesKey(PHANDLE KeyHandle) {
  SIZE_T BuffLengthIn; 
  int PersistedStateLocation; 
  PVOID PoolWithTag; 
  int v6; 
  int v7; 
  struct _UNICODE_STRING DestinationString; 
  unsigned int BuffLengthOut; 

  BuffLengthOut = 0;
  DestinationString = 0i64;
  BuffLengthIn = 276i64;
  
  while ( 1 ) {
    PoolWithTag = ExAllocatePoolWithTag(PagedPool, BuffLengthIn, 0x49464555u);
    
	if ( !PoolWithTag ) {
      PersistedStateLocation = 0xC000009A;
      goto LABEL_7;
    }
	
    PersistedStateLocation = RtlGetPersistedStateLocation(
                               L"FirmwareResources",
                               0i64,
                               L"\\REGISTRY\\MACHINE\\SYSTEM\\CurrentControlSet\\Control\\FirmwareResources",
                               0i64,
                               PoolWithTag,
                               BuffLengthIn,
                               &BuffLengthOut);
    
	if ( PersistedStateLocation != 0x80000005 )
      break;
    
	if ( BuffLengthOut <= BuffLengthIn ) {
      PersistedStateLocation = 0xC00000E5;
      break;
    }
	
    BuffLengthIn = BuffLengthOut;
    ExFreePoolWithTag(PoolWithTag, 0);
  }
  
  if ( PersistedStateLocation >= 0 ) {
    RtlInitUnicodeString(&DestinationString, PoolWithTag);
    
	PersistedStateLocation = UefiCreateRegistryKey(0, &DestinationString, v6, v7, 0i64, KeyHandle);
  }
  
LABEL_7:
  if ( PoolWithTag )
    ExFreePoolWithTag(PoolWithTag, 0);
  
  return PersistedStateLocation;
}