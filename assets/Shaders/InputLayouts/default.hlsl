#ifndef H_DEFAULT_INPUT_LAYOUT_HLSL
#define H_DEFAULT_INPUT_LAYOUT_HLSL

// input_layout_flags: 11100

struct VertexIn
{
  float3 pos : POSITION;
  float3 normal : NORMAL;
  float2 uv : TEXCOORD;
};

struct VertexOut
{
  float4 pos : SV_POSITION;
  float3 world_pos : POSITION;
  float3 normal : NORMAL;
  float2 uv : TEXCOORD;
};

#endif
