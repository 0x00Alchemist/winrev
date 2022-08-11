/* Interesting observation from my dear friend
   At the start of the system, the first page has WE rights (first 0xF0000 bytes)
   
    kd> !pte 0000000000000000
                                          VA 0000000000000000
	PXE at FFFFA150A8542000    PPE at FFFFA150A8400000    PDE at FFFFA15080000000    PTE at FFFFA10000000000
	contains 00000000001AD023  contains 00000000001AC063  contains 00000000001AB023  contains 0000000000000063
	pfn 1ad       ----A--KWEV  pfn 1ac       ---DA--KWEV  pfn 1ab       ----A--KWEV  pfn 0         ---DA--KWEV

	kd> kb
	#  RetAddr               : Args to Child                                                           : Call Site
	00 fffff804`6496bc75     : 00000000`ffffffff fffff804`64600110 fffff804`65200b20 ffffffff`c000000d : nt!DebugService2+0x5
	01 fffff804`64fb2c33     : 00000000`00000001 00000000`00000001 fffff804`5fa38830 00000000`00000000 : nt!DbgLoadImageSymbols+0x45
	02 fffff804`64f8b17c     : 00000000`0000008e 00000000`00000006 00000000`001a6ff0 00000000`00000000 : nt!KdInitSystem+0xad3
	03 00000000`00000000     : 00000000`00000000 00000000`00000000 00000000`00000000 00000000`00000000 : nt!KiSystemStartup+0x16c
*/

