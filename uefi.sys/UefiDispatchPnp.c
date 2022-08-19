__int64 __fastcall UefiDispatchPnp(PDEVICE_OBJECT Pdo, PIRP Irp) {
  _DWORD *DeviceExtension; 
  struct _IO_STACK_LOCATION *CurrentStackLocation; 
  unsigned int Status; 
  UCHAR MinorFunction; 
  unsigned int started; 
  PIO_SECURITY_CONTEXT SecurityContext; 
  int SecurityQos_high; 
  int DeviceRelations; 

  DeviceExtension = Pdo->DeviceExtension;
  CurrentStackLocation = Irp->Tail.Overlay.CurrentStackLocation;
  
  if ( *DeviceExtension == 1 ) {
    if ( CurrentStackLocation->MinorFunction ) {
      if ( CurrentStackLocation->MinorFunction == 1 || CurrentStackLocation->MinorFunction == 5 ) {
        Status = 0xC0000001;
        goto LABEL_40;
      }
	  
      if ( CurrentStackLocation->MinorFunction != 7 ) {
        if ( CurrentStackLocation->MinorFunction == 20 ) {
          LODWORD(Irp->IoStatus.Information) |= 0x20u;
          Status = 0;
		  
LABEL_32:
          Irp->IoStatus.Status = Status;
        }
		
        return UefiDispatchForwardIrp(Pdo, Irp);
      }
      DeviceRelations = UefiQueryDeviceRelations(Pdo);
    } else {
      DeviceRelations = UefiStartDevice(Pdo);
    }
	
    Status = DeviceRelations;
    
	if ( DeviceRelations >= 0 )
      goto LABEL_32;
    
	if ( DeviceRelations != 0xC00000BB )
      goto LABEL_39;
    
	return UefiDispatchForwardIrp(Pdo, Irp);
  }
  
  if ( *DeviceExtension != 2 ) {
    Status = 0xC0000010;
    goto LABEL_39;
  }
  
  MinorFunction = CurrentStackLocation->MinorFunction;
  if ( MinorFunction <= 7u ) {
    if ( MinorFunction == 7 ) {
      started = UefiQueryDeviceRelations(Pdo);
      goto LABEL_13;
    }
	
    if ( MinorFunction ) {
      if ( MinorFunction != 1 ) {
LABEL_8:
        Status = 0;
        goto LABEL_40;
      }
	  
      if ( DeviceExtension[2] != 1 ) {
        Status = 0xC0000001;
        goto LABEL_39;
      }
	  
      goto LABEL_20;
    }
	
    if ( DeviceExtension[2] == 1 ) {
      started = UefiEsrtStartDevice(Pdo);
LABEL_13:
      Status = started;
      goto LABEL_39;
    }
LABEL_20:
    Status = 0;
    goto LABEL_39;
  }
  
  if ( MinorFunction != 9 ) {
    if ( MinorFunction > 9u ) {
      if ( MinorFunction <= 0xBu )
        goto LABEL_8;
	
      if ( MinorFunction == 19 ) {
        if ( DeviceExtension[2] == 1 ) {
          started = UefiEsrtQueryId(Pdo, CurrentStackLocation->Parameters.Read.Length, &Irp->IoStatus.Information);
          goto LABEL_13;
        }
		
        goto LABEL_20;
      }
    }
	
    goto LABEL_22;
  }
  
  SecurityContext = CurrentStackLocation->Parameters.Create.SecurityContext;
  if ( WORD1(SecurityContext->SecurityQos) != 1 ) {
LABEL_22:
    Status = 0xC00000BB;
    goto LABEL_39;
  }
  
  // __SKVLLZ: Filling security context for PnP device
  SecurityQos_high = HIDWORD(SecurityContext->SecurityQos);
  HIDWORD(SecurityContext[2].SecurityQos) = 0;
  LODWORD(SecurityContext[2].AccessState) = 0;
  HIDWORD(SecurityContext->SecurityQos) = SecurityQos_high & 0xFFFFFE03 | 0xC0;
  HIDWORD(SecurityContext[2].AccessState) = 0;
  LODWORD(SecurityContext->AccessState) = -1;
  HIDWORD(SecurityContext->AccessState) = -1;
  SecurityContext->FullCreateOptions = 1;
  HIDWORD(SecurityContext[1].AccessState) = 4;
  SecurityContext[1].DesiredAccess = 4;
  Status = 0;
  
  if ( DeviceExtension[2] == 1 )
    *(CurrentStackLocation->Parameters.WMI.ProviderId + 4) |= 0x100u;

LABEL_39:
  if ( Status == 0xC00000BB ) {
    Status = Irp->IoStatus.Status;
    goto LABEL_42;
  }
  
LABEL_40:
  Irp->IoStatus.Status = Status;

LABEL_42:
  IofCompleteRequest(Irp, 0);

  return Status;
}