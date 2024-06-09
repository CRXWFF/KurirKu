#include <iostream>
#include <unordered_map>
#include <vector>
#include <queue>
#include <stack>
#include <string>
#include <climits>

using namespace std;

// Fitur Nomer 1: Struktur untuk menyimpan informasi graf
struct Graph {
    unordered_map<string, unordered_map<string, int>> adjList;
};

// Fungsi untuk menambahkan edge ke dalam graf
void addEdge(Graph &graph, const string &u, const string &v, int weight) {
    graph.adjList[u][v] = weight;
    graph.adjList[v][u] = weight;
}

// Algoritma Dijkstra untuk mencari jarak terpendek
unordered_map<string, int> dijkstra(const Graph &graph, const string &start, unordered_map<string, string> &previous) {
    unordered_map<string, int> distances;
    for (const auto &pair : graph.adjList) {
        distances[pair.first] = INT_MAX;
    }
    distances[start] = 0;

    priority_queue<pair<int, string>, vector<pair<int, string>>, greater<pair<int, string>>> pq;
    pq.push({0, start});

    while (!pq.empty()) {
        int currentDistance = pq.top().first;
        string currentNode = pq.top().second;
        pq.pop();

        for (const auto &neighbor : graph.adjList.at(currentNode)) {
            string neighborNode = neighbor.first;
            int weight = neighbor.second;
            int distance = currentDistance + weight;

            if (distance < distances[neighborNode]) {
                distances[neighborNode] = distance;
                pq.push({distance, neighborNode});
                previous[neighborNode] = currentNode;
            }
        }
    }

    return distances;
}

// Fungsi untuk mencetak jalur dari start ke end
void printPath(const unordered_map<string, string> &previous, const string &start, const string &end) {
    stack<string> path;
    string current = end;

    while (current != start) {
        path.push(current);
        current = previous.at(current);
    }
    path.push(start);

    while (!path.empty()) {
        cout << path.top();
        path.pop();
        if (!path.empty()) {
            cout << " -> ";
        }
    }
    cout << endl;
}

// Fitur nomer 2: Struktur untuk mengelompokkan barang berdasarkan lokasi dan tujuan
struct TreeNode {
    string lokasi;
    string tujuan;
    queue<string> berkas;
    TreeNode *kiri;
    TreeNode *kanan;

    TreeNode(string loc, string dest) : lokasi(loc), tujuan(dest), kiri(nullptr), kanan(nullptr) {}
};

// Fungsi untuk memasukkan berkas baru ke dalam BST
TreeNode* masukkanBerkas(TreeNode *root, const string &lokasi, const string &tujuan, const string &berkas) {
    if (root == nullptr) {
        root = new TreeNode(lokasi, tujuan);
        root->berkas.push(berkas);
    } else if (lokasi < root->lokasi || (lokasi == root->lokasi && tujuan < root->tujuan)) {
        root->kiri = masukkanBerkas(root->kiri, lokasi, tujuan, berkas);
    } else if (lokasi > root->lokasi || (lokasi == root->lokasi && tujuan > root->tujuan)) {
        root->kanan = masukkanBerkas(root->kanan, lokasi, tujuan, berkas);
    } else {
        root->berkas.push(berkas);
    }
    return root;
}

// Fungsi untuk melakukan traversal in-order pada BST dan mencetak berkas yang dikelompokkan berdasarkan lokasi
void inorderTraversal(TreeNode *root) {
    if (root != nullptr) {
        inorderTraversal(root->kiri);
        cout << "-------------------------------------" << endl;
        cout << "Lokasi: " << root->lokasi << endl;
        cout << "Tujuan: " << root->tujuan << endl;
        cout << "Berkas: ";
        queue<string> tempQueue = root->berkas;
        while (!tempQueue.empty()) {
            cout << tempQueue.front() << " ";
            tempQueue.pop();
        }
        cout << endl;
        inorderTraversal(root->kanan);
    }
}

// Fitur nomer 3: Fungsi untuk menghitung lokasi barang berdasarkan waktu dan kecepatan
void hitungLokasiBarang(double jam, double kilometer, double kecepatanRataRata) {
    double jarakTempuh = jam * kecepatanRataRata;

    if (kilometer <= jarakTempuh) {
        cout << "Barang saat ini sudah mencapai tujuan atau dalam perjalanan.\n";
        cout << "Total kilometer yang ditempuh: " << kilometer << " km\n";
    } else {
        cout << "Barang masih dalam perjalanan.\n";
        cout << "Perkiraan kilometer yang sudah ditempuh: " << jarakTempuh << " km\n";
        cout << "Total kilometer yang harus ditempuh: " << kilometer << " km\n";
    }
}

