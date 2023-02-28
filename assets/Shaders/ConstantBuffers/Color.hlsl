// byte_Width: 16
// name: Color

#define _c_Color(x) \
cbuffer Color : register(b##x##) \
{ \
  float4 color; \
}
