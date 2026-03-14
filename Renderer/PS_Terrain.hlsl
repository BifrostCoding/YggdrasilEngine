#include "Terrain.hlsl"

float4 PSMain(PS_INPUT input) : SV_TARGET
{
  input.normal = normalize(input.normal);

  float4 diffuse = ObjTexture.Sample(ObjSamplerState, input.TexCoord);

  float3 color = diffuse * light.ambient;
  color += saturate(dot(light.dir, input.normal) * light.diffuse * diffuse);

  float fogStart = 20.0f;
  float fogEnd = 100.0f;

  float3 fogColor = float3(0.6, 0.7, 0.8);
  
  // Fog
  float dist = distance(cameraPos, input.WorldPos);
  float fogFactor = saturate((fogEnd - dist) / (fogEnd - fogStart));

  color = lerp(fogColor, color, fogFactor);

  return float4(color, diffuse.a);
}