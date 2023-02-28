#include "../../InputLayouts/default.hlsl"
#include "../../ConstantBuffers/EntityTransform.hlsl"

#define NORMAL_LENGTH 0.3f

_c_EntityTransform(0);

[maxvertexcount(2)]
void main(point VertexIn vin[1], inout LineStream<VertexOut> out_stream)
{
    VertexOut point_a;
    VertexOut point_b;

    point_a.pos =  mul(mul(float4(vin[0].pos.xyz, 1.0f), view), projection);
    point_a.world_pos = vin[0].pos;
    point_a.normal = vin[0].normal;
    point_a.uv = vin[0].uv;

    point_b.pos = float4(vin[0].pos.xyz + (vin[0].normal * NORMAL_LENGTH), 1.0f);
    point_b.pos = mul(mul(point_b.pos, view), projection);
    point_b.world_pos = vin[0].pos + (vin[0].normal * NORMAL_LENGTH);
    point_b.normal = vin[0].normal;
    point_b.uv = vin[0].uv;

    out_stream.Append(point_a);
    out_stream.Append(point_b);
}
