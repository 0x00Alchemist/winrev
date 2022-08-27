LONG __fastcall ExpWorkMicrocode(__int64 ptrRtlMicrocodeWorkerFunction) {
  ExpAcquireMicrocodeUpdateLock(); // __SKVLLZ.: Acquire fast mutex lock
  
  *(ptrRtlMicrocodeWorkerFunction + 32) = (*ptrRtlMicrocodeWorkerFunction)();
  
  ExpReleaseMicrocodeUpdateLock(); // __SKVLLZ.: Release fast mutex lock
  
  return KeSetEvent((ptrRtlMicrocodeWorkerFunction + 8), 0, 0);
}