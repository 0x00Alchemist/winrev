__int64 __fastcall UefiDispatchWmi(_DEVICE_OBJECT *Pdo, IRP *pIrp) {
  return UefiDispatchForwardIrp(Pdo, pIrp);
}