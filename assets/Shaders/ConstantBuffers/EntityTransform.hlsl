// byte_Width: 256
// name: EntityTransform

#define _c_EntityTransform(x) \
cbuffer EntityTransform : register(b##x##) \
{ \
    matrix model; \
    matrix view; \
    matrix projection; \
    matrix trans_inv_model; \
}
