__int64 __fastcall UefiAddDevice(struct _DRIVER_OBJECT *PDrvObj, struct _DEVICE_OBJECT *Pdo) {
  NTSTATUS DeviceStatus; 
  struct _DEVICE_OBJECT *_Pdo; 
  unsigned int Status; 
  _QWORD *DeviceExtension; 
  PDEVICE_OBJECT DeviceObjPtr; 
  PDEVICE_OBJECT SourceDevice;

  SourceDevice = 0i64;
  
  DeviceStatus = IoCreateDevice(PDrvObj, 0x28u, 0i64, 0x2Au, 0, 0, &SourceDevice);
  
  _Pdo = SourceDevice;
  Status = DeviceStatus;
  if ( DeviceStatus >= 0 ) {
	  
    DeviceExtension = SourceDevice->DeviceExtension;
    *DeviceExtension = 1;
    DeviceExtension[2] = Pdo;
    DeviceExtension[3] = SourceDevice;
    SourceDevice->Flags &= ~0x80u;
    
	DeviceObjPtr = IoAttachDeviceToDeviceStack(SourceDevice, Pdo);
    if ( DeviceObjPtr ) {
      _Pdo = 0i64;
      DeviceExtension[4] = DeviceObjPtr;
      SourceDevice = 0i64;
    } else {
      _Pdo = SourceDevice;
      Status = 0xC000000E;
    }
  }
  
  if ( _Pdo )
    IoDeleteDevice(_Pdo);
  
  return Status;
}