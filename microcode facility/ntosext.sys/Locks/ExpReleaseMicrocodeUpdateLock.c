void ExpReleaseMicrocodeUpdateLock() {
  KeAcquireGuardedMutex(&ExpMicrocodeUpdateLock);
  
  if ( --IsObjectReceived )
    KeSetEvent(&Event, 0, 0);
  
  KeReleaseGuardedMutex(&ExpMicrocodeUpdateLock);
}