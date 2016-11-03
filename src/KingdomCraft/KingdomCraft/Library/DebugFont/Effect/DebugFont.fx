cbuffer cbMatrixWVP : register(b0)
{
	float4x4 matWVP;
	float4 TexelOffset;
	float4 PosOffset;
};

Texture2D Tex : register(t0);
SamplerState  Sampler : register(s0);

struct VS_IN
{
	float3 pos   : POSITION;   // 頂点座標
	float4 color : COLOR;      // 頂点カラー
	float2 texel : TEXCOORD;   // テクセル
};

struct VS_OUT
{
	float4 pos   : SV_POSITION;
	float4 color : COLOR0;
	float2 texel : TEXCOORD0;
};

VS_OUT VS(VS_IN In)
{
	VS_OUT Out;
	In.pos.xy += PosOffset.xy;
	Out.pos = mul(float4(In.pos, 1.0f), matWVP);
	Out.color = In.color;
	Out.texel = In.texel;

	return Out;
}

float4 PS(VS_OUT In) : SV_TARGET
{
	return Tex.Sample(Sampler, In.texel + TexelOffset.xy) * In.color;
}
