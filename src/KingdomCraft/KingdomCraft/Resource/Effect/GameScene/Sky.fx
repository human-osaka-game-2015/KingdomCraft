Texture2D g_Texture : register(t0);
SamplerState g_Sampler : register(s0);

cbuffer camera : register(b1)
{
    matrix g_View;
    matrix g_Proj;
};

cbuffer model : register(b0)
{
    matrix g_World;
};

struct VS_OUTPUT
{
    float4 Pos : SV_POSITION;
    float4 Color : COLOR;
    float2 UV : TEXCOORD;
};

struct PS_INPUT
{
    float4 Pos : SV_POSITION;
    float4 Color : COLOR;
    float2 UV : TEXCOORD;
};

VS_OUTPUT VS(float4 Pos : POSITION, float2 UV : TEXCOORD)
{
    VS_OUTPUT Out;
    Out.Pos = mul(Pos, g_World);
    Out.Pos = mul(Out.Pos, g_View);
    Out.Pos = mul(Out.Pos, g_Proj);
    Out.UV = UV;
    return Out;
}

float4 PS(PS_INPUT IN) : SV_Target
{
    float4 Color;
    //まだ、テクスチャを貼れるようになっていないので分かるように青色で表示しておく
	//Out.Color = Texture.Sample(Sampler, IN.UV);
    Color.a = 1;
    Color.r = 0;
    Color.g = 0;
    Color.b = 0.5;
    return Color;
}
