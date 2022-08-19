NTSTATUS __stdcall DriverEntry(_DRIVER_OBJECT *DriverObject, PUNICODE_STRING RegistryPath) {
  NTSTATUS Status;

  UefiDriverObject = DriverObject;
  DriverObject->DriverUnload = UefiDriverUnload;
  DriverObject->DriverExtension->AddDevice = &UefiAddDevice;
  DriverObject->MajorFunction[27] = UefiDispatchPnp;
  DriverObject->MajorFunction[22] = UefiDispatchPower;
  DriverObject->MajorFunction[23] = UefiDispatchWmi;
  
  Status = UefiEsrtInitialize(RegistryPath);
  if ( Status >= 0 )
    UefiTraceInitialize();
  
  return Status;
}