__int64 __fastcall UefiDispatchForwardIrp(__int64 Flags, IRP *pIrp) {
  __int64 IrpFlags; 
  unsigned int Status; 

  IrpFlags = *(Flags + 64); //__SKVLLZ: Cannot say what is it really
  
  if ( *IrpFlags == 1 ) {
    ++pIrp->CurrentLocation;
    ++pIrp->Tail.Overlay.CurrentStackLocation;
    
	return IofCallDriver(*(IrpFlags + 32), pIrp); // __SKVLLZ: first arg is pointer on DEVICE_OBJECT struct. Idk what is it really now..
  } else {
    Status = pIrp->IoStatus.Status;
    
	IofCompleteRequest(pIrp, 0);
  }
  
  return Status;
}