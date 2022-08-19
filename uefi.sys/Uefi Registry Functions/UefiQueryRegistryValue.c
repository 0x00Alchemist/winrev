__int64 __fastcall UefiQueryRegistryValue(
        HANDLE KeyHandle,
        PUNICODE_STRING ValueName,
        _DWORD *PoolWithTag_1,
        void *KeyValueInfo,
        unsigned int Length,
        _DWORD *ResLength)
{
  _DWORD *PoolWithTag; 
  unsigned int ValueKey_swap; 
  NTSTATUS ValueKey; 
  size_t ResPool; 
  int ResultLength[10]; 

  ResultLength[0] = 0;
  
  PoolWithTag = ExAllocatePoolWithTag(PagedPool, Length + 16, 0x49464555u);
  if ( PoolWithTag ) {
    ValueKey = ZwQueryValueKey(KeyHandle, ValueName, KeyValuePartialInformation, PoolWithTag, Length + 16, ResultLength);
    ValueKey_swap = ValueKey;
    
	if ( ValueKey == 0x80000005 ) {
      ValueKey_swap = 0;
	  
LABEL_8:
      if ( PoolWithTag_1 )
        *PoolWithTag_1 = PoolWithTag[1];
      
	  ResPool = PoolWithTag[2];
      if ( ResLength )
        *ResLength = ResPool;
      
	  if ( ResPool <= Length && KeyValueInfo )
        memmove(KeyValueInfo, PoolWithTag + 3, ResPool);
      else
        ValueKey_swap = 0xC0000023;
      
	  goto LABEL_16;
    }
    
	if ( ValueKey == 0xC0000023 ) {
      ValueKey_swap = 0xC00000E5;
    } else if ( ValueKey >= 0 ) {
      goto LABEL_8;
    }
	
LABEL_16:
    ExFreePoolWithTag(PoolWithTag, 0);
    
	return ValueKey_swap;
  }
  
  return 0xC000009A;
}