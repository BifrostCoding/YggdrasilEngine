#include "StaticMesh.hlsl"

float4 PSMain(PS_INPUT input) : SV_TARGET
{
	input.normal = normalize(input.normal);

	float4 diffuse = ObjTexture.Sample(ObjSamplerState, input.TexCoord);

	float3 color = diffuse * light.ambient;
	color += saturate(dot(light.dir, input.normal) * light.diffuse * diffuse);
    
	return float4(color, diffuse.a);
}