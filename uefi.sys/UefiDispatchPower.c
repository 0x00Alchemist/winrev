__int64 __fastcall UefiDispatchPower(_DEVICE_OBJECT *Pdo, IRP *pIrp)
{
  _DWORD *Extension; 
  struct _IO_STACK_LOCATION *CurrentStackLocation; 
  unsigned int Status; 

  Extension = Pdo->DeviceExtension;
  CurrentStackLocation = pIrp->Tail.Overlay.CurrentStackLocation;
  Status = pIrp->IoStatus.Status;
  
  PoStartNextPowerIrp(pIrp);
  if ( *Extension == 1 ) {
    return UefiDispatchForwardIrp(Pdo, pIrp);
  } else if ( *Extension == 2 ) {
    if ( (CurrentStackLocation->MinorFunction - 2) <= 1u ) {
      Status = 0;
      pIrp->IoStatus.Status = 0;
    }
	
    IofCompleteRequest(pIrp, 0);
  } else {
    return 0xC0000010;
  }
  
  return Status;
}