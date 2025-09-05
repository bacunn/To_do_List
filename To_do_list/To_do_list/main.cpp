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
    //alttaki bölüm program her açýldýðýnda dosyalardaki verilerin okunmasýný saðlar 
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
            cout << "Gorev Ekleme Menusu" << endl;//Görev girilir girilen görev ve tarih verilerini gorevler ve tarih dosyalarýna eklenmesini saðlar  
            cout << "Eklenmek istenen gorevi giriniz:";
            getline(cin, gorevList[sayac]);

            cout << "Tarih Giriniz:";
            getline(cin, tarih[sayac]);

            ofstream gorevlerDosya("Gorevler.txt", ios::app);//dosyanýn sonuna veri eklenir
            gorevlerDosya << gorevList[sayac] << endl;
            gorevlerDosya.close();

            ofstream tarihDosya("Tarih.txt", ios::app);
            tarihDosya << tarih[sayac] << endl;
            tarihDosya.close();

            sayac++;
        }
        else if (secim == "2") {//Görev ve tarih veilerinin düzenli bir þekilde gösterilmesi için olan bölüm
            cout << "Gorevleri Goster Menusu" << endl;
            for (int i = 0; i < sayac; i++) {
                cout << i + 1 << ") " << gorevList[i] << " -- " << tarih[i] << endl;
            }
        }
        else if (secim == "3") {//Görev ve tarih verilerinde deðiþiklik yapmak istenildiði zaman istenilen tarih ve görevi dosyalardan bularak düzenlenmesini (güncellenmesini)saðlayan bölüm
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

                ofstream gorevlerDosya("Gorevler.txt", ios::trunc);//burada dosyanýn içireiði temizlenerek düzenlenen veriler yeniden dosyaya yazýlýr
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
        else if (secim == "5") {//Tamamlanan görevleri tarihleri ile birlikte Tamamlanan dosyasýna alarak tamamlanan gorevleri gösterir
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
            ofstream gorevlerDosya("Gorevler.txt", ios::trunc);//Tamamlanan görev tamamlanan dosyasýna yazýldýktan sonra deðiþen gorevler ve tarih dosyalarý yeniden yazýlýr
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
