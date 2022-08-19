NTSTATUS __fastcall UefiEsrtTraceLog(
        __int64 FirmwareResData,
        int FirmwareResData_Offset1,
        int ptrData,
        int FirmwareResData_Offset2,
        int FirmwareResData_Offset3,
        int FirmwareResData_Offset4,
        int unkPhaseData,
        int ResourceBuffLength,
        NTSTATUS *SysTimeLowPartData,
        char unkSpecChar,
        char unkSpecChar_1,
        int ptrData_1,
        int pValueInfo,
        unsigned __int16 *argUnicodeStrLength,
        int ControlFlow,
        int FirmwareData,
        int ValueInfoData,
        int RegValues)
{
  NTSTATUS result; 
  char v19; 
  char v20; 
  int v21; 
  int v22; 
  int v23; 
  int v24; 
  int v25;
  int v26; 
  int v27; 
  int v28; 
  int v29; 
  int v30; 
  int v31; 
  int v32; 
  int v33; 
  __int64 dwSysTimeData; 
  unsigned int Total; 
  __int64 v36; 
  EVENT_DESCRIPTOR EventDescriptor; 
  struct _EVENT_DATA_DESCRIPTOR UserData; 
  void *pUnk; 
  int v40; 
  int v41; 
  __int64 *v42; 
  __int64 v43; 
  __int64 v44; 
  __int64 v45; 
  int *v46; 
  __int64 v47; 
  int *v48; 
  __int64 v49; 
  int *v50; 
  __int64 v51; 
  int *v52; 
  __int64 v53; 
  int *v54; 
  __int64 v55; 
  int *v56; 
  __int64 v57; 
  int *v58; 
  __int64 v59; 
  __int64 *v60; 
  __int64 v61; 
  char *v62; 
  __int64 v63; 
  char *v64; 
  __int64 v65; 
  int *v66; 
  __int64 v67; 
  int *v68; 
  __int64 v69; 
  int *v70; 
  __int64 v71; 
  __int64 v72; 
  int v73[2]; 
  int *v74; 
  __int64 v75; 
  int *v76; 
  __int64 v77; 
  int *v78; 
  __int64 v79; 
  int *v80; 
  __int64 v81; 

  dwSysTimeData = 0i64;
  if ( SysTimeLowPartData ) {
    HIDWORD(dwSysTimeData) = SysTimeLowPartData[1];
    result = *SysTimeLowPartData;
    LODWORD(dwSysTimeData) = *SysTimeLowPartData;
  }
  
  if ( dword_1C0003010 > 5 && (qword_1C0003020 & 0x800000000000i64) != 0 ) {
    result = 0;
	
    if ( (qword_1C0003028 & 0x800000000000i64) == qword_1C0003028 ) {
	  // __SKVLLZ.: Generating log here but I'm too lazy to clean it up
      v44 = FirmwareResData;
      v42 = &v36;
      v46 = &v21;
      v48 = &v22;
      v23 = FirmwareResData_Offset4;
      v50 = &v23;
      v24 = FirmwareResData_Offset3;
      v52 = &v24;
      v54 = &v25;
      v26 = unkPhaseData;
      v56 = &v26;
      v27 = ResourceBuffLength;
      v58 = &v27;
      v60 = &dwSysTimeData;
      v19 = unkSpecChar;
      v62 = &v19;
      v20 = unkSpecChar_1;
      v64 = &v20;
      v28 = ptrData_1;
      v66 = &v28;
      v29 = pValueInfo;
      v68 = &v29;
      v70 = v73;
      v72 = *(argUnicodeStrLength + 1);
      v73[0] = *argUnicodeStrLength;
      v30 = ControlFlow;
      v74 = &v30;
      v22 = ptrData;
      v31 = FirmwareData;
      v21 = FirmwareResData_Offset1;
      v76 = &v31;
      v36 = 0x1000800i64;
      v43 = 8i64;
      v45 = 16i64;
      v47 = 4i64;
      v49 = 4i64;
      v51 = 4i64;
      v53 = 4i64;
      v25 = FirmwareResData_Offset2;
      v55 = 4i64;
      v57 = 4i64;
      v59 = 4i64;
      v61 = 8i64;
      v63 = 1i64;
      v65 = 1i64;
      v67 = 4i64;
      v69 = 4i64;
      v71 = 2i64;
      v73[1] = 0;
      v75 = 4i64;
      v32 = ValueInfoData;
      v77 = 4i64;
      v78 = &v32;
      v33 = RegValues;
      v80 = &v33;
      *&EventDescriptor.Level = 5;
      UserData.Ptr = EventInformation;
      v79 = 4i64;
      v81 = 4i64;
      *&EventDescriptor.Id = 184549376;
      EventDescriptor.Keyword = 0x800000000000i64;
      UserData.Size = *EventInformation;
      pUnk = &unk_1C00028D4;
      UserData.Reserved = 2;
      v41 = 1;
      v40 = 374;
	  
      Total = &TraceLoggingMetadataEnd - &TraceLoggingMetadata;
      
	  return EtwWriteTransfer(RegHandle, &EventDescriptor, 0i64, 0i64, 0x16u, &UserData);
    }
  }
  
  return result;
}