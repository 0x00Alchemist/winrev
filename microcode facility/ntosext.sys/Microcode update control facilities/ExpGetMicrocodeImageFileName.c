NTSTATUS __fastcall ExpGetMicrocodeImageFileName(struct _UNICODE_STRING *UnicodeString) {
  int appended; 
  unsigned int Length; 
  WCHAR *PoolWithTag; 
  struct _UNICODE_STRING DestinationString; 
  UNICODE_STRING Source; 
  struct _STRING SourceString; 

  SourceString = 0i64;
  DestinationString = 0i64;
  Source = 0i64;
  
  RtlInitUnicodeString(&DestinationString, 0i64);
  RtlInitUnicodeString(&Source, 0i64);
  
  /* __SKVLLZ.: Here we are getting KPRCB (Kernel Process Control block)
	and getting Vendor string by offset 0x8590 */
  RtlInitAnsiString(&SourceString, KeGetCurrentPrcb() + 0x8590); 
  
  /* __SKVLLZ.: Appending ANSI string with received Vendor string (GenuineIntel / AuthenticAMD, lol, good names)
	and allocating it */
  appended = RtlAnsiStringToUnicodeString(&Source, &SourceString, 1u);
  
  if ( appended >= 0 ) {
    Length = Source.Length + 70;
	
    PoolWithTag = ExAllocatePoolWithTag(PagedPool, Length, 0x646F4375u);
    DestinationString.Buffer = PoolWithTag;
    if ( !PoolWithTag ) {
      appended = 0xC000009A;
      goto LABEL_9;
    }
	
    memset(PoolWithTag, 0, Length);
    
	DestinationString.Length = 0;
    DestinationString.MaximumLength = Length;
    
	// __SKVLLZ.: Append "general" string firstly
	appended = RtlAppendUnicodeToString(&DestinationString, L"\\SystemRoot\\System32\\mcupdate_");
    if ( appended >= 0 ) {
	// __SKVLLZ.: Append DestinationString with received Vendor string
      appended = RtlAppendUnicodeStringToString(&DestinationString, &Source);
      
	  if ( appended >= 0 ) {
		// __SKVLLZ.: Append extension
        appended = RtlAppendUnicodeToString(&DestinationString, L".dll");
        
		if ( appended >= 0 )
			// __SKVLLZ.: got it!
          *UnicodeString = DestinationString;
      }
    }
  }
  
  PoolWithTag = DestinationString.Buffer;

LABEL_9:
  if ( Source.Buffer ) {
    RtlFreeUnicodeString(&Source);
    PoolWithTag = DestinationString.Buffer;
  }
  
  if ( appended < 0 && PoolWithTag )
    ExFreePoolWithTag(PoolWithTag, 0x646F4375u);
  
  return appended;
}