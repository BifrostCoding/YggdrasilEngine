#include "Terrain.hlsl"

float4 PSMain(PS_INPUT input) : SV_TARGET
{
  // Normal normalisieren
  input.normal = normalize(input.normal);

  // Texturfarbe
  float4 colorDefault = TextureDefault.Sample(ObjSamplerState, input.TexCoord);
  float4 colorSlope   = TextureSlope.Sample(ObjSamplerState, input.TexCoord);
  
  float slope = 1.0f - input.normal.y;

  float blendAmount = saturate(slope / 0.2f);
  
  float3 diffuse = lerp(colorDefault, colorSlope, blendAmount);

  // Ambient (leicht kühl, damit Schatten nicht neutral sind)
  float3 ambientColor = diffuse * light.ambient.rgb;

  // Berechne Lichtintensität
  float NdotL = saturate(dot(light.dir, input.normal));

  // Grundbeleuchtung (ohne diffuse nochmal zu multiplizieren)
  float3 litColor = diffuse * light.diffuse.rgb * NdotL;

  // Schattenblau definieren
  float3 shadowTint = float3(0.0f, 0.015f, 0.04f); // kühler Blauton

  // Schatten färben: je dunkler das Licht, desto mehr Blau
  litColor = lerp(shadowTint, litColor, NdotL);

  // Kombiniere Ambient + Licht
  float3 color = ambientColor + litColor;

  float fogStart = 40.0f;
  float fogEnd   = 120.0f;

  float3 fogColor = float3(0.5f, 0.7f, 0.95f);
  
  // Fog
  float dist = distance(cameraPos, input.WorldPos);
  float fogFactor = saturate((fogEnd - dist) / (fogEnd - fogStart));

  color = lerp(fogColor, color, fogFactor);

  return float4(color, 1.0f);
}