#include<iostream>
#include<fstream>
#include<string>
#include<locale>
#include<cmath>
//Ahmet Metehan ***** --- M�hendislik Projesi --- 2016123*** --- Normal ��retim
#define hashBoyut 72
#define boyut 72

using namespace std;

int bulundu = 0; //arad���m�z kelime veya benzeri tabloda yoksa kontrol� sa�lamak i�in bu de�i�keni kullan�yoruz.

void degerAtama(string dizi[boyut], string hashTable[hashBoyut]);
void arama(string hashTable[hashBoyut]);
void a(string dizi[hashBoyut], string kelime);
void b(string dizi[hashBoyut], string kelime);

int main(){
	string kelime, dizi[boyut], hashTable[hashBoyut];
	ifstream oku;
	int bulund = 0;
	int sayac = 0, toplam = 0, h; //toplam burada kelimenin hash degeri yani ascii kodlar�yla elde ettigimiz deger. h ise hash tablosunda yerlestirecegimiz indis degeri
	
	oku.open("word.txt"); //Dosyadaki kelimerin bulundu�u dosyay� a�t�k
	
	while(!(oku.eof())){ // Text sonuna gelene kadar okumaya devam et
		oku >> kelime; //kelimeleri okuyoruz kelime de�i�kenine at�yoruz
		
		for(int i = 0; i < kelime.length(); i++){ 
			kelime[i] = tolower(kelime[i]); //kelimenin uzunlugunu al�p her harfi k�c�ge �evirdik
		}
		dizi[sayac] = kelime; // okunan her kelimeyi diziye atad�k
		sayac++;
	}
	
	oku.close(); //dosyay� kapatt�k
	
	
	for(int m = 0; m < hashBoyut; m++){
		hashTable[m] = "-1"; //Dizi nin bo� olup olmad���n� kontrol etmek i�in string olarak -1 atad�k
	}
	
	degerAtama(dizi, hashTable); // hash tablosuna atama fonksiyonunu �a��r�yoruz
	
	cout << "Hash Degeri\tTablodaki Indis Degeri\t\tIndis\t\tKelime" << endl;
	cout << "--------------------------------------------------------------------------" << endl;
	
	for(int m = 0; m < hashBoyut; m++){ // Kelimeri, indislerini ve hash degerlerini yazd�ran fonksiyon
		kelime = hashTable[m]; //kelimenin hash degeri gibi �zelliklerini bulmak i�in tablodaki her degeri de�i�kene at�yoruz
		for(int k = 0; k < kelime.length(); k++){
			toplam = toplam + ((int)kelime[k]*pow((k+1),2)); //kelimenin hash degerini buluyoruz
		}
		
		h = toplam % hashBoyut; //kelimenin normalde hash tablosunda olmas� gereken indisi (h degeri)
		
		cout << toplam << "\t\t" << h << "\t\t\t\t" << m << "\t\t" << hashTable[m] << endl; //Hash fonksiyonu ile yerle�tirdi�imiz kelimeleri yazd�r�yoruz
		toplam = 0;
	}
	while(true){
		arama(hashTable); //ilk arama fonksiyonunu sonsuz d�ng� ile �a��r�yoruz. Program� bitirmek kullan�c�n�n elinde
	}
	
	return 0;
}

void degerAtama(string dizi[boyut], string hashTable[hashBoyut]){ //hash tablosuna kelimeleri atama fonksiyonumuz
	int kontrol = 0, toplam = 0, h = 0; //burada da toplam hash degeri. h hash tablosundaki indis degeri
	string kelime; //kelimelerin �zerinde i�lem yapmak i�in kullanacag�m�z de�i�ken
	
	for(int i = 0; i < boyut; i++){
		kelime = dizi[i]; //i�lem yap�lacak kelimeyi diziden string bir de�i�kene at�yoruz
		for(int j = 0; j < kelime.length(); j++){
			toplam = toplam + ((int)kelime[j]*pow((j+1),2)); //kelimerin her harfinin ascii kodunu alup hash fonksiyonu i�in key degeri �recetegiz.
		}
		
		h = toplam % hashBoyut; //hash fonksiyonu ile kelimenin indisini �retiyoruz
		
		if(hashTable[h] == "-1")
				hashTable[h] = kelime; //dizinin i�i bo� ise kelimeyi yazd�r�yoruz
		else{
			kontrol = h+1; // doluysa bir sonraki indisi kontrol etmek i�in artt�rd�k ve de�i�kene atad�k
			if(kontrol == hashBoyut)
				kontrol = 0; //dizinin son indisi ise ba�a d�nmek i�in
			while(true){
				if(hashTable[kontrol] == "-1"){
					hashTable[kontrol] = kelime; //bo� bi indis bulduktan sonra kelimeyi indise yazar ve break ile d�ng�den ��kar
					break;
				}
				else{
					kontrol += 1; //dizide yer bulamad�ysak kontrol etmek i�in yine artt�rd�k
					if(kontrol == hashBoyut)
						kontrol = 0; //dizinin son indisi ise ba�a d�nmek i�in
				}	
			}
		}
		toplam = 0;
	}
}


