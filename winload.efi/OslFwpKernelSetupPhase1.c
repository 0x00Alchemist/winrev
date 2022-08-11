DWORD64 __fastcall OslFwpKernelSetupPhase1(_LoaderParamBlock *LoaderParamBlock) {
  INT64 MemMapBuff;
  INT MemoryMap;
  INT64 MemMapSize_Swap1; 
  INT64 DescrSize_Swap1;
  UINT MemMapBuffptr; 
  INT64 v7; 
  INT64 v8; 
  DWORD64 *v9;
  INT64 (__fastcall *_OslpBzmWbinvd)();
  INT64 gAcpiTableProtocol;
  CHAR VATranslated;
  INT64 MapKeySwap;
  UINT count;
  UINT8 *UnknwnGuessedAcpiTableOffset; 
  IN64 counter; 
  UINT64 v17;
  BOOL i; 
  INT64 MaskIndex; 
  UINT64 BitPosForTest; 
  INT64 MsrVal_1; 
  INT64 MsrVal_2; 
  UINT64 MsrVal_3; 
  INT64 v24;
  UINT64 qword20;
  UINT64 MemMapSize;
  UINT64 DescriptorSize;
  UIN64 MapKey; 
  UINT64 (__fastcall *Rsdt)();
  INT DescriptorVersion;
  INT64 MemMapSize_Swap2;

  MemMapSize_Swap2 = 0i64;
  EfipGetRsdt(&Rsdt);
  LoaderParamBlock->dword124 = 0;
  BlBdStop();
  MemMapBuff = OslFwpMemoryMapBufferVa;
  qword20 = LoaderParamBlock->qword20;
  MemMapSize = OslFwpMemoryMapSize;
  MemoryMap = EfiGetMemoryMap(&MemMapSize, OslFwpMemoryMapBufferVa, &MapKey, &DescriptorSize, &DescriptorVersion);

  if ( MemoryMap >= 0 ) {
    MemMapSize_Swap1 = MemMapSize;
    MemMapSize_Swap2 = MemMapSize;
    if ( MemMapSize ) {
      DescrSize_Swap1 = DescriptorSize;
      do {
        MemMapBuffptr = *MemMapBuff;
        if ( (*MemMapBuff - 1) > 3 && MemMapBuffptr != 7 && MemMapBuffptr < 0x80000000 ) {
          OslFwpMarkFirmwareMemoryRegion(
            &LoaderParamBlock->qword20,
            &qword20,
            *(MemMapBuff + 8) >> 12,
            *(MemMapBuff + 24) & 0xFFFFFFFFFFFFFi64);
          MemMapSize_Swap1 = MemMapSize;
          DescrSize_Swap1 = DescriptorSize;
        }
		
        if ( *(MemMapBuff + 32) < 0 ) {
          v7 = LoaderParamBlock->unsigned_int140;
          v8 = LoaderParamBlock->unsigned_int144;
          
		  if ( LoaderParamBlock->unsigned_int140 ) {
            v9 = (LoaderParamBlock->qword138 + 8i64);
            while ( v9[3] >= 0 || *v9 != *(MemMapBuff + 8) || v9[2] != *(MemMapBuff + 24) ) {
              v9 = (v9 + v8);
              v7 -= v8;
              if ( !v7 )
                goto LABEL_15;
            }
          } else {
LABEL_15:
            ++LoaderParamBlock->dword124;
          }
        }
        MemMapSize_Swap1 -= DescrSize_Swap1;
        MemMapBuff += DescrSize_Swap1;
        MemMapSize = MemMapSize_Swap1;
      } while ( MemMapSize_Swap1 );
    }
	
	
    if ( byte_1801AB868 ) {
      _OslpBzmWbinvd = OslpBzmWbinvd;
      gAcpiTableProtocol = qword_1801AB860;     // __SKVLLZ.: based on OslInitializeBootZeroedMemory function
	  
      if ( *CurrentExecutionContext == 1 ) {
LABEL_25:
		// __SKVLLZ.: Looks lige another EFI service table (maybe EFI_BOOT_SERVICES),
		// 			  that works with protocol
        (*(gAcpiTableProtocol + 16))(gAcpiTableProtocol, _OslpBzmWbinvd, 0i64, 0i64, 0i64, 0i64, 0i64);
        JUMPOUT(0x1800064F3i64);
      }
      
	  if ( qword_1801AB860 )
        VATranslated = MmArchTranslateVirtualAddress(qword_1801AB860, &Rsdt, 0i64, 0i64);
      else
        VATranslated = 0;
      
	  if ( VATranslated ) {
        gAcpiTableProtocol = Rsdt;
		
        if ( MmArchTranslateVirtualAddress(OslpBzmWbinvd, &Rsdt, 0i64, 0i64) ) {
          _OslpBzmWbinvd = Rsdt;
          BlpArchSwitchContext(1i64);
          goto LABEL_25;
        }
      }
      byte_1801AB868 = 0;
    }
    MapKeySwap = MapKey;
	
    if ( *CurrentExecutionContext != 1 )
      BlpArchSwitchContext(1i64);

    // __SKVLLZ.: Looks like EFI_BOOT_SERVICES.ExitBootServices function that terminates all boot services
    // 			  gBS->ExitBootServices(EfiImageHandle, MapKey);
    (*(gBS + 232))(EfiImageHandle, MapKeySwap);
    JUMPOUT(0x180006555i64);
  }
  
  if ( BdDebugDevice )
    BlBdEnableBusMaster(BdDebugDevice);
  if ( KdDebugDevice )
    BlBdEnableBusMaster(KdDebugDevice);

  BlBdStart();
  
  if ( byte_1801AB868 ) {
    count = 0;
    UnknwnGuessedAcpiTableOffset = &qword_1801AB878->unsigned___int828;		// AcpiTable?
	
    if ( qword_1801AB878->unsigned___int824 ) {
      counter = qword_1801AB878->unsigned___int824;
	  
      do {
        v17 = *UnknwnGuessedAcpiTableOffset << 8;
        __writemsr(0x82u, v17);
        LODWORD(Rsdt) = 0;
        qword20 = __readmsr(0x83u);
		
        for ( i = !_BitScanForward64(&MaskIndex, qword20); !i; i = !_BitScanForward64(&MaskIndex, qword20) ) {
          BitPosForTest = MaskIndex;
          __writemsr(0x82u, MaskIndex | v17);
          MsrVal_1 = __readmsr(0x84u);
          MsrVal_2 = __readmsr(0x85u);
          MsrVal_3 = __readmsr(0x86u);
		  
		  // The fuck
          if ( (MsrVal_3 & 1) == 0 ) {
            v24 = 2i64 * count;
            *(qword_1801AB870 + 8 * v24) = MsrVal_1 >> 12;
            *(qword_1801AB870 + 8 * v24 + 8) = (MsrVal_2 >> 12) - *(qword_1801AB870 + 16i64 * count++);
          }
		  
          _bittestandreset64(&qword20, BitPosForTest);
        }
        UnknwnGuessedAcpiTableOffset += 8;
        --counter;
      } while ( counter );
    }
	
    OslFwpMarkZeroedMemoryWorker(&LoaderParamBlock->qword20, qword_1801AB870, count);
  }
  
  return MemoryMap;
}
