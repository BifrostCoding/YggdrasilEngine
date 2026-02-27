#include "StaticMesh.hlsl"

PS_INPUT VSMain(VS_INPUT input)
{
	PS_INPUT output;

	output.Pos = mul(input.inPos, WVP);

	output.normal = mul(input.normal, (float3x4) World);

	output.TexCoord = input.inTexCoord;

	return output;
}