inline S32 S32.clamp(int32_t min, int32_t max) {
  S32 n = *this;
  n = n > max ? max : n;
  return n < min ? min : n;
}

inline S32 S32.clamp_byte {
  S32 n = *this;
  n = n > 255 ? 255 : n;
  return n < 0 ? 0 : n;
}

inline U32 U32.clamp(int32_t min, int32_t max) {
  U32 n = *this;
  n = n > max ? max : n;
  return n < min ? min : n;
}

inline U32 U32.clamp_byte {
  U32 n = *this;
  return n > 255 ? 255 : n;
}

inline F32 F32.clamp(F32 min, F32 max) {
  F32 d = *this;
  const F32 t = d < min ? min : d;
  return t > max ? max : t;
}

inline F32 F32.clamp_byte {
  F32 n = *this;
  n = n > 255.0f ? 255.0f : n;
  return n < 0.0f ? 0.0f : n;
}
