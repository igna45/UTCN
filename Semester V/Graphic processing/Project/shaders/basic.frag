#version 410 core

in vec3 fPosition;
in vec3 fNormal;
in vec2 fTexCoords;



out vec4 fColor;

//matrice
uniform mat4 model;
uniform mat4 view;
uniform mat3 normalMatrix;

//lighting
uniform vec3 lightDir;
uniform vec3 lightColor;


//umbre
uniform sampler2D shadowMap;
in vec4 fragPosLightSpace;


uniform vec3 lightPunctiformColor;

uniform vec3 lightPunctiform;

// textures
uniform sampler2D diffuseTexture;
uniform sampler2D specularTexture;


uniform int afisLuminaDoi;
uniform int afisCeata;
//components

float constant = 0.01f;
float linear = 0.004f;
float quadratic = 0.0004f;


vec3 ambient;
float ambientStrength = 0.2f;
vec3 diffuse;
vec3 specular;
float specularStrength = 0.5f;


vec4 fPosEye;

void computeDirLight()
{
    // Pre-calculate the light direction and eye space coordinates
    vec3 lightDirectionNormalized = normalize(view * vec4(lightDir, 0.0f)).xyz;
    vec4 eyeSpacePosition = view * model * vec4(fPosition, 1.0f);
    vec3 eyeSpaceNormal = normalize(normalMatrix * fNormal);
    vec3 eyeSpaceViewDirection = normalize(-eyeSpacePosition.xyz);

    // Compute the reflection direction for the specular component
    vec3 reflectedLightDirection = reflect(-lightDirectionNormalized, eyeSpaceNormal);

    // Calculate the dot products for diffuse and specular components
    float diffuseDotProduct = max(dot(eyeSpaceNormal, lightDirectionNormalized), 0.0f);
    float specularDotProduct = pow(max(dot(eyeSpaceViewDirection, reflectedLightDirection), 0.0f), 32.0f);

    // Calculate each light component
    ambient = ambientStrength * lightColor;
    diffuse = diffuseDotProduct * lightColor;
    specular = specularStrength * specularDotProduct * lightColor;
}


vec3 computePunctiformLight(vec3 diffTex, vec3 specTex) 
 {
    fPosEye = vec4(fPosition, 1.0f);

    //compute distance to light
	float dist = length(lightPunctiform - fPosEye.xyz);
	//compute attenuation
	float att = 1.0f / (constant + linear * dist + quadratic * (dist * dist));

    //transform normal
	vec3 normalEye = normalize(fNormal);
    //compute light direction
	vec3 lightDirN = normalize(lightPunctiform -  fPosEye.xyz);
    //compute view direction 
	vec3 viewDirN = normalize(lightPunctiform- fPosEye.xyz);

    //compute ambient light
	vec3 ambient1 = att  *ambientStrength * lightPunctiformColor;
    //compute diffuse light
	vec3 diffuse1 = att * max(dot(normalEye, lightDirN), 0.0f) * lightPunctiformColor;

    vec3 halfVector = normalize(lightDirN + viewDirN);
	float specCoeff = pow(max(dot(viewDirN, halfVector), 0.3f), 32.0f);
	vec3 specular1 = att * specularStrength * specCoeff * lightPunctiformColor;


	
	return  min(((ambient + diffuse) * diffTex + specular * specTex ) * att * 2, 1.0f);


}

float computeShadow()
{

	vec3 normalizedCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;

	normalizedCoords = normalizedCoords * 0.5 + 0.5;
	
	if (normalizedCoords.z > 1.0f) return 0.0f;

	float closestDepth = texture(shadowMap, normalizedCoords.xy).r;

	float currentDepth = normalizedCoords.z;

	float bias = max(0.05f * (1.0f - dot(fNormal,lightDir)), 0.05f);
	float shadow = currentDepth - bias > closestDepth ? 1.0 : 0.0;	

	return shadow;

}

float computeFog()
{
 fPosEye = view * model * vec4(fPosition, 1.0f);
 float fragmentDistance = length(fPosEye);
 float fogDensity = 0.077f;
 float fogFactor = exp(-pow(fragmentDistance * fogDensity, 2));
 return clamp(fogFactor, 0.0f, 1.0f);
}

void main() 
{
    vec4 texColorDiffuse = texture(diffuseTexture, fTexCoords);
    if(texColorDiffuse.a < 0.005 ){
       discard;
    }
    vec4 texColorSpecular = texture(specularTexture, fTexCoords);
    if(texColorSpecular.a < 0.005 ){
        discard;
    }    
    computeDirLight();
    vec3 punctLight = computePunctiformLight(texColorDiffuse.rgb,texColorSpecular.rgb);

    ambient *= texColorDiffuse.rgb;
	diffuse *= texColorDiffuse.rgb;
	specular *= texColorSpecular.rgb;
    
    float shadow = computeShadow();
    vec3 color = min((ambient + (1.0f - shadow)*diffuse) + (1.0f - shadow)*specular, 1.0f);

    if(afisLuminaDoi == 1)color = color + punctLight;
    
    vec4 colorFull = vec4(color, 1.0f);

    if(afisCeata == 1)
    {        
        float fogFactor = computeFog();
        vec4 fogColor = vec4(0.5f, 0.5f, 0.5f, 1.0f);
        fColor = fogColor * (1 - fogFactor) + colorFull * fogFactor;
    }else
    {
        fColor = colorFull;
    }

}