__int64 __fastcall UefiEsrtGetFirmwareVersionString(
        int Data,
        unsigned __int16 *argStrLength,			// __SKVLLZ.: pUnicodeString->Length
        struct _UNICODE_STRING *pUnicodeStr)
{
  int argData_swap1; 
  unsigned int j; 
  unsigned int nextInterpreted;
  WCHAR *PoolWithTag; 
  WCHAR *SrcString; 
  NTSTATUS Status; 
  const void *pArgStrSrcBuff; 
  size_t pArgStrSize; 
  const wchar_t *ws; 
  wchar_t *ptrFoundedChar; 
  wchar_t *ptrFoundedChar_swap; 
  unsigned int InterpretedChr; 
  __int64 index; 
  NTSTATUS Status_1; 
  USHORT Length; 
  struct _UNICODE_STRING *pUnicodeStr_2; 
  BOOLEAN UnicodeString; 
  unsigned int Status_2; 
  int *pSpecArr; 
  unsigned int k; 
  int a;
  unsigned int diff; 
  unsigned int i; 
  int shlByte; 
  unsigned int v29; 
  PWSTR Buffer; 
  unsigned __int64 MaxLength; 
  WCHAR *pBuff; 
  __int16 PreviousMaxLength; 
  __int64 m; 
  const wchar_t *dota2; 
  signed __int64 diff_2; 
  __int64 v37; 
  unsigned __int64 CurrentMaxLength; 
  __int64 v39; 
  struct _UNICODE_STRING DestinationString; 
  int argData_swap; 
  int *pSpecArr_1; 
  wchar_t *EndPtr; 
  const wchar_t *dota; 
  __int64 v45; 
  PUNICODE_STRING pUnicodeStr_1; 
  int specArr[32]; 

  pUnicodeStr_1 = pUnicodeStr;
  argData_swap = Data;
  argData_swap1 = Data;
  *(&DestinationString.MaximumLength + 1) = 0;
  v45 = 0i64;
  EndPtr = 0i64;
  DestinationString.MaximumLength = 128;
  j = 0;
  nextInterpreted = 0;
  
  PoolWithTag = ExAllocatePoolWithTag(PagedPool, 0x80ui64, 0x49464555u);
  
  DestinationString.Buffer = PoolWithTag;
  SrcString = PoolWithTag;
  if ( !PoolWithTag )
    return 0xC000009A;
  
  if ( argStrLength ) {
    pArgStrSrcBuff = *(argStrLength + 1);
	
    if ( pArgStrSrcBuff ) {
      pArgStrSize = *argStrLength;
	  
      if ( pArgStrSize < 0x7E ) {
        memmove(PoolWithTag, pArgStrSrcBuff, pArgStrSize);
        ws = SrcString;
        SrcString[*argStrLength >> 1] = 0;
		
        while ( 1 ) {
          ptrFoundedChar = wcschr(ws, 0x2Eu);
          ptrFoundedChar_swap = ptrFoundedChar;
          
		  if ( ptrFoundedChar ) {
            *ptrFoundedChar = 0;
            ptrFoundedChar_swap = ptrFoundedChar + 1;
          }
		  
          InterpretedChr = wcstoul(ws, &EndPtr, 10);
          
		  if ( !InterpretedChr || !EndPtr || *EndPtr || j >= 0x20 )
            break;
          
		  index = j;
          nextInterpreted += InterpretedChr;
          ++j;
          
		  specArr[index] = InterpretedChr;
		  
          if ( nextInterpreted > 0x20 ) {
            DestinationString.Length = 0;
            goto LABEL_17;
          }
          
		  ws = ptrFoundedChar_swap;
          if ( !ptrFoundedChar_swap )
            goto LABEL_26;
        }
        j = 0;
      }
    }
  }
  
LABEL_26:
  DestinationString.Length = 0;
  
