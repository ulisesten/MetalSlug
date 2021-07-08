/* Ulises Mtz El
 * jueves 13 de jul de 2017
 * Valores coordenada altura
 */

#include "util.h"

void setRects( Rects* rects ){
    int startPosition = 50;

    rects->fullScreenHightCompensation = 38;

    rects->floorRect.x = 0;
	rects->floorRect.y = 0;
	rects->floorRect.w = 502;
	rects->floorRect.h = 248;

    rects->traceRect.x = 0;
    rects->traceRect.y = 287;
    rects->traceRect.w = 502;
    rects->traceRect.h = 72;

    rects->horizonRect.x = 10;
    rects->horizonRect.y = 560;
    rects->horizonRect.w = 502;
    rects->horizonRect.h = 248;

    rects->skyRect.x = 10;
    rects->skyRect.y = 408;
    rects->skyRect.w = 502;
    rects->skyRect.h = 248;

    rects->playerSpriteFrame.x = 10 + startPosition;
	rects->playerSpriteFrame.y = 5;
	rects->playerSpriteFrame.w = 35;
	rects->playerSpriteFrame.h = 35;

    rects->playerUpperBodyPosition.x = -28 + startPosition;
    rects->playerUpperBodyPosition.y = 0; //old 50
    rects->playerUpperBodyPosition.w = 35;
    rects->playerUpperBodyPosition.h = 35;

    rects->playerLowerBodyPosition.x = -30 + startPosition;
    rects->playerLowerBodyPosition.y = 21; //old 71
    rects->playerLowerBodyPosition.w = 35;
    rects->playerLowerBodyPosition.h = 35;

    rects->playerLowerBodyPositionBackward.x = -26 + startPosition;
    rects->playerLowerBodyPositionBackward.y = 21; //old 71
    rects->playerLowerBodyPositionBackward.w = 35;
    rects->playerLowerBodyPositionBackward.h = 35;
}

void settingFloorHight(int floor[]){
    FILE *fptr;
    int index = 0;

    fptr = fopen("../assets/measurements/floor.txt", "r");
    if(!fptr)
        printf("Error opening file\n");

    while ( index < 534 ) {
         fscanf(fptr, "%d", &floor[index]);
         index++;
    }

    fclose(fptr);

}

void readMeasurements(int array[], const char* file_name, int length){
    FILE *fptr = NULL;
    int index = 0;


    fptr = fopen(file_name, "r");
    if(!fptr)
        printf("Error opening file\n");

    while ( index < length ) {
         fscanf(fptr, "%d", &array[index]);
         index++;
    }

    fclose(fptr);

}

void setConfiguration(struct SdlConfig* config){
    Rects rects;
    Indices i = {0,0,0,0};;

    setRects(&rects);
    clarkStandSetRect(          rects.upperBodyRect       ,    rects.lowerBodyRect);
    clarkLowerBodyRunSetRect(   rects.lowerBodyRunRect    );
    clarkUpperBodyShootSetRect( rects.upperBodyShootRect  );

    config->rects = rects;
    config->i     = i;
}

void clarkStandSetRect(SDL_Rect torzo[4],SDL_Rect pierna[1]){
    torzo[0].x=10; torzo[0].y=5;//Parado--------------------------
    torzo[0].w=35; torzo[0].h=35;

    torzo[1].x=43; torzo[1].y=5;
    torzo[1].w=35; torzo[1].h=35;

    torzo[2].x=76; torzo[2].y=5;
    torzo[2].w=35; torzo[2].h=35;

    torzo[3].x=109; torzo[3].y=5;
    torzo[3].w=35; torzo[3].h=35;

    pierna[0].x=145; pierna[0].y=20;
    pierna[0].w=35; pierna[0].h=34;//-----------------------------
}

