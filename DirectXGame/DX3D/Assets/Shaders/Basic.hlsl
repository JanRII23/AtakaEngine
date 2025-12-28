struct VSInput
{
    float3 position : POSITION0;
    float3 position1 : POSITION1;
    float4 color : COLOR0;
    float4 color1 : COLOR1;
};

struct VSOutput
{
    float4 position : SV_Position;
    float4 color : COLOR0;
    float4 color1 : COLOR1;
};

cbuffer constant : register(b0)
{
    unsigned int m_time;
}

VSOutput VSMain(VSInput input)
{
    VSOutput output;
    output.position = lerp(float4(input.position, 1), float4(input.position1, 1), (sin(m_time / 1000.0f) + 1.0f) / 2.0f);
    output.color = input.color;
    output.color1 = input.color1;
    return output;
}


float4 PSMain(VSOutput input) : SV_Target
{
    return lerp(input.color, input.color1, (sin(m_time / 1000.0f) + 1.0f) / 2.0f);
}