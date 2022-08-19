// __SKVLLZ.: From UefiDispatchPnp function: UefiEsrtQueryId(Pdo, CurrentStackLocation->Parameters.Read.Length, &Irp->IoStatus.Information);
__int64 __fastcall UefiEsrtQueryId(_DEVICE_OBJECT *Pdo, int Length, _QWORD *Information) {
  PVOID DeviceExtension; 
  NTSTATUS Status; 
  wchar_t *str; 
  __int64 ptrDevExt; 
  unsigned int _Length; 
  const wchar_t *v10; 
  signed __int64 diff; 
  size_t pcbRem; 
  NTSTRSAFE_PWSTR _PszDest; 
  NTSTRSAFE_PWSTR CurrPszDest; 
  _WORD *PoolWithTag; 
  _WORD *PoolTag; 
  size_t *dwFlags; 
  ULONG pszFormat; 
  NTSTRSAFE_PWSTR ppszDestEnd; 
  size_t pcbRemaining; 
  struct _UNICODE_STRING GuidString; 
  wchar_t pszDest[128]; 

  DeviceExtension = Pdo->DeviceExtension;
  ppszDestEnd = 0i64;
  Status = 0;
  str = 0i64;
  GuidString = 0i64;
  ptrDevExt = *(DeviceExtension + 4);
  
  if ( Length < 0 ) {
LABEL_19:
    Status = 0xC00000BB;
    _Length = 0;
	
LABEL_20:
    if ( Status < 0 )
      return Status;
    
	goto LABEL_21;
  }
  
  if ( Length <= 1 ) {
    Status = RtlStringFromGUID(*(DeviceExtension + 4), &GuidString);
    if ( Status < 0 )
      return Status;
    
	pcbRem = 256i64;
    _PszDest = pszDest;
	
    if ( Length ) {
      pcbRemaining = 256i64;
      ppszDestEnd = pszDest;
	  
      Status = RtlStringCbPrintfExW(
                 pszDest,
                 0x100ui64,
                 &ppszDestEnd,
                 &pcbRemaining,
                 0x800u,
                 L"UEFI\\RES_%wZ&REV_%X",
                 &GuidString,
                 *(ptrDevExt + 20));
      
	  if ( Status < 0 )
        goto LABEL_15;
      
	  _PszDest = ++ppszDestEnd;
      pcbRem = pcbRemaining - 2;
    }
    
	Status = RtlStringCbPrintfExW(_PszDest, pcbRem, &ppszDestEnd, 0i64, 0x800u, L"UEFI\\RES_%wZ", &GuidString);
    if ( Status >= 0 ) {
      CurrPszDest = ppszDestEnd + 1;
	  
LABEL_16:
      RtlFreeUnicodeString(&GuidString);
      
	  if ( Status < 0 )
        return Status;
      
	  diff = CurrPszDest - pszDest;
      
	  goto LABEL_18;
    }
LABEL_15:
    CurrPszDest = ppszDestEnd;
    
	goto LABEL_16;
  }
  
  if ( Length != 2 ) {
    if ( Length == 3 )
    {
      str = L"0";
      _Length = 6;
	  
LABEL_21:
      
	  PoolWithTag = ExAllocatePoolWithTag(PagedPool, _Length + 2i64, 0x49464555u);
      PoolTag = PoolWithTag;
      
	  if ( PoolWithTag ) {
        memmove(PoolWithTag, str, _Length);
		
        PoolTag[_Length >> 1] = 0;
        *Information = PoolTag;
      } else {
        return 0xC000009A;
      }
	  
      return Status;
    }
	
    goto LABEL_19;
  }
  
  ppszDestEnd = pszDest;
  pcbRemaining = 256i64;
  
  Status = RtlStringCbPrintfExW(pszDest, 0x100ui64, &ppszDestEnd, &pcbRemaining, 0x800u, L"UEFI\\CC_%04X%04X");
  if ( Status >= 0 ) {
    ++ppszDestEnd;
    Status = RtlStringCbCopyExW(ppszDestEnd, pcbRemaining - 2, v10, &ppszDestEnd, dwFlags, pszFormat);
    
	if ( Status >= 0 ) {
      diff = ppszDestEnd - pszDest + 2;
	  
LABEL_18:
      str = pszDest;
      _Length = 2 * (diff >> 1);
      
	  goto LABEL_20;
    }
  }
  
  return Status;
}