#include<iostream>
#include<fstream>
#include<string>
#include<locale>
#include<cmath>
//Ahmet Metehan ***** --- Mühendislik Projesi --- 2016123*** --- Normal Öðretim
#define hashBoyut 72
#define boyut 72

using namespace std;

int bulundu = 0; //aradýðýmýz kelime veya benzeri tabloda yoksa kontrolü saðlamak için bu deðiþkeni kullanýyoruz.

void degerAtama(string dizi[boyut], string hashTable[hashBoyut]);
void arama(string hashTable[hashBoyut]);
void a(string dizi[hashBoyut], string kelime);
void b(string dizi[hashBoyut], string kelime);

int main(){
	string kelime, dizi[boyut], hashTable[hashBoyut];
	ifstream oku;
	int bulund = 0;
	int sayac = 0, toplam = 0, h; //toplam burada kelimenin hash degeri yani ascii kodlarýyla elde ettigimiz deger. h ise hash tablosunda yerlestirecegimiz indis degeri
	
	oku.open("word.txt"); //Dosyadaki kelimerin bulunduðu dosyayý açtýk
	
	while(!(oku.eof())){ // Text sonuna gelene kadar okumaya devam et
		oku >> kelime; //kelimeleri okuyoruz kelime deðiþkenine atýyoruz
		
		for(int i = 0; i < kelime.length(); i++){ 
			kelime[i] = tolower(kelime[i]); //kelimenin uzunlugunu alýp her harfi kücüge çevirdik
		}
		dizi[sayac] = kelime; // okunan her kelimeyi diziye atadýk
		sayac++;
	}
	
	oku.close(); //dosyayý kapattýk
	
	
	for(int m = 0; m < hashBoyut; m++){
		hashTable[m] = "-1"; //Dizi nin boþ olup olmadýðýný kontrol etmek için string olarak -1 atadýk
	}
	
	degerAtama(dizi, hashTable); // hash tablosuna atama fonksiyonunu çaðýrýyoruz
	
	cout << "Hash Degeri\tTablodaki Indis Degeri\t\tIndis\t\tKelime" << endl;
	cout << "--------------------------------------------------------------------------" << endl;
	
	for(int m = 0; m < hashBoyut; m++){ // Kelimeri, indislerini ve hash degerlerini yazdýran fonksiyon
		kelime = hashTable[m]; //kelimenin hash degeri gibi özelliklerini bulmak için tablodaki her degeri deðiþkene atýyoruz
		for(int k = 0; k < kelime.length(); k++){
			toplam = toplam + ((int)kelime[k]*pow((k+1),2)); //kelimenin hash degerini buluyoruz
		}
		
		h = toplam % hashBoyut; //kelimenin normalde hash tablosunda olmasý gereken indisi (h degeri)
		
		cout << toplam << "\t\t" << h << "\t\t\t\t" << m << "\t\t" << hashTable[m] << endl; //Hash fonksiyonu ile yerleþtirdiðimiz kelimeleri yazdýrýyoruz
		toplam = 0;
	}
	while(true){
		arama(hashTable); //ilk arama fonksiyonunu sonsuz döngü ile çaðýrýyoruz. Programý bitirmek kullanýcýnýn elinde
	}
	
	return 0;
}

void degerAtama(string dizi[boyut], string hashTable[hashBoyut]){ //hash tablosuna kelimeleri atama fonksiyonumuz
	int kontrol = 0, toplam = 0, h = 0; //burada da toplam hash degeri. h hash tablosundaki indis degeri
	string kelime; //kelimelerin üzerinde iþlem yapmak için kullanacagýmýz deðiþken
	
	for(int i = 0; i < boyut; i++){
		kelime = dizi[i]; //iþlem yapýlacak kelimeyi diziden string bir deðiþkene atýyoruz
		for(int j = 0; j < kelime.length(); j++){
			toplam = toplam + ((int)kelime[j]*pow((j+1),2)); //kelimerin her harfinin ascii kodunu alup hash fonksiyonu için key degeri ürecetegiz.
		}
		
		h = toplam % hashBoyut; //hash fonksiyonu ile kelimenin indisini üretiyoruz
		
		if(hashTable[h] == "-1")
				hashTable[h] = kelime; //dizinin içi boþ ise kelimeyi yazdýrýyoruz
		else{
			kontrol = h+1; // doluysa bir sonraki indisi kontrol etmek için arttýrdýk ve deðiþkene atadýk
			if(kontrol == hashBoyut)
				kontrol = 0; //dizinin son indisi ise baþa dönmek için
			while(true){
				if(hashTable[kontrol] == "-1"){
					hashTable[kontrol] = kelime; //boþ bi indis bulduktan sonra kelimeyi indise yazar ve break ile döngüden çýkar
					break;
				}
				else{
					kontrol += 1; //dizide yer bulamadýysak kontrol etmek için yine arttýrdýk
					if(kontrol == hashBoyut)
						kontrol = 0; //dizinin son indisi ise baþa dönmek için
				}	
			}
		}
		toplam = 0;
	}
}


