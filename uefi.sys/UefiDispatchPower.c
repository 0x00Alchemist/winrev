__int64 __fastcall UefiDispatchPower(__int64 Flags, IRP *pIrp) {
  _DWORD *IrpFlags;
  struct _IO_STACK_LOCATION *CurrentStackLocation;
  unsigned int Status;

  IrpFlags = *(Flags + 64); //__SKVLLZ: Cannot say what is it really
  
  CurrentStackLocation = pIrp->Tail.Overlay.CurrentStackLocation;
  Status = pIrp->IoStatus.Status;
  
  PoStartNextPowerIrp(pIrp);
  if ( *IrpFlags == 1 ) {
    return UefiDispatchForwardIrp(Flags, pIrp);
  } else if ( *IrpFlags == 2 ) {
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