void arama(string hashTable[hashBoyut]){ //ilk aramam�z
	string kelime;
	bool bul = false; // bu de�i�ken di�er arama algoritmalar�na girip girmesini kontrol eder.
	int kontrol = 0, toplam = 0, h, k;
	
	
	if(k != 49){
		cout << "\nAramak istediginiz kelimeyi giriniz (Aramayi bitirmek icin \"1\" girin): "; // kullan�c�dan aramak istedi�i kelimeyi al�yoruz.
		cin >> kelime; // ��kmak isterse 1 girmesi yeterli.
		k = (int)kelime[0]; //kelime string oldugundan ilk degeri 1 ise ��kar. ascii kodu ile kontrol yap�yoruz
	}
	else{
		cout << "Program kapaniyor..."; // kullan�c� 1 girdi ise program kapan�r
		exit(0); // program� bitirme komutu
	}
	
	for(int i = 0; i < kelime.length(); i++){ 
		kelime[i] = tolower(kelime[i]); //kelimenin uzunlugunu al�p her harfi kucuge �evirdik. kullanc� b�y�k harf girsede k�c�k olarak ele alm�� olduk
	}
	
	for(int j = 0; j < kelime.length(); j++){
			toplam = toplam + ((int)kelime[j]*pow((j+1),2)); //kelimenin ascii kodlar�yla key de�erini uretiyoruz
	}
	
	h = toplam % hashBoyut; // indis degerini �rettik
	
	if(kelime == hashTable[h]){ //e�er arad�g�m�z kelime hash tablosunda ayn� indiste bulunuyorsa gerekli mesajlar� yazd�r�r
		cout << "\nGirdiginiz \"" << kelime << "\" kelimesi metin doyasinda bulunmaktadir. Dizide " << h << ". indistedir." << endl;
		bul = true; // kelimeyi buldugumuz i�in bul true olur ve di�er arama algoritmalar�na girmez (satir 148)
	}
	else{
		kontrol = h+1; // doluysa bir sonraki indisi kontrol etmek icin artt�rd�k ve degiskene atad�k
		if(kontrol == hashBoyut)
			kontrol = 0; //dizinin son indisi ise ba�a d�nmek i�in
		while(kontrol != h){ // h degerine e�it oldugunda 1 tur d�nm�� olur ve kontrol� b�rak�r
			if(hashTable[kontrol] == kelime){ //arad�g�m�z kelime tablodaki indiste yoksa s�rekli bir sonrakini kontrol eder
				cout << "\nGirdiginiz \"" << kelime << "\" kelimesi metin doyasinda bulunmaktadir.Dizide " << kontrol << ". indistedir." << endl;
				bul = true;
				break;
			}
			else{
				kontrol += 1; //dizide kelimeyi bulamad�ysak kontrol etmek icin yine artt�rd�k
				if(kontrol == hashBoyut)
					kontrol = 0; //dizinin son indisi ise ba�a d�nmek i�in
			}	
		}
	}
	
	if(bul == false){ // aranan kelime bulunamad�ysa bul degeri false olur ve diger arama algoritmalar� devreye girer
		bulundu = 0;
		a(hashTable,kelime); // 1. arama algoritmas� (harf eksilterek arama)
		b(hashTable,kelime); // 2. arama algoritmas� (harf de�i�tirerek arama)
		if(bulundu == 0){
			cout << "\nAradiginiz kelime veya benzeri bulunamadi" << endl;
		}
	}
}