void arama(string hashTable[hashBoyut]){ //ilk aramamýz
	string kelime;
	bool bul = false; // bu deðiþken diðer arama algoritmalarýna girip girmesini kontrol eder.
	int kontrol = 0, toplam = 0, h, k;
	
	
	if(k != 49){
		cout << "\nAramak istediginiz kelimeyi giriniz (Aramayi bitirmek icin \"1\" girin): "; // kullanýcýdan aramak istediði kelimeyi alýyoruz.
		cin >> kelime; // çýkmak isterse 1 girmesi yeterli.
		k = (int)kelime[0]; //kelime string oldugundan ilk degeri 1 ise çýkar. ascii kodu ile kontrol yapýyoruz
	}
	else{
		cout << "Program kapaniyor..."; // kullanýcý 1 girdi ise program kapanýr
		exit(0); // programý bitirme komutu
	}
	
	for(int i = 0; i < kelime.length(); i++){ 
		kelime[i] = tolower(kelime[i]); //kelimenin uzunlugunu alýp her harfi kucuge çevirdik. kullancý büyük harf girsede kücük olarak ele almýþ olduk
	}
	
	for(int j = 0; j < kelime.length(); j++){
			toplam = toplam + ((int)kelime[j]*pow((j+1),2)); //kelimenin ascii kodlarýyla key deðerini uretiyoruz
	}
	
	h = toplam % hashBoyut; // indis degerini ürettik
	
	if(kelime == hashTable[h]){ //eðer aradýgýmýz kelime hash tablosunda ayný indiste bulunuyorsa gerekli mesajlarý yazdýrýr
		cout << "\nGirdiginiz \"" << kelime << "\" kelimesi metin doyasinda bulunmaktadir. Dizide " << h << ". indistedir." << endl;
		bul = true; // kelimeyi buldugumuz için bul true olur ve diðer arama algoritmalarýna girmez (satir 148)
	}
	else{
		kontrol = h+1; // doluysa bir sonraki indisi kontrol etmek icin arttýrdýk ve degiskene atadýk
		if(kontrol == hashBoyut)
			kontrol = 0; //dizinin son indisi ise baþa dönmek için
		while(kontrol != h){ // h degerine eþit oldugunda 1 tur dönmüþ olur ve kontrolü býrakýr
			if(hashTable[kontrol] == kelime){ //aradýgýmýz kelime tablodaki indiste yoksa sürekli bir sonrakini kontrol eder
				cout << "\nGirdiginiz \"" << kelime << "\" kelimesi metin doyasinda bulunmaktadir.Dizide " << kontrol << ". indistedir." << endl;
				bul = true;
				break;
			}
			else{
				kontrol += 1; //dizide kelimeyi bulamadýysak kontrol etmek icin yine arttýrdýk
				if(kontrol == hashBoyut)
					kontrol = 0; //dizinin son indisi ise baþa dönmek için
			}	
		}
	}
	
	if(bul == false){ // aranan kelime bulunamadýysa bul degeri false olur ve diger arama algoritmalarý devreye girer
		bulundu = 0;
		a(hashTable,kelime); // 1. arama algoritmasý (harf eksilterek arama)
		b(hashTable,kelime); // 2. arama algoritmasý (harf deðiþtirerek arama)
		if(bulundu == 0){
			cout << "\nAradiginiz kelime veya benzeri bulunamadi" << endl;
		}
	}
}

