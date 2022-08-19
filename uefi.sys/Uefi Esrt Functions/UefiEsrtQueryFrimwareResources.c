__int64 __fastcall UefiEsrtQueryFirmwareResources(HANDLE KeyHandle) {
  unsigned int i;
  int Status; 
  ULONG Buff; 
  WCHAR *PoolWithTag; 
  ULONG Index; 
  GUID *unkGuid; 
  NTSTATUS EnumKeyStatus; 
  __int64 v9; 
  PCWSTR *pUnkWstr; 
  GUID *guid; 
  GUID *guid_swap; 
  GUID *NewGuid; 
  GUID **ppGuid; 
  ULONG PrevBuff; 
  ULONG ResultLength; 
  int Pool; 
  _DWORD KeyHandlea[3]; 
  struct _UNICODE_STRING DestinationString; 
  struct _UNICODE_STRING ValueName; 
  GUID Guid; 
  GUID v23; 
  __int64 firstDigits; 
  __int128 KeyInformation; 
  __int128 v26; 
  __int64 v27; 

  i = 0;
  ResultLength = 0;
  v27 = 0i64;
  firstDigits = 0i64;
  Pool = 0;
  
  memset(KeyHandlea, 0, sizeof(KeyHandlea));
  
  KeyInformation = 0i64;
  v26 = 0i64;
  DestinationString = 0i64;
  Guid = 0i64;
  v23 = 0i64;
  ValueName = 0i64;
  
  Status = ZwQueryKey(KeyHandle, KeyCachedInformation, &KeyInformation, 0x28u, &ResultLength);
  if ( Status < 0 )
    return Status;
  
  if ( !HIDWORD(KeyInformation) )
    return 0;
  
  Buff = 2 * v26 + 26;
  PrevBuff = Buff;
  
  PoolWithTag = ExAllocatePoolWithTag(PagedPool, Buff, 0x49464555u);
  if ( !PoolWithTag )
    return 0xC000009A;
  
  Index = 0;
  unkGuid = qword_1C0003070;
  
  if ( !HIDWORD(KeyInformation) )
    goto LABEL_37;
  
  while ( 1 ) {
    EnumKeyStatus = ZwEnumerateKey(KeyHandle, Index, KeyBasicInformation, PoolWithTag, Buff, &ResultLength);
    Status = EnumKeyStatus;
    
	if ( EnumKeyStatus < 0 ) {
      if ( EnumKeyStatus == 0x8000001A )
        Status = 0;
	
      goto LABEL_37;
    }
    
	PoolWithTag[(*(PoolWithTag + 3) >> 1) + 8] = 0;
    firstDigits = 0i64;
    Guid = 0i64;
    v23 = 0i64;
    
	RtlInitUnicodeString(&DestinationString, PoolWithTag + 8);
    Status = RtlGUIDFromString(&DestinationString, &Guid);
    if ( Status >= 0 ) {
      Status = UefiOpenRegistryKey(KeyHandle, &DestinationString, v9, &KeyHandlea[1]);
      
	  if ( Status >= 0 )
        break;
    }
	
LABEL_31:
    if ( ++Index >= HIDWORD(KeyInformation) )
      goto LABEL_37;
  }
  
  pUnkWstr = &unk_1C0002010;
  
  while ( 1 ) {
    RtlInitUnicodeString(&ValueName, *(pUnkWstr - 2));
    Status = UefiQueryRegistryValue(*&KeyHandlea[1], &ValueName, &Pool, &Guid + *pUnkWstr, *(pUnkWstr - 1), KeyHandlea);
    
	if ( Status >= 0 && Pool == *(pUnkWstr - 2) && KeyHandlea[0] == *(pUnkWstr - 1) )
      goto LABEL_16;
    
	if ( *(pUnkWstr + 8) )
      break;
    
	Status = 0;

LABEL_16:
    ++i;
    pUnkWstr += 4;
    
	if ( i >= 5 ) {
      i = 0;
      goto LABEL_20;
    }
  }
  
  i = 0;
  
  if ( Status >= 0 )
    Status = 0xC000090B;

LABEL_20:
  ZwClose(*&KeyHandlea[1]);
  
  if ( Status < 0 ) {
LABEL_30:
    Buff = PrevBuff;
    goto LABEL_31;
  }
  
  guid = P;
  if ( P != unkGuid ) {
    do {
      guid_swap = guid;
      if ( *&guid[1].Data1 == *&Guid.Data1 && *guid[1].Data4 == *Guid.Data4 )
        break;
      guid = *&guid->Data1;
      guid_swap = 0i64;
    } while ( guid != unkGuid );
    
	if ( guid_swap ) {
      guid_swap[1] = Guid;
      guid_swap[2] = v23;
      *&guid_swap[3].Data1 = firstDigits;
	  
      goto LABEL_30;
    }
  }
  
  NewGuid = ExAllocatePoolWithTag(PagedPool, 0x38ui64, 0x49464555u);
  if ( NewGuid ) {
    NewGuid[1] = Guid;
    NewGuid[2] = v23;
    *&NewGuid[3].Data1 = firstDigits;
    ppGuid = qword_1C0003070;
	
    if ( *qword_1C0003070 != &P )
      __fastfail(3u);
    
	*&NewGuid->Data1 = &P;
    *NewGuid->Data4 = ppGuid;
    *ppGuid = NewGuid;
    
	qword_1C0003070 = NewGuid;
    
	goto LABEL_30;
  }
  
  Status = 0xC000009A;

LABEL_37:
  ExFreePoolWithTag(PoolWithTag, 0);
  
  return Status;
}