__int64 __fastcall UefiOpenDeviceClassRegistryKey(GUID *Guid, __int64 a2, void **KeyHandle) {
  NTSTATUS RegGuidStr; 
  // __SKVLLZ: v6 and v7 - unused
  __int64 v6; 
  __int64 v7; 
  struct _UNICODE_STRING GuidString; 
  HANDLE Handle; 

  Handle = 0i64;
  GuidString = 0i64;
  
  RtlInitUnicodeString(&GuidString, 0i64);
  RegGuidStr = RtlStringFromGUID(Guid, &GuidString);
  
  if ( RegGuidStr >= 0 ) {
    RegGuidStr = UefiOpenRegistryKey(0i64, aPr, v6, &Handle);
    
	if ( RegGuidStr >= 0 )
      RegGuidStr = UefiOpenRegistryKey(Handle, &GuidString, v7, KeyHandle);
  }
  
  if ( Handle )
    ZwClose(Handle);
  
  RtlFreeUnicodeString(&GuidString);
  return RegGuidStr;
}