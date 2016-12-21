Texture2D g_Texture: register(t0);
SamplerState g_Sampler : register(s0);

cbuffer global
{
	matrix g_WorldMat;
	float4 g_ViewPort;
};

struct VS_OUTPUT
{
	float4 Pos	 : SV_POSITION;
	float2 UV	 : TEXCOORD;
	float4 Color : COLOR;
};

struct PS_INPUT
{
	float4 Pos   : SV_POSITION;
	float2 UV    : TEXCOORD;
	float4 Color : COLOR;
};

VS_OUTPUT VS(float4 Pos : POSITION, float2 UV : TEXCOORD, float4 Color : COLOR)
{
	VS_OUTPUT Out;
	
	Out.Pos   = mul(Pos, g_WorldMat);
	Out.Pos.x = (Out.Pos.x / g_ViewPort.x) * 2 - 1;
	Out.Pos.y = 1 - (Out.Pos.y / g_ViewPort.y) * 2;
	Out.UV = UV;
	Out.Color = Color;

	return Out;
}

float4 PS(PS_INPUT Input) : SV_Target
{
	float4 OutColor;
	OutColor = g_Texture.Sample(g_Sampler, Input.UV);
	OutColor *= Input.Color;
	return OutColor;
}
