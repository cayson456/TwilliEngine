// byte_Width: 16
// name: ViewVector

#define _c_ViewVector(x) \
cbuffer ViewVector : register(b##x##) \
{ \
  float3 camera_pos; \
  int __light_padding; \
}
