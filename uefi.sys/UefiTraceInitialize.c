NTSTATUS UefiTraceInitialize() {
  GUID EventInfoGuid;
  NTSTATUS result; 
  GUID ProviderId; 

  EventInfoGuid = *(EventInformation - 1);
  
  xmmword_1C0003038 = 0i64;
  
  ProviderId = EventInfoGuid;
  result = EtwRegister(&ProviderId, tlgEnableCallback, &dword_1C0003010, &RegHandle);
  if ( !result )
    return EtwSetInformation(RegHandle, EventProviderSetTraits, EventInformation, *EventInformation);
  
  return result;
}