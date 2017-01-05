Texture2D Texture: register(t0);
SamplerState Sampler : register(s0);

cbuffer global
{
	matrix g_WorldMat;
	float4 g_Alpha;
	float4 g_ViewPort;//ビューポート（スクリーン）横サイズ
	float4 g_TexScroll;
};

struct PS_INPUT
{
	float4 Pos   : SV_POSITION;
	float4 Color : COLOR;
	float2 UV    : TEXCOORD;
};

struct VS_OUTPUT
{
	float4 Pos	 : SV_POSITION;
	float4 Color : COLOR;
	float2 UV	 : TEXCOORD;
};

VS_OUTPUT VS(float4 Pos : POSITION, float2 UV : TEXCOORD)
{
	VS_OUTPUT Out;
	
	Out.Pos   = mul(Pos, g_WorldMat);

	Out.Pos.x = (Out.Pos.x / g_ViewPort.x) * 2 - 1;
	Out.Pos.y = 1 - (Out.Pos.y / g_ViewPort.y) * 2;
	Out.UV = UV;
	Out.UV.x += g_TexScroll.x;
	Out.UV.y += g_TexScroll.y;

	return Out;
}

float4 PS(PS_INPUT Input) : SV_Target
{
	PS_INPUT Out;
	Out.Color = Texture.Sample(Sampler, Input.UV);
	Out.Color.a *= g_Alpha.a;
	return Out.Color;
}