// Fitur nomer 4: Fungsi untuk estimasi waktu pengiriman berdasarkan jarak terpendek dan kecepatan rata-rata
void estimasiWaktuSampai(const Graph &graph, const string &start, const string &end, double kecepatanRataRata) {
    unordered_map<string, string> previous;
    unordered_map<string, int> distances = dijkstra(graph, start, previous);

    if (distances[end] != INT_MAX) {
        double waktu = distances[end] / kecepatanRataRata;
        cout << "Estimasi waktu sampai dari " << start << " ke " << end << " adalah " << waktu << " jam." << endl;
        cout << "Rute: ";
        printPath(previous, start, end);
    } else {
        cout << "Tidak ada jalur yang menghubungkan " << start << " dan " << end << endl;
    }
}

// Fitur nomer 5: Struktur untuk menyimpan informasi pengirim dan penerima
struct info {
    string namaPengirim;
    string alamatPengirim;
    string kontakPengirim;
    string namaPenerima;
    string alamatPenerima;
    string kontakPenerima;
    string nomorResi;
    string tglKirim;
    double beratBarang;
};

// Fitur nomer 6: Struktur dan fungsi untuk pengelolaan antrian pengiriman
const int ukuran = 20;
struct Barang {
    int top;
    string isi[ukuran];
    int total[ukuran];
    string nama;
    int jumlah;
} q;

void createQueue() {
    q.top = 0;
}

void displayQueue() {
    cout << "\n====== Menampilkan Daftar Antrian ======" << endl;
    cout << "No |   Nama Barang   |   Jumlah Barang   |" << endl;
    for (int i = 0; i < q.top; i++) {
        cout << i + 1 << "  |  " << q.isi[i] << "   |   " << q.total[i] << "   |" << endl;
    }
}

void insertQueue(const string &namaBarang, int jumlahBarang) {
    if (q.top < ukuran) {
        q.isi[q.top] = namaBarang;
        q.total[q.top] = jumlahBarang;
        q.top++;
    } else {
        cout << "Antrian sudah penuh.\n";
    }
}

