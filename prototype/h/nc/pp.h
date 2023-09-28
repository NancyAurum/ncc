//pre-processor definitions

#pp_map(f,x,[xs]) {f(x)#if xs_n != 0 , pp_map(f,xs) #endif}
