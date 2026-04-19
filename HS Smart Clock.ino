#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <U8g2lib.h>
#include <Wire.h>

// OLED
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE);

// WEB
ESP8266WebServer server(80);

// TIME
int jam = 12, menit = 0;
int hari = 1, bulan = 1, tahun = 2026;

unsigned long lastMillis = 0;
bool blinkState = true;

// INTRO
bool showIntro = true;
unsigned long introStart;

// WIFI
const char* ssid = "HS Smart Clock";
const char* password = "12345678";

// BULAN
const char* namaBulan[] = {
  "Jan","Feb","Mar","Apr","Mei","Jun",
  "Jul","Agu","Sep","Okt","Nov","Des"
};

// ================= WEB =================
String htmlPage(){
return R"====(
<!DOCTYPE html>
<html>
<head>
<meta name="viewport" content="width=device-width, initial-scale=1">
<style>
body{
font-family:sans-serif;
background:linear-gradient(135deg,#0f2027,#2c5364);
color:white;text-align:center;padding-top:40px;
}
input{width:60px;padding:10px;margin:5px;border-radius:10px;border:none;text-align:center;}
button{padding:12px 20px;border:none;border-radius:10px;background:#00c6ff;color:white;}
</style>
</head>
<body>

<h2>HS Smart Clock</h2>

<div>
<input id="h" placeholder="HH">
<input id="m" placeholder="MM">
</div>

<div>
<input id="d" placeholder="DD">
<input id="mo" placeholder="MM">
<input id="y" placeholder="YYYY">
</div>

<br>
<button onclick="setData()">SET</button>

<script>
function setData(){
let h=h.value,m=m.value,d=d.value,mo=mo.value,y=y.value;
fetch(`/set?jam=${h}&menit=${m}&hari=${d}&bulan=${mo}&tahun=${y}`);
}
</script>

</body>
</html>
)====";
}

// ================= HANDLE =================
void handleRoot(){ server.send(200,"text/html",htmlPage()); }

void handleSet(){
  if(server.hasArg("jam")) jam=server.arg("jam").toInt();
  if(server.hasArg("menit")) menit=server.arg("menit").toInt();
  if(server.hasArg("hari")) hari=server.arg("hari").toInt();
  if(server.hasArg("bulan")) bulan=server.arg("bulan").toInt();
  if(server.hasArg("tahun")) tahun=server.arg("tahun").toInt();

  server.send(200,"text/plain","OK");
}

// ================= SETUP =================
void setup(){
  u8g2.begin();
  WiFi.softAP(ssid,password);

  server.on("/",handleRoot);
  server.on("/set",handleSet);
  server.begin();

  introStart=millis();
}

// ================= LOOP =================
void loop(){
  server.handleClient();

  // INTRO SCREEN
  if(showIntro){
    drawIntroAnim();
    if(millis()-introStart>4000) showIntro=false;
    return;
  }

  // UPDATE PER MENIT
  if(millis()-lastMillis>=60000){
    lastMillis=millis();
    menit++; blinkState=!blinkState;

    if(menit>=60){menit=0; jam++;}
    if(jam>=24){jam=0; tambahHari();}
  }

  drawDisplay();
}

// ================= INTRO ANIMASI =================
void drawIntroAnim(){
  u8g2.clearBuffer();

  int t = millis() - introStart;

  // animasi naik dari bawah
  int y = 64 - (t / 20);
  if (y < 38) y = 38;

  // TEKS UTAMA
  u8g2.setFont(u8g2_font_logisoso24_tf);
  int x = (128 - u8g2.getStrWidth("Smart")) / 2;
  u8g2.drawStr(x, y, "Smart");

  // baris kedua
  if (t > 400) {
    int x2 = (128 - u8g2.getStrWidth("Clock")) / 2;
    u8g2.drawStr(x2, y + 20, "Clock");
  }

  u8g2.sendBuffer();
}

// ================= DISPLAY =================
void drawDisplay(){
  u8g2.clearBuffer();

  char waktu[10];
  if(blinkState) sprintf(waktu,"%02d:%02d",jam,menit);
  else sprintf(waktu,"%02d %02d",jam,menit);

  // JAM BESAR
  u8g2.setFont(u8g2_font_logisoso32_tn);
  int x=(128-u8g2.getStrWidth(waktu))/2;
  u8g2.drawStr(x,42,waktu);

  // TANGGAL
  char tanggal[25];
  sprintf(tanggal,"%02d %s %d",hari,namaBulan[bulan-1],tahun);

  u8g2.setFont(u8g2_font_7x13_tf);
  int tx=(128-u8g2.getStrWidth(tanggal))/2;
  u8g2.drawStr(tx,60,tanggal);

  // PROGRESS BAR PER MENIT
  int progress = map(millis()%60000,0,60000,0,128);
  u8g2.drawBox(0,0,progress,3);

  u8g2.sendBuffer();
}

// ================= TANGGAL =================
void tambahHari(){
  int maxHari;

  if(bulan==2){
    if((tahun%4==0 && tahun%100!=0)||(tahun%400==0)) maxHari=29;
    else maxHari=28;
  }
  else if(bulan==4||bulan==6||bulan==9||bulan==11) maxHari=30;
  else maxHari=31;

  hari++;
  if(hari>maxHari){hari=1; bulan++;}
  if(bulan>12){bulan=1; tahun++;}
}