int main() {
    int pilihan;
    string border = "============================================";
    string welcome = "SELAMAT DATANG DI APLIKASI UPI FILE EXPRESS";

    do {
        cout << border << "\n" << welcome << "\n" << border << endl;
        cout << "1. Pencarian Rute Tercepat\n2. Pengelompokkan Barang Berdasarkan Lokasi\n3. Pelacakan Barang\n4. Estimasi Waktu Sampai\n5. Resi Barang\n6. Pengelolaan Antrian Pengiriman\n7. Exit\n"
             << border << "\nMasukkan Pilihan Anda: ";
        cin >> pilihan;

        if (pilihan == 1) {
            cout << border << endl;
            Graph graph;
            int numEdges;
            cout << "Masukkan jumlah edge: ";
            cin >> numEdges;

            cout << "Masukkan edge dalam format: vertex1 vertex2 bobot" << endl;
            for (int i = 0; i < numEdges; ++i) {
                string u, v;
                int weight;
                cin >> u >> v >> weight;
                addEdge(graph, u, v, weight);
            }

            string start, end;
            cout << "Masukkan vertex awal: ";
            cin >> start;
            cout << "Masukkan vertex tujuan: ";
            cin >> end;

            unordered_map<string, string> previous;
            unordered_map<string, int> distances = dijkstra(graph, start, previous);

            if (distances[end] != INT_MAX) {
                cout << "Jarak terpendek dari " << start << " ke " << end << " adalah " << distances[end] << " Kilometer" << endl;
                cout << "Rute: ";
                printPath(previous, start, end);
            } else {
                cout << "Tidak ada jalur yang menghubungkan " << start << " dan " << end << endl;
            }
        } else if (pilihan == 2) {
            TreeNode *root = nullptr;
            int jumlahBarang;
            cout << border << endl;
            cout << "Masukkan jumlah barang: ";
            cin >> jumlahBarang;

            for (int i = 0; i < jumlahBarang; ++i) {
                string lokasi, tujuan, berkas;
                cout << "Masukkan lokasi barang: ";
                cin >> lokasi;
                cout << "Masukkan tujuan barang: ";
                cin >> tujuan;
                cout << "Masukkan nama berkas: \n";
                cin >> berkas;
                root = masukkanBerkas(root, lokasi, tujuan, berkas);
            }

            cout << "Barang yang dikelompokkan berdasarkan lokasi dan tujuan:" << endl;
            inorderTraversal(root);
        } else if (pilihan == 3) {
            double jam, kilometer, kecepatanRataRata;
            cout << border << endl;
            cout << "Masukkan waktu tempuh dalam jam: ";
            cin >> jam;
            cout << "Masukkan jarak tempuh dalam kilometer: ";
            cin >> kilometer;
            cout << "Masukkan kecepatan rata-rata dalam km/jam: ";
            cin >> kecepatanRataRata;

            hitungLokasiBarang(jam, kilometer, kecepatanRataRata);
        } else if (pilihan == 4) {
            cout << border << endl;
            Graph graph;
            int numEdges;
            cout << "Masukkan jumlah edge: ";
            cin >> numEdges;

            cout << "Masukkan edge dalam format: tempat_awal tempat_tujuan bobot" << endl;
            for (int i = 0; i < numEdges; ++i) {
                string u, v;
                int weight;
                cin >> u >> v >> weight;
                addEdge(graph, u, v, weight);
            }

            string start, end;
            double kecepatanRataRata;
            cout << "Masukkan tempat awal: ";
            cin >> start;
            cout << "Masukkan tempat tujuan: ";
            cin >> end;
            cout << "Masukkan kecepatan rata-rata dalam km/jam: ";
            cin >> kecepatanRataRata;

            estimasiWaktuSampai(graph, start, end, kecepatanRataRata);
        } else if (pilihan == 5) {
            cout << border << endl;
            info barang;
            cout << "Masukkan Nama Pengirim: ";
            cin >> barang.namaPengirim;
            cout << "Masukkan Alamat Pengirim: ";
            cin >> barang.alamatPengirim;
            cout << "Masukkan Kontak Pengirim: ";
            cin >> barang.kontakPengirim;
            cout << "Masukkan Nama Penerima: ";
            cin >> barang.namaPenerima;
            cout << "Masukkan Alamat Penerima: ";
            cin >> barang.alamatPenerima;
            cout << "Masukkan Kontak Penerima: ";
            cin >> barang.kontakPenerima;
            cout << "Masukkan Nomor Resi: ";
            cin >> barang.nomorResi;
            cout << "Masukkan Tanggal Kirim: ";
            cin >> barang.tglKirim;
            cout << "Masukkan Berat Barang: ";
            cin >> barang.beratBarang;
            cout << border << endl;
            cout << "Resi Barang" << endl;
            cout << "Nama Pengirim: " << barang.namaPengirim << endl;
            cout << "Alamat Pengirim: " << barang.alamatPengirim << endl;
            cout << "Kontak Pengirim: " << barang.kontakPengirim << endl;
            cout << "Nama Penerima: " << barang.namaPenerima << endl;
            cout << "Alamat Penerima: " << barang.alamatPenerima << endl;
            cout << "Kontak Penerima: " << barang.kontakPenerima << endl;
            cout << "Nomor Resi: " << barang.nomorResi << endl;
            cout << "Tanggal Kirim: " << barang.tglKirim << endl;
            cout << "Berat Barang: " << barang.beratBarang << " kg" << endl;
        } else if (pilihan == 6) {
            cout << border << endl;
            createQueue();
            int pilihanAntrian;
            do {
                cout << "1. Masukkan Barang ke Antrian\n2. Tampilkan Daftar Antrian\n3. Kembali ke Menu Utama\nPilih: ";
                cin >> pilihanAntrian;

                if (pilihanAntrian == 1) {
                    cout << "Masukkan Nama Barang: ";
                    cin >> q.nama;
                    cout << "Masukkan Jumlah Barang: ";
                    cin >> q.jumlah;
                    insertQueue(q.nama, q.jumlah);
                } else if (pilihanAntrian == 2) {
                    displayQueue();
                }
            } while (pilihanAntrian != 3);
        }
    } while (pilihan != 7);

    return 0;
}
