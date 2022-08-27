void ExpInitializeMicrocodeUpdateLock() {
  KeInitializeGuardedMutex(&ExpMicrocodeUpdateLock); 
  // __SKVLLZ.: ExpMicrocodeUpdateLock is a Fast Mutex (_FAST_MUTEX), I'm shocked, too
  /* 
	struct _FAST_MUTEX {
		LONG Count;
		PVOID Owner;
		ULONG Contention;
		KEVENT Event;
		ULONG OldIrql;
	}
  */
  
  IsObjectReceived = 0;
  KeInitializeEvent(&Event, SynchronizationEvent, 0);
}