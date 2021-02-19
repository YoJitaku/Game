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
 202;
 -19.07935;3.35395;11.05400;,
 -22.46130;3.35395;11.05400;,
 -22.25735;4.51065;11.05400;,
 -22.46130;3.35395;13.00490;,
 -22.25735;4.51065;13.00490;,
 -19.07935;3.35395;13.00490;,
 -21.67010;5.52780;11.05400;,
 -21.67010;5.52780;13.00490;,
 -20.77035;6.28275;11.05400;,
 -20.77035;6.28275;13.00490;,
 -19.66660;6.68445;11.05400;,
 -19.66660;6.68445;13.00490;,
 -18.49210;6.68445;11.05400;,
 -18.49210;6.68445;13.00490;,
 -17.38840;6.28275;11.05400;,
 -17.38840;6.28275;13.00490;,
 -16.48865;5.52780;11.05400;,
 -16.48865;5.52780;13.00490;,
 -15.90140;4.51065;11.05400;,
 -15.90140;4.51065;13.00490;,
 -15.69745;3.35395;11.05400;,
 -15.69745;3.35395;13.00490;,
 -15.90140;2.19725;11.05400;,
 -15.90140;2.19725;13.00490;,
 -16.48865;1.18010;11.05400;,
 -16.48865;1.18010;13.00490;,
 -17.38840;0.42515;11.05400;,
 -17.38840;0.42515;13.00490;,
 -18.49210;0.02345;11.05400;,
 -18.49210;0.02345;13.00490;,
 -19.66660;0.02345;11.05400;,
 -19.66660;0.02345;13.00490;,
 -20.77035;0.42515;11.05400;,
 -20.77035;0.42515;13.00490;,
 -21.67010;1.18010;11.05400;,
 -21.67010;1.18010;13.00490;,
 -22.25735;2.19725;11.05400;,
 -22.25735;2.19725;13.00490;,
 -19.07935;3.35395;-12.91900;,
 -22.46130;3.35395;-12.91900;,
 -22.25735;4.51065;-12.91900;,
 -22.46130;3.35395;-10.96810;,
 -22.25735;4.51065;-10.96810;,
 -19.07935;3.35395;-10.96810;,
 -21.67010;5.52780;-12.91900;,
 -21.67010;5.52780;-10.96810;,
 -20.77035;6.28275;-12.91900;,
 -20.77035;6.28275;-10.96810;,
 -19.66660;6.68445;-12.91900;,
 -19.66660;6.68445;-10.96810;,
 -18.49210;6.68445;-12.91900;,
 -18.49210;6.68445;-10.96810;,
 -17.38840;6.28275;-12.91900;,
 -17.38840;6.28275;-10.96810;,
 -16.48865;5.52780;-12.91900;,
 -16.48865;5.52780;-10.96810;,
 -15.90140;4.51065;-12.91900;,
 -15.90140;4.51065;-10.96810;,
 -15.69745;3.35395;-12.91900;,
 -15.69745;3.35395;-10.96810;,
 -15.90140;2.19725;-12.91900;,
 -15.90140;2.19725;-10.96810;,
 -16.48865;1.18010;-12.91900;,
 -16.48865;1.18010;-10.96810;,
 -17.38840;0.42515;-12.91900;,
 -17.38840;0.42515;-10.96810;,
 -18.49210;0.02345;-12.91900;,
 -18.49210;0.02345;-10.96810;,
 -19.66660;0.02345;-12.91900;,
 -19.66660;0.02345;-10.96810;,
 -20.77035;0.42515;-12.91900;,
 -20.77035;0.42515;-10.96810;,
 -21.67010;1.18010;-12.91900;,
 -21.67010;1.18010;-10.96810;,
 -22.25735;2.19725;-12.91900;,
 -22.25735;2.19725;-10.96810;,
 17.70135;3.35395;11.05400;,
 14.31945;3.35395;11.05400;,
 14.52340;4.51065;11.05400;,
 14.31945;3.35395;13.00490;,
 14.52340;4.51065;13.00490;,
 17.70135;3.35395;13.00490;,
 15.11065;5.52780;11.05400;,
 15.11065;5.52780;13.00490;,
 16.01045;6.28275;11.05400;,
 16.01045;6.28275;13.00490;,
 17.11410;6.68445;11.05400;,
 17.11410;6.68445;13.00490;,
 18.28860;6.68445;11.05400;,
 18.28860;6.68445;13.00490;,
 19.39230;6.28275;11.05400;,
 19.39230;6.28275;13.00490;,
 20.29205;5.52780;11.05400;,
 20.29205;5.52780;13.00490;,
 20.87930;4.51065;11.05400;,
 20.87930;4.51065;13.00490;,
 21.08325;3.35395;11.05400;,
 21.08325;3.35395;13.00490;,
 20.87930;2.19725;11.05400;,
 20.87930;2.19725;13.00490;,
 20.29205;1.18010;11.05400;,
 20.29205;1.18010;13.00490;,
 19.39230;0.42515;11.05400;,
 19.39230;0.42515;13.00490;,
 18.28860;0.02345;11.05400;,
 18.28860;0.02345;13.00490;,
 17.11410;0.02345;11.05400;,
 17.11410;0.02345;13.00490;,
 16.01045;0.42515;11.05400;,
 16.01045;0.42515;13.00490;,
 15.11065;1.18010;11.05400;,
 15.11065;1.18010;13.00490;,
 14.52340;2.19725;11.05400;,
 14.52340;2.19725;13.00490;,
 17.70135;3.35395;-12.91900;,
 14.31945;3.35395;-12.91900;,
 14.52340;4.51065;-12.91900;,
 14.31945;3.35395;-10.96810;,
 14.52340;4.51065;-10.96810;,
 17.70135;3.35395;-10.96810;,
 15.11065;5.52780;-12.91900;,
 15.11065;5.52780;-10.96810;,
 16.01045;6.28275;-12.91900;,
 16.01045;6.28275;-10.96810;,
 17.11410;6.68445;-12.91900;,
 17.11410;6.68445;-10.96810;,
 18.28860;6.68445;-12.91900;,
 18.28860;6.68445;-10.96810;,
 19.39230;6.28275;-12.91900;,
 19.39230;6.28275;-10.96810;,
 20.29205;5.52780;-12.91900;,
 20.29205;5.52780;-10.96810;,
 20.87930;4.51065;-12.91900;,
 20.87930;4.51065;-10.96810;,
 21.08325;3.35395;-12.91900;,
 21.08325;3.35395;-10.96810;,
 20.87930;2.19725;-12.91900;,
 20.87930;2.19725;-10.96810;,
 20.29205;1.18010;-12.91900;,
 20.29205;1.18010;-10.96810;,
 19.39230;0.42515;-12.91900;,
 19.39230;0.42515;-10.96810;,
 18.28860;0.02345;-12.91900;,
 18.28860;0.02345;-10.96810;,
 17.11410;0.02345;-12.91900;,
 17.11410;0.02345;-10.96810;,
 16.01045;0.42515;-12.91900;,
 16.01045;0.42515;-10.96810;,
 15.11065;1.18010;-12.91900;,
 15.11065;1.18010;-10.96810;,
 14.52340;2.19725;-12.91900;,
 14.52340;2.19725;-10.96810;,
 30.39630;1.99790;-11.88300;,
 30.39630;26.58080;-11.88300;,
 30.39630;26.58080;12.06840;,
 30.39630;1.99790;12.06840;,
 30.39630;1.99790;12.06840;,
 30.39630;26.58080;12.06840;,
 -10.71890;26.58080;12.06840;,
 -10.71890;1.99790;12.06840;,
 -29.96580;1.99790;12.06840;,
 -29.96580;11.18550;12.06840;,
 -29.96580;11.18550;-11.88300;,
 -29.96580;1.99790;-11.88300;,
 -10.71890;26.58080;-11.88300;,
 -10.71890;33.33850;-11.88300;,
 30.39630;33.33850;-11.88300;,
 30.39630;26.58080;-11.88300;,
 30.39630;33.33850;-11.88300;,
 -10.71890;33.33850;-11.88300;,
 -10.71890;33.33850;12.06840;,
 30.39630;33.33850;12.06840;,
 -10.71890;1.99790;-11.88300;,
 30.39630;1.99790;-11.88300;,
 30.39630;1.99790;12.06840;,
 -10.71890;1.99790;12.06840;,
 30.39630;33.33850;-11.88300;,
 30.39630;33.33850;12.06840;,
 30.39630;33.33850;12.06840;,
 -10.71890;33.33850;12.06840;,
 -10.71890;26.58080;12.06840;,
 -10.71890;26.58080;-11.88300;,
 30.39630;1.99790;-11.88300;,
 -10.71890;1.99790;-11.88300;,
 -20.36825;1.99790;12.06840;,
 -20.36825;1.99790;-11.88300;,
 -20.36825;1.99790;-11.88300;,
 -20.36825;26.58080;-11.88300;,
 -20.36825;26.58080;-11.88300;,
 -20.36825;26.58080;12.06840;,
 -20.36825;26.58080;12.06840;,
 -29.96580;11.18550;12.06840;,
 -29.96580;1.99790;12.06840;,
 -20.36825;1.99790;12.06840;,
 -29.96580;1.99790;12.06840;,
 -29.96580;1.99790;-11.88300;,
 -29.96580;1.99790;-11.88300;,
 -29.96580;11.18550;-11.88300;,
 -20.36825;26.58080;12.06840;,
 -10.71890;26.58080;12.06840;,
 -10.71890;26.58080;-11.88300;,
 -20.36825;26.58080;-11.88300;;
 
 234;
 3;0,1,2;,
 4;1,3,4,2;,
 3;3,5,4;,
 3;0,2,6;,
 4;2,4,7,6;,
 3;4,5,7;,
 3;0,6,8;,
 4;6,7,9,8;,
 3;7,5,9;,
 3;0,8,10;,
 4;8,9,11,10;,
 3;9,5,11;,
 3;0,10,12;,
 4;10,11,13,12;,
 3;11,5,13;,
 3;0,12,14;,
 4;12,13,15,14;,
 3;13,5,15;,
 3;0,14,16;,
 4;14,15,17,16;,
 3;15,5,17;,
 3;0,16,18;,
 4;16,17,19,18;,
 3;17,5,19;,
 3;0,18,20;,
 4;18,19,21,20;,
 3;19,5,21;,
 3;0,20,22;,
 4;20,21,23,22;,
 3;21,5,23;,
 3;0,22,24;,
 4;22,23,25,24;,
 3;23,5,25;,
 3;0,24,26;,
 4;24,25,27,26;,
 3;25,5,27;,
 3;0,26,28;,
 4;26,27,29,28;,
 3;27,5,29;,
 3;0,28,30;,
 4;28,29,31,30;,
 3;29,5,31;,
 3;0,30,32;,
 4;30,31,33,32;,
 3;31,5,33;,
 3;0,32,34;,
 4;32,33,35,34;,
 3;33,5,35;,
 3;0,34,36;,
 4;34,35,37,36;,
 3;35,5,37;,
 3;0,36,1;,
 4;36,37,3,1;,
 3;37,5,3;,
 3;38,39,40;,
 4;39,41,42,40;,
 3;41,43,42;,
 3;38,40,44;,
 4;40,42,45,44;,
 3;42,43,45;,
 3;38,44,46;,
 4;44,45,47,46;,
 3;45,43,47;,
 3;38,46,48;,
 4;46,47,49,48;,
 3;47,43,49;,
 3;38,48,50;,
 4;48,49,51,50;,
 3;49,43,51;,
 3;38,50,52;,
 4;50,51,53,52;,
 3;51,43,53;,
 3;38,52,54;,
 4;52,53,55,54;,
 3;53,43,55;,
 3;38,54,56;,
 4;54,55,57,56;,
 3;55,43,57;,
 3;38,56,58;,
 4;56,57,59,58;,
 3;57,43,59;,
 3;38,58,60;,
 4;58,59,61,60;,
 3;59,43,61;,
 3;38,60,62;,
 4;60,61,63,62;,
 3;61,43,63;,
 3;38,62,64;,
 4;62,63,65,64;,
 3;63,43,65;,
 3;38,64,66;,
 4;64,65,67,66;,
 3;65,43,67;,
 3;38,66,68;,
 4;66,67,69,68;,
 3;67,43,69;,
 3;38,68,70;,
 4;68,69,71,70;,
 3;69,43,71;,
 3;38,70,72;,
 4;70,71,73,72;,
 3;71,43,73;,
 3;38,72,74;,
 4;72,73,75,74;,
 3;73,43,75;,
 3;38,74,39;,
 4;74,75,41,39;,
 3;75,43,41;,
 3;76,77,78;,
 4;77,79,80,78;,
 3;79,81,80;,
 3;76,78,82;,
 4;78,80,83,82;,
 3;80,81,83;,
 3;76,82,84;,
 4;82,83,85,84;,
 3;83,81,85;,
 3;76,84,86;,
 4;84,85,87,86;,
 3;85,81,87;,
 3;76,86,88;,
 4;86,87,89,88;,
 3;87,81,89;,
 3;76,88,90;,
 4;88,89,91,90;,
 3;89,81,91;,
 3;76,90,92;,
 4;90,91,93,92;,
 3;91,81,93;,
 3;76,92,94;,
 4;92,93,95,94;,
 3;93,81,95;,
 3;76,94,96;,
 4;94,95,97,96;,
 3;95,81,97;,
 3;76,96,98;,
 4;96,97,99,98;,
 3;97,81,99;,
 3;76,98,100;,
 4;98,99,101,100;,
 3;99,81,101;,
 3;76,100,102;,
 4;100,101,103,102;,
 3;101,81,103;,
 3;76,102,104;,
 4;102,103,105,104;,
 3;103,81,105;,
 3;76,104,106;,
 4;104,105,107,106;,
 3;105,81,107;,
 3;76,106,108;,
 4;106,107,109,108;,
 3;107,81,109;,
 3;76,108,110;,
 4;108,109,111,110;,
 3;109,81,111;,
 3;76,110,112;,
 4;110,111,113,112;,
 3;111,81,113;,
 3;76,112,77;,
 4;112,113,79,77;,
 3;113,81,79;,
 3;114,115,116;,
 4;115,117,118,116;,
 3;117,119,118;,
 3;114,116,120;,
 4;116,118,121,120;,
 3;118,119,121;,
 3;114,120,122;,
 4;120,121,123,122;,
 3;121,119,123;,
 3;114,122,124;,
 4;122,123,125,124;,
 3;123,119,125;,
 3;114,124,126;,
 4;124,125,127,126;,
 3;125,119,127;,
 3;114,126,128;,
 4;126,127,129,128;,
 3;127,119,129;,
 3;114,128,130;,
 4;128,129,131,130;,
 3;129,119,131;,
 3;114,130,132;,
 4;130,131,133,132;,
 3;131,119,133;,
 3;114,132,134;,
 4;132,133,135,134;,
 3;133,119,135;,
 3;114,134,136;,
 4;134,135,137,136;,
 3;135,119,137;,
 3;114,136,138;,
 4;136,137,139,138;,
 3;137,119,139;,
 3;114,138,140;,
 4;138,139,141,140;,
 3;139,119,141;,
 3;114,140,142;,
 4;140,141,143,142;,
 3;141,119,143;,
 3;114,142,144;,
 4;142,143,145,144;,
 3;143,119,145;,
 3;114,144,146;,
 4;144,145,147,146;,
 3;145,119,147;,
 3;114,146,148;,
 4;146,147,149,148;,
 3;147,119,149;,
 3;114,148,150;,
 4;148,149,151,150;,
 3;149,119,151;,
 3;114,150,115;,
 4;150,151,117,115;,
 3;151,119,117;,
 4;152,153,154,155;,
 4;156,157,158,159;,
 4;160,161,162,163;,
 4;164,165,166,167;,
 4;168,169,170,171;,
 4;172,173,174,175;,
 4;153,176,177,154;,
 4;157,178,179,158;,
 4;180,170,169,181;,
 4;167,182,183,164;,
 4;175,184,185,172;,
 4;183,186,187,164;,
 4;188,162,161,189;,
 4;190,191,192,193;,
 4;184,194,195,185;,
 4;186,196,197,187;,
 4;198,199,200,201;,
 4;193,159,158,190;;
 
 MeshMaterialList {
  7;
  234;
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
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
  1,
  4,
  0,
  4,
  2,
  2,
  1,
  4,
  2,
  4,
  2,
  4,
  0,
  4,
  2,
  4,
  6,
  4;;
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\Car\\CarHead2.png";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\Car\\CarAss2.png";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\Car\\CarTop2.png";
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
    "data\\TEXTURE\\Car\\CarWindow2.png";
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
    "data\\TEXTURE\\Car\\CarTop2-2.png";
   }
  }
 }
 MeshNormals {
  38;
  0.000000;0.000000;-1.000000;,
  0.000000;0.000000;1.000000;,
  -1.000000;0.000000;0.000000;,
  -0.939694;0.342017;0.000000;,
  -0.766038;0.642795;0.000000;,
  -0.499981;0.866037;0.000000;,
  -0.173635;0.984810;0.000000;,
  0.173643;0.984809;0.000000;,
  0.499987;0.866033;0.000000;,
  0.766039;0.642794;0.000000;,
  0.939694;0.342016;0.000000;,
  1.000000;0.000000;0.000000;,
  0.939694;-0.342016;-0.000000;,
  0.766039;-0.642794;-0.000000;,
  0.499987;-0.866033;-0.000000;,
  0.173643;-0.984809;-0.000000;,
  -0.173635;-0.984810;0.000000;,
  -0.499980;-0.866037;0.000000;,
  -0.766038;-0.642795;0.000000;,
  -0.939694;-0.342017;0.000000;,
  -0.939694;0.342016;0.000000;,
  -0.766030;0.642805;0.000000;,
  -0.499981;0.866036;0.000000;,
  -0.173650;0.984807;0.000000;,
  0.173643;0.984809;0.000000;,
  0.499987;0.866033;0.000000;,
  0.939694;0.342017;0.000000;,
  0.939694;-0.342017;-0.000000;,
  0.499987;-0.866033;-0.000000;,
  0.173643;-0.984809;-0.000000;,
  -0.173650;-0.984807;0.000000;,
  -0.499981;-0.866036;0.000000;,
  -0.766030;-0.642805;0.000000;,
  -0.939694;-0.342016;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  -0.961407;0.275132;0.000000;,
  -0.485270;0.874365;0.000000;;
  234;
  3;0,0,0;,
  4;2,2,3,3;,
  3;1,1,1;,
  3;0,0,0;,
  4;3,3,4,4;,
  3;1,1,1;,
  3;0,0,0;,
  4;4,4,5,5;,
  3;1,1,1;,
  3;0,0,0;,
  4;5,5,6,6;,
  3;1,1,1;,
  3;0,0,0;,
  4;6,6,7,7;,
  3;1,1,1;,
  3;0,0,0;,
  4;7,7,8,8;,
  3;1,1,1;,
  3;0,0,0;,
  4;8,8,9,9;,
  3;1,1,1;,
  3;0,0,0;,
  4;9,9,10,10;,
  3;1,1,1;,
  3;0,0,0;,
  4;10,10,11,11;,
  3;1,1,1;,
  3;0,0,0;,
  4;11,11,12,12;,
  3;1,1,1;,
  3;0,0,0;,
  4;12,12,13,13;,
  3;1,1,1;,
  3;0,0,0;,
  4;13,13,14,14;,
  3;1,1,1;,
  3;0,0,0;,
  4;14,14,15,15;,
  3;1,1,1;,
  3;0,0,0;,
  4;15,15,16,16;,
  3;1,1,1;,
  3;0,0,0;,
  4;16,16,17,17;,
  3;1,1,1;,
  3;0,0,0;,
  4;17,17,18,18;,
  3;1,1,1;,
  3;0,0,0;,
  4;18,18,19,19;,
  3;1,1,1;,
  3;0,0,0;,
  4;19,19,2,2;,
  3;1,1,1;,
  3;0,0,0;,
  4;2,2,3,3;,
  3;1,1,1;,
  3;0,0,0;,
  4;3,3,4,4;,
  3;1,1,1;,
  3;0,0,0;,
  4;4,4,5,5;,
  3;1,1,1;,
  3;0,0,0;,
  4;5,5,6,6;,
  3;1,1,1;,
  3;0,0,0;,
  4;6,6,7,7;,
  3;1,1,1;,
  3;0,0,0;,
  4;7,7,8,8;,
  3;1,1,1;,
  3;0,0,0;,
  4;8,8,9,9;,
  3;1,1,1;,
  3;0,0,0;,
  4;9,9,10,10;,
  3;1,1,1;,
  3;0,0,0;,
  4;10,10,11,11;,
  3;1,1,1;,
  3;0,0,0;,
  4;11,11,12,12;,
  3;1,1,1;,
  3;0,0,0;,
  4;12,12,13,13;,
  3;1,1,1;,
  3;0,0,0;,
  4;13,13,14,14;,
  3;1,1,1;,
  3;0,0,0;,
  4;14,14,15,15;,
  3;1,1,1;,
  3;0,0,0;,
  4;15,15,16,16;,
  3;1,1,1;,
  3;0,0,0;,
  4;16,16,17,17;,
  3;1,1,1;,
  3;0,0,0;,
  4;17,17,18,18;,
  3;1,1,1;,
  3;0,0,0;,
  4;18,18,19,19;,
  3;1,1,1;,
  3;0,0,0;,
  4;19,19,2,2;,
  3;1,1,1;,
  3;0,0,0;,
  4;2,2,20,20;,
  3;1,1,1;,
  3;0,0,0;,
  4;20,20,21,21;,
  3;1,1,1;,
  3;0,0,0;,
  4;21,21,22,22;,
  3;1,1,1;,
  3;0,0,0;,
  4;22,22,23,23;,
  3;1,1,1;,
  3;0,0,0;,
  4;23,23,24,24;,
  3;1,1,1;,
  3;0,0,0;,
  4;24,24,25,25;,
  3;1,1,1;,
  3;0,0,0;,
  4;25,25,9,9;,
  3;1,1,1;,
  3;0,0,0;,
  4;9,9,26,26;,
  3;1,1,1;,
  3;0,0,0;,
  4;26,26,11,11;,
  3;1,1,1;,
  3;0,0,0;,
  4;11,11,27,27;,
  3;1,1,1;,
  3;0,0,0;,
  4;27,27,13,13;,
  3;1,1,1;,
  3;0,0,0;,
  4;13,13,28,28;,
  3;1,1,1;,
  3;0,0,0;,
  4;28,28,29,29;,
  3;1,1,1;,
  3;0,0,0;,
  4;29,29,30,30;,
  3;1,1,1;,
  3;0,0,0;,
  4;30,30,31,31;,
  3;1,1,1;,
  3;0,0,0;,
  4;31,31,32,32;,
  3;1,1,1;,
  3;0,0,0;,
  4;32,32,33,33;,
  3;1,1,1;,
  3;0,0,0;,
  4;33,33,2,2;,
  3;1,1,1;,
  3;0,0,0;,
  4;2,2,20,20;,
  3;1,1,1;,
  3;0,0,0;,
  4;20,20,21,21;,
  3;1,1,1;,
  3;0,0,0;,
  4;21,21,22,22;,
  3;1,1,1;,
  3;0,0,0;,
  4;22,22,23,23;,
  3;1,1,1;,
  3;0,0,0;,
  4;23,23,24,24;,
  3;1,1,1;,
  3;0,0,0;,
  4;24,24,25,25;,
  3;1,1,1;,
  3;0,0,0;,
  4;25,25,9,9;,
  3;1,1,1;,
  3;0,0,0;,
  4;9,9,26,26;,
  3;1,1,1;,
  3;0,0,0;,
  4;26,26,11,11;,
  3;1,1,1;,
  3;0,0,0;,
  4;11,11,27,27;,
  3;1,1,1;,
  3;0,0,0;,
  4;27,27,13,13;,
  3;1,1,1;,
  3;0,0,0;,
  4;13,13,28,28;,
  3;1,1,1;,
  3;0,0,0;,
  4;28,28,29,29;,
  3;1,1,1;,
  3;0,0,0;,
  4;29,29,30,30;,
  3;1,1,1;,
  3;0,0,0;,
  4;30,30,31,31;,
  3;1,1,1;,
  3;0,0,0;,
  4;31,31,32,32;,
  3;1,1,1;,
  3;0,0,0;,
  4;32,32,33,33;,
  3;1,1,1;,
  3;0,0,0;,
  4;33,33,2,2;,
  3;1,1,1;,
  4;11,11,11,11;,
  4;1,1,1,1;,
  4;2,36,36,2;,
  4;0,0,0,0;,
  4;34,34,34,34;,
  4;35,35,35,35;,
  4;11,11,11,11;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;0,0,0,0;,
  4;35,35,35,35;,
  4;0,0,0,0;,
  4;37,36,36,37;,
  4;1,1,1,1;,
  4;35,35,35,35;,
  4;0,0,0,0;,
  4;37,34,34,37;,
  4;1,1,1,1;;
 }
 MeshTextureCoords {
  202;
  0.496342;0.498845;,
  0.240058;0.498845;,
  0.255514;0.417479;,
  0.240058;0.498845;,
  0.255514;0.417479;,
  0.496342;0.498845;,
  0.300016;0.345930;,
  0.300016;0.345930;,
  0.368198;0.292825;,
  0.368198;0.292825;,
  0.451840;0.264568;,
  0.451840;0.264568;,
  0.540844;0.264568;,
  0.540844;0.264568;,
  0.624482;0.292825;,
  0.624482;0.292825;,
  0.692665;0.345930;,
  0.692665;0.345930;,
  0.737167;0.417479;,
  0.737167;0.417479;,
  0.752622;0.498845;,
  0.752622;0.498845;,
  0.737167;0.580210;,
  0.737167;0.580210;,
  0.692665;0.651759;,
  0.692665;0.651759;,
  0.624482;0.704864;,
  0.624482;0.704864;,
  0.540844;0.733121;,
  0.540844;0.733121;,
  0.451840;0.733121;,
  0.451840;0.733121;,
  0.368198;0.704864;,
  0.368198;0.704864;,
  0.300016;0.651759;,
  0.300016;0.651759;,
  0.255514;0.580210;,
  0.255514;0.580210;,
  0.496342;0.498845;,
  0.240058;0.498845;,
  0.255514;0.417479;,
  0.240058;0.498845;,
  0.255514;0.417479;,
  0.496342;0.498845;,
  0.300016;0.345930;,
  0.300016;0.345930;,
  0.368198;0.292825;,
  0.368198;0.292825;,
  0.451840;0.264568;,
  0.451840;0.264568;,
  0.540844;0.264568;,
  0.540844;0.264568;,
  0.624482;0.292825;,
  0.624482;0.292825;,
  0.692665;0.345930;,
  0.692665;0.345930;,
  0.737167;0.417479;,
  0.737167;0.417479;,
  0.752622;0.498845;,
  0.752622;0.498845;,
  0.737167;0.580210;,
  0.737167;0.580210;,
  0.692665;0.651759;,
  0.692665;0.651759;,
  0.624482;0.704864;,
  0.624482;0.704864;,
  0.540844;0.733121;,
  0.540844;0.733121;,
  0.451840;0.733121;,
  0.451840;0.733121;,
  0.368198;0.704864;,
  0.368198;0.704864;,
  0.300016;0.651759;,
  0.300016;0.651759;,
  0.255514;0.580210;,
  0.255514;0.580210;,
  0.500000;0.495732;,
  0.256187;0.495732;,
  0.270890;0.415174;,
  0.256187;0.495732;,
  0.270890;0.415174;,
  0.500000;0.495732;,
  0.313227;0.344335;,
  0.313227;0.344335;,
  0.378097;0.291757;,
  0.378097;0.291757;,
  0.457663;0.263780;,
  0.457663;0.263780;,
  0.542337;0.263780;,
  0.542337;0.263780;,
  0.621906;0.291757;,
  0.621906;0.291757;,
  0.686773;0.344335;,
  0.686773;0.344335;,
  0.729109;0.415174;,
  0.729109;0.415174;,
  0.743813;0.495732;,
  0.743813;0.495732;,
  0.729109;0.576289;,
  0.729109;0.576289;,
  0.686773;0.647128;,
  0.686773;0.647128;,
  0.621906;0.699706;,
  0.621906;0.699706;,
  0.542337;0.727683;,
  0.542337;0.727683;,
  0.457663;0.727683;,
  0.457663;0.727683;,
  0.378097;0.699706;,
  0.378097;0.699706;,
  0.313227;0.647128;,
  0.313227;0.647128;,
  0.270890;0.576289;,
  0.270890;0.576289;,
  0.500000;0.495732;,
  0.256187;0.495732;,
  0.270890;0.415174;,
  0.256187;0.495732;,
  0.270890;0.415174;,
  0.500000;0.495732;,
  0.313227;0.344335;,
  0.313227;0.344335;,
  0.378097;0.291757;,
  0.378097;0.291757;,
  0.457663;0.263780;,
  0.457663;0.263780;,
  0.542337;0.263780;,
  0.542337;0.263780;,
  0.621906;0.291757;,
  0.621906;0.291757;,
  0.686773;0.344335;,
  0.686773;0.344335;,
  0.729109;0.415174;,
  0.729109;0.415174;,
  0.743813;0.495732;,
  0.743813;0.495732;,
  0.729109;0.576289;,
  0.729109;0.576289;,
  0.686773;0.647128;,
  0.686773;0.647128;,
  0.621906;0.699706;,
  0.621906;0.699706;,
  0.542337;0.727683;,
  0.542337;0.727683;,
  0.457663;0.727683;,
  0.457663;0.727683;,
  0.378097;0.699706;,
  0.378097;0.699706;,
  0.313227;0.647128;,
  0.313227;0.647128;,
  0.270890;0.576289;,
  0.270890;0.576289;,
  0.262192;0.770995;,
  0.262192;0.331188;,
  0.737808;0.331188;,
  0.737808;0.770995;,
  0.712195;0.919725;,
  0.367745;0.919725;,
  0.367745;0.344825;,
  0.712195;0.344825;,
  0.734572;0.286846;,
  0.734572;0.450855;,
  0.269294;0.450855;,
  0.269294;0.286846;,
  0.367745;0.344825;,
  0.273058;0.344825;,
  0.273058;0.919725;,
  0.367745;0.919725;,
  0.700506;0.074362;,
  0.370223;0.074362;,
  0.370223;0.925119;,
  0.700506;0.925119;,
  0.370223;0.074362;,
  0.700506;0.074362;,
  0.700506;0.925119;,
  0.370223;0.925119;,
  0.262192;0.210287;,
  0.737808;0.210287;,
  0.273058;0.919725;,
  0.273058;0.344825;,
  0.370223;0.925119;,
  0.370223;0.074362;,
  0.712195;0.919725;,
  0.712195;0.344825;,
  0.292709;0.925119;,
  0.292709;0.074362;,
  0.712195;0.209901;,
  0.367745;0.209901;,
  0.269294;0.725678;,
  0.734572;0.725678;,
  0.367745;0.209901;,
  0.583460;0.075702;,
  0.712195;0.075702;,
  0.712195;0.209901;,
  0.215611;0.925119;,
  0.215611;0.074362;,
  0.712195;0.075702;,
  0.583460;0.075702;,
  0.727370;0.499395;,
  0.727370;0.499395;,
  0.272630;0.499395;,
  0.272630;0.499395;;
 }
}
