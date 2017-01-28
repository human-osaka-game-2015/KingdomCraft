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

struct VS_INPUT
{
	float3 Pos   : POSITION;
};

struct VS_OUTPUT
{
    float4 Pos : SV_POSITION;
};

VS_OUTPUT VS(VS_INPUT In)
{
    VS_OUTPUT Out;
	Out.Pos = mul(float4(In.Pos, 1.0f), g_World);
    Out.Pos = mul(Out.Pos, g_View);
    Out.Pos = mul(Out.Pos, g_Proj);
    return Out;
}

float4 PS(VS_OUTPUT In) : SV_TARGET
{
    float4 Color;
    Color.a = 1;
	Color.r = 0.4;
	Color.g = 0.4;
	Color.b = 0.4;
    
    return Color;
}
