#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <sstream>
using namespace std;

const int MAX_KURSI = 5;

struct Pemesanan {
    int idPesan;
    string namaPenumpang;
    string noKTP;
    string rute;
    string tanggal;
    string kelas;
    int nomorKursi;
    double hargaTiket;
    Pemesanan* next;
};

struct NodeStack {
    Pemesanan data;
    NodeStack* next;
};

struct NodeQueue {
    string namaPenumpang;
    string noKTP;
    string rute;
    string tanggal;
    string kelas;
    NodeQueue* next;
};

// linked list

struct LinkedListPemesanan {
    Pemesanan* head;
    int jumlahData;
    int idCounter;
};

void initList(LinkedListPemesanan &list) {
    list.head = nullptr;
    list.jumlahData = 0;
    list.idCounter = 1;
}

void tambahPemesanan(LinkedListPemesanan &list,
                     string nama, string ktp, string rute,
                     string tanggal, string kelas,
                     int kursi, double harga) {

    Pemesanan* baru = new Pemesanan();

    baru->idPesan       = list.idCounter++;
    baru->namaPenumpang = nama;
    baru->noKTP         = ktp;
    baru->rute          = rute;
    baru->tanggal       = tanggal;
    baru->kelas         = kelas;
    baru->nomorKursi    = kursi;
    baru->hargaTiket    = harga;
    baru->next          = nullptr;

    if (list.head == nullptr) {
        list.head = baru;
    }

    else {

        Pemesanan* temp = list.head;

        while (temp->next != nullptr) {
            temp = temp->next;
        }

        temp->next = baru;
    }

    list.jumlahData++;
}

Pemesanan* hapusPemesanan(LinkedListPemesanan &list, int id) {

    if (list.head == nullptr)
        return nullptr;

    Pemesanan* prev = nullptr;
    Pemesanan* curr = list.head;

    while (curr != nullptr && curr->idPesan != id) {
        prev = curr;
        curr = curr->next;
    }

    if (curr == nullptr)
        return nullptr;

    if (prev == nullptr)
        list.head = curr->next;

    else
        prev->next = curr->next;

    curr->next = nullptr;

    list.jumlahData--;

    return curr;
}

Pemesanan* cariByID(LinkedListPemesanan &list, int id) {

    if (list.jumlahData == 0)
        return nullptr;

    Pemesanan** arr = new Pemesanan*[list.jumlahData];

    Pemesanan* temp = list.head;

    for (int i = 0; i < list.jumlahData; i++) {
        arr[i] = temp;
        temp = temp->next;
    }

    int lo = 0;
    int hi = list.jumlahData - 1;

    while (lo <= hi) {

        int mid = (lo + hi) / 2;

        if (arr[mid]->idPesan == id) {

            Pemesanan* hasil = arr[mid];

            delete[] arr;

            return hasil;
        }

        else if (arr[mid]->idPesan < id) {
            lo = mid + 1;
        }

        else {
            hi = mid - 1;
        }
    }

    delete[] arr;

    return nullptr;
}

// searching by nama
Pemesanan* cariByNama(LinkedListPemesanan &list, string nama) {

    Pemesanan* temp = list.head;

    while (temp != nullptr) {

        if (temp->namaPenumpang == nama) {
            return temp;
        }

        temp = temp->next;
    }

    return nullptr;
}

void bubbleSortByNama(LinkedListPemesanan &list) {

    if (!list.head || !list.head->next)
        return;

    bool swapped;

    do {

        swapped = false;

        Pemesanan* curr = list.head;

        while (curr->next != nullptr) {

            if (curr->namaPenumpang > curr->next->namaPenumpang) {

                swap(curr->idPesan,       curr->next->idPesan);
                swap(curr->namaPenumpang, curr->next->namaPenumpang);
                swap(curr->noKTP,         curr->next->noKTP);
                swap(curr->rute,          curr->next->rute);
                swap(curr->tanggal,       curr->next->tanggal);
                swap(curr->kelas,         curr->next->kelas);
                swap(curr->nomorKursi,    curr->next->nomorKursi);
                swap(curr->hargaTiket,    curr->next->hargaTiket);

                swapped = true;
            }

            curr = curr->next;
        }

    } while (swapped);

    cout << "  [Bubble Sort] Data berhasil diurutkan A-Z berdasarkan nama.\n";
}

