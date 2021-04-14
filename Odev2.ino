int segment[]={0,1,2,3,4,5,6};    // ortak katotlu 7 li göstergeye gidecek çıkışlarımı tanımladım
int displaySec[]={7,8};         //birler ya da onlar basamağını gösteren 7 li göstergeyi transistör yardımıyla seçmek için iki çıkış tanımladım.
int ileri=9, geri=10, durdur=11;  //sayıcımı ileri, geri saymasını kontrol edecek inputlarımı isimlendirdim
bool ileriset=false, geriset=false;    //butonlara basıldığında bu basılma olayını set etmek için boolean değişkenler tanımladım
int pot = 0;                    //analog pinimin numarasını değişkene atadım

byte gosterge[10][7] =        //sırasıyla ekrana yazdırılacak sayıları sıfırdan dokuza 7 li göstergedeki a ucundan başlamak üzere hangi ledler yanacaksa bu ledler için haritalama yapıp dizi oluşturdum 
{{ 1,1,1,1,1,1,0 }, // = 7 li göstergede 0 değeri görülür
 { 0,1,1,0,0,0,0 }, // = 7 li göstergede 1 değeri görülür
 { 1,1,0,1,1,0,1 }, // = 7 li göstergede 2 değeri görülür
 { 1,1,1,1,0,0,1 }, // = 7 li göstergede 3 değeri görülür
 { 0,1,1,0,0,1,1 }, // = 7 li göstergede 4 değeri görülür
 { 1,0,1,1,0,1,1 }, // = 7 li göstergede 5 değeri görülür
 { 1,0,1,1,1,1,1 }, // = 7 li göstergede 6 değeri görülür
 { 1,1,1,0,0,0,0 }, // = 7 li göstergede 7 değeri görülür
 { 1,1,1,1,1,1,1 }, // = 7 li göstergede 8 değeri görülür
 { 1,1,1,1,0,1,1 } //  = 7 li göstergede 9 değeri görülür
 };

void setup() {
  for(int i=0; i<=8; i++){        //çıkışlarımı for döngüsü yardımıyla tanımladım
    pinMode(i,OUTPUT);
  }
  pinMode(9,INPUT);           //butonlarımı yani girişlerimi tanımladım
  pinMode(10,INPUT);
  pinMode(11,INPUT);
}

void loop() {
  static int birler;        //sayaç değişkenimin birler basamağını tutacağım değişkeni tanımladım
  static int onlar;         //sayaç değişkenimin onlar basamağını tutacağım değişkeni tanımladım
  static int sayac=0;       // yukarı yada aşağı sayacağım sayıyı atacağım değişkeni tanımladım
  static int bekleme;       // analog girişle aldığım süreyi atayacağım değişkeni tanımladım
  bekleme= analogRead(pot); //analog girişten bekleme süresi olarak kullanacağım 0-1024 arasında sayıyı aldım
  if (digitalRead(ileri)){    // ileri butonu basıldığında bunu kalıcı hale getirip sürekli sayıcımı artırmak için set ettim
    geriset=false;
    ileriset=true;
  }
  if (digitalRead(geri)){     // geri butonu basıldığında bunu kalıcı hale getirip sürekli sayıcımı azaltmak için set ettim
    ileriset=false;
    geriset=true;
  }
  if (digitalRead(durdur)){  //sayacı durdurmak için ileri ve geri setlerimi false yaptım
    ileriset=false;
    geriset=false;
  }
  if(sayac<99&&(ileriset)){  //sayaç 99 a kadar sayacağından bu sayıdan küçük olduğunda ve ileri butonuna basıldıysa ileri sayacak
    sayac++;
    delay(bekleme);       // potansiyometreden okuduğum analog değer kadar beklettim
  }
  if(sayac>0 && (geriset)){ //sayaç 0 a kadar azalarak sayacağından bu sayıdan büyük olduğunda ve geri butonuna basılmışsa geri sayacak
    sayac--; 
    delay(bekleme);     
  }
  birler=sayac%10;        //sayıcıya aktarılacak sayının birler basamağını aldım
  onlar=sayac/10;         //sayıcıya aktarılacak sayının onlar basamağını aldım
  updateDisplay(birler, onlar); //birler ve onlar basamağındaki sayıları göstergelerde göstermek üzere yeni bir metota gönderdim
  }
  void updateDisplay(int birler, int onlar){
    digitalWrite(displaySec[0], HIGH);          //birler basamağındaki ortak katotlu 7 li göstergemin transistörünü tetikledim
    digitalWrite(displaySec[1], LOW);
    setSegments(birler);                        //birler basamağındaki sayıyı iki boyutlu gosterge dizimin birinci boyutuna gönderdim böylelikle sayım kaçsa ona göre çıkış verecek
    delay(5);                                   //bekleme süresi kadar bekleyip aynı işlemleri onlar basamağı için yaptım
    digitalWrite(displaySec[0], LOW);         
    digitalWrite(displaySec[1], HIGH);        //onlar basamağındaki ortak katotlu 7 li göstergemin transistörünü tetikledim
    setSegments(onlar);
    delay(5);
    }
    void setSegments(int n)
    {
    for (int i=0; i < 8; i++)                 //birler yada onlar basamağındaki değişkeni göstermek için sayımı iki boyutlu gosterge dizimin birinci boyutuna gönderdim ve 0 dan 7 ye kadar sayı göstergede gözükecek şekilde çıkış verdim
    {
    digitalWrite(segment[i], gosterge[n][i]);
    }
}
