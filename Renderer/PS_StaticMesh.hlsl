#include "StaticMesh.hlsl"

float4 PSMain(PS_INPUT input) : SV_TARGET
{
  // Normal normalisieren
  input.normal = normalize(input.normal);

  // Texturfarbe
  float4 diffuse = ObjTexture.Sample(ObjSamplerState, input.TexCoord);

  // Ambient (leicht kühl, damit Schatten nicht neutral sind)
  float3 ambientColor = diffuse.rgb * light.ambient.rgb;

  // Berechne Lichtintensität
  float NdotL = saturate(dot(light.dir, input.normal));

  // Grundbeleuchtung (ohne diffuse nochmal zu multiplizieren)
  float3 litColor = diffuse.rgb * light.diffuse.rgb * NdotL;

  // Schattenblau definieren
  float3 shadowTint = float3(0.0f, 0.015f, 0.075f); // kühler Blauton

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
  
  float4 finalColor = float4(color, diffuse.a);
  
  clip(finalColor.a - 0.25f);

  return finalColor;
}