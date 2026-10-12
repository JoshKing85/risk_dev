#version 120

uniform sampler2D texture;
uniform float grainStrength;

float random(vec2 position)
{
    return fract(
        sin(dot(position, vec2(12.9898, 78.233)))
        * 43758.5453
    );
}

void main()
{
    vec2 uv = gl_TexCoord[0].xy;

    vec4 colour = texture2D(texture, uv);

    float noise = random(gl_FragCoord.xy);

    float grain = (noise - 0.5) * grainStrength;

    colour.rgb = clamp(
        colour.rgb + vec3(grain),
        0.0,
        1.0
    );

    gl_FragColor = colour;
}