void clarkLowerBodyRunSetRect(SDL_Rect lowerBody[6]){
    lowerBody[0].x=13;  lowerBody[0].y=434;
    lowerBody[0].w=34;  lowerBody[0].h=34;
    lowerBody[1].x=57;  lowerBody[1].y=434;
    lowerBody[1].w=34;  lowerBody[1].h=34;         
    lowerBody[2].x=101; lowerBody[2].y=434;
    lowerBody[2].w=34;  lowerBody[2].h=34;
    lowerBody[3].x=133; lowerBody[3].y=434;
    lowerBody[3].w=34;  lowerBody[3].h=34;
    lowerBody[4].x=167; lowerBody[4].y=434;
    lowerBody[4].w=34;  lowerBody[4].h=34;
    lowerBody[5].x=201; lowerBody[5].y=434;
    lowerBody[5].w=34;  lowerBody[5].h=34;//----------------------------
}

void clarkUpperBodyShootSetRect(SDL_Rect upperBody[9]){
    upperBody[0].x=19;   upperBody[0].y=50;//Disparando adelante------------
    upperBody[0].w=35;   upperBody[0].h=35;

    upperBody[1].x=85;   upperBody[1].y=50;
    upperBody[1].w=35;   upperBody[1].h=35;

    upperBody[2].x=153;  upperBody[2].y=50;
    upperBody[2].w=35;   upperBody[2].h=35;

    upperBody[3].x=206;  upperBody[3].y=50;
    upperBody[3].w=35;   upperBody[3].h=35;

    upperBody[4].x=206;  upperBody[4].y=50;
    upperBody[4].w=35;   upperBody[4].h=35;

    upperBody[5].x=303;  upperBody[5].y=50;
    upperBody[5].w=35;   upperBody[5].h=35;

    upperBody[6].x=352;  upperBody[6].y=50;
    upperBody[6].w=35;   upperBody[6].h=35;

    upperBody[7].x=401;  upperBody[7].y=48;
    upperBody[7].w=35;   upperBody[7].h=35;

    upperBody[8].x=449;  upperBody[8].y=49;
    upperBody[8].w=35;   upperBody[8].h=35;

    upperBody[9].x=498;  upperBody[9].y=50;
    upperBody[9].w=35;   upperBody[9].h=35;//------
}

