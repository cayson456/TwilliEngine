// byte_Width: 144

#define MATERIAL(x) \
cbuffer Material : register(b##x##) \
{ \
  float4 ambient_color; \
  float4 emissive_color; \
  float4 diffuse_color; \
  float4 specular_color; \
  float4 reflectance; \
  float opacity; \
  float specular_power; \
  float index_of_refraction; \
  bool has_ambient_texture; \
  bool has_emissive_texture; \
  bool has specular_texture; \
  bool has_normal_texture; \
  bool has_bump_texture; \
  float bump_intensity; \
  float specular_scale; \
  float alpha_threshold;
  int2 __padding; \
}
