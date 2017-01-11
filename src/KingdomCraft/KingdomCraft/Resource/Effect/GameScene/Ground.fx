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

struct VS_INPUT
{
	float3 Pos   : POSITION;
	float3 Normal : NORMAL;
	float2 UV : TEXCOORD;
};

struct VS_OUTPUT
{
	float4 Pos : SV_POSITION;
	float4 Normal : NORMAL;
	float2 UV : TEXCOORD;
};

VS_OUTPUT VS(VS_INPUT In)
{
	VS_OUTPUT Out;
	Out.Pos = mul(float4(In.Pos, 1.0f), g_World);
	Out.Pos = mul(Out.Pos, g_View);
	Out.Pos = mul(Out.Pos, g_Proj);
	Out.UV = In.UV;
	return Out;
}

float4 PS(VS_OUTPUT In) : SV_TARGET
{
	return g_Texture.Sample(g_Sampler, In.UV);
}