  if ( j ) {
    pSpecArr = specArr;
    pSpecArr_1 = specArr;
    k = 0;
    dota = L".";
    
	do {
      a = 0;
      diff = nextInterpreted - *pSpecArr;
      
	  for ( i = diff; i < nextInterpreted; a |= shlByte )
        shlByte = 1 << i++;
      
	  v29 = (a & argData_swap1) >> diff;
      nextInterpreted -= *pSpecArr;
      
	  if ( k ) {
        Buffer = 0i64;
        MaxLength = 0i64;
        Status = 0;
        if ( (DestinationString.Length & 1) != 0
          || (DestinationString.MaximumLength & 1) != 0
          || DestinationString.Length > DestinationString.MaximumLength
          || DestinationString.MaximumLength == 0xFFFF ) {
          Status = 0xC000000D;
        } else {
          if ( !DestinationString.Buffer && (DestinationString.Length || DestinationString.MaximumLength) ) {
            Status = 0xC000000D;
          } else {
            Buffer = DestinationString.Buffer;
            MaxLength = DestinationString.MaximumLength >> 1;
          }
		  
          if ( Status < 0 )
            goto LABEL_22;
          
		  pBuff = Buffer;
          PreviousMaxLength = MaxLength;
          m = 0i64;
          
		  if ( MaxLength ) {
            dota2 = L"."; // no way
            diff_2 = Buffer - dota;
            v37 = 0x7FFFi64;
            CurrentMaxLength = MaxLength;
            Status = 0;
            
			do {
              if ( !v37 )
                break;
              if ( *dota2 == v45 )
                break;
              *(dota2 + diff_2) = *dota2;
              --v37;
              ++dota2;
              ++m;
              --CurrentMaxLength;
            } while ( CurrentMaxLength );
            
			if ( !CurrentMaxLength && v37 && *dota2 )
              Status = 0x80000005;
            
			pSpecArr = pSpecArr_1;
            pBuff = &Buffer[m];
            PreviousMaxLength = MaxLength - m;
            
			if ( Status < 0 ) {
              pBuff = Buffer;
              PreviousMaxLength = MaxLength;
              LOWORD(m) = 0;
            }
          } else {
            Status = Buffer != 0i64 ? 0x80000005 : 0xC000000D;
          }
		  
          DestinationString.Length = 2 * m;
		  
          if ( (Status + 0x80000000) < 0 || Status == 0x80000005 ) {
            DestinationString.Length = 0;
            DestinationString.MaximumLength = 2 * PreviousMaxLength;
            DestinationString.Buffer = pBuff;
          }
        }
		
        if ( Status < 0 )
          goto LABEL_22;
      
	  }
      
	  LODWORD(v39) = v29;
      
	  Status = RtlUnicodeStringPrintfEx(&DestinationString, &DestinationString, 0x800u, L"%u", v39);
      if ( Status < 0 )
        goto LABEL_22;
      
	  argData_swap1 = argData_swap;
      ++pSpecArr;
      ++k;
      pSpecArr_1 = pSpecArr;
    } while ( k < j );
	
    Length = 2 * (DestinationString.Buffer - SrcString);
    
	goto LABEL_19;
  }
  
LABEL_17:
  Status_1 = RtlUnicodeStringPrintfEx(&DestinationString, 0i64, 0x800u, L"%X", argData_swap1);
  SrcString = DestinationString.Buffer;
  
  Status = Status_1;
  if ( Status_1 >= 0 ) {
    Length = DestinationString.Length;
	
LABEL_19:
    pUnicodeStr_2 = pUnicodeStr_1;
    SrcString[Length >> 1] = 0;
    UnicodeString = RtlCreateUnicodeString(pUnicodeStr_2, SrcString);
    Status_2 = Status;
    if ( !UnicodeString )
      Status_2 = 0xC000009A;
    Status = Status_2;
  }
  
LABEL_22:
  if ( SrcString )
    ExFreePoolWithTag(SrcString, 0);
  
  return Status;
}