xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 194;
 135.69165;26.66565;-38.56035;,
 135.69165;73.83795;-38.56035;,
 135.69165;73.83795;39.30690;,
 135.69165;26.66565;39.30690;,
 135.69165;26.66565;39.30690;,
 135.69165;73.83795;39.30690;,
 -116.92830;73.83795;39.30690;,
 -116.92830;26.66565;39.30690;,
 -135.16590;9.94140;39.30690;,
 -135.16590;26.66565;39.30690;,
 -135.16590;26.66565;-38.56035;,
 -135.16590;9.94140;-38.56035;,
 -116.92830;9.94140;-38.56035;,
 -116.92830;26.66565;-38.56035;,
 135.69165;26.66565;-38.56035;,
 135.69165;9.94140;-38.56035;,
 135.69165;73.83795;-38.56035;,
 -116.92830;73.83795;-38.56035;,
 -116.92830;73.83795;39.30690;,
 135.69165;73.83795;39.30690;,
 -116.92830;9.94140;-38.56035;,
 135.69165;9.94140;-38.56035;,
 135.69165;9.94140;39.30690;,
 -116.92830;9.94140;39.30690;,
 -135.16590;9.94140;39.30690;,
 -135.16590;9.94140;-38.56035;,
 -135.16590;26.66565;-38.56035;,
 -119.89289;73.83795;-38.56035;,
 -116.92830;73.83795;-38.56035;,
 -119.89289;73.83795;-38.56035;,
 -119.89289;73.83795;39.30690;,
 -135.16590;26.66565;39.30690;,
 -135.16590;9.94140;39.30690;,
 -116.92830;9.94140;39.30690;,
 135.69165;9.94140;39.30690;,
 135.69165;9.94140;-38.56035;,
 135.69165;73.83795;-38.56035;,
 -119.89289;73.83795;39.30690;,
 -119.89289;73.83795;-38.56035;,
 -135.16590;9.94140;-38.56035;,
 -119.89289;73.83795;39.30690;,
 80.02110;10.09755;-34.81965;,
 91.32690;10.09755;-34.81965;,
 90.64500;13.75185;-34.81965;,
 91.32690;10.09755;-41.94120;,
 90.64500;13.75185;-41.94120;,
 80.02110;10.09755;-41.94120;,
 88.68180;16.96530;-34.81965;,
 88.68180;16.96530;-41.94120;,
 85.67400;19.35045;-34.81965;,
 85.67400;19.35045;-41.94120;,
 81.98430;20.61960;-34.81965;,
 81.98430;20.61960;-41.94120;,
 78.05790;20.61960;-34.81965;,
 78.05790;20.61960;-41.94120;,
 74.36820;19.35045;-34.81965;,
 74.36820;19.35045;-41.94120;,
 71.36040;16.96530;-34.81965;,
 71.36040;16.96530;-41.94120;,
 69.39720;13.75185;-34.81965;,
 69.39720;13.75185;-41.94120;,
 68.71545;10.09755;-34.81965;,
 68.71545;10.09755;-41.94120;,
 69.39720;6.44325;-34.81965;,
 69.39720;6.44325;-41.94120;,
 71.36040;3.22980;-34.81965;,
 71.36040;3.22980;-41.94120;,
 74.36820;0.84465;-34.81965;,
 74.36820;0.84465;-41.94120;,
 78.05790;-0.42450;-34.81965;,
 78.05790;-0.42450;-41.94120;,
 81.98430;-0.42450;-34.81965;,
 81.98430;-0.42450;-41.94120;,
 85.67400;0.84465;-34.81965;,
 85.67400;0.84465;-41.94120;,
 88.68180;3.22980;-34.81965;,
 88.68180;3.22980;-41.94120;,
 90.64500;6.44325;-34.81965;,
 90.64500;6.44325;-41.94120;,
 -87.23475;10.13790;-34.80705;,
 -75.92910;10.13790;-34.80705;,
 -76.61085;13.79220;-34.80705;,
 -75.92910;10.13790;-41.92860;,
 -76.61085;13.79220;-41.92860;,
 -87.23475;10.13790;-41.92860;,
 -78.57405;17.00565;-34.80705;,
 -78.57405;17.00565;-41.92860;,
 -81.58200;19.39080;-34.80705;,
 -81.58200;19.39080;-41.92860;,
 -85.27155;20.65995;-34.80705;,
 -85.27155;20.65995;-41.92860;,
 -89.19810;20.65995;-34.80705;,
 -89.19810;20.65995;-41.92860;,
 -92.88765;19.39080;-34.80705;,
 -92.88765;19.39080;-41.92860;,
 -95.89545;17.00565;-34.80705;,
 -95.89545;17.00565;-41.92860;,
 -97.85880;13.79220;-34.80705;,
 -97.85880;13.79220;-41.92860;,
 -98.54055;10.13790;-34.80705;,
 -98.54055;10.13790;-41.92860;,
 -97.85880;6.48360;-34.80705;,
 -97.85880;6.48360;-41.92860;,
 -95.89545;3.27015;-34.80705;,
 -95.89545;3.27015;-41.92860;,
 -92.88765;0.88500;-34.80705;,
 -92.88765;0.88500;-41.92860;,
 -89.19810;-0.38415;-34.80705;,
 -89.19810;-0.38415;-41.92860;,
 -85.27155;-0.38415;-34.80705;,
 -85.27155;-0.38415;-41.92860;,
 -81.58200;0.88500;-34.80705;,
 -81.58200;0.88500;-41.92860;,
 -78.57405;3.27015;-34.80705;,
 -78.57405;3.27015;-41.92860;,
 -76.61085;6.48360;-34.80705;,
 -76.61085;6.48360;-41.92860;,
 -87.23475;10.13790;41.41425;,
 -75.92910;10.13790;41.41425;,
 -76.61085;13.79220;41.41425;,
 -75.92910;10.13790;34.29270;,
 -76.61085;13.79220;34.29270;,
 -87.23475;10.13790;34.29270;,
 -78.57405;17.00565;41.41425;,
 -78.57405;17.00565;34.29270;,
 -81.58200;19.39080;41.41425;,
 -81.58200;19.39080;34.29270;,
 -85.27155;20.65995;41.41425;,
 -85.27155;20.65995;34.29270;,
 -89.19810;20.65995;41.41425;,
 -89.19810;20.65995;34.29270;,
 -92.88765;19.39080;41.41425;,
 -92.88765;19.39080;34.29270;,
 -95.89545;17.00565;41.41425;,
 -95.89545;17.00565;34.29270;,
 -97.85880;13.79220;41.41425;,
 -97.85880;13.79220;34.29270;,
 -98.54055;10.13790;41.41425;,
 -98.54055;10.13790;34.29270;,
 -97.85880;6.48360;41.41425;,
 -97.85880;6.48360;34.29270;,
 -95.89545;3.27015;41.41425;,
 -95.89545;3.27015;34.29270;,
 -92.88765;0.88500;41.41425;,
 -92.88765;0.88500;34.29270;,
 -89.19810;-0.38415;41.41425;,
 -89.19810;-0.38415;34.29270;,
 -85.27155;-0.38415;41.41425;,
 -85.27155;-0.38415;34.29270;,
 -81.58200;0.88500;41.41425;,
 -81.58200;0.88500;34.29270;,
 -78.57405;3.27015;41.41425;,
 -78.57405;3.27015;34.29270;,
 -76.61085;6.48360;41.41425;,
 -76.61085;6.48360;34.29270;,
 135.69165;9.94140;39.30690;,
 80.02110;10.68600;41.50125;,
 91.32690;10.68600;41.50125;,
 90.64500;14.34030;41.50125;,
 91.32690;10.68600;34.37970;,
 90.64500;14.34030;34.37970;,
 80.02110;10.68600;34.37970;,
 88.68180;17.55375;41.50125;,
 88.68180;17.55375;34.37970;,
 85.67400;19.93890;41.50125;,
 85.67400;19.93890;34.37970;,
 81.98430;21.20805;41.50125;,
 81.98430;21.20805;34.37970;,
 78.05790;21.20805;41.50125;,
 78.05790;21.20805;34.37970;,
 74.36820;19.93890;41.50125;,
 74.36820;19.93890;34.37970;,
 71.36040;17.55375;41.50125;,
 71.36040;17.55375;34.37970;,
 69.39720;14.34030;41.50125;,
 69.39720;14.34030;34.37970;,
 68.71545;10.68600;41.50125;,
 68.71545;10.68600;34.37970;,
 69.39720;7.03170;41.50125;,
 69.39720;7.03170;34.37970;,
 71.36040;3.81825;41.50125;,
 71.36040;3.81825;34.37970;,
 74.36820;1.43310;41.50125;,
 74.36820;1.43310;34.37970;,
 78.05790;0.16395;41.50125;,
 78.05790;0.16395;34.37970;,
 81.98430;0.16395;41.50125;,
 81.98430;0.16395;34.37970;,
 85.67400;1.43310;41.50125;,
 85.67400;1.43310;34.37970;,
 88.68180;3.81825;41.50125;,
 88.68180;3.81825;34.37970;,
 90.64500;7.03170;41.50125;,
 90.64500;7.03170;34.37970;;
 
 232;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;8,9,10,11;,
 4;12,13,14,15;,
 4;16,17,18,19;,
 4;20,21,22,23;,
 4;23,24,25,20;,
 4;26,27,28,13;,
 4;17,29,30,18;,
 4;31,32,33,7;,
 4;3,34,35,0;,
 4;13,28,36,14;,
 4;9,37,38,10;,
 4;13,12,39,26;,
 4;7,6,40,31;,
 3;41,42,43;,
 4;42,44,45,43;,
 3;44,46,45;,
 3;41,43,47;,
 4;43,45,48,47;,
 3;45,46,48;,
 3;41,47,49;,
 4;47,48,50,49;,
 3;48,46,50;,
 3;41,49,51;,
 4;49,50,52,51;,
 3;50,46,52;,
 3;41,51,53;,
 4;51,52,54,53;,
 3;52,46,54;,
 3;41,53,55;,
 4;53,54,56,55;,
 3;54,46,56;,
 3;41,55,57;,
 4;55,56,58,57;,
 3;56,46,58;,
 3;41,57,59;,
 4;57,58,60,59;,
 3;58,46,60;,
 3;41,59,61;,
 4;59,60,62,61;,
 3;60,46,62;,
 3;41,61,63;,
 4;61,62,64,63;,
 3;62,46,64;,
 3;41,63,65;,
 4;63,64,66,65;,
 3;64,46,66;,
 3;41,65,67;,
 4;65,66,68,67;,
 3;66,46,68;,
 3;41,67,69;,
 4;67,68,70,69;,
 3;68,46,70;,
 3;41,69,71;,
 4;69,70,72,71;,
 3;70,46,72;,
 3;41,71,73;,
 4;71,72,74,73;,
 3;72,46,74;,
 3;41,73,75;,
 4;73,74,76,75;,
 3;74,46,76;,
 3;41,75,77;,
 4;75,76,78,77;,
 3;76,46,78;,
 3;41,77,42;,
 4;77,78,44,42;,
 3;78,46,44;,
 3;79,80,81;,
 4;80,82,83,81;,
 3;82,84,83;,
 3;79,81,85;,
 4;81,83,86,85;,
 3;83,84,86;,
 3;79,85,87;,
 4;85,86,88,87;,
 3;86,84,88;,
 3;79,87,89;,
 4;87,88,90,89;,
 3;88,84,90;,
 3;79,89,91;,
 4;89,90,92,91;,
 3;90,84,92;,
 3;79,91,93;,
 4;91,92,94,93;,
 3;92,84,94;,
 3;79,93,95;,
 4;93,94,96,95;,
 3;94,84,96;,
 3;79,95,97;,
 4;95,96,98,97;,
 3;96,84,98;,
 3;79,97,99;,
 4;97,98,100,99;,
 3;98,84,100;,
 3;79,99,101;,
 4;99,100,102,101;,
 3;100,84,102;,
 3;79,101,103;,
 4;101,102,104,103;,
 3;102,84,104;,
 3;79,103,105;,
 4;103,104,106,105;,
 3;104,84,106;,
 3;79,105,107;,
 4;105,106,108,107;,
 3;106,84,108;,
 3;79,107,109;,
 4;107,108,110,109;,
 3;108,84,110;,
 3;79,109,111;,
 4;109,110,112,111;,
 3;110,84,112;,
 3;79,111,113;,
 4;111,112,114,113;,
 3;112,84,114;,
 3;79,113,115;,
 4;113,114,116,115;,
 3;114,84,116;,
 3;79,115,80;,
 4;115,116,82,80;,
 3;116,84,82;,
 3;117,118,119;,
 4;118,120,121,119;,
 3;120,122,121;,
 3;117,119,123;,
 4;119,121,124,123;,
 3;121,122,124;,
 3;117,123,125;,
 4;123,124,126,125;,
 3;124,122,126;,
 3;117,125,127;,
 4;125,126,128,127;,
 3;126,122,128;,
 3;117,127,129;,
 4;127,128,130,129;,
 3;128,122,130;,
 3;117,129,131;,
 4;129,130,132,131;,
 3;130,122,132;,
 3;117,131,133;,
 4;131,132,134,133;,
 3;132,122,134;,
 3;117,133,135;,
 4;133,134,136,135;,
 3;134,122,136;,
 3;117,135,137;,
 4;135,136,138,137;,
 3;136,122,138;,
 3;117,137,139;,
 4;137,138,140,139;,
 3;138,122,140;,
 3;117,139,141;,
 4;139,140,142,141;,
 3;140,122,142;,
 3;117,141,143;,
 4;141,142,144,143;,
 3;142,122,144;,
 3;117,143,145;,
 4;143,144,146,145;,
 3;144,122,146;,
 3;117,145,147;,
 4;145,146,148,147;,
 3;146,122,148;,
 3;117,147,149;,
 4;147,148,150,149;,
 3;148,122,150;,
 3;117,149,151;,
 4;149,150,152,151;,
 3;150,122,152;,
 3;117,151,153;,
 4;151,152,154,153;,
 3;152,122,154;,
 3;117,153,118;,
 4;153,154,120,118;,
 3;154,122,120;,
 4;7,33,155,4;,
 3;156,157,158;,
 4;157,159,160,158;,
 3;159,161,160;,
 3;156,158,162;,
 4;158,160,163,162;,
 3;160,161,163;,
 3;156,162,164;,
 4;162,163,165,164;,
 3;163,161,165;,
 3;156,164,166;,
 4;164,165,167,166;,
 3;165,161,167;,
 3;156,166,168;,
 4;166,167,169,168;,
 3;167,161,169;,
 3;156,168,170;,
 4;168,169,171,170;,
 3;169,161,171;,
 3;156,170,172;,
 4;170,171,173,172;,
 3;171,161,173;,
 3;156,172,174;,
 4;172,173,175,174;,
 3;173,161,175;,
 3;156,174,176;,
 4;174,175,177,176;,
 3;175,161,177;,
 3;156,176,178;,
 4;176,177,179,178;,
 3;177,161,179;,
 3;156,178,180;,
 4;178,179,181,180;,
 3;179,161,181;,
 3;156,180,182;,
 4;180,181,183,182;,
 3;181,161,183;,
 3;156,182,184;,
 4;182,183,185,184;,
 3;183,161,185;,
 3;156,184,186;,
 4;184,185,187,186;,
 3;185,161,187;,
 3;156,186,188;,
 4;186,187,189,188;,
 3;187,161,189;,
 3;156,188,190;,
 4;188,189,191,190;,
 3;189,161,191;,
 3;156,190,192;,
 4;190,191,193,192;,
 3;191,161,193;,
 3;156,192,157;,
 4;192,193,159,157;,
 3;193,161,159;;
 
 MeshMaterialList {
  6;
  232;
  1,
  3,
  0,
  3,
  2,
  2,
  2,
  3,
  2,
  3,
  1,
  3,
  0,
  3,
  3,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  3,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5;;
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\Car\\CarHead1.png";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\Car\\CarAss1.png";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\Car\\CarTop1.png";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\Car\\CarWindow1.png";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\Car\\CarWheel1.png";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\Car\\CarWheel1.png";
   }
  }
 }
 MeshNormals {
  67;
  0.000000;0.000000;-1.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.000000;0.000000;1.000000;,
  0.000000;1.000000;0.000000;,
  -1.000000;0.000000;0.000000;,
  -0.987769;0.155921;0.000000;,
  0.933605;0.358303;0.000000;,
  0.748909;0.662673;0.000000;,
  0.480191;0.877164;0.000000;,
  0.164890;0.986312;0.000000;,
  -0.164890;0.986312;0.000000;,
  -0.480191;0.877164;0.000000;,
  -0.748909;0.662673;0.000000;,
  -0.933612;0.358285;0.000000;,
  -0.933612;-0.358285;0.000000;,
  -0.748909;-0.662673;0.000000;,
  -0.480191;-0.877164;0.000000;,
  -0.164890;-0.986312;0.000000;,
  0.164890;-0.986312;-0.000000;,
  0.480191;-0.877164;-0.000000;,
  0.748909;-0.662673;-0.000000;,
  0.933605;-0.358303;-0.000000;,
  1.000000;0.000000;0.000000;,
  0.933612;0.358285;0.000000;,
  0.748901;0.662682;0.000000;,
  0.480186;0.877167;0.000000;,
  0.164897;0.986311;0.000000;,
  -0.164897;0.986311;0.000000;,
  -0.480196;0.877161;0.000000;,
  -0.748898;0.662685;0.000000;,
  -0.933606;0.358301;0.000000;,
  -0.933606;-0.358301;0.000000;,
  -0.748898;-0.662685;0.000000;,
  -0.480196;-0.877161;0.000000;,
  -0.164897;-0.986311;0.000000;,
  0.164897;-0.986311;-0.000000;,
  0.480186;-0.877167;-0.000000;,
  0.748901;-0.662682;-0.000000;,
  0.933612;-0.358285;-0.000000;,
  0.933612;0.358285;0.000000;,
  0.164897;0.986311;0.000000;,
  -0.164897;0.986311;0.000000;,
  -0.480196;0.877161;0.000000;,
  -0.933606;-0.358301;0.000000;,
  0.933612;-0.358285;-0.000000;,
  -0.951377;0.308028;0.000000;,
  0.000000;0.000000;1.000000;,
  0.000000;0.000000;-1.000000;,
  1.000000;0.000000;0.000000;,
  0.933605;0.358303;0.000000;,
  0.748909;0.662673;0.000000;,
  0.480191;0.877164;0.000000;,
  0.164890;0.986312;0.000000;,
  -0.164890;0.986312;0.000000;,
  -0.480191;0.877164;0.000000;,
  -0.748909;0.662673;0.000000;,
  -0.933612;0.358285;0.000000;,
  -1.000000;0.000000;0.000000;,
  -0.933612;-0.358285;0.000000;,
  -0.748909;-0.662673;0.000000;,
  -0.480191;-0.877164;0.000000;,
  -0.164890;-0.986312;0.000000;,
  0.164890;-0.986312;-0.000000;,
  0.480191;-0.877164;-0.000000;,
  0.748909;-0.662673;-0.000000;,
  0.933605;-0.358303;-0.000000;;
  232;
  4;1,1,1,1;,
  4;3,3,3,3;,
  4;5,6,6,5;,
  4;0,0,0,0;,
  4;4,4,4,4;,
  4;2,2,2,2;,
  4;2,2,2,2;,
  4;0,0,0,0;,
  4;4,4,4,4;,
  4;3,3,3,3;,
  4;1,1,1,1;,
  4;0,0,0,0;,
  4;6,46,46,6;,
  4;0,0,0,0;,
  4;3,3,3,3;,
  3;3,3,3;,
  4;1,1,7,7;,
  3;0,0,0;,
  3;3,3,3;,
  4;7,7,8,8;,
  3;0,0,0;,
  3;3,3,3;,
  4;8,8,9,9;,
  3;0,0,0;,
  3;3,3,3;,
  4;9,9,10,10;,
  3;0,0,0;,
  3;3,3,3;,
  4;10,10,11,11;,
  3;0,0,0;,
  3;3,3,3;,
  4;11,11,12,12;,
  3;0,0,0;,
  3;3,3,3;,
  4;12,12,13,13;,
  3;0,0,0;,
  3;3,3,3;,
  4;13,13,14,14;,
  3;0,0,0;,
  3;3,3,3;,
  4;14,14,5,5;,
  3;0,0,0;,
  3;3,3,3;,
  4;5,5,15,15;,
  3;0,0,0;,
  3;3,3,3;,
  4;15,15,16,16;,
  3;0,0,0;,
  3;3,3,3;,
  4;16,16,17,17;,
  3;0,0,0;,
  3;3,3,3;,
  4;17,17,18,18;,
  3;0,0,0;,
  3;3,3,3;,
  4;18,18,19,19;,
  3;0,0,0;,
  3;3,3,3;,
  4;19,19,20,20;,
  3;0,0,0;,
  3;3,3,3;,
  4;20,20,21,21;,
  3;0,0,0;,
  3;3,3,3;,
  4;21,21,22,22;,
  3;0,0,0;,
  3;3,3,3;,
  4;22,22,1,1;,
  3;0,0,0;,
  3;3,3,3;,
  4;23,23,24,24;,
  3;0,0,0;,
  3;3,3,3;,
  4;24,24,25,25;,
  3;0,0,0;,
  3;3,3,3;,
  4;25,25,26,26;,
  3;0,0,0;,
  3;3,3,3;,
  4;26,26,27,27;,
  3;0,0,0;,
  3;3,3,3;,
  4;27,27,28,28;,
  3;0,0,0;,
  3;3,3,3;,
  4;28,28,29,29;,
  3;0,0,0;,
  3;3,3,3;,
  4;29,29,30,30;,
  3;0,0,0;,
  3;3,3,3;,
  4;30,30,31,31;,
  3;0,0,0;,
  3;3,3,3;,
  4;31,31,5,5;,
  3;0,0,0;,
  3;3,3,3;,
  4;5,5,32,32;,
  3;0,0,0;,
  3;3,3,3;,
  4;32,32,33,33;,
  3;0,0,0;,
  3;3,3,3;,
  4;33,33,34,34;,
  3;0,0,0;,
  3;3,3,3;,
  4;34,34,35,35;,
  3;0,0,0;,
  3;3,3,3;,
  4;35,35,36,36;,
  3;0,0,0;,
  3;3,3,3;,
  4;36,36,37,37;,
  3;0,0,0;,
  3;3,3,3;,
  4;37,37,38,38;,
  3;0,0,0;,
  3;3,3,3;,
  4;38,38,39,39;,
  3;0,0,0;,
  3;3,3,3;,
  4;39,39,23,23;,
  3;0,0,0;,
  3;3,3,3;,
  4;23,23,40,40;,
  3;0,0,0;,
  3;3,3,3;,
  4;40,40,25,25;,
  3;0,0,0;,
  3;3,3,3;,
  4;25,25,26,26;,
  3;0,0,0;,
  3;3,3,3;,
  4;26,26,41,41;,
  3;0,0,0;,
  3;3,3,3;,
  4;41,41,42,42;,
  3;0,0,0;,
  3;3,3,3;,
  4;42,42,43,43;,
  3;0,0,0;,
  3;3,3,3;,
  4;43,43,30,30;,
  3;0,0,0;,
  3;3,3,3;,
  4;30,30,31,31;,
  3;0,0,0;,
  3;3,3,3;,
  4;31,31,5,5;,
  3;0,0,0;,
  3;3,3,3;,
  4;5,5,44,44;,
  3;0,0,0;,
  3;3,3,3;,
  4;44,44,33,33;,
  3;0,0,0;,
  3;3,3,3;,
  4;33,33,34,34;,
  3;0,0,0;,
  3;3,3,3;,
  4;34,34,35,35;,
  3;0,0,0;,
  3;3,3,3;,
  4;35,35,36,36;,
  3;0,0,0;,
  3;3,3,3;,
  4;36,36,37,37;,
  3;0,0,0;,
  3;3,3,3;,
  4;37,37,38,38;,
  3;0,0,0;,
  3;3,3,3;,
  4;38,38,45,45;,
  3;0,0,0;,
  3;3,3,3;,
  4;45,45,23,23;,
  3;0,0,0;,
  4;3,3,3,3;,
  3;47,47,47;,
  4;49,49,50,50;,
  3;48,48,48;,
  3;47,47,47;,
  4;50,50,51,51;,
  3;48,48,48;,
  3;47,47,47;,
  4;51,51,52,52;,
  3;48,48,48;,
  3;47,47,47;,
  4;52,52,53,53;,
  3;48,48,48;,
  3;47,47,47;,
  4;53,53,54,54;,
  3;48,48,48;,
  3;47,47,47;,
  4;54,54,55,55;,
  3;48,48,48;,
  3;47,47,47;,
  4;55,55,56,56;,
  3;48,48,48;,
  3;47,47,47;,
  4;56,56,57,57;,
  3;48,48,48;,
  3;47,47,47;,
  4;57,57,58,58;,
  3;48,48,48;,
  3;47,47,47;,
  4;58,58,59,59;,
  3;48,48,48;,
  3;47,47,47;,
  4;59,59,60,60;,
  3;48,48,48;,
  3;47,47,47;,
  4;60,60,61,61;,
  3;48,48,48;,
  3;47,47,47;,
  4;61,61,62,62;,
  3;48,48,48;,
  3;47,47,47;,
  4;62,62,63,63;,
  3;48,48,48;,
  3;47,47,47;,
  4;63,63,64,64;,
  3;48,48,48;,
  3;47,47,47;,
  4;64,64,65,65;,
  3;48,48,48;,
  3;47,47,47;,
  4;65,65,66,66;,
  3;48,48,48;,
  3;47,47,47;,
  4;66,66,49,49;,
  3;48,48,48;;
 }
 MeshTextureCoords {
  194;
  0.222434;0.590568;,
  0.222434;0.287791;,
  0.778613;0.287791;,
  0.778613;0.590568;,
  0.575554;0.956870;,
  0.322539;0.956870;,
  0.322539;0.104421;,
  0.575554;0.104421;,
  0.246578;0.294670;,
  0.246578;0.399895;,
  0.752469;0.399895;,
  0.752469;0.294670;,
  0.665257;0.104421;,
  0.575554;0.104421;,
  0.575554;0.956870;,
  0.665257;0.956870;,
  0.638361;0.841795;,
  0.638361;0.228348;,
  0.357211;0.228348;,
  0.357211;0.841795;,
  0.638361;0.228348;,
  0.638361;0.841795;,
  0.357211;0.841795;,
  0.357211;0.228348;,
  0.357211;0.184061;,
  0.638361;0.184061;,
  0.575554;0.042879;,
  0.322539;0.094417;,
  0.322539;0.104421;,
  0.638361;0.221149;,
  0.357211;0.221149;,
  0.575554;0.042879;,
  0.665257;0.042879;,
  0.665257;0.104421;,
  0.778613;0.697913;,
  0.222434;0.697913;,
  0.322539;0.956870;,
  0.246578;0.696694;,
  0.752469;0.696694;,
  0.665257;0.042879;,
  0.322539;0.094417;,
  0.496380;0.512835;,
  0.747603;0.512835;,
  0.732451;0.431471;,
  0.747603;0.512835;,
  0.732451;0.431471;,
  0.496380;0.512835;,
  0.688827;0.359923;,
  0.688827;0.359923;,
  0.621992;0.306817;,
  0.621992;0.306817;,
  0.540004;0.278559;,
  0.540004;0.278559;,
  0.452756;0.278559;,
  0.452756;0.278559;,
  0.370769;0.306817;,
  0.370769;0.306817;,
  0.303933;0.359923;,
  0.303933;0.359923;,
  0.260309;0.431471;,
  0.260309;0.431471;,
  0.245160;0.512835;,
  0.245160;0.512835;,
  0.260309;0.594199;,
  0.260309;0.594199;,
  0.303933;0.665747;,
  0.303933;0.665747;,
  0.370769;0.718853;,
  0.370769;0.718853;,
  0.452756;0.747111;,
  0.452756;0.747111;,
  0.540004;0.747111;,
  0.540004;0.747111;,
  0.621992;0.718853;,
  0.621992;0.718853;,
  0.688827;0.665747;,
  0.688827;0.665747;,
  0.732451;0.594199;,
  0.732451;0.594199;,
  0.494758;0.504521;,
  0.747223;0.504521;,
  0.731999;0.424367;,
  0.747223;0.504521;,
  0.731999;0.424367;,
  0.494758;0.504521;,
  0.688159;0.353882;,
  0.688159;0.353882;,
  0.620989;0.301566;,
  0.620989;0.301566;,
  0.538598;0.273728;,
  0.538598;0.273728;,
  0.450914;0.273728;,
  0.450914;0.273728;,
  0.368524;0.301566;,
  0.368524;0.301566;,
  0.301357;0.353882;,
  0.301357;0.353882;,
  0.257513;0.424367;,
  0.257513;0.424367;,
  0.242289;0.504521;,
  0.242289;0.504521;,
  0.257513;0.584675;,
  0.257513;0.584675;,
  0.301357;0.655159;,
  0.301357;0.655159;,
  0.368524;0.707475;,
  0.368524;0.707475;,
  0.450914;0.735313;,
  0.450914;0.735313;,
  0.538598;0.735313;,
  0.538598;0.735313;,
  0.620989;0.707475;,
  0.620989;0.707475;,
  0.688159;0.655159;,
  0.688159;0.655159;,
  0.731999;0.584675;,
  0.731999;0.584675;,
  0.494758;0.504521;,
  0.747223;0.504521;,
  0.731999;0.424367;,
  0.747223;0.504521;,
  0.731999;0.424367;,
  0.494758;0.504521;,
  0.688159;0.353882;,
  0.688159;0.353882;,
  0.620989;0.301566;,
  0.620989;0.301566;,
  0.538598;0.273728;,
  0.538598;0.273728;,
  0.450914;0.273728;,
  0.450914;0.273728;,
  0.368524;0.301566;,
  0.368524;0.301566;,
  0.301357;0.353882;,
  0.301357;0.353882;,
  0.257513;0.424367;,
  0.257513;0.424367;,
  0.242289;0.504521;,
  0.242289;0.504521;,
  0.257513;0.584675;,
  0.257513;0.584675;,
  0.301357;0.655159;,
  0.301357;0.655159;,
  0.368524;0.707475;,
  0.368524;0.707475;,
  0.450914;0.735313;,
  0.450914;0.735313;,
  0.538598;0.735313;,
  0.538598;0.735313;,
  0.620989;0.707475;,
  0.620989;0.707475;,
  0.688159;0.655159;,
  0.688159;0.655159;,
  0.731999;0.584675;,
  0.731999;0.584675;,
  0.665257;0.956870;,
  0.496380;0.499733;,
  0.747603;0.499733;,
  0.732451;0.418369;,
  0.747603;0.499733;,
  0.732451;0.418369;,
  0.496380;0.499733;,
  0.688827;0.346821;,
  0.688827;0.346821;,
  0.621992;0.293715;,
  0.621992;0.293715;,
  0.540004;0.265457;,
  0.540004;0.265457;,
  0.452756;0.265457;,
  0.452756;0.265457;,
  0.370769;0.293715;,
  0.370769;0.293715;,
  0.303933;0.346821;,
  0.303933;0.346821;,
  0.260309;0.418369;,
  0.260309;0.418369;,
  0.245160;0.499733;,
  0.245160;0.499733;,
  0.260309;0.581097;,
  0.260309;0.581097;,
  0.303933;0.652645;,
  0.303933;0.652645;,
  0.370769;0.705751;,
  0.370769;0.705751;,
  0.452756;0.734009;,
  0.452756;0.734009;,
  0.540004;0.734009;,
  0.540004;0.734009;,
  0.621992;0.705751;,
  0.621992;0.705751;,
  0.688827;0.652645;,
  0.688827;0.652645;,
  0.732451;0.581097;,
  0.732451;0.581097;;
 }
}
