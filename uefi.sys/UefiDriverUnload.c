PVOID UefiDriverUnload() {
  REGHANDLE Handle_RegHandle; 
  _DRIVER_OBJECT *DrvObj; 
  PVOID result; 

  Handle_RegHandle = RegHandle;
  RegHandle = 0i64;
  
  dword_1C0003010 = 0;
  
  EtwUnregister(Handle_RegHandle);
  while ( 1 ) {
    result = P;
	
    if ( P == &P )
      break;
    
	if ( *(P + 1) != &P || (DrvObj = *P, *(*P + 8i64) != P) )
      __fastfail(3u);
    
	P = *P;
    
	DrvObj->DeviceObject = &P;
    ExFreePoolWithTag(result, 0);
  }
  
  return result;
}