void tampilkanSemua(LinkedListPemesanan &list) {

    if (list.head == nullptr) {
        cout << "  Belum ada data pemesanan.\n";
        return;
    }

    cout << "\n" << string(78, '=') << "\n";

    cout << left
         << setw(5)  << "ID"
         << setw(18) << "Nama"
         << setw(22) << "Rute"
         << setw(14) << "Tanggal"
         << setw(12) << "Kelas"
         << setw(6)  << "Krs"
         << "Harga (Rp)" << "\n";

    cout << string(78, '-') << "\n";

    Pemesanan* temp = list.head;

    while (temp != nullptr) {

        cout << left
             << setw(5)  << temp->idPesan
             << setw(18) << temp->namaPenumpang
             << setw(22) << temp->rute
             << setw(14) << temp->tanggal
             << setw(12) << temp->kelas
             << setw(6)  << temp->nomorKursi
             << fixed << setprecision(0)
             << temp->hargaTiket << "\n";

        temp = temp->next;
    }

    cout << string(78, '=') << "\n";

    cout << "  Total pemesanan: "
         << list.jumlahData << "\n";
}

// stack

struct Stack {
    NodeStack* top;
    int ukuran;
};

void initStack(Stack &s) {
    s.top = nullptr;
    s.ukuran = 0;
}

bool isEmptyStack(Stack &s) {
    return s.top == nullptr;
}

void push(Stack &s, Pemesanan data) {

    NodeStack* baru = new NodeStack();

    baru->data = data;
    baru->next = s.top;

    s.top = baru;

    s.ukuran++;

    cout << "Pembatalan disimpan ke riwayat.\n";
}

Pemesanan pop(Stack &s) {

    if (isEmptyStack(s)) {

        cout << "  Stack kosong!\n";

        return Pemesanan{};
    }

    NodeStack* hapus = s.top;

    Pemesanan data = hapus->data;

    s.top = s.top->next;

    delete hapus;

    s.ukuran--;

    return data;
}

void tampilkanStack(Stack &s) {

    if (isEmptyStack(s)) {

        cout << "  Riwayat pembatalan kosong.\n";

        return;
    }

    cout << "\n";
    cout << "=== RIWAYAT PEMBATALAN ===\n";

    NodeStack* temp = s.top;

    int no = 1;

    while (temp != nullptr) {

        cout << no++ << ". "
             << temp->data.namaPenumpang
             << " | "
             << temp->data.rute
             << " | "
             << temp->data.tanggal
             << "\n";

        temp = temp->next;
    }
}

// queue

struct Queue {
    NodeQueue* front;
    NodeQueue* rear;
    int ukuran;
};

void initQueue(Queue &q) {
    q.front = nullptr;
    q.rear = nullptr;
    q.ukuran = 0;
}

bool isEmptyQueue(Queue &q) {
    return q.front == nullptr;
}

void enqueue(Queue &q,
             string nama,
             string ktp,
             string rute,
             string tanggal,
             string kelas) {

    NodeQueue* baru = new NodeQueue();

    baru->namaPenumpang = nama;
    baru->noKTP         = ktp;
    baru->rute          = rute;
    baru->tanggal       = tanggal;
    baru->kelas         = kelas;
    baru->next          = nullptr;

    if (q.rear == nullptr) {
        q.front = q.rear = baru;
    }

    else {
        q.rear->next = baru;
        q.rear = baru;
    }

    q.ukuran++;

    cout << "  [QUEUE] Masuk waitlist.\n";
}

NodeQueue* dequeue(Queue &q) {

    if (isEmptyQueue(q))
        return nullptr;

    NodeQueue* keluar = q.front;

    q.front = q.front->next;

    if (q.front == nullptr)
        q.rear = nullptr;

    q.ukuran--;

    return keluar;
}

void tampilkanQueue(Queue &q) {

    if (isEmptyQueue(q)) {

        cout << "  Waitlist kosong.\n";

        return;
    }

    cout << "\n";
    cout << "=== DAFTAR WAITLIST ===\n";

    NodeQueue* temp = q.front;

    int no = 1;

    while (temp != nullptr) {

        cout << no++ << ". "
             << temp->namaPenumpang
             << " | "
             << temp->rute
             << " | "
             << temp->tanggal
             << "\n";

        temp = temp->next;
    }
}

// file handling

