#include <iostream>
#include <string>
#include <cstdlib>  // Untuk fungsi rand() dan srand()
#include <ctime>    // Untuk fungsi time()
#include <fstream>  // Untuk operasi file

using namespace std;

// Struktur untuk menyimpan informasi pengirim dan penerima
struct info {
    string namaPengirim;
    string alamatPengirim;
    string kontakPengirim;
    string namaPenerima;
    string alamatPenerima;
    string kontakPenerima;
    string nomorResi;
    string tglKirim;
    float beratBarang;
    float harga;    // Tambahkan harga
};

// Fungsi untuk meng-generate nomor resi random sebanyak 4 digit
string generateNomorResi() {
    srand(time(0)); // Menginisialisasi seed random dengan waktu sekarang
    int resi = rand() % 9000 + 1000; // Meng-generate nomor random 4 digit
    return to_string(resi);
}

// Fungsi untuk menyimpan nomor resi ke dalam file
void simpanNomorResiKeFile(const string& nomorResi) {
    ofstream file("resi.txt");
    if (file.is_open()) {
        file << nomorResi << endl;
        file.close();
        cout << Border << endl;
    } else {
        cout << BorderKecil << endl;
    }
}

int main() {
    info informasi;

    // Input informasi pengirim
    cout << "Masukkan informasi pengirim:" << endl;
    cout << "Nama Lengkap: ";
    getline(cin, informasi.namaPengirim);
    cout << "Alamat: ";
    getline(cin, informasi.alamatPengirim);
    cout << "Nomor Handphone: ";
    getline(cin, informasi.kontakPengirim);

    // Input informasi penerima
    cout << "Masukkan informasi penerima:" << endl;
    cout << "Nama Lengkap: ";
    getline(cin, informasi.namaPenerima);
    cout << "Alamat: ";
    getline(cin, informasi.alamatPenerima);
    cout << "Nomor Handphone: ";
    getline(cin, informasi.kontakPenerima);

    // Generate nomor resi random
    informasi.nomorResi = generateNomorResi();


    // Input tgl kirim
    cout << "Masukkan tanggal pengiriman (dd/mm/yyyy): ";
    cin >> informasi.tglKirim;

    // Input berat barang
    cout << "Masukkan berat barang (dalam gram): ";
    cin >> informasi.beratBarang;

    // Input harga
    cout << "Masukkan harga: Rp. ";
    cin >> informasi.harga;

    // Menampilkan resi barang
    cout << "\n=== Resi Barang ===" << endl;
    cout << "Informasi Pengirim:" << endl;
    cout << "Nama Lengkap: " << informasi.namaPengirim << endl;
    cout << "Alamat: " << informasi.alamatPengirim << endl;
    cout << "Nomor Handphone: " << informasi.kontakPengirim << endl;

    cout << "\nInformasi Penerima:" << endl;
    cout << "Nama Lengkap: " << informasi.namaPenerima << endl;
    cout << "Alamat: " << informasi.alamatPenerima << endl;
    cout << "Nomor Handphone: " << informasi.kontakPenerima << endl;

    cout << "\nNomor Resi: " << informasi.nomorResi << endl;
    cout << "Tanggal Pengiriman: " << informasi.tglKirim << endl;
    cout << "Berat Barang: " << informasi.beratBarang << " gram" << endl;
    cout << "Harga: Rp." << informasi.harga << endl;

    // Simpan nomor resi ke dalam file
    simpanNomorResiKeFile(informasi.nomorResi);

    return 0;
}


#include <iostream>
#include <string>
#include <cstdlib>  // Untuk fungsi rand() dan srand()
#include <ctime>    // Untuk fungsi time()
#include <fstream>  // Untuk operasi file
#include <iomanip>

using namespace std;

// Struktur untuk menyimpan informasi pengirim dan penerima
struct info {
    string namaPengirim;
    string alamatPengirim;
    string kontakPengirim;
    string namaPenerima;
    string alamatPenerima;
    string kontakPenerima;
    string nomorResi;
    string tglKirim;
    float beratBarang;
    float harga;    // Tambahkan harga
};

// Fungsi untuk meng-generate nomor resi random sebanyak 4 digit
string generateNomorResi() {
    srand(time(0)); // Menginisialisasi seed random dengan waktu sekarang
    int resi = rand() % 9000 + 1000; // Meng-generate nomor random 4 digit
    return to_string(resi);
}

// Fungsi untuk menyimpan nomor resi ke dalam file
void simpanNomorResiKeFile(const string& nomorResi) {
    ofstream file("resi.txt");
    if (file.is_open()) {
        file << "Nomor Resi: " << nomorResi << endl;
        file.close();
        cout << "==========" << endl;
    } else {
        cout << "----------" << endl;
    }
}

void printHorizontalBorder() {
    cout << "+--------------------+--------------------+--------------------+--------------------+--------------------+--------------------+---------------+----------+---------------+" << endl;
}

int main() {
    info informasi;

    // Input informasi pengirim
    cout << "Masukkan informasi pengirim:" << endl;
    cout << "Nama Lengkap: ";
    getline(cin, informasi.namaPengirim);
    cout << "Alamat: ";
    getline(cin, informasi.alamatPengirim);
    cout << "Nomor Handphone: ";
    getline(cin, informasi.kontakPengirim);

    // Input informasi penerima
    cout << "Masukkan informasi penerima:" << endl;
    cout << "Nama Lengkap: ";
    getline(cin, informasi.namaPenerima);
    cout << "Alamat: ";
    getline(cin, informasi.alamatPenerima);
    cout << "Nomor Handphone: ";
    getline(cin, informasi.kontakPenerima);

    // Generate nomor resi random
    informasi.nomorResi = generateNomorResi();

   
    // Input tgl kirim
    cout << "Masukkan tanggal pengiriman (dd/mm/yyyy): ";
    cin >> informasi.tglKirim;

    // Input berat barang
    cout << "Masukkan berat barang (dalam gram): ";
    cin >> informasi.beratBarang;

    // Input harga
    cout << "Masukkan harga (dalam rupiah): ";
    cin >> informasi.harga;

    // Menampilkan resi barang
    cout << "\n=== Resi Barang ===" << endl;

    cout << "| " << left << setw(20) << "Pengirim" << "| " << left << setw(20) << informasi.namaPengirim << " |" << endl;

    cout << "| " << left << setw(20) << "Alamat Pengirim" << "| " << left << setw(20) << informasi.alamatPengirim << " |" << endl;

    cout << "| " << left << setw(20) << "No. HP Pengirim" << "| " << left << setw(20) << informasi.kontakPengirim << " |" << endl;

    cout << "| " << left << setw(20) << "Penerima" << "| " << left << setw(20) << informasi.namaPenerima << " |" << endl;

    cout << "| " << left << setw(20) << "Alamat Penerima" << "| " << left << setw(20) << informasi.alamatPenerima << " |" << endl;

    cout << "| " << left << setw(20) << "No. HP Penerima" << "| " << left << setw(20) << informasi.kontakPenerima << " |" << endl;

    cout << "| " << left << setw(20) << "No. Resi" << "| " << left << setw(20) << informasi.nomorResi << " |" << endl;

    cout << "| " << left << setw(20) << "Harga" << "| " << left << setw(20) << informasi.harga << " |" << endl;
    cout << "| " << left << setw(20) << "Tanggal" << "| " << left << setw(20) << informasi.tglKirim << " |" << endl;
    
    
     // Simpan nomor resi ke dalam file
    simpanNomorResiKeFile(informasi.nomorResi);


    return 0;
}
