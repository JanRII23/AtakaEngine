Texture2D EarthColor : register(t0);
sampler EarthColorSampler : register(s0);

Texture2D EarthSpecular : register(t1);
sampler EarthSpecularSampler : register(s1);

Texture2D Clouds : register(t2);
sampler CloudsSampler : register(s2);

Texture2D EarthNight : register(t3);
sampler EarthNightSampler : register(s3);

//TODO: do these need to be updated? check 11:45 "Creating 3D Engine"
struct VSInput
{
    float3 position : POSITION0;
    float2 texcoord : TEXCOORD0;
    float3 normal : NORMAL0;
    float3 direction_to_camera : TEXCOORD2;
};

struct VSOutput
{
    float4 position : SV_POSITION;
    float2 texcoord : TEXCOORD0;
    float3 normal : NORMAL0;
    float3 direction_to_camera : TEXCOORD2;
}; 

cbuffer constant : register(b0)
{
    row_major float4x4 m_world;
    row_major float4x4 m_view;
    row_major float4x4 m_proj;
    float4 m_light_direction;
    float4 m_camera_position;
    float m_time;
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
    float4 earth_color = EarthColor.Sample(EarthColorSampler, 1.0 - input.texcoord);
    float earth_spec = EarthSpecular.Sample(EarthSpecularSampler, 1.0 - input.texcoord).r;
    float clouds = Clouds.Sample(CloudsSampler, 1.0 - input.texcoord + float2(m_time/100.0, 0)).r;
    float4 earth_night = EarthNight.Sample(EarthNightSampler, 1.0 - input.texcoord);
    
    //AMBIENT LIGHT
    float ka = 1.5;
    float3 ia = float3(0.09, 0.082, 0.082);
    ia *= (earth_color.rgb);
    
    float3 ambient_light = ka * ia;
    
    //DIFFUSE LIGHT
    
    float kd = 0.7;
    float3 id_day = float3(1.0, 1.0, 1.0);
    id_day *= (earth_color.rgb + clouds);
    
    float3 id_night = float3(1.0, 1.0, 1.0);
    id_night *= (earth_night.rgb + clouds * 0.3);
    
    float amount_diffuse_light = dot(m_light_direction.xyz, input.normal);
    
    float3 id = lerp(id_night, id_day, (amount_diffuse_light + 1.0) / 2.0);
    
     //DIFFUSE LIGHT
    float3 diffuse_light = kd * id;
   
    //SPECULAR LIGHT
    float ks = earth_spec;
    float3 is = float3(1.0, 1.0, 1.0);
    float3 reflected_light = reflect(-m_light_direction.xyz, input.normal);
    float shininess = 30.0;
    float amount_specular_light = pow(max(0.0, dot(reflected_light, input.direction_to_camera)), shininess);
    
    float3 specular_light = ks * amount_specular_light * is;
    
    float3 final_light = ambient_light + diffuse_light + specular_light;
    
    return float4(final_light, 1.0);
    
    //return Texture.Sample(TextureSampler, input.texcoord * 0.5);
    //return lerp(input.color, input.color1, (sin(m_time / 1000.0f) + 1.0f) / 2.0f);
}