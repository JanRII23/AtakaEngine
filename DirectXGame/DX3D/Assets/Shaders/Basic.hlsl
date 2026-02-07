struct VSInput
{
    float3 position : POSITION0;
    float2 texcoord : TEXCOORD0;
//    float4 color : COLOR0;
//  float4 color1 : COLOR1;
};

struct VSOutput
{
    float4 position : SV_Position;
    float2 texcoord : TEXCOORD0;
//    float4 color : COLOR0;
//    float4 color1 : COLOR1;
};

cbuffer constant : register(b0)
{
    row_major float4x4 m_world;
    row_major float4x4 m_view;
    row_major float4x4 m_proj;
    unsigned int m_time;
    float3 _padding;
}

VSOutput VSMain(VSInput input)
{
    VSOutput output;
    
    //WORLD SPACE
    output.position = mul(float4(input.position, 1.0f), m_world);
    
    //VIEW SPACE
    output.position = mul(output.position, m_view);
    
    //SCREEN SPACE
    output.position = mul(output.position, m_proj);
    
    output.texcoord = input.texcoord;
    //output.color1 = input.color1;
    return output;
}


float4 PSMain(VSOutput input) : SV_Target
{
    return lerp((sin(m_time / 1000.0f) + 1.0f) / 2.0f);
}