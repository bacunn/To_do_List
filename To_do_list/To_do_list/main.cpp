#include <iostream>
#include <string>
#include <fstream>
using namespace std;

int main() {
    const int say = 50;
    string gorevList[say];
    string tarih[say];
    int sayac = 0;
    string secim;
    //alttaki b�l�m program her a��ld���nda dosyalardaki verilerin okunmas�n� sa�lar 
    ifstream gorevOku("Gorevler.txt");
    ifstream tarihOku("Tarih.txt");
    while (sayac < say && getline(gorevOku, gorevList[sayac]) && getline(tarihOku, tarih[sayac])) {
        sayac++;
    }
    gorevOku.close();
    tarihOku.close();

    while (true) {
        cout << "Hangi islemi yapmak istersiniz" << endl;
        cout << "1-Gorev ekleme" << endl << "2-Gorevleri goster" << endl << "3-Gorev Duzenleme" << endl << "4-Cikis" << endl << "5-Tamamlanan Gorevler";


        cout << "Secim:";
        cin >> secim;
        cin.ignore();

        if (secim == "1") {
            cout << "Gorev Ekleme Menusu" << endl;//G�rev girilir girilen g�rev ve tarih verilerini gorevler ve tarih dosyalar�na eklenmesini sa�lar  
            cout << "Eklenmek istenen gorevi giriniz:";
            getline(cin, gorevList[sayac]);

            cout << "Tarih Giriniz:";
            getline(cin, tarih[sayac]);

            ofstream gorevlerDosya("Gorevler.txt", ios::app);//dosyan�n sonuna veri eklenir
            gorevlerDosya << gorevList[sayac] << endl;
            gorevlerDosya.close();

            ofstream tarihDosya("Tarih.txt", ios::app);
            tarihDosya << tarih[sayac] << endl;
            tarihDosya.close();

            sayac++;
        }
        else if (secim == "2") {//G�rev ve tarih veilerinin d�zenli bir �ekilde g�sterilmesi i�in olan b�l�m
            cout << "Gorevleri Goster Menusu" << endl;
            for (int i = 0; i < sayac; i++) {
                cout << i + 1 << ") " << gorevList[i] << " -- " << tarih[i] << endl;
            }
        }
        else if (secim == "3") {//G�rev ve tarih verilerinde de�i�iklik yapmak istenildi�i zaman istenilen tarih ve g�revi dosyalardan bularak d�zenlenmesini (g�ncellenmesini)sa�layan b�l�m
            cout << "Gorev Duzenleme Menusu" << endl;
            int duzenNo;
            cout << "Hangi gorevi duzenlemek istiyorsunuz(lutfen sayi olarak giriniz): ";
            cin >> duzenNo;
            cin.ignore();

            if (duzenNo < 1 || duzenNo > sayac) {
                cout << "Yanlis bir numara girdiniz" << endl;
            }
            else {
                cout << "Yeni Gorev Giriniz: ";
                string yeniGorev;
                getline(cin, yeniGorev);
                gorevList[duzenNo - 1] = yeniGorev;

                cout << "Yeni Tarih Giriniz: ";
                string yeniTarih;
                getline(cin, yeniTarih);
                tarih[duzenNo - 1] = yeniTarih;

                ofstream gorevlerDosya("Gorevler.txt", ios::trunc);//burada dosyan�n i�irei�i temizlenerek d�zenlenen veriler yeniden dosyaya yaz�l�r
                ofstream tarihDosya("Tarih.txt", ios::trunc);
                for (int i = 0; i < sayac; i++) {
                    gorevlerDosya << gorevList[i] << endl;
                    tarihDosya << tarih[i] << endl;
                }
                gorevlerDosya.close();
                tarihDosya.close();
            }
        }
        else if (secim == "4") {
            return 0;
        }
        else if (secim == "5") {//Tamamlanan g�revleri tarihleri ile birlikte Tamamlanan dosyas�na alarak tamamlanan gorevleri g�sterir
            cout << "Tamamlanan Gorevler Menusu" << endl;

            int tamamNo;
            cout << "Tamamlanan gorevin numarasi" << endl;
            cin >> tamamNo;
            cin.ignore();

            if (tamamNo < 1 || tamamNo>sayac) {
                cout << "Yanlis bir numara girdiniz" << endl;

            }
            else {
                ofstream tamamDosya("Tamamlanan.txt", ios::app);
                tamamDosya << gorevList[tamamNo - 1] << "--" << tarih[tamamNo - 1] << endl;
                tamamDosya.close();

                for (int i = tamamNo - 1; i < sayac - 1; i++) {
                    gorevList[i] = gorevList[i + 1];
                    tarih[i] = tarih[i + 1];
                }
                sayac--;
            }
            ofstream gorevlerDosya("Gorevler.txt", ios::trunc);//Tamamlanan g�rev tamamlanan dosyas�na yaz�ld�ktan sonra de�i�en gorevler ve tarih dosyalar� yeniden yaz�l�r
            ofstream tarihDosya("Tarih.txt", ios::trunc);
            for (int i = 0; i < sayac; i++) {
                gorevlerDosya << gorevList[i] << endl;
                tarihDosya << tarih[i] << endl;
            }
            gorevlerDosya.close();
            tarihDosya.close();

            cout << "Tamamlanan Gorevler" << endl;
            ifstream tamamlananDosya("Tamamlanan.txt");
            string satir;
            int sayi = 1;
            while (getline(tamamlananDosya, satir)) {
                cout << sayi++ << ") " << satir << endl;
            }
            tamamlananDosya.close();

        }
    }
}
