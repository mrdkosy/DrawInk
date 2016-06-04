uniform sampler2DRect tex;
uniform vec3 color;

void main(void){
    vec2 st = vec2(gl_TexCoord[0].x, gl_TexCoord[0].y);
    vec4  getColor = texture2DRect(tex, st);
    if(getColor.rgb == vec3(0.)){
        getColor.rgb = color;
    }
    gl_FragColor = getColor;
    
}