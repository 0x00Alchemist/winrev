void ExpAcquireMicrocodeUpdateLock() {
  int ObjectFlag; 

  KeAcquireGuardedMutex(&ExpMicrocodeUpdateLock);
  ObjectFlag = IsObjectReceived++; // __SKVLLZ.: I suppose it is a flags
  KeReleaseGuardedMutex(&ExpMicrocodeUpdateLock);
  
  if ( ObjectFlag )
    KeWaitForSingleObject(&Event, WrExecutive, 0, 0, 0i64);
}