void simpanKeFile(LinkedListPemesanan &list) {

    ofstream file("pemesanankereta.txt");

    if (!file) {

        cout << "  Gagal membuka file!\n";

        return;
    }

    Pemesanan* temp = list.head;

    while (temp != nullptr) {

        file << temp->idPesan << "|"
             << temp->namaPenumpang << "|"
             << temp->noKTP << "|"
             << temp->rute << "|"
             << temp->tanggal << "|"
             << temp->kelas << "|"
             << temp->nomorKursi << "|"
             << temp->hargaTiket << "\n";

        temp = temp->next;
    }

    file.close();

    cout << "  Data berhasil disimpan ke file.\n";
}

// baca file
void bacaDariFile(LinkedListPemesanan &list) {

    ifstream file("pemesanankereta.txt");

    if (!file)
        return;

    string baris;

    while (getline(file, baris)) {

        stringstream ss(baris);

        string id,
               nama,
               ktp,
               rute,
               tanggal,
               kelas,
               kursi,
               harga;

        getline(ss, id, '|');
        getline(ss, nama, '|');
        getline(ss, ktp, '|');
        getline(ss, rute, '|');
        getline(ss, tanggal, '|');
        getline(ss, kelas, '|');
        getline(ss, kursi, '|');
        getline(ss, harga);

        tambahPemesanan(
            list,
            nama,
            ktp,
            rute,
            tanggal,
            kelas,
            stoi(kursi),
            stod(harga)
        );

        list.head->idPesan = stoi(id);
    }

    file.close();
}

// helper

double getHarga(string k) {

    if (k == "1" || k == "Eksekutif")
        return 350000;

    if (k == "2" || k == "Bisnis")
        return 200000;

    return 100000;
}

string namaKelas(string p) {

    if (p == "1")
        return "Eksekutif";

    if (p == "2")
        return "Bisnis";

    return "Ekonomi";
}

void header() {

    cout << "\n";
    cout << "  +-------------------------------------------------+\n";
    cout << "  |      SISTEM PEMESANAN KERETA API NUSANTARA      |\n";
    cout << "  +-------------------------------------------------+\n";
}

void menuUtama() {

    cout << "\n";
    cout << "  +----------------------------------------------+\n";
    cout << "  |                  MENU UTAMA                  |\n";
    cout << "  +----------------------------------------------+\n";
    cout << "  |  1. Pesan Tiket                              |\n";
    cout << "  |  2. Lihat Semua Pemesanan                    |\n";
    cout << "  |  3. Cari Pemesanan (Searching)               |\n";
    cout << "  |  4. Urutkan Data (Bubble Sort)               |\n";
    cout << "  |  5. Batalkan Tiket (Stack - Push)            |\n";
    cout << "  |  6. Riwayat Pembatalan (Stack)               |\n";
    cout << "  |  7. Waitlist (Queue)                         |\n";
    cout << "  |  8. Simpan ke File                           |\n";
    cout << "  |  0. Keluar                                   |\n";
    cout << "  +----------------------------------------------+\n";
    cout << "  Pilih: ";
}

// main

