// byte_Width: 92
// num_elements: 6
// name: Light

#define LIGHT_NUM_ELEMENTS 6

struct Light
{
    float3 pos_world_space;
    float3 directon_world_space;
    float3 pos_view_space;
    float3 direction_view_space;

    float4 color;
    float spotlight_angle;
    float range;

    bool enabled;
    int type;

    int3 __padding;
};

#define _t_Light(x) \
StructuredBuffer<Light> gLights : register(t##x##)