void a(string dizi[hashBoyut], string kelime){ // 1. arama algoritmas� (harf eksilterek arama)
	string kelime1 ,kelimeKontrol;
	int sayac = 0, toplam = 0, kontrol = 0, h;
	
	for(int m = 0; m < kelime.length(); m++){
		kelime1="";
		for(int i = 0; i < kelime.length(); i++){
			if(i != sayac){ // kelime sayactan farkl�ysa toplama ile yeni bir kelime �retiyoruz
				kelime1 += kelime[i]; //kelimenin i. indisini her defas�nda es ge�iyoruz. B�ylece her defas�nda 1 harfi eksilmi� bir �ekilde yeni bir kelime elde ediyoruz
			}
		}
		
		for(int j = 0; j < kelime1.length(); j++){
				toplam = toplam + ((int)kelime1[j]*pow((j+1),2)); //kelimenin ascii kodlar�yla key de�erini uretiyoruz
		}
		
		h = toplam % hashBoyut; // kontrol edecegimiz indis degeri �rettik
	
		if(kelime1 == dizi[h]){ //bu k�s�m arama algoritmas�yla ayn�
			if(kelimeKontrol != kelime1){
				cout << "\nGirdiginiz \"" << kelime << "\" kelimesi metin doyasinda bulunmamaktadir. Benzeri " << kelime1 << " olarak bulunmustur." << endl;
				bulundu = 1;
				kelimeKontrol = kelime1; //ayn� harfleri yer de�i�tridi�imiz da ayn� kelime ortaya ��kabiliyo
			} //(baseball gibi baseballl aradg�m�zda l harfi 2 kez eksilecek ve ayn� kelime ortaya ��kacak)
		} //bu y�zden buldugumuz kelimeyi kelime kontrol de�i�kenine atad�k ve kelime bu de�i�kenden farkl�ysa yazd�r�yoruz
		else{
			kontrol = h+1; // doluysa bir sonraki indisi kontrol etmek icin artt�rd�k ve degiskene atad�k
			if(kontrol == hashBoyut)
				kontrol = 0; //dizinin son indisi ise ba�a d�nmek i�in
			while(kontrol != h){
				if(dizi[kontrol] == kelime1){
					if(kelimeKontrol != kelime1){
						cout << "\nGirdiginiz \"" << kelime << "\" kelimesi metin doyasinda bulunmamaktadir. Benzeri " << kelime1 << " olarak bulunmustur." << endl;
						bulundu = 1;
						kelimeKontrol = kelime1; // bu kontroller yukardaki ile ayn� (sat�r 178)
						break;
					}
					break;
				}
				else{
					kontrol += 1; //dizide kelimeyi bulamad�ysak kontrol etmek icin yine artt�rd�k
					if(kontrol == hashBoyut)
						kontrol = 0; //dizinin son indisi ise ba�a d�nmek i�in
				}
			}
		}
		
		sayac++;
		toplam = 0;
		kontrol = 0;
		
	}
}

void b(string dizi[hashBoyut], string kelime){ // 2. arama algoritmas� (harf de�i�tirerek arama)
	string kelime1, harf;
	string kelime2 = kelime;
	string kelimeKontrol;
	int sayac = 1, toplam = 0, kontrol = 0, h, sayac1 = 0;
	
	for(int m = 1; m < kelime.length(); m++){
		kelime1="";
		for(int i = 1; i < kelime.length(); i++){ // harfi de�i�tirme d�ng�m�z. i nin 1 den ba�lama nedeni  kelimenin i. harfi ve bir �ncekini de�i�terecek olmam�z
			if(i == sayac){ // sayac kac�nc� harfi de�i�tirecegimizi belirtiyo
				
				harf = kelime[i]; // kelimenin i. harfini harf de�i�kenine at�yoruz temp gibi ge�i�i de�i�ken bu
				kelime1 += harf; //harfi kelime1 e ekliyoruz
				kelime1 += kelime[i-1]; // daha sonrada kelimenin i. indisinden bir �ncekini kelime1 e ekliyoruz yani burada i. indis ile i-1. indis yer de�i�tirdi
				sayac1 += 2; // 2 harfte i�lme yapt�g�m�z i�in indisi tutan sayac1'i 2 artt�rd�k
			}
			else{
				kelime1 += kelime[sayac1]; //kelimede yer de�i�tirmeyen harfleri direk topluyoruz
				sayac1++; //sayac1 kelimedeki harflerin indisini tutuyo
			}
		}
		
		for(int j = 0; j < kelime1.length(); j++){
			toplam = toplam + ((int)kelime1[j]*pow((j+1),2)); //kelimenin ascii kodlar�yla key de�erini uretiyoruz
		}
		
		h = toplam % hashBoyut; // kontrol edecegimiz indis degerini �rettik
		
		if(kelime1 == dizi[h]){ //buradaki arama mant�g�da 1. arama (a) fonksiypnu ile ayn�
			if(kelimeKontrol != kelime1){
				cout << "\nGirdiginiz \"" << kelime2 << "\" kelimesi metin doyasinda bulunmamaktadir. Benzeri " << kelime1 << " olarak bulunmustur." << endl;
				bulundu = 1;
				kelimeKontrol = kelime1;
			}
		}
		else{
			kontrol = h+1; // doluysa bir sonraki indisi kontrol etmek icin artt�rd�k ve degiskene atad�k
			if(kontrol == hashBoyut)
				kontrol = 0; //dizinin son indisi ise ba�a d�nmek i�in
			while(kontrol != h){
				if(dizi[kontrol] == kelime1){
					if(kelimeKontrol != kelime1){
						cout << "\nGirdiginiz \"" << kelime2 << "\" kelimesi metin doyasinda bulunmamaktadir. Benzeri " << kelime1 << " olarak bulunmustur." << endl;
						bulundu = 1;
						kelimeKontrol = kelime1;
						break;
					}
				}
				else{
					kontrol += 1; //dizide kelimeyi bulamad�ysak kontrol etmek icin yine artt�rd�k
					if(kontrol == hashBoyut)
						kontrol = 0; //dizinin son indisi ise ba�a d�nmek i�in
				}
			}
		}
		
		sayac++;
		sayac1 = 0;
		toplam = 0;
		kontrol = 0;
	}
}

