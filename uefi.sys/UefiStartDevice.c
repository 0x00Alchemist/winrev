__int64 __fastcall UefiStartDevice(_DEVICE_OBJECT *Pdo) {
  _QWORD *DeviceExtension; 
  char *j; 
  NTSTATUS Status; 
  struct _DRIVER_OBJECT *DrvObj; 
  char *ExtSymbol; 
  PVOID *i; 
  _QWORD *Extension; 
  struct _DEVICE_OBJECT *_Pdo; 
  PDEVICE_OBJECT DeviceObject; 

  DeviceExtension = Pdo->DeviceExtension;
  
  j = 0i64;
  DeviceObject = 0i64;
  Status = 0;
  DrvObj = UefiDriverObject;
  ExtSymbol = 0i64;
  
  if ( !DeviceExtension[1] ) {
    for ( i = P; i != &P; i = *i ) {
      Status = IoCreateDevice(DrvObj, 0x28u, 0i64, 0x2Au, 0x80u, 0, &DeviceObject);
      
	  if ( Status < 0 )
        goto LABEL_14;
      
	  Extension = DeviceObject->DeviceExtension;
      Extension[2] = 0i64;
      *(Extension + 2) = 1;
      *Extension = 2;
      Extension[3] = DeviceObject;
      Extension[4] = i + 2;
      
	  if ( j ) {
        if ( ExtSymbol )
          *(ExtSymbol + 1) = Extension + 1;
      } else {
        j = (Extension + 1);
      }
	  
      ExtSymbol = (Extension + 1);
      DeviceObject->Flags &= ~0x80u;
    }
    DeviceExtension[1] = j;
	
LABEL_14:
    for ( j = 0i64; j; j = *(j + 1) ) {
      _Pdo = *(j + 2);                          // __SKVLLZ: go to another device extension
	  
      if ( _Pdo )
        IoDeleteDevice(_Pdo);
    }
  }
  
  return Status;
}