__int64 __fastcall UefiDispatchForwardIrp(_DEVICE_OBJECT *Pdo, IRP *pIrp) {
  PDEVICE_OBJECT *Extension; 
  unsigned int Status;

  Extension = Pdo->DeviceExtension;
  
  if ( *Extension == 1 ) {
    ++pIrp->CurrentLocation;
    ++pIrp->Tail.Overlay.CurrentStackLocation;
	
    return IofCallDriver(Extension[4], pIrp);
  } else {
    Status = pIrp->IoStatus.Status;
    IofCompleteRequest(pIrp, 0);
  }
  
  return Status;
}