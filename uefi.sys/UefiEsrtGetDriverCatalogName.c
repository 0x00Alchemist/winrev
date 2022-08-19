__int64 __fastcall UefiEsrtGetDriverCatalogName(PDEVICE_OBJECT Pdo, PUNICODE_STRING DestinationString) {
  PVOID Data; 
  NTSTATUS DevicePropertyData; 
  NTSTATUS DevicePropData; 
  wchar_t *DataFound; 
  char *specChr; 
  __int64 j; 
  signed __int64 unknwn; 
  __int64 i; 
  __int16 idklol; 
  char *v13; 
  SIZE_T NumberOfBytes; 
  ULONG Type; 

  Type = 0;
  LODWORD(NumberOfBytes) = 0;
  Data = 0i64;
  
  DevicePropertyData = IoGetDevicePropertyData(Pdo, &DEVPKEY_Device_DriverInfPath, 0, 0, 0, 0i64, &NumberOfBytes, &Type);
  
  DevicePropData = DevicePropertyData;
  if ( DevicePropertyData != 0xC0000023 ) {
    if ( DevicePropertyData >= 0 )
      return 0xC00000E5;
  
    return DevicePropData;
  }
  
  if ( Type != 18 || NumberOfBytes < 2 )
    goto LABEL_24;
  
  Data = ExAllocatePoolWithTag(PagedPool, NumberOfBytes, 0x49464555u);
  if ( !Data )
    return 0xC000009A;
  
  DevicePropData = IoGetDevicePropertyData(
                     Pdo,
                     &DEVPKEY_Device_DriverInfPath,
                     0,
                     0,
                     NumberOfBytes,
                     Data,
                     &NumberOfBytes,
                     &Type);
					 
  if ( DevicePropData < 0 )
    goto LABEL_25;
  
  if ( Type != 18 )
    goto LABEL_24;
  
  if ( *(Data + (NumberOfBytes >> 1) - 1) )
    goto LABEL_24;
  
  DataFound = wcsrchr(Data, 0x2Eu);
  if ( !DataFound )
    goto LABEL_24;
  
  specChr = (DataFound + 1);
  
  j = -1i64;
  do
    ++j;
  while ( *&specChr[2 * j] );
  
  if ( j == 3 ) {
    unknwn = L"cat" - specChr;
    i = 4i64;
    
	do {
      if ( i == 2147483654 )
        break;
      
	  idklol = *&specChr[unknwn];
      
	  if ( !idklol )
        break;
      
	  *specChr = idklol;
      specChr += 2;
      --i;
    } while ( i );
    
	v13 = specChr - 2;
    if ( i )
      v13 = specChr;
    
	*v13 = 0;
    
	DevicePropData = i == 0 ? 0x80000005 : 0;
    
	if ( i && !RtlCreateUnicodeString(DestinationString, Data) )
      DevicePropData = 0xC000009A;
  } else {
LABEL_24:
    DevicePropData = 0xC000090B;
  }
  
LABEL_25:
  if ( Data )
    ExFreePoolWithTag(Data, 0);
  
  return DevicePropData;
}