/*void setFloor(int piso[]){
    piso[  0]=128;
    piso[  1]=128;
    piso[  2]=128;
    piso[  3]=128;
    piso[  4]=128;
    piso[  5]=128;
    piso[  6]=128;
    piso[  7]=128;
    piso[  8]=128;
    piso[  9]=128;
    piso[ 10]=128;
    piso[ 11]=127;
    piso[ 12]=127;
    piso[ 13]=127;
    piso[ 14]=127;
    piso[ 15]=127;
    piso[ 16]=126;
    piso[ 17]=126;
    piso[ 18]=126;
    piso[ 19]=126;
    piso[ 20]=126;
    piso[ 21]=125;
    piso[ 22]=125;
    piso[ 23]=125;
    piso[ 24]=125;
    piso[ 25]=125;
    piso[ 26]=124;
    piso[ 27]=124;
    piso[ 28]=124;
    piso[ 29]=124;
    piso[ 30]=124;
    piso[ 31]=123;
    piso[ 32]=123;
    piso[ 33]=123;
    piso[ 34]=123;
    piso[ 35]=123;
    piso[ 36]=122;
    piso[ 37]=122;
    piso[ 38]=122;
    piso[ 39]=122;
    piso[ 40]=122;
    piso[ 41]=121;
    piso[ 42]=121;
    piso[ 43]=121;
    piso[ 44]=121;
    piso[ 45]=121;
    piso[ 46]=120;
    piso[ 47]=120;
    piso[ 48]=120;
    piso[ 49]=120;
    piso[ 50]=120;
    piso[ 51]=119;
    piso[ 52]=119;
    piso[ 53]=119;
    piso[ 54]=119;
    piso[ 55]=119;
    piso[ 56]=118;
    piso[ 57]=118;
    piso[ 58]=118;
    piso[ 59]=118;
    piso[ 60]=118;
    piso[ 61]=117;
    piso[ 62]=117;
    piso[ 63]=117;
    piso[ 64]=117;
    piso[ 65]=117;
    piso[ 66]=116;
    piso[ 67]=116;
    piso[ 68]=116;
    piso[ 69]=116;
    piso[ 70]=116;
    piso[ 71]=115;
    piso[ 72]=115;
    piso[ 73]=115;
    piso[ 74]=115;
    piso[ 75]=115;
    piso[ 76]=114;
    piso[ 77]=114;
    piso[ 78]=114;
    piso[ 79]=114;
    piso[ 80]=114;
    piso[ 81]=113;
    piso[ 82]=113;
    piso[ 83]=113;
    piso[ 84]=113;
    piso[ 85]=113;
    piso[ 86]=112;
    piso[ 87]=112;
    piso[ 88]=112;
    piso[ 89]=112;
    piso[ 90]=112;
    piso[ 91]=111;
    piso[ 92]=111;
    piso[ 93]=111;
    piso[ 94]=111;
    piso[ 95]=111;
    piso[ 96]=110;
    piso[ 97]=110;
    piso[ 98]=110;
    piso[ 99]=110;
    piso[100]=110;
    piso[101]=109;
    piso[102]=109;
    piso[103]=109;
    piso[104]=109;
    piso[105]=109;
    piso[106]=108;
    piso[107]=108;
    piso[108]=108;
    piso[109]=108;
    piso[110]=108;
    piso[111]=107;
    piso[112]=107;
    piso[113]=107;
    piso[114]=107;
    piso[115]=106;
    piso[116]=106;
    piso[117]=106;
    piso[118]=106;
    piso[119]=106;
    piso[120]=105;
    piso[121]=105;
    piso[122]=105;
    piso[123]=105;
    piso[124]=105;
    piso[125]=105;
    piso[126]=104;
    piso[127]=104;
    piso[128]=104;
    piso[129]=104;
    piso[130]=104;
    piso[131]=104;
    piso[132]=103;
    piso[133]=103;
    piso[134]=103;
    piso[135]=103;
    piso[136]=103;
    piso[137]=103;
    piso[138]=102;
    piso[139]=102;
    piso[140]=102;
    piso[141]=102;
    piso[142]=102;
    piso[143]=102;
    piso[144]=101;
    piso[145]=101;
    piso[146]=101;
    piso[147]=101;
    piso[148]=101;
    piso[149]=101;
    piso[150]=102;
    piso[151]=102;
    piso[152]=104;
    piso[153]=104;
    piso[154]=104;
    piso[155]=104;
    piso[156]=105;
    piso[157]=105;
    piso[158]=105;
    piso[159]=105;
    piso[160]=105;
    piso[161]=105;
    piso[162]=106;
    piso[163]=106;
    piso[164]=106;
    piso[165]=106;
    piso[166]=107;
    piso[167]=107;
    piso[168]=107;
    piso[169]=107;
    piso[170]=107;
    piso[171]=107;
    piso[172]=108;
    piso[173]=108;
    piso[174]=108;
    piso[175]=108;
    piso[176]=108;
    piso[177]=108;
    piso[178]=109;
    piso[179]=109;
    piso[180]=109;
    piso[181]=109;
    piso[182]=109;
    piso[183]=109;
    piso[184]=110;
    piso[185]=110;
    piso[186]=110;
    piso[187]=110;
    piso[188]=110;
    piso[189]=110;
    piso[190]=111;
    piso[191]=111;
    piso[192]=111;
    piso[193]=111;
    piso[194]=111;
    piso[195]=111;
    piso[196]=112;
    piso[197]=112;
    piso[198]=112;
    piso[199]=112;
    piso[200]=112;
    piso[201]=112;
    piso[202]=113;
    piso[203]=113;
    piso[204]=113;
    piso[205]=113;
    piso[206]=114;
    piso[207]=114;
    piso[208]=114;
    piso[209]=114;
    piso[210]=115;
    piso[211]=115;
    piso[212]=115;
    piso[213]=115;
    piso[214]=116;
    piso[215]=116;
    piso[216]=116;
    piso[217]=116;
    piso[218]=117;
    piso[219]=117;
    piso[220]=117;
    piso[221]=117;
    piso[222]=118;
    piso[223]=118;
    piso[224]=118;
    piso[225]=118;
    piso[226]=119;
    piso[227]=119;
    piso[228]=119;
    piso[229]=119;
    piso[230]=120;
    piso[231]=120;
    piso[232]=120;
    piso[233]=120;
    piso[234]=120;
    piso[235]=120;
    piso[236]=121;
    piso[237]=121;
    piso[238]=121;
    piso[239]=121;
    piso[240]=121;
    piso[241]=121;
    piso[242]=122;
    piso[243]=122;
    piso[244]=122;
    piso[245]=122;
    piso[246]=123;
    piso[247]=123;
    piso[248]=123;
    piso[249]=123;
    piso[250]=124;
    piso[251]=124;
    piso[252]=124;
    piso[253]=124;
    piso[254]=125;
    piso[255]=125;
    piso[256]=125;
    piso[257]=125;
    piso[258]=125;
    piso[259]=125;
    piso[260]=126;
    piso[261]=126;
    piso[262]=126;
    piso[263]=126;
    piso[264]=126;
    piso[265]=126;
    piso[266]=127;
    piso[267]=127;
    piso[268]=127;
    piso[269]=127;
    piso[270]=127;
    piso[271]=127;
    piso[272]=128;
    piso[273]=128;
    piso[274]=128;
    piso[275]=128;
    piso[276]=128;
    piso[277]=128;
    piso[278]=129;
    piso[279]=129;
    piso[280]=129;
    piso[281]=129;
    piso[282]=129;
    piso[283]=129;
    piso[284]=130;
    piso[285]=130;
    piso[286]=130;
    piso[287]=130;
    piso[288]=130;
    piso[289]=130;
    piso[290]=131;
    piso[291]=131;
    piso[292]=131;
    piso[293]=131;
    piso[294]=131;
    piso[295]=131;
    piso[296]=132;
    piso[297]=132;
    piso[298]=132;
    piso[299]=132;
    piso[300]=132;
    piso[301]=132;
    piso[302]=132;
    piso[303]=132;
    piso[304]=132;
    piso[305]=132;
    piso[306]=132;
    piso[307]=132;
    piso[308]=132;
    piso[309]=132;
    piso[310]=132;
    piso[311]=132;
    piso[312]=132;
    piso[313]=132;
    piso[314]=132;
    piso[315]=132;
    piso[316]=132;
    piso[317]=132;
    piso[318]=132;
    piso[319]=132;
    piso[320]=132;
    piso[321]=132;
    piso[322]=132;
    piso[323]=132;
    piso[324]=132;
    piso[325]=132;
    piso[326]=132;
    piso[327]=131;
    piso[328]=131;
    piso[329]=131;
    piso[330]=131;
    piso[331]=131;
    piso[332]=131;
    piso[333]=131;
    piso[334]=131;
    piso[335]=130;
    piso[336]=130;
    piso[337]=130;
    piso[338]=130;
    piso[339]=130;
    piso[340]=130;
    piso[341]=130;
    piso[342]=130;
    piso[343]=129;
    piso[344]=129;
    piso[345]=129;
    piso[346]=129;
    piso[347]=129;
    piso[348]=129;
    piso[349]=128;
    piso[350]=128;
    piso[351]=128;
    piso[352]=128;
    piso[353]=128;
    piso[354]=128;
    piso[355]=127;
    piso[356]=127;
    piso[357]=127;
    piso[358]=127;
    piso[359]=127;
    piso[360]=127;
    piso[361]=126;
    piso[362]=126;
    piso[363]=126;
    piso[364]=126;
    piso[365]=126;
    piso[366]=126;
    piso[367]=125;
    piso[368]=125;
    piso[369]=125;
    piso[370]=125;
    piso[371]=125;
    piso[372]=125;
    piso[373]=124;
    piso[374]=124;
    piso[375]=124;
    piso[376]=124;
    piso[377]=124;
    piso[378]=124;
    piso[379]=123;
    piso[380]=123;
    piso[381]=123;
    piso[382]=123;
    piso[383]=123;
    piso[384]=123;
    piso[385]=122;
    piso[386]=122;
    piso[387]=122;
    piso[388]=122;
    piso[389]=122;
    piso[390]=122;
    piso[391]=121;
    piso[392]=121;
    piso[393]=121;
    piso[394]=121;
    piso[395]=121;
    piso[396]=121;
    piso[397]=120;
    piso[398]=120;
    piso[399]=120;
    piso[400]=120;
    piso[401]=120;
    piso[402]=120;
    piso[403]=119;
    piso[404]=119;
    piso[405]=119;
    piso[406]=119;
    piso[407]=119;
    piso[408]=119;
    piso[409]=118;
    piso[410]=118;
    piso[411]=118;
    piso[412]=118;
    piso[413]=118;
    piso[414]=118;
    piso[415]=117;
    piso[416]=117;
    piso[417]=117;
    piso[418]=117;
    piso[419]=118;/////////
    piso[420]=118;
    piso[421]=118;
    piso[422]=118;
    piso[423]=119;
    piso[424]=119;
    piso[425]=119;
    piso[426]=119;
    piso[427]=119;
    piso[428]=120;
    piso[429]=120;////////
    piso[430]=121;
    piso[431]=121;
    piso[432]=122;
    piso[433]=122;
    piso[434]=123;
    piso[435]=123;
    piso[436]=124;
    piso[437]=124;
    piso[438]=125;
    piso[439]=125;////////
    piso[440]=126;
    piso[441]=126;
    piso[442]=126;
    piso[443]=126;
    piso[444]=127;
    piso[445]=127;
    piso[446]=127;
    piso[447]=127;
    piso[448]=128;
    piso[449]=128;////////
    piso[450]=128;
    piso[451]=128;
    piso[452]=129;
    piso[453]=129;
    piso[454]=129;
    piso[455]=129;
    piso[456]=130;
    piso[457]=130;
    piso[458]=130;
    piso[459]=130;////////
    piso[460]=131;
    piso[461]=131;
    piso[462]=131;
    piso[463]=131;
    piso[464]=132;
    piso[465]=132;
    piso[466]=132;
    piso[467]=132;
    piso[468]=132;
    piso[469]=133;////////
    piso[470]=133;
    piso[471]=133;
    piso[472]=133;
    piso[473]=133;
    piso[474]=134;
    piso[475]=134;
    piso[476]=134;
    piso[477]=134;
    piso[478]=134;
    piso[479]=136;///////
    piso[480]=136;
    piso[481]=136;
    piso[482]=136;
    piso[483]=136;
    piso[484]=137;
    piso[485]=137;
    piso[486]=137;
    piso[487]=137;
    piso[488]=137;
    piso[489]=138;//////
    piso[490]=138;
    piso[491]=138;
    piso[492]=138;
    piso[493]=138;
    piso[494]=139;
    piso[495]=139;
    piso[496]=139;
    piso[497]=139;
    piso[498]=139;
    piso[499]=140;///////
    piso[500]=140;
    piso[501]=140;
    piso[502]=140;//Resolución
    piso[503]=140;
    piso[504]=141;
    piso[505]=141;
    piso[506]=141;
    piso[507]=141;
    piso[508]=141;
    piso[509]=142;///////

    piso[510]=142;
    piso[511]=142;
    piso[512]=142;
    piso[513]=142;
    piso[514]=142;
    piso[515]=143;
    piso[516]=143;
    piso[517]=143;
    piso[518]=143;
    piso[519]=143;
}*/