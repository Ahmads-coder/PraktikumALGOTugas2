#include <iostream>
#include <stdio.h>
#include <string>
#include <iomanip>
using namespace std;

// menyimpan data film
struct Film{
    string judul;
    int lisensi;
    int tahun;
    float rating;
};

// quick sort untuk mengurutkan rating film dari terbesar
void quickS(Film data[], int kiri, int kanan){
    int i = kiri;
    int j = kanan;
// pivot diambil dari tengah data
    float pivot = data[(kiri+kanan)/2].rating;

    Film temp;
    while(i <= j){
        while(data[i].rating > pivot){
            i++;
        }
        while(data[j].rating < pivot){
            j--;
        } 
        if(i <= j){
            temp = data[i];
            data[i] = data[j];
            data[j] = temp;

            i++;
            j--;
        }
    }
//rekurssif
    if(kiri < j){
        quickS(data,kiri,j);
    }
    if(i < kanan){
        quickS(data,i,kanan);
    }
}

int main(){
    Film data[100], temp;
    int n = 0;      
    int menu;     

    FILE *file;
    file = fopen("netfilm_db.txt","r");

    if(file != NULL){

        char jdl[100];
// baca file sampai akhir
        while(fscanf(file,"%[^;];%d;%d;%f\n",
        jdl,&data[n].lisensi,&data[n].tahun,&data[n].rating)!=EOF){

            data[n].judul = jdl;
            n++; 
        }
        fclose(file);
    }
	do{
		cout << "\n+=====================================+\n";
        cout << "|     NETFILM SYSTEM - DASBOARD       |\n";
        cout << "+=====================================+\n";
        cout << "| [ 1 ] Lihat Katalog Film            |\n";
        cout << "| [ 2 ] Urutkan Rating (QuickSort)     |\n";
        cout << "| [ 3 ] Urutkan Abjad (Bubble Sort)    |\n";
        cout << "| [ 4 ] Cari Film (Linear Search)     |\n";
        cout << "| [ 5 ] Cari Film (Binary Search)     |\n";
        cout << "| [ 6 ] Tambah Film Baru              |\n";
        cout << "| [ 0 ] Keluar dan Simpan             |\n";
        cout << "+=====================================+\n";

        cout << "Pilih Menu => ";
        cin >> menu;

	if(menu == 1){
        cout << "\n+=======================================================+\n";
        cout << "|             NETFILM CONTENT CATALOG                   |\n";
        cout << "+=======================================================+\n";
        cout << "| ID | " << left << setw(20) << "JUDUL FILM"
             << " | " << setw(8) << "LISENSI"
             << " | " << setw(5) << "TAHUN"
             << " | " << setw(6) << "RATING |\n";
        cout << "+-------------------------------------------------------+\n";
	for(int i=0;i<n;i++){

		cout << "| " << setw(2) << i+1 << " | "
             << left << setw(20) << data[i].judul
             << " | " << setw(8) << data[i].lisensi
             << " | " << setw(5) << data[i].tahun
             << " | " << setw(6) << data[i].rating
             << " |\n";
        }
        cout << "+=======================================================+\n";

        cout << "\nTekan enter untuk kembali ke menu...";
        cin.ignore();
        cin.get();
        }
// mengurutkan film berdasarkan rating tertinggi
	else if(menu == 2){
		quickS(data,0,n-1);

        cout << "\nKatalog berhasil diurutkan berdasarkan Rating Tertinggi\n";
		cout << "\nTekan enter untuk kembali ke menu...";
        cin.ignore();
        cin.get();
	}

// bubble sort mengurutkan judul film  abjat A-Z
	else if(menu == 3){

        for(int i=0;i<n-1;i++){
			for(int j=0;j<n-i-1;j++){

				if(data[j].judul > data[j+1].judul){

					temp = data[j];
                    data[j] = data[j+1];
                    data[j+1] = temp;
                }
            }
        }

		cout << "\nKatalog berhasil diurutkan berdasarkan Abjad A-Z\n";

        cout << "\nTekan enter untuk kembali ke menu...";
        cin.ignore();
        cin.get();
    }

// pencarian film linear search
        else if(menu == 4){

            if(n >= 30){
                cout << "\nData sudah >= 30, gunakan Binary Search\n";
                cout << "\nTekan enter untuk kembali ke menu...";
                cin.ignore();
                cin.get();
            } else{
				string key;
                bool found=false;
                cin.ignore();

                cout << "Keyword Judul : ";
                getline(cin,key);

		for(int i=0;i<n;i++){
			if(data[i].judul.find(key) != string::npos){
				cout << "\n[FOUND]\n";
                cout << data[i].judul << " (" << data[i].tahun << ")\n";

				found=true;
           }
		}
		if(!found){
			cout << "\nJudul tidak ditemukan\n";
        }
            cout << "\nTekan enter untuk kembali ke menu...";
            cin.get();
            }
        }

// pencarian film dengan binary search
        else if(menu == 5){
            if(n < 30){
                cout << "\nData kurang dari 30, gunakan Linear Search\n";
                cout << "\nTekan enter untuk kembali ke menu...";
                cin.ignore();
                cin.get();
            } else{
				string key;
                int left=0,right=n-1,mid;
                bool found=false;
                cin.ignore();

                cout << "Judul Lengkap : ";
                getline(cin,key);

		while(left <= right){
			mid = (left+right)/2;

				if(data[mid].judul == key){
					cout << "\n[FOUND]\n";
                    cout << data[mid].judul << " (" << data[mid].tahun << ")\n";

                    found=true;
                    break;
                    
                } else if(data[mid].judul < key){
                        left = mid+1;
                  } else{
                        right = mid-1;
                  }
                } if(!found){
					cout << "\nJudul Tidak Ditemukan\n";
                    cout << "Pastikan data sudah di sortting A-Z\n";
                }

                cout << "\nTekan enter untuk kembali ke menu...";
                cin.get();
            }
        }

		else if(menu == 6){
            int jumlah;

            cout << "Berapa film yang akan ditambahkan : ";
            cin >> jumlah;

            cin.ignore();

            for(int i=0;i<jumlah;i++){
                cout << "\nData Film ke-" << i+1 << endl;

                cout << "Judul Film : ";
                getline(cin,data[n].judul);

                cout << "Harga Lisensi : ";
                cin >> data[n].lisensi;

                cout << "Tahun : ";
                cin >> data[n].tahun;

                cout << "Rating : ";
                cin >> data[n].rating;

                cin.ignore();

                n++; // jml data bertambah
            }

            cout << "\n Sukses!] Data berhasil ditambahkan";

            cout << "\nTekan enter untuk kembali ke menu...";
            cin.get();
        }

    }while(menu != 0);

// bukan file dan simpan data baru
    file = fopen("netfilm_db.txt","w");

    for(int i=0;i<n;i++){
        fprintf(file,"%s;%d;%d;%.1f\n",
        data[i].judul.c_str(),
        data[i].lisensi,
        data[i].tahun,
        data[i].rating);
    }
    fclose(file);
    cout << "\[Sukses!] Data berhasil disimpan kefile netfilm_db.txt\n";

}
