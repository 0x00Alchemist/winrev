__int64 __fastcall UefiQueryDeviceRelations(_DEVICE_OBJECT *Pdo, int a2, _QWORD *Mem)
{
  _QWORD *DeviceExtension; // r14
  unsigned int v4; // ebx
  _DWORD *Allocated; // rax
  _DWORD *PoolTag_swap; // rsi
  __int64 Extension; // rax
  unsigned int i; // ebp
  _DWORD *PoolWithTag; // rax
  __int64 ObjBody; // r14
  unsigned int j; // eax

  DeviceExtension = Pdo->DeviceExtension;
  v4 = 0;
  
  if ( *DeviceExtension == 1 ) {
    if ( !a2 ) {
      Extension = DeviceExtension[1];
      i = 0;
	  
      while ( Extension ) {
        Extension = *(Extension + 8);
        ++i;
      }
	  
      PoolWithTag = ExAllocatePoolWithTag(PagedPool, 8i64 * i + 16, 0x49464555u);
      PoolTag_swap = PoolWithTag;
      if ( PoolWithTag ) {
        ObjBody = DeviceExtension[1];
        *PoolWithTag = 0;
		
        if ( ObjBody ) {
          j = 0;
		  
          do {
            if ( j >= i )
              break;
            *&PoolTag_swap[2 * j + 2] = *(ObjBody + 16);
            ObfReferenceObject(*(ObjBody + 16));
            ObjBody = *(ObjBody + 8);
            j = ++*PoolTag_swap;
          } while ( ObjBody );
        }
		
        goto LABEL_18;
      }
	  
      return 0xC000009A;
    }
	
    return 0xC00000BB;
  }
  
  if ( *DeviceExtension == 2 ) {
    if ( a2 == 4 ) {
		
      Allocated = ExAllocatePoolWithTag(PagedPool, 0x10ui64, 0x49464555u);
      PoolTag_swap = Allocated;
	  
      if ( Allocated ) {
        *Allocated = 1;
        *(Allocated + 1) = Pdo;
        ObfReferenceObject(Pdo);

LABEL_18:
        *Mem = PoolTag_swap;
        return v4;
      }
	  
      return 0xC000009A;
    }
	
    return 0xC00000BB;
  }
  
  return 0xC0000010;
}