int main() {
    
    LinkedListPemesanan daftarPesan;
	initList(daftarPesan);
	bacaDariFile(daftarPesan);

    Stack riwayatBatal;
    initStack(riwayatBatal);

    Queue waitlist;
    initQueue(waitlist);

    header();

    int pilihan;

    do {

        menuUtama();

        cin >> pilihan;
        cin.ignore();

        switch (pilihan) {

        case 1: {

            cout << "\n=== PESAN TIKET ===\n";

            cout << "Rute tersedia:\n";
            cout << "1. Jakarta    -> Surabaya\n";
            cout << "2. Bandung    -> Yogyakarta\n";
            cout << "3. Jakarta    -> Malang\n";
            cout << "4. Surabaya   -> Bali\n";
            cout << "5. Yogyakarta -> Semarang\n";

            cout << "Pilih Rute (1-5): ";

            int pRute;
            cin >> pRute;
            cin.ignore();

            string ruteArr[] = {
                "Jakarta-Surabaya",
                "Bandung-Yogyakarta",
                "Jakarta-Malang",
                "Surabaya-Bali",
                "Yogyakarta-Semarang"
            };

            string rute;

            if (pRute >= 1 && pRute <= 5) {
                rute = ruteArr[pRute - 1];
            }

            else {
                rute = "Tidak Diketahui";
            }

            string nama, ktp, tgl, kelas;
            int kursi;

            cout << "Nama Penumpang            : ";
            getline(cin, nama);

            cout << "No KTP                    : ";
            getline(cin, ktp);

            cout << "Tanggal (YYYY-MM-DD)      : ";
            getline(cin, tgl);

            cout << "Kelas (1=Eks/2=Bis/3=Eko) : ";
            getline(cin, kelas);

            cout << "Nomor Kursi (1-5)         : ";
            cin >> kursi;
            cin.ignore();

            if (kursi < 1 || kursi > MAX_KURSI) {

                cout << "Kursi tidak valid!\n";

                break;
            }

            bool terpakai = false;

            Pemesanan* cek = daftarPesan.head;

            while (cek != nullptr) {

                if (cek->rute == rute &&
                    cek->tanggal == tgl &&
                    cek->nomorKursi == kursi) {

                    terpakai = true;

                    break;
                }

                cek = cek->next;
            }

            if (terpakai) {

                cout << "Kursi sudah penuh.\n";

                enqueue(waitlist,
                        nama,
                        ktp,
                        rute,
                        tgl,
                        namaKelas(kelas));
            }

            else {

                tambahPemesanan(
                    daftarPesan,
                    nama,
                    ktp,
                    rute,
                    tgl,
                    namaKelas(kelas),
                    kursi,
                    getHarga(kelas)
                );

                cout << "Pemesanan berhasil!\n";
            }

            break;
        }

        case 2:

            tampilkanSemua(daftarPesan);

            break;

        case 3: {

    cout << "\n=== MENU SEARCHING ===\n";
    cout << "1. Cari berdasarkan ID\n";
    cout << "2. Cari berdasarkan Nama\n";
    cout << "Pilih: ";

    int pilihCari;

    cin >> pilihCari;
    cin.ignore();

    if (pilihCari == 1) {

        int id;

        cout << "Masukkan ID Pemesanan: ";
        cin >> id;
        cin.ignore();

        Pemesanan* hasil =
            cariByID(daftarPesan, id);

        if (hasil != nullptr) {

            cout << "\n=== DATA DITEMUKAN ===\n";

            cout << "ID      : "
                 << hasil->idPesan << "\n";

            cout << "Nama    : "
                 << hasil->namaPenumpang << "\n";

            cout << "Rute    : "
                 << hasil->rute << "\n";

            cout << "Tanggal : "
                 << hasil->tanggal << "\n";

            cout << "Kelas   : "
                 << hasil->kelas << "\n";

            cout << "Kursi   : "
                 << hasil->nomorKursi << "\n";
        }

        else {

            cout << "Data tidak ditemukan.\n";
        }

    }

    else if (pilihCari == 2) {

        string nama;

        cout << "Masukkan Nama Penumpang: ";

        getline(cin, nama);

        Pemesanan* hasil =
            cariByNama(daftarPesan, nama);

        if (hasil != nullptr) {

            cout << "\n=== DATA DITEMUKAN ===\n";

            cout << "ID      : "
                 << hasil->idPesan << "\n";

            cout << "Nama    : "
                 << hasil->namaPenumpang << "\n";

            cout << "Rute    : "
                 << hasil->rute << "\n";

            cout << "Tanggal : "
                 << hasil->tanggal << "\n";

            cout << "Kelas   : "
                 << hasil->kelas << "\n";

            cout << "Kursi   : "
                 << hasil->nomorKursi << "\n";
        }

        else {

            cout << "Nama tidak ditemukan.\n";
        }

    }

    else {

        cout << "Pilihan tidak valid.\n";
    }

    break;
}

        case 4:

            bubbleSortByNama(daftarPesan);

            tampilkanSemua(daftarPesan);

            break;

        case 5: {

            tampilkanSemua(daftarPesan);

            int id;

            cout << "Masukkan ID yang dibatalkan: ";
            cin >> id;
            cin.ignore();

            Pemesanan* hapus =
                hapusPemesanan(daftarPesan, id);

            if (hapus != nullptr) {

                push(riwayatBatal, *hapus);

                cout << "Pemesanan berhasil dibatalkan.\n";

                delete hapus;
            }

            else {

                cout << "ID tidak ditemukan.\n";
            }

            break;
        }

        case 6:

            tampilkanStack(riwayatBatal);

            break;

        case 7:

            tampilkanQueue(waitlist);

            break;

        case 8:

            simpanKeFile(daftarPesan);

            break;

        case 0:

            cout << "\nTerima kasih.\n";

            break;

        default:

            cout << "Pilihan tidak valid.\n";
        }

    } while (pilihan != 0);

    return 0;
}