void a(string dizi[hashBoyut], string kelime){ // 1. arama algoritmasý (harf eksilterek arama)
	string kelime1 ,kelimeKontrol;
	int sayac = 0, toplam = 0, kontrol = 0, h;
	
	for(int m = 0; m < kelime.length(); m++){
		kelime1="";
		for(int i = 0; i < kelime.length(); i++){
			if(i != sayac){ // kelime sayactan farklýysa toplama ile yeni bir kelime üretiyoruz
				kelime1 += kelime[i]; //kelimenin i. indisini her defasýnda es geçiyoruz. Böylece her defasýnda 1 harfi eksilmiþ bir þekilde yeni bir kelime elde ediyoruz
			}
		}
		
		for(int j = 0; j < kelime1.length(); j++){
				toplam = toplam + ((int)kelime1[j]*pow((j+1),2)); //kelimenin ascii kodlarýyla key deðerini uretiyoruz
		}
		
		h = toplam % hashBoyut; // kontrol edecegimiz indis degeri ürettik
	
		if(kelime1 == dizi[h]){ //bu kýsým arama algoritmasýyla ayný
			if(kelimeKontrol != kelime1){
				cout << "\nGirdiginiz \"" << kelime << "\" kelimesi metin doyasinda bulunmamaktadir. Benzeri " << kelime1 << " olarak bulunmustur." << endl;
				bulundu = 1;
				kelimeKontrol = kelime1; //ayný harfleri yer deðiþtridiðimiz da ayný kelime ortaya çýkabiliyo
			} //(baseball gibi baseballl aradgýmýzda l harfi 2 kez eksilecek ve ayný kelime ortaya çýkacak)
		} //bu yüzden buldugumuz kelimeyi kelime kontrol deðiþkenine atadýk ve kelime bu deðiþkenden farklýysa yazdýrýyoruz
		else{
			kontrol = h+1; // doluysa bir sonraki indisi kontrol etmek icin arttýrdýk ve degiskene atadýk
			if(kontrol == hashBoyut)
				kontrol = 0; //dizinin son indisi ise baþa dönmek için
			while(kontrol != h){
				if(dizi[kontrol] == kelime1){
					if(kelimeKontrol != kelime1){
						cout << "\nGirdiginiz \"" << kelime << "\" kelimesi metin doyasinda bulunmamaktadir. Benzeri " << kelime1 << " olarak bulunmustur." << endl;
						bulundu = 1;
						kelimeKontrol = kelime1; // bu kontroller yukardaki ile ayný (satýr 178)
						break;
					}
					break;
				}
				else{
					kontrol += 1; //dizide kelimeyi bulamadýysak kontrol etmek icin yine arttýrdýk
					if(kontrol == hashBoyut)
						kontrol = 0; //dizinin son indisi ise baþa dönmek için
				}
			}
		}
		
		sayac++;
		toplam = 0;
		kontrol = 0;
		
	}
}

void b(string dizi[hashBoyut], string kelime){ // 2. arama algoritmasý (harf deðiþtirerek arama)
	string kelime1, harf;
	string kelime2 = kelime;
	string kelimeKontrol;
	int sayac = 1, toplam = 0, kontrol = 0, h, sayac1 = 0;
	
	for(int m = 1; m < kelime.length(); m++){
		kelime1="";
		for(int i = 1; i < kelime.length(); i++){ // harfi deðiþtirme döngümüz. i nin 1 den baþlama nedeni  kelimenin i. harfi ve bir öncekini deðiþterecek olmamýz
			if(i == sayac){ // sayac kacýncý harfi deðiþtirecegimizi belirtiyo
				
				harf = kelime[i]; // kelimenin i. harfini harf deðiþkenine atýyoruz temp gibi geçiçi deðiþken bu
				kelime1 += harf; //harfi kelime1 e ekliyoruz
				kelime1 += kelime[i-1]; // daha sonrada kelimenin i. indisinden bir öncekini kelime1 e ekliyoruz yani burada i. indis ile i-1. indis yer deðiþtirdi
				sayac1 += 2; // 2 harfte iþlme yaptýgýmýz için indisi tutan sayac1'i 2 arttýrdýk
			}
			else{
				kelime1 += kelime[sayac1]; //kelimede yer deðiþtirmeyen harfleri direk topluyoruz
				sayac1++; //sayac1 kelimedeki harflerin indisini tutuyo
			}
		}
		
		for(int j = 0; j < kelime1.length(); j++){
			toplam = toplam + ((int)kelime1[j]*pow((j+1),2)); //kelimenin ascii kodlarýyla key deðerini uretiyoruz
		}
		
		h = toplam % hashBoyut; // kontrol edecegimiz indis degerini ürettik
		
		if(kelime1 == dizi[h]){ //buradaki arama mantýgýda 1. arama (a) fonksiypnu ile ayný
			if(kelimeKontrol != kelime1){
				cout << "\nGirdiginiz \"" << kelime2 << "\" kelimesi metin doyasinda bulunmamaktadir. Benzeri " << kelime1 << " olarak bulunmustur." << endl;
				bulundu = 1;
				kelimeKontrol = kelime1;
			}
		}
		else{
			kontrol = h+1; // doluysa bir sonraki indisi kontrol etmek icin arttýrdýk ve degiskene atadýk
			if(kontrol == hashBoyut)
				kontrol = 0; //dizinin son indisi ise baþa dönmek için
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
					kontrol += 1; //dizide kelimeyi bulamadýysak kontrol etmek icin yine arttýrdýk
					if(kontrol == hashBoyut)
						kontrol = 0; //dizinin son indisi ise baþa dönmek için
				}
			}
		}
		
		sayac++;
		sayac1 = 0;
		toplam = 0;
		kontrol = 0;
	}
}

