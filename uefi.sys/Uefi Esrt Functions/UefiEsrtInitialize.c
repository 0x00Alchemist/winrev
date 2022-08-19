__int64 __fastcall UefiEsrtInitialize(struct _UNICODE_STRING *RegistryPath, __int64 a2, __int64 AccessMask) {
  __int64 _AccessMask; 
  __int64 __AccessMask; 
  __int64 SystemInformation; 
  HANDLE Handle; 
  HANDLE DirHandle; 

  Handle = 0i64;
  DirHandle = 0i64;
  qword_1C0003070 = &P;
  P = &P;
  
  if( UefiOpenRegistryKey(0i64, L"HJ", AccessMask, &Handle) >= 0 ) {
    UefiEsrtQueryFirmwareResources(Handle);
    ZwClose(Handle);
  }
  
  if ( UefiOpenRegistryKey(0i64, RegistryPath, _AccessMask, &DirHandle) >= 0 ) {
    SystemInformation = 8i64;
	// __SKVLLZ: Oh shit oh fuck
    if ( ZwQuerySystemInformation(MaxSystemInfoClass|SystemProcessInformation, &SystemInformation, 8u, 0i64) >= 0
      && (SystemInformation & 0x200000000i64) != 0
      && UefiOpenRegistryKey(DirHandle, &UefiEsrtServiceSubKeyPath, __AccessMask, &Handle) >= 0 ) {
      UefiEsrtQueryFirmwareResources(Handle);
      
	  ZwClose(Handle);
    }
	
    ZwClose(DirHandle);
  }
  
  return 0i64;
}