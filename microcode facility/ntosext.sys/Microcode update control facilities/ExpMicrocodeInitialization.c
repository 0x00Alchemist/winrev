NTSTATUS __fastcall ExpMicrocodeInitialization(BYTE flag) {
  NTSTATUS result; 
  __int64 v2; 
  __int64 v3; 
  __int64 v4; 
  __int64 v5; 
  PCALLBACK_OBJECT CallbackObject; 
  struct _UNICODE_STRING DestString; 
  struct _UNICODE_STRING DestinationString; 
  struct _OBJECT_ATTRIBUTES ObjectAttributes; 
  PHV_X64_HYPERVISOR_FEATURES HvpFeatures; 

  *(&ObjectAttributes.Length + 1) = 0;
  *(&ObjectAttributes.Attributes + 1) = 0;
  CallbackObject = 0i64;
  DestString = 0i64;
  DestinationString = 0i64;
  
  if ( flag == 1 ) {
    RtlInitUnicodeString(&DestinationString, L"mcupdate.dll"); 
    ExpInitializeMicrocodeUpdateLock();         // __SKVLLZ.: Init FAST mutex
    RtlInitUnicodeString(&DestString, L"\\Callback\\PowerState");
    
	ObjectAttributes.RootDirectory = 0i64;
    ObjectAttributes.ObjectName = &DestString; // __SKVLLZ.: opening PowerState callback
    ObjectAttributes.Length = 48;
    ObjectAttributes.Attributes = 80;
    *(&ObjectAttributes.SecurityDescriptor) = 0i64;
    
	result = ExCreateCallback(&CallbackObject, &ObjectAttributes, 0, 1u);
    if ( result < 0 )
      return result;
    
	ExpMicrocodeCallbackRegistrationHandle = ExRegisterCallback(CallbackObject, ExpMicrocodePowerStateCallback, 0i64);
    
	if ( !ExpMicrocodeImageHandle ) {
      KeEnterCriticalRegion();
      ExAcquireResourceSharedLite(PsLoadedModuleResource, 1u);
      ExReleaseResourceLite(PsLoadedModuleResource);
      KeLeaveCriticalRegion();
    }
  } else if ( flag == 2 ) {
    *(&HvpFeatures) = 0i64;
	
	// __SKVLLZ.: Get Microsoft-compatible features
    HviGetHypervisorFeatures(&HvpFeatures);
    if ( (HvpFeatures & 0x100000000000i64) != 0 ) {
      ExpMicrocodeInformationUnload();
	  
      if ( ExpMicrocodeCallbackRegistrationHandle )
        ExUnregisterCallback(ExpMicrocodeCallbackRegistrationHandle);
    
	} else {
		// __SKVLLZ.: Really cannot say what is it
      HalPrivateDispatchTable[0x1A](v3, v2, v4, v5, CallbackObject);
    }
  }
  
  return 0;
}