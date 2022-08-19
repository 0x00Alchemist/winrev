__int64 __fastcall UefiEsrtStartDevice(PDEVICE_OBJECT Pdo) {
  __int64 KeyValueInfo_swap; 
  _QWORD *DeviceExtension; 
  int ValueInfoData; 
  char unkSpecSymb_1; 
  __int64 FirmwareRes_Data; 
  int *ptrData; 
  int RegistryValues; 
  int RegValues; 
  __int64 DateData_swap; 
  unsigned int unkFirmwareData_swap; 
  int FirmwareData; 
  char unkSpecSymbFlag; 
  __int64 InstallDateData_swap; 
  __int64 v15; 
  __int64 v16; 
  unsigned int HIResLength; 
  bool ResLengthFlag; 
  __int64 SysTimeLowPart; 
  __int64 v20; 
  unsigned __int64 FirmDataOffset; 
  __int64 pattern_1; 
  int PropData; 
  ULONG ReqSizeElem; 
  NTSTATUS DeleteKeyStatus_1; 
  NTSTATUS DeleteKeyStatus; 
  int unkFirmwareData; 
  char v29; 
  char unkSpecSymb; 
  unsigned int ControlFlow; 
  ULONG RequiredSize[3]; 
  int PhaseFirmwareValueNameData; 
  HANDLE KeyHandle; 
  int PoolWithTag; 
  __int64 ResLength; 
  unsigned int Data; 
  int ValueInfo; 
  int unkPhaseData; 
  void *DeviceRegKey; 
  __int64 InstallDateData; 
  HANDLE KeyHandle_1; 
  int pValueInfo; 
  int pData; 
  __int64 DateData; 
  __int64 KeyValueInfo; 
  __int64 SysTimeLowPartData; 
  struct _UNICODE_STRING UnicodeString; 
  UNICODE_STRING GuidString; 
  HANDLE Handle; 
  struct _UNICODE_STRING DestinationString; 
  struct _UNICODE_STRING BuffStr; 
  struct _UNICODE_STRING BuffStr_1; 
  GUID Guid; 
  __int128 SystemInformation[3];
  __int64 QueryTable[42]; // __SKVLLZ.: RTL_QUERY_REGISTRY_TABLE

  KeyValueInfo_swap = 0i64;
  DeviceRegKey = 0i64;
  unkFirmwareData = -1;
  DeviceExtension = Pdo->DeviceExtension;
  KeyHandle_1 = 0i64;
  Guid = 0i64;
  *&GuidString.Length = 0i64;
  GuidString.Buffer = 0i64;
  ValueInfoData = 0;
  *&UnicodeString.Length = 0i64;
  unkSpecSymb_1 = 0;
  UnicodeString.Buffer = 0i64;
  *&DestinationString.Length = 0i64;
  DestinationString.Buffer = 0i64;
  ControlFlow = 0;
  *&BuffStr.Length = 0i64;
  BuffStr.Buffer = 0i64;
  *&BuffStr_1.Length = 0i64;
  BuffStr_1.Buffer = 0i64;
  DateData = 0i64;
  PhaseFirmwareValueNameData = 0;
  KeyHandle = 0i64;
  Handle = 0i64;
  InstallDateData = 0i64;
  unkPhaseData = 0;
  SysTimeLowPartData = 0i64;
  Data = 0;
  RequiredSize[0] = 0;
  RequiredSize[1] = 0;
  RequiredSize[2] = 0;
  FirmwareRes_Data = DeviceExtension[4];
  ValueInfo = 0;
  KeyValueInfo = 0i64;
  unkSpecSymb = 0;
  pData = 0;
  pValueInfo = 0;
  PoolWithTag = 0;
  ResLength = 0xFFFFFFFF00000000ui64;
  v29 = 0;
  
  if ( IoGetDevicePropertyData(
         Pdo,
         &DEVPKEY_FirmwareResource_Version,
         0,
         0,
         4u,
         &Data,
         &RequiredSize[2],
         &RequiredSize[1]) < 0
    || RequiredSize[2] != 4
    || RequiredSize[1] != 7 )
  {
    Data = *(FirmwareRes_Data + 20);
  }
  
  // __SKVLLZ.: Setting Firmware Resource information 
  IoSetDevicePropertyData(Pdo, &DEVPKEY_FirmwareResource_Id, 0, 0, 0xDu, 0x10u, FirmwareRes_Data);
  IoSetDevicePropertyData(Pdo, &DEVPKEY_FirmwareResource_Type, 0, 0, 7u, 4u, (FirmwareRes_Data + 16));
  ptrData = (FirmwareRes_Data + 20);
  IoSetDevicePropertyData(Pdo, &DEVPKEY_FirmwareResource_Version, 0, 0, 7u, 4u, (FirmwareRes_Data + 20));
  IoSetDevicePropertyData(Pdo, &DEVPKEY_FirmwareResource_LowestSupportedVersion, 0, 0, 7u, 4u, (FirmwareRes_Data + 24));
  
  if ( IoOpenDeviceRegistryKey(Pdo, 1u, 0x20019u, &DeviceRegKey) < 0 )
    goto LABEL_28;
  
  memset(QueryTable, 0, sizeof(QueryTable));
  
  LODWORD(QueryTable[1]) = 288;
  LODWORD(QueryTable[4]) = 0x1000000;
  LODWORD(QueryTable[8]) = 288;
  QueryTable[2] = L"FirmwareId";
  LODWORD(QueryTable[11]) = 0x1000000;
  QueryTable[3] = &GuidString;
  QueryTable[9] = L"FirmwareFilename";
  QueryTable[10] = &UnicodeString;
  QueryTable[16] = L"FirmwareVersion";
  QueryTable[17] = &ControlFlow;
  QueryTable[23] = L"FirmwareVersionFormat";
  QueryTable[24] = &BuffStr_1;
  QueryTable[30] = L"FirmwareStatus";
  LODWORD(QueryTable[15]) = 288;
  LODWORD(QueryTable[18]) = 0x4000000;
  LODWORD(QueryTable[22]) = 288;
  LODWORD(QueryTable[25]) = 0x1000000;
  LODWORD(QueryTable[29]) = 288;
  LODWORD(QueryTable[32]) = 0x4000000;
  QueryTable[31] = &unkFirmwareData;
  
  RegistryValues = RtlQueryRegistryValuesEx(0xC0000000i64, DeviceRegKey, QueryTable, 0i64, 0i64);
  RegValues = RegistryValues;
  if ( RegistryValues < 0 ) {
    if ( RegistryValues != 0xC0000024 ) {
LABEL_29:
      FirmwareData = unkFirmwareData;
      goto LABEL_30;
    }
	
LABEL_8:
    RegValues = 0xC0000182;
    goto LABEL_29;
  }
  
  if ( !ControlFlow
    || IoGetDevicePropertyData(Pdo, &DEVPKEY_Device_DriverDate, 0, 0, 8u, &DateData, &RequiredSize[2], &RequiredSize[1]) >= 0
    && RequiredSize[1] == 16
    && RequiredSize[2] == 8 ) {
    DateData_swap = DateData;
  } else {
    DateData_swap = 0i64;
    DateData = 0i64;
  }
  
  if ( DateData_swap )
    IoSetDevicePropertyData(Pdo, &DEVPKEY_Device_FirmwareDate, 0, 0, 0x10u, 8u, &DateData);
  else
    IoSetDevicePropertyData(Pdo, &DEVPKEY_Device_FirmwareDate, 0, 0, 0, 0, 0i64);
  
  if ( UefiEsrtGetFirmwareVersionString(*ptrData, &BuffStr_1.Length, &BuffStr) < 0 )
    IoSetDevicePropertyData(Pdo, &DEVPKEY_Device_FirmwareVersion, 0, 0, 0, 0, 0i64);
  else
    IoSetDevicePropertyData(Pdo, &DEVPKEY_Device_FirmwareVersion, 0, 0, 0x12u, BuffStr.Length + 2, BuffStr.Buffer);
  
  if ( !GuidString.Buffer || !UnicodeString.Buffer || !ControlFlow ) {
LABEL_28:
    RegValues = 0;
    goto LABEL_29;
  }
  
  unkFirmwareData_swap = unkFirmwareData;
  
  if ( unkFirmwareData >= 1 )
    unkFirmwareData_swap = 0xC0000184;
  
  unkFirmwareData = unkFirmwareData_swap;
  if ( ControlFlow == *ptrData ) {
    unkFirmwareData = 0;
    RegValues = ZwSetValueKey(DeviceRegKey, &UefiFirmwareStatusValueName, 0, 4u, &unkFirmwareData, 4u);
    if ( RegValues < 0 )
      goto LABEL_29;
    goto LABEL_28;
  }
  
  RegValues = RtlGUIDFromString(&GuidString, &Guid);
  if ( RegValues < 0 )
    goto LABEL_29;
  if ( *&Guid.Data1 != *FirmwareRes_Data || *Guid.Data4 != *(FirmwareRes_Data + 8) )
    goto LABEL_8;
  
  RegValues = IoOpenDeviceRegistryKey(Pdo, 2u, 0x20019u, &KeyHandle_1);
  
  if ( RegValues < 0 )
    goto LABEL_29;
  
  if ( UefiQueryRegistryValue(
         KeyHandle_1,
         &UefiFirmwareInstallDateValueName,
         &PoolWithTag,
         &KeyValueInfo,
         8u,
         &ResLength) >= 0
    && PoolWithTag == 3
    && ResLength == 8 ) {
    KeyValueInfo_swap = KeyValueInfo;
  } else {
    KeyValueInfo = 0i64;
  }
  
  if ( IoGetDevicePropertyData(
         Pdo,
         &DEVPKEY_Device_InstallDate,
         0,
         0,
         8u,
         &InstallDateData,
         &RequiredSize[2],
         &RequiredSize[1]) >= 0
    && RequiredSize[1] == 16
    && RequiredSize[2] == 8 ) {
    InstallDateData_swap = InstallDateData;
  } else {
    InstallDateData_swap = 0i64;
    InstallDateData = 0i64;
  }
  
  if ( KeyValueInfo_swap ) {
    if ( KeyValueInfo_swap == InstallDateData_swap ){
      FirmwareData = unkFirmwareData;
	  
      if ( unkFirmwareData != -1 && Data <= *ptrData ) {
        RegValues = unkFirmwareData;
        goto LABEL_30;
      }
    }
  }
  
  RegValues = UefiEsrtOpenFirmwareResourcesKey(&Handle);
  
  if ( RegValues < 0 )
    goto LABEL_29;
  
  RegValues = UefiCreateRegistryKey(Handle, &GuidString, v15, v16, RequiredSize, &KeyHandle);
  if ( RegValues < 0 )
    goto LABEL_29;
  if ( RequiredSize[0] != 2 ) {
    v20 = 1i64;
    if ( RequiredSize[0] == 1 && ControlFlow < *ptrData )
    {
      ZwDeleteKey(KeyHandle);
	  
LABEL_82:
      v20 = 1i64;
      goto LABEL_83;
    }
	
    goto LABEL_83;
  }
  
  HIResLength = unkFirmwareData;
  if ( unkFirmwareData == -1 && KeyValueInfo_swap == InstallDateData ) {
	// __SKVLLZ.: Phase (?) information about device
    memset(QueryTable, 0, sizeof(QueryTable));
    QueryTable[2] = L"Phase";
    LODWORD(QueryTable[1]) = 288;
    LODWORD(QueryTable[4]) = 0x4000000;
    QueryTable[3] = &PhaseFirmwareValueNameData;
    LODWORD(QueryTable[8]) = 288;
    QueryTable[9] = L"LastAttemptStatus";
    LODWORD(QueryTable[11]) = 0x4000000;
    QueryTable[10] = &ResLength + 4;
    QueryTable[16] = L"LastAttemptVersion";
    LODWORD(QueryTable[15]) = 288;
    LODWORD(QueryTable[18]) = 0x4000000;
    QueryTable[17] = &unkPhaseData;
	
    if ( RtlQueryRegistryValuesEx(0xC0000000i64, KeyHandle, QueryTable, 0i64, 0i64) < 0 ) {
      PhaseFirmwareValueNameData = 0;
      unkFirmwareData = -1;
      goto LABEL_59;
    }
	
    HIResLength = HIDWORD(ResLength);
    if ( HIDWORD(ResLength) == -1 ) {
      ResLengthFlag = 0;
    } else {
      ResLengthFlag = HIDWORD(ResLength) == 0;
      
	  if ( !HIDWORD(ResLength) )
        goto LABEL_69;
      
	  if ( ResLength >= 0 ) {
        HIResLength = 0xC000022D;
LABEL_70:
        unkFirmwareData = HIResLength;
        goto LABEL_71;
      }
    }
	
    if ( !ResLengthFlag )
      goto LABEL_70;
  
LABEL_69:
    HIResLength = 0xC0000186;
    goto LABEL_70;
  }
  
LABEL_71:
  if ( !PhaseFirmwareValueNameData || HIResLength == -1 ) {
LABEL_59:
    RequiredSize[0] = 1;
    RegValues = UefiQueryRegistryValue(
                  KeyHandle,
                  &UefiFirmwarePolicyValueName,
                  &PoolWithTag,
                  &ValueInfo,
                  4u,
                  &ResLength);
    
	if ( RegValues >= 0 && PoolWithTag == 4 && ResLength == 4 )
      ValueInfoData = ValueInfo;
    else
      RegValues = 0;
  
    goto LABEL_82;
  }
  
  RegValues = ZwSetValueKey(DeviceRegKey, &UefiFirmwareStatusValueName, 0, 4u, &unkFirmwareData, 4u);
  
  if ( RegValues < 0 )
    goto LABEL_29;
  
  // __SKVLLZ.: Set info about latest version and status of some device object
  IoSetDevicePropertyData(Pdo, &DEVPKEY_FirmwareResource_LastAttemptVersion, 0, 0, 7u, 4u, &unkPhaseData);
  IoSetDevicePropertyData(Pdo, &DEVPKEY_FirmwareResource_LastAttemptStatus, 0, 0, 0x18u, 4u, &ResLength + 4);
  memset(SystemInformation, 0, sizeof(SystemInformation));
  
  if ( ZwQuerySystemInformation(SystemTimeOfDayInformation, SystemInformation, 0x30u, 0i64) < 0 ) {
    SysTimeLowPart = *&KUSER_SHARED_DATA.SystemTime.LowPart;
    ValueInfoData = ValueInfo;
    KeyValueInfo_swap = KeyValueInfo;
  } else {
    SysTimeLowPart = *&SystemInformation[0];
  }
  
  SysTimeLowPartData = SysTimeLowPart;
  IoSetDevicePropertyData(Pdo, &DEVPKEY_FirmwareResource_LastAttemptDate, 0, 0, 0x10u, 8u, &SysTimeLowPartData);
  
  v20 = 1i64;
  unkSpecSymb = 1;

LABEL_83:
  FirmwareData = unkFirmwareData;
  if ( !PhaseFirmwareValueNameData )
    goto LABEL_96;
  
  if ( RequiredSize[0] != 1 ) {
    if ( (unkFirmwareData + 1) <= 1 )
      goto LABEL_96;
    
	v29 = 0;
	// __SKVLLZ.: I think it's about checking firmware data on specific NTSTATUS
    if ( unkFirmwareData > 0xC00000BB ) {
      if ( unkFirmwareData == 0xC0000186 || unkFirmwareData == 0xC000022D )
        goto LABEL_93;
	
      if ( unkFirmwareData != 0xC00002D3 && unkFirmwareData != 0xC00002DE ) {
        if ( unkFirmwareData != 0xC00004B9 )
          goto LABEL_96;
        
		goto LABEL_93;
      }
    } else if ( unkFirmwareData == 0xC00000BB ) {
      v29 = 1;
    } else {
      FirmDataOffset = (unkFirmwareData + 0x3FFFFFFF);
      if ( FirmDataOffset <= 0x2C ) {
        pattern_1 = 0x100200000001i64;
        
		if ( _bittest64(&pattern_1, FirmDataOffset) )
          goto LABEL_93;
      }
	  
      if ( unkFirmwareData == 0xC0000058 )
        goto LABEL_93;
      
	  if ( unkFirmwareData != 0xC000009A )
        goto LABEL_96;
    }
    LOBYTE(v20) = 0;
	
LABEL_93:
    PropData = UefiEsrtRetryFirmwareUpdate(Pdo, KeyHandle_1, v20, &pData, &pValueInfo);
    FirmwareData = unkFirmwareData;
    RegValues = PropData;
    ReqSizeElem = RequiredSize[0];
    
	if ( RegValues >= 0 )
      ReqSizeElem = 1;
    
	RequiredSize[0] = ReqSizeElem;

LABEL_96:
    if ( RequiredSize[0] != 1 )
      goto LABEL_121;
  }
  
  if ( ControlFlow > *ptrData || ValueInfoData ) {
    if ( ValueInfoData && ControlFlow < *(FirmwareRes_Data + 24) ) {
      RegValues = 0xC0000424;
      goto LABEL_30;
    }
	
    RegValues = ZwSetValueKey(KeyHandle, &UefiFirmwareVersionValueName, 0, 4u, &ControlFlow, 4u);
    if ( RegValues < 0 )
      goto LABEL_29;
    
	RegValues = ZwSetValueKey(
                  KeyHandle,
                  &UefiFirmwareFilenameValueName,
                  0,
                  1u,
                  UnicodeString.Buffer,
                  UnicodeString.Length + 2);
    
	if ( RegValues < 0 )
      goto LABEL_29;
    
	PhaseFirmwareValueNameData = 0;
    RegValues = ZwSetValueKey(KeyHandle, &UefiFirmwarePhaseValueName, 0, 4u, &PhaseFirmwareValueNameData, 4u);
    
	if ( RegValues < 0 )
      goto LABEL_29;
    
	if ( UefiEsrtGetDriverCatalogName(Pdo, &DestinationString) < 0 ) {
      RegValues = ZwDeleteValueKey(KeyHandle, &UefiFirmwareCatalogValueName);
	  
      if ( (RegValues + 0x80000000) >= 0 && RegValues != 0xC0000034 )
        goto LABEL_29;
    } else {
      RegValues = ZwSetValueKey(
                    KeyHandle,
                    &UefiFirmwareCatalogValueName,
                    0,
                    1u,
                    DestinationString.Buffer,
                    DestinationString.Length + 2);
      
	  if ( RegValues < 0 )
        goto LABEL_29;
    }
    
	DeleteKeyStatus_1 = ZwDeleteValueKey(DeviceRegKey, &UefiFirmwareStatusValueName);
    RegValues = DeleteKeyStatus_1;
    if ( DeleteKeyStatus_1 == 0xC0000034 ) {
      RegValues = 0;
    } else if ( DeleteKeyStatus_1 < 0 ) {
      goto LABEL_29;
    }
	
    IoSetDevicePropertyData(Pdo, &DEVPKEY_FirmwareResource_PendingVersion, 0, 0, 7u, 4u, &ControlFlow);
    unkSpecSymb_1 = 1;
	
    goto LABEL_124;
  }
  
LABEL_121:
  if ( ControlFlow < *ptrData && !ValueInfoData ) {
    unkFirmwareData = 0;
    RegValues = ZwSetValueKey(DeviceRegKey, &UefiFirmwareStatusValueName, 0, 4u, &unkFirmwareData, 4u);
    
	if ( RegValues < 0 )
      goto LABEL_29;

LABEL_124:
    FirmwareData = unkFirmwareData;
  }
  
  if ( KeyValueInfo_swap != InstallDateData ) {
    RegValues = ZwSetValueKey(KeyHandle_1, &UefiFirmwareInstallDateValueName, 0, 3u, &InstallDateData, 8u);
    
	if ( RegValues < 0 )
      goto LABEL_29;
    
	DeleteKeyStatus = ZwDeleteValueKey(KeyHandle_1, &UefiFirmwareRetryCountValueName);
    RegValues = DeleteKeyStatus;
	
    if ( DeleteKeyStatus == 0xC0000034 ) {
      RegValues = 0;
    } else if ( DeleteKeyStatus < 0 ) {
      goto LABEL_29;
    }
	
    FirmwareData = unkFirmwareData;
  }
  
  if ( unkSpecSymb_1 ) {
    RegValues = FirmwareData;
	
    if ( !v29 )
      RegValues = 0xC00002D2;
  } else if ( FirmwareData ) {
    RegValues = 0xC00000E5;
	
    if ( FirmwareData != -1 )
      RegValues = FirmwareData;
  }
  
LABEL_30:
  unkSpecSymbFlag = unkSpecSymb;
  // __SKVLLZ.: After getting all info about device we starting trace log function
  UefiEsrtTraceLog(
    FirmwareRes_Data,
    *(FirmwareRes_Data + 16),
    *ptrData,
    *(FirmwareRes_Data + 24),
    *(FirmwareRes_Data + 32),
    *(FirmwareRes_Data + 36),
    unkPhaseData,
    SHIDWORD(ResLength),
    &SysTimeLowPartData,
    unkSpecSymb,
    unkSpecSymb_1,
    pData,
    pValueInfo,
    &UnicodeString.Length,
    ControlFlow,
    FirmwareData,
    ValueInfoData,
    RegValues);

  // __SKVLLZ.: If smth going wrong, we write it in device property field "Problem Status Override)
  if ( RegValues == 0xC00002D2 && (unkFirmwareData + 1) > 1 )
    IoSetDevicePropertyData(Pdo, &DEVPKEY_Device_ProblemStatusOverride, 0, 0, 0x18u, 4u, &unkFirmwareData);
  else
    IoSetDevicePropertyData(Pdo, &DEVPKEY_Device_ProblemStatusOverride, 0, 0, 0, 0, 0i64);
  
  // __SKVLLZ.: Setting pending verison to zero, maybe
  if ( !unkSpecSymb_1 )
    IoSetDevicePropertyData(Pdo, &DEVPKEY_FirmwareResource_PendingVersion, 0, 0, 0, 0, 0i64);
  
  // __SKVLLZ.: Zeroing some attempts properties
  if ( !unkSpecSymbFlag ) {
    IoSetDevicePropertyData(Pdo, &DEVPKEY_FirmwareResource_LastAttemptVersion, 0, 0, 0, 0, 0i64);
    IoSetDevicePropertyData(Pdo, &DEVPKEY_FirmwareResource_LastAttemptStatus, 0, 0, 0, 0, 0i64);
    IoSetDevicePropertyData(Pdo, &DEVPKEY_FirmwareResource_LastAttemptDate, 0, 0, 0, 0, 0i64);
  }
  
  if ( KeyHandle )
    ZwClose(KeyHandle);
  
  if ( Handle )
    ZwClose(Handle);
  
  RtlFreeUnicodeString(&GuidString);
  RtlFreeUnicodeString(&UnicodeString);
  RtlFreeUnicodeString(&DestinationString);
  RtlFreeUnicodeString(&BuffStr);
  RtlFreeUnicodeString(&BuffStr_1);
  
  if ( DeviceRegKey )
    ZwClose(DeviceRegKey);
  
  if ( KeyHandle_1 )
    ZwClose(KeyHandle_1);
  
  return RegValues;
}