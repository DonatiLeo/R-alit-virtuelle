
varying highp vec4 outColor;
varying highp vec4 gl_FragCoord;

void main(void)
{
    gl_FragColor = outColor*(1.0 - gl_FragCoord.z*0.6);
    gl_FragColor.a = outColor.a ;
}
