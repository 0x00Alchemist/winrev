__int64 __fastcall UefiEsrtRetryFirmwareUpdate(
        struct _DEVICE_OBJECT *Pdo,
        void *KeyHandle,
        __int64 a3,
        unsigned int *pData,
        unsigned int *pValueInfo)
{
  unsigned int HIValueInfo; 
  char v7; 
  __int64 v9; 
  int DevicePropertyData; 
  unsigned int Data; 
  int InfoClass; 
  __int64 ValueInfo; 
  ULONG Type; 
  ULONG RequiredSize[3]; 
  GUID Guid; 

  HIValueInfo = 0;
  Data = 0;
  InfoClass = 0;
  v7 = a3;
  ValueInfo = 0i64;
  Type = 0;
  
  memset(RequiredSize, 0, sizeof(RequiredSize));
  Guid = 0i64;
  
  DevicePropertyData = IoGetDevicePropertyData(Pdo, &DEVPKEY_Device_ClassGuid, 0, 0, 0x10u, &Guid, RequiredSize, &Type);
  if ( DevicePropertyData < 0 )
    goto LABEL_22;

  if ( Type != 13 || RequiredSize[0] != 16 ) {

LABEL_21:
    DevicePropertyData = 0xC000090B;
    goto LABEL_22;
  }
  
  DevicePropertyData = UefiOpenDeviceClassRegistryKey(&Guid, v9, &RequiredSize[1]);
  
  if ( DevicePropertyData < 0 )
    goto LABEL_22;

  // __SKVLLZ.: I'm not sure that's the right interpretation
  DevicePropertyData = UefiQueryRegistryValue(  
                         *&RequiredSize[1],
                         &UefiFirmwareMaxRetryCountValueName,
                         &InfoClass,
                         &ValueInfo + 4,
                         4u,
                         &ValueInfo);
  
  if ( DevicePropertyData < 0 ) {
    HIValueInfo = HIDWORD(ValueInfo);
    goto LABEL_22;
  }
  
  if ( InfoClass != 4 || ValueInfo != 4 ) {
    HIValueInfo = HIDWORD(ValueInfo);
    goto LABEL_21;
  }
  
  HIValueInfo = HIDWORD(ValueInfo);
  if ( HIDWORD(ValueInfo) ) {
    DevicePropertyData = UefiQueryRegistryValue(
                           KeyHandle,
                           &UefiFirmwareRetryCountValueName,
                           &InfoClass,
                           &Data,
                           4u,
                           &ValueInfo);
    
	if ( DevicePropertyData < 0 || InfoClass != 4 || ValueInfo != 4 ) {
      DevicePropertyData = 0;
      Data = 0;
    }
	
    if ( HIValueInfo == -1 || Data < HIValueInfo ) {
      if ( v7 && Data != -1 ) {
        ++Data;
        ZwSetValueKey(KeyHandle, &UefiFirmwareRetryCountValueName, 0, 4u, &Data, 4u);
      }
    } else {
      DevicePropertyData = 0xC000042B;
    }
	
  } else {
    DevicePropertyData = 0xC0000364;
  }
  
LABEL_22:
  if ( *&RequiredSize[1] )
    ZwClose(*&RequiredSize[1]);
  
  if ( pData )
    *pData = Data;
  
  if ( pValueInfo )
    *pValueInfo = HIValueInfo;
  
  return DevicePropertyData;
}