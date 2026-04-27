Texture2D Texture : register(t0);
sampler TextureSampler : register(s0);

struct VSInput
{
    float3 position : POSITION0;
    float2 texcoord : TEXCOORD0;
    float3 normal : NORMAL0;
    float3 direction_to_camera : TEXCOORD2;
    //float4 color : COLOR0;
    //float4 color1 : COLOR1;
};

struct VSOutput
{
    float4 position : SV_Position;
    float2 texcoord : TEXCOORD0;
    float3 normal : TEXCOORD1;
    float3 direction_to_camera : TEXCOORD2;
    //float4 color : COLOR0;
    //float4 color1 : COLOR1;
}; 

cbuffer constant : register(b0)
{
    row_major float4x4 m_world;
    row_major float4x4 m_view;
    row_major float4x4 m_proj;
    float4 m_light_direction;
    float4 m_camera_position;
}

VSOutput VSMain(VSInput input)
{
    VSOutput output;
    
    //WORLD SPACE
    output.position = mul(float4(input.position, 1.0f), m_world);
    
    output.direction_to_camera = normalize(output.position.xyz - m_camera_position.xyz);
    
    //VIEW SPACE
    output.position = mul(output.position, m_view);
    
    //SCREEN SPACE
    output.position = mul(output.position, m_proj);
    
    output.texcoord = input.texcoord;
    output.normal = input.normal;
    return output;
}


float4 PSMain(VSOutput input) : SV_Target
{
    //AMBIENT LIGHT
    float ka = 0.1;
    float3 ia = float3(1.0, 1.0, 1.0);
    
    float3 ambient_light = ka * ia;
    
    //DIFFUSE LIGHT
    float kd = 0.7;
    float3 id = float3(1.0, 1.0, 1.0);
    float amount_diffuse_light = max(0.0, dot(m_light_direction.xyz, input.normal));
    
    float3 diffuse_light = kd * amount_diffuse_light * id;
    //DIFFUSE LIGHT
    
    //SPECULAR LIGHT
    float ks = 1.0;
    float3 is = float3(1.0, 1.0, 1.0);
    float3 reflected_light = reflect(-m_light_direction.xyz, input.normal);
    float shininess = 30.0;
    float amount_specular_light = pow(max(0.0, dot(reflected_light, input.direction_to_camera)), shininess);
    
    float3 specular_light = ks * amount_diffuse_light * is;
    
    float3 final_light = ambient_light + diffuse_light + specular_light;
    
    return float4(final_light, 1.0);
    
    //return Texture.Sample(TextureSampler, input.texcoord * 0.5);
    //return lerp(input.color, input.color1, (sin(m_time / 1000.0f) + 1.0f) / 2.0f);
}