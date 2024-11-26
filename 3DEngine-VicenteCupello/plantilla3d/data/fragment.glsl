uniform sampler2D texSampler;
varying vec2 ftex;
varying vec3 fcolor;

void main() 
{
    gl_FragColor = texture2D(texSampler, ftex) * vec4(fcolor, 1);
}