__noreturn __fastcall VOID KiSystemStartup(INT64 LdrParamBlockData, INT64 a2, INT64 a3, INT64 a4) {
    UnknownStructCR_Reg *UnknwContolRegStruct;
    DWORD64 cr0; 
    DWORD64 cr2; 
    DWORD64 cr3; 
    DWORD64 cr4; 
    INT64 ControlValue; 
    DWORD64 v12; 
    DWORD64 v13; 
    DWORD64 v14; 
    VOID *buff_XSave; 
    UINT *LdrParamBlockPtr; 
    _EPROCESS *Process; 
    INT64 v18;
    DWOR64 FarPtrIdtBase; 
    INT64 shrTickCPUValue; 
    DWORD64 RandomTickCPUValue; 
    INT64 RawSecurityCookie; 
    _ETHREAD *CurrentThread; 
    BOOL WaitFlag;
 
    KeLoaderBlock_0 = LdrParamBlockData;        // Неебу
    if ( !*(*(LdrParamBlockData + 136) + 36i64) )
        KdInitSystem(-1, KeLoaderBlock_0, a3, a4);
 
    UnknwContolRegStruct = *(KeLoaderBlock_0 + 136);
    _RDX = UnknwContolRegStruct[-2].gap160;     // Тоже неебу
    *(_RDX + 24) = _RDX;
    *(_RDX + 32) = UnknwContolRegStruct;
 
    // Write CR-regs into some control structure (idk about how name it)
    cr0 = __readcr0();
    UnknwContolRegStruct->qword100 = cr0;
 
    cr2 = __readcr2();
    UnknwContolRegStruct->qword108 = cr2;
 
    cr3 = __readcr3();
    UnknwContolRegStruct->qword110 = cr3;
 
    cr4 = __readcr4();
    UnknwContolRegStruct->qword118 = cr4;
	
	// Save GDT
    __sgdt(&UnknwContolRegStruct->char156);
    ControlValue = UnknwContolRegStruct->qword158;
    *_RDX = ControlValue;
	
	// Save IDT
    __sidt(&UnknwContolRegStruct->char166);
    *(_RDX + 56) = UnknwContolRegStruct->qword168;
 
    __asm {
        str     word ptr [rdx+2F0h]; Store Task Register
        sldt    word ptr [rdx+2F2h]; Store Local Descriptor Table Register
    }
 
    *UnknwContolRegStruct->gap0 = 0x1F80;
    _mm_setcsr(*UnknwContolRegStruct->gap0);
    if ( !*&UnknwContolRegStruct->gap0[36] )
        *(ControlValue + 80) = 0x3C00;
 
    if ( !VslVsmEnabled ) {
        _AX = 0;
        __asm { lldt    ax; Load Local Descriptor Table Register }
    }
 
    *MK_FP(0x2B, _RDX + 8) = *MK_FP(0x2B, ControlValue + 66);
    *MK_FP(0x2B, _RDX + 10) = *MK_FP(0x2B, ControlValue + 68);
    *MK_FP(0x2B, _RDX + 11) = *MK_FP(0x2B, ControlValue + 71);
    *MK_FP(0x2B, _RDX + 12) = *MK_FP(0x2B, ControlValue + 72);
    v12 = HIDWORD(_RDX);
    
    __writemsr(0xC0000101, __PAIR64__(v12, UnknwContolRegStruct - 384));
    __writemsr(0xC0000102, __PAIR64__(v12, UnknwContolRegStruct - 384));
 
    if ( !*MK_FP(0x2B, &UnknwContolRegStruct->gap0[36]) ) {
        _guard_dispatch_icall_fptr = &guard_dispatch_icall;
        _guard_check_icall_fptr[0] = guard_check_icall;
    }
 
    KiInitializeBootStructures(KeLoaderBlock_0);
 
    if ( !*MK_FP(0x2B, *MK_FP(0x2B, KeLoaderBlock_0 + 0x88) + 0x24i64) )
        KdInitSystem(0, KeLoaderBlock_0, v13, v14);
 
    KiInitializeXSave(KeLoaderBlock_0, *MK_FP(0x2B, *MK_FP(0x2B, KeLoaderBlock_0 + 0x88) + 0x24i64));
 
    __writecr8(0xFui64);
    buff_XSave = alloca(KiXSaveAreaLength);
 
    LdrParamBlockPtr = KeLoaderBlock_0;
	
    /* __SKVLLZ.: LOADER_PARAMETER_BLOCK offsets here:
				  ULONG_PTR Process;
				  ULONG_PTR Thread;
	*/
	InitProcess = *MK_FP(0x2B, KeLoaderBlock_0 + 144); 
    InitThread = *MK_FP(0x2B, KeLoaderBlock_0 + 152);
	
    if ( (KiKvaShadow & 1) != 0 ) {
        FarPtrIdtBase = *MK_FP(0x2B, *MK_FP(0x2B, &KeGetPcr()->IdtBase) + 0x1078i64);
        __writegsqword(0x9008u, FarPtrIdtBase);
    } else {
        FarPtrIdtBase = *MK_FP(0x2B, *MK_FP(0x2B, &KeGetPcr()->TssBase) + 4i64);
    }
 
    __writegsqword(0x1A8u, FarPtrIdtBase);
 
    KiInitializeKernel(
        InitProcess,
        InitThread,
        FarPtrIdtBase,
        *MK_FP(0x2B, LdrParamBlockPtr + 0x22),
        *MK_FP(0x2B, *MK_FP(0x2B, LdrParamBlockPtr + 0x22) + 0x24i64),
        LdrParamBlockPtr);
 
    if ( !*MK_FP(0x2B, &KeGetPcr()->Prcb.Number) ) {
		// Generating security cookie
        RandomTickCPUValue = __rdtsc();
        shrTickCPUValue = __ROR8__(RandomTickCPUValue, 49);
        RawSecurityCookie = __ROL8__(ExpSecurityCookieRandomData ^ shrTickCPUValue ^ RandomTickCPUValue, 16);
        
        LOWORD(RawSecurityCookie) = 0;
        
        _security_cookie = __ROR8__(RawSecurityCookie, 16);
        _security_cookie_complement = ~_security_cookie;
    }
 
    CurrentThread = KeGetCurrentThread();
    *MK_FP(0x2B, &CurrentThread->Tcb.WaitBlockFill11[70]) = 2;
    do {
        WaitFlag = KiBarrierWait == 0;
        _mm_pause();
    } while ( !WaitFlag );
 
    KiIdleLoop(CurrentThread, shrTickCPUValue);
}
