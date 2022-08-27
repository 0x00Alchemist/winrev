NTSTATUS __stdcall ExpMicrocodeInformationLoad() {
  KPROCESSOR_MODE PreviousMode; 
  NTSTATUS result; 
  struct _WORK_QUEUE_ITEM WorkItem; 
  __int64 (*RtlExpMicrocodeLoadImage)(); 
  __m256 Event; 

  WorkItem.List.Blink = 0i64;
  
  memset(&Event, 0, sizeof(Event));
  PreviousMode = *(KeGetCurrentThread() + 562);
  
  if ( !PreviousMode )
    goto LABEL_6;
  
  // __SKVLLZ.: Chceck if we can load drivers
  if ( !SeSinglePrivilegeCheck(SeExports->SeLoadDriverPrivilege, PreviousMode) )
    return 0xC0000061;
  
  // __SKVLLZ.: checking magic number, idk what to say
  if ( _InterlockedIncrement(&ExpUserModeCallerCount) == 1 ) {
LABEL_6:
    RtlExpMicrocodeLoadImage = ExpLoadMicrocodeImage; // __SKVLLZ.: And yeah, idk how to name runtime function too
	
    KeInitializeEvent(&Event, NotificationEvent, 0);
    
	WorkItem.List.Flink = 0i64;
    WorkItem.WorkerRoutine = ExpWorkMicrocode;  // __SKVLLZ.: Setting Worker routine
    WorkItem.Parameter = &RtlExpMicrocodeLoadImage; // __SKVLLZ.: Setting Worker load image parameter
    
	ExQueueWorkItem(&WorkItem, DelayedWorkQueue);
    KeWaitForSingleObject(&Event, UserRequest, 0, 0, 0i64);
    
	result = LODWORD(Event.m256_f32[6]);
    
	if ( !PreviousMode )
      return result;
  
  } else {
    result = 0xC0000043;
  }
  
  _InterlockedDecrement(&ExpUserModeCallerCount);
